/*
* Copyright (c) 2015-2018 in2H2 inc.
* System developed for in2H2 inc. by Intermotion Technology, Inc.
*
* Full system RTL, C sources and board design files available at https://github.com/nearist
*
* in2H2 inc. Team Members:
* - Chris McCormick - Algorithm Research and Design
* - Matt McCormick - Board Production, System Q/A
*
* Intermotion Technology Inc. Team Members:
* - Mick Fandrich - Project Lead
* - Dr. Ludovico Minati - Board Architecture and Design, FPGA Technology Advisor
* - Vardan Movsisyan - RTL Team Lead
* - Khachatur Gyozalyan - RTL Design
* - Tigran Papazyan - RTL Design
* - Taron Harutyunyan - RTL Design
* - Hayk Ghaltaghchyan - System Software
*
* Tecno77 S.r.l. Team Members:
* - Stefano Aldrigo, Board Layout Design
*
* We dedicate this project to the memory of Bruce McCormick, an AI pioneer
* and advocate, a good friend and father.
*
* These materials are provided free of charge: you can redistribute them and/or modify
* them under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* These materials are distributed in the hope that they will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*
* File description: The entry point of Lattice FPGA SPI configuration tool
*/

/**************************************************************
*
* Lattice Semiconductor Corp. Copyright 2011
*
* Slave SPI Embedded (SSPI Embedded) is embedded software that enables
* the user to Program Lattice Semiconductor's Field Programmable Gated Array
* (FPGA) with Slave SPI port.  Depending on users' system configuration,
* some of the source codes need to be modified to fit the system.
*
*
* sspi Embedded C Source comprised with 4 modules:
* main.c is the module provides input and output support.
* SSPIEm.c is the modeule provides Main processing engine
* intrface.c is the module provides the interface to get the algorithm and programming data
* core.c is the module interpret the algorithm and data files.
* hardware.c is the module access the SSPI port of the device(s).
*
*
***************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "SSPIEm.h"
#include "debug.h"
#include "artix_if.h"

/***************************************************************
*
* Supported SSPIEm versions.
*
***************************************************************/

#define VME_VERSION_NUMBER "4.0"

/***************************************************************
*
* SSPI Embedded Return Codes.
*
***************************************************************/

#define VME_VERIFICATION_FAILURE        -1
#define VME_FILE_READ_FAILURE           -2
#define VME_VERSION_FAILURE             -3
#define VME_INVALID_FILE                -4
#define VME_ARGUMENT_FAILURE            -5
#define VME_CRC_FAILURE                 -6

/***************************************************************
*
* External variables declared in hardware.c module.
*
***************************************************************/
extern unsigned int a_uiRowCount;

/***************************************************************
*
* Error Messages
*
***************************************************************/
const char MSG_ERROR_BOARD_NUM_INVALID[] = "ERROR! : Board number is invalid (Valid values are 0-99).\n";
const char MSG_ERROR_LANE_NUM_INVALID[] = "ERROR! : Lane number is invalid (Valid values are 0,1,2).\n";
const char MSG_ERROR_BOARD_NOT_FOUND[] = "ERROR! : Board not found.\n";
const char MSG_ERROR_SPI_FREQ_INVALID[] = "ERROR! : SPI Frequency is invalid (Valid values are 2 to 10).\n";
const char MSG_ERROR_SPI_POL_INVALID[] = "ERROR! : SPI Polarity is invalid (Valid values are 0 or 1).\n";
const char MSG_ERROR_SPI_PHASE_INVALID[] = "ERROR! : SPI Phase is invalid (Valid values are 0 or 1).\n";
const char MSG_ERROR_MASK_INVALID[] = "ERROR! : FPGA Select is invalid (Valid values are 01 to 7F).\n";
const char MSG_ERROR_ALGO_FILE_INVALID[] = "ERROR! : Algorithm file name is invalid or not provided.\n";
const char MSG_ERROR_DATA_FILE_INVALID[] = "ERROR! : Data file name is invalid or not provided.\n";
const char MSG_ERROR_CMD_INVALID[] = "ERROR! : Invalid Command.\n";

const char MSG_SUCCESS_RESET[] = "SUCCESS! : All FPGAs are reset for Lane %d.\n";
const char MSG_SUCCESS_SPI_CONFIG[] = "SUCCESS! : Configured SPI for Lane %d, Frequency = %d mHz, Polarity = %d, Phase = %d.\n";
const char MSG_SUCCESS_PULSE[] = "SUCCESS! : Pulsed program pin for Lane %d.\n";
const char MSG_SUCCESS_PROG_FPGA[] = "SUCCESS! : FPGAs programmed successfully. Lane %d, FPGA Select = %.2X.\n";

void printError(int code) {
    printf("ERROR! : Code %d - ", code);
    switch (code) {
        case ERROR_INIT_ALGO:
            printf("Initialize algorithm file fail.\n");
            break;
        case ERROR_INIT_DATA:
            printf("Initialize data file fail.\n");
            break;
        case ERROR_INIT_VERSION:
            printf("Version not supported.\n");
            break;
        case ERROR_INIT_CHECKSUM:
            printf("Header checksum fail.\n");
            break;
        case ERROR_INIT_SPI:
            printf("Initialize SPI fail.\n");
            break;
        case ERROR_INIT:
            printf("Initialization fail.\n");
            break;
        case ERROR_PROC_ALGO:
            printf("Incorrect algorithm format.\n");
            break;
        case ERROR_PROC_DATA:
            printf("Invalid data.\n");
            break;
        case ERROR_PROC_HARDWARE:
            printf("Hardware fail.\n");
            break;
        case ERROR_VERIFICATION:
            printf("Verification fail.\n");
            if (a_uiRowCount > 0) {
                printf("Failed on Frame %d\n", a_uiRowCount);
            }
            break;
        case ERROR_IDCODE:
            printf("IDCODE verification fail.\n");
            break;
        case ERROR_USERCODE:
            printf("USERCODE verification fail.\n");
            break;
        case ERROR_SED:
            printf("SED CRC verification fail.\n");
            break;
        case ERROR_TAG:
            printf("TAG Memory verification fail.\n");
            break;
        case ERROR_LOOP_COND:
            printf("LOOP condition fail.\n");
            break;
        default:
            printf("Process fail.\n");
            break;
    }
}

int cmdResetAll(unsigned int lane) {
    set_lane_num(lane);
    artix_if_spi_reset_lane();

    return 0;
}

int cmdSPIConfig(unsigned int lane, unsigned int freq, unsigned int pol, unsigned int phase) {
    artix_if_spi_init(lane, freq, pol, phase);
    return 0;
}

int cmdProgPulse(unsigned int lane) {
    set_lane_num(lane);
    artix_if_spi_prog_pulse();
    return 0;
}

int cmdProgFpga(unsigned int lane, unsigned int mask, char sea[], char sed[]) {
    set_lane_num(lane);
    artix_if_spi_fpga_select(mask);
    SSPIEm_preset(sea, sed);

    int ec = SSPIEm(0xFFFFFFFF);

    if (ec != 2) {
        printError(ec);
        return 1;
    } else {
        return 0;
    }
}

// Display help information
void help() {
    printf("spi_cfg - spi_cfg\n\n");
    printf("Usage example:\n");
    printf("spi_cfg (-b|--board) integer (-l|--lane) integer (-c|--cmd) string [(-h|--help)] [(-a|--sea) string] [(-d|--sed) string] [(-m|--mask) integer] [(-f|--freq) integer] [(-p|--pol) integer] [(-o|--phase) integer]\n\n");
    printf("Options:\n");
    printf("-h or --help: Displays this information.\n");
    printf("-b or --board integer: Board number. Required.\n");
    printf("-l or --lane integer: Lane number. Required.\n");
    printf("-c or --cmd string: Command. Required.\n");
    printf("-a or --sea string: SEA file.\n");
    printf("-d or --sed string: SED file.\n");
    printf("-m or --mask integer: FPGA Select.\n");
    printf("-f or --freq integer: SPI Frequency.\n");
    printf("-p or --pol integer: SPI Polarity.\n");
    printf("-o or --phase integer: SPI Phase.\n");
    exit(1);
}

/***************************************************************
*
* main
*
***************************************************************/

#define COMMANDS_COUNT 4

char gCommandList[COMMANDS_COUNT][100] = {
        "reset_all",
        "spi_config",
        "prog_pulse",
        "prog_fpga"
};

int main(int argc, char *argv[]) {
    // Here your var definition
    int exitCode = 0;

    // Here flags (options without arguments) and arguments with defined type
    unsigned int board = 0xFF;
    unsigned int lane = 0xFF;
    char *cmd = NULL;
    char *sea = NULL;
    char *sed = NULL;
    unsigned int mask = 0;
    unsigned int freq = 1;
    unsigned int pol = 1;
    unsigned int phase = 1;

    // GetOpt option definition
    char *opt_board = 0;
    char *opt_lane = 0;
    char *opt_cmd = 0;
    char *opt_sea = 0;
    char *opt_sed = 0;
    char *opt_mask = 0;
    char *opt_freq = 0;
    char *opt_pol = 0;
    char *opt_phase = 0;

    int next_option;
    const char *const short_options = "hb:l:c:a:d:m:f:p:o:";
    const struct option long_options[] =
            {
                    {"help",  0, NULL, 'h'},
                    {"board", 1, NULL, 'b'},
                    {"lane",  1, NULL, 'l'},
                    {"cmd",   1, NULL, 'c'},
                    {"sea",   1, NULL, 'a'},
                    {"sed",   1, NULL, 'd'},
                    {"mask",  1, NULL, 'm'},
                    {"freq",  1, NULL, 'f'},
                    {"pol",   1, NULL, 'p'},
                    {"phase", 1, NULL, 'o'},
                    {NULL,    0, NULL, 0}
            };

    // Parse options
    while (1) {
        // Obtain a option
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        if (next_option == -1)
            break; // No more options. Break loop.

        switch (next_option) {

            case 'h' : // -h or --help 
                help();
                break;

            case 'b' : // -b or --board
                opt_board = optarg;
                board = (unsigned int) strtoul(opt_board, NULL, 10);
                break;

            case 'l' : // -l or --lane
                opt_lane = optarg;
                lane = (unsigned int) strtoul(opt_lane, NULL, 10);
                break;

            case 'c' : // -c or --cmd
                opt_cmd = optarg;
                cmd = (char *) malloc(sizeof(char) * (strlen(opt_cmd) + 1));
                strcpy(cmd, opt_cmd);
                break;

            case 'a' : // -a or --sea
                opt_sea = optarg;
                sea = (char *) malloc(sizeof(char) * (strlen(opt_sea) + 1));
                strcpy(sea, opt_sea);
                break;

            case 'd' : // -d or --sed
                opt_sed = optarg;
                sed = (char *) malloc(sizeof(char) * (strlen(opt_sed) + 1));
                strcpy(sed, opt_sed);
                break;

            case 'm' : // -m or --mask
                opt_mask = optarg;
                mask = (unsigned int) strtoul(opt_mask, NULL, 16);
                break;

            case 'f' : // -f or --freq
                opt_freq = optarg;
                freq = (unsigned int) strtoul(opt_freq, NULL, 10);
                break;

            case 'p' : // -p or --pol
                opt_pol = optarg;
                pol = (unsigned int) strtoul(opt_pol, NULL, 10);
                break;

            case 'o' : // -o or --phase
                opt_phase = optarg;
                phase = (unsigned int) strtoul(opt_phase, NULL, 10);
                break;

            case '?' : // Invalid option
                help(); // Return help

            case -1 : // No more options
                break;

            default : // Something unexpected? Aborting
                return (1);
        }
    }

    // Check for mandatory arguments
    if (opt_board == 0 || opt_lane == 0 || opt_cmd == 0) {
        printf("Mandatory arguments not specified\n");
        help();
    }

    // Iterate over rest arguments called argv[optind]
    while (optind < argc) {
        // Your code here 

        optind++;
    }

    if (board > 99) {
        printf(MSG_ERROR_BOARD_NUM_INVALID);
        exitCode = 1;
    }

    if (lane > 2) {
        printf(MSG_ERROR_LANE_NUM_INVALID);
        exitCode = 1;
    }

    if (artix_if_init(board) != 0) {
        printf(MSG_ERROR_BOARD_NOT_FOUND);
        exitCode = 1;
    }

    if (!strcmp(cmd, gCommandList[0])) {// Reset All
        if (cmdResetAll(lane) == 0) {
            printf(MSG_SUCCESS_RESET, lane);
        } else {
            exitCode = 1;
        }
    } else if (!strcmp(cmd, gCommandList[2])) {// Pulse programm pin
        if (cmdProgPulse(lane) == 0) {
            printf(MSG_SUCCESS_PULSE, lane);
        } else {
            exitCode = 1;
        }
    } else if (!strcmp(cmd, gCommandList[1])) { // Configure SPI master
        if (freq < 2 || freq > 10) {
            printf(MSG_ERROR_SPI_FREQ_INVALID);
            exitCode = 1;
        }
        if (pol > 1) {
            printf(MSG_ERROR_SPI_POL_INVALID);
            exitCode = 1;
        }
        if (phase > 1) {
            printf(MSG_ERROR_SPI_PHASE_INVALID);
            exitCode = 1;
        }

        if(exitCode == 0) {
            if (cmdSPIConfig(lane, freq, pol, phase) == 0) {
                printf(MSG_SUCCESS_SPI_CONFIG, lane, freq, pol, phase);
            } else {
                exitCode = 1;
            }
        }
    } else if (!strcmp(cmd, gCommandList[3])) { // Program FPGAs
        if (mask < 0x01 || mask > 0x7F) {
            printf(MSG_ERROR_MASK_INVALID);
            exitCode = 1;
        }
        if (sea == NULL || !strcmp(sea, "")) {
            printf(MSG_ERROR_ALGO_FILE_INVALID);
            exitCode = 1;
        } else if (access(sea, F_OK) == -1) {
            printf(MSG_ERROR_ALGO_FILE_INVALID);
            exitCode = 1;
        }
        if (sed == NULL || !strcmp(sed, "")) {
            printf(MSG_ERROR_DATA_FILE_INVALID);
            exitCode = 1;
        } else if (access(sed, F_OK) == -1) {
            printf(MSG_ERROR_DATA_FILE_INVALID);
            exitCode = 1;
        }

        if(exitCode == 0) {
            if (cmdProgFpga(lane, mask, sea, sed) == 0) {
                printf(MSG_SUCCESS_PROG_FPGA, lane, mask);
            } else {
                exitCode = 1;
            }
        }
    } else {
        printf(MSG_ERROR_CMD_INVALID);
        exitCode = 1;
    }

    artix_if_finish();

    return exitCode;
}