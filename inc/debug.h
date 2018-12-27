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
#ifndef _DEBUG_H
#define _DEBUG_H

/* level 1 error definition */
#define DBGU_L1_ALGO_INIT        1
#define DBGU_L1_MISMATCH        2
#define NO_ALGOID                1
#define COMMENT_END_UNEXPECTED    2
#define NO_VERSION                3
#define NO_BUFFERREQ            4
#define NO_STACKREQ                5
#define NO_MASKBUFREQ            6
#define NO_CHANNEL                7
#define NO_HEADERCS                8
#define NO_STARTOFALGO            9
#define NO_COMPRESSION            10
#define    INIT_SPI_FAIL            11
#define INIT_ALGO_FAIL            12

#define DBGU_L1_ALGO_PROC        3
#define UNABLE_TO_GET_BYTE        1
#define COMMENT_END_UNEXPECTED    2
#define NO_NUMBER_OF_REPEAT        3
#define NO_NUMBER_OF_LOOP        4
#define NO_NUMBER_OF_WAIT        5
#define UNRECOGNIZED_OPCODE        6

#define DBGU_L1_PROCESS            4
#define TRANX_FAIL                1
#define RUNCLOCK_FAIL            2
#define REPEAT_FAIL                3
#define LOOP_FAIL                4
#define RESETDATA_FAIL            5

#define DBGU_L1_ALGO_TRANX        5
#define NO_TRANX_OPCODE            1
#define NO_TRANSOUT_SIZE        2
#define NO_TRANSOUT_TYPE        3
#define NO_TRANSOUT_DATA        4
#define NO_ENDTRAN                5
#define UNRECOGNIZED_OPCODE        6
#define NO_TRANSIN_SIZE            7
#define NO_TRANSIN_TYPE            8
#define NO_TRANSIN_MASK            9
#define NO_TRANSIN_DATA            10

#define DBGU_L1_TRANX_PROC        6
#define STARTTRAN_FAIL            1
#define    TOGGLECS_FAIL            3
#define TRANX_OUT_ALGO_FAIL        4
#define TRANX_OUT_PROG_FAIL        5
#define TRANX_IN_ALGO_FAIL        6
#define TRANX_IN_PROG_FAIL        7
#define TRANX_OPCODE_FAIL        8
#define ENDTRAN_FAIL            9
#define COMPARE_FAIL            10
#define COMMENT_END_UNEXPECTED    2
#define DECOMPRESSION_FAIL        11

#define DBGU_L1_REPEAT            7
#define BUFFER_FAIL                1
#define STACK_MISMATCH            2
#define REPEAT_SIZE_EXCEED        3
#define REPEAT_COND_FAIL        4
#define REPEAT_COMMENT_FAIL        5

#define DBGU_L1_LOOP            8
#define BUFFER_FAIL                1
#define STACK_MISMATCH            2
#define LOOP_SIZE_EXCEED        3
#define LOOP_COND_FAIL            4
#define LOOP_COMMENT_FAIL        5

/* level 2 debugging definition */
#define    DBGU_L2_INIT            10
#define INIT_BEGIN                1
#define INIT_COMPLETE            2

#define DBGU_L2_PROC            11
#define START_PROC                1
#define START_PROC_BUFFER        2
#define END_PROC                3
#define END_PROC_BUFFER            4
#define ENTER_STARTTRAN            5
#define ENTER_RUNCLOCK            6
#define ENTER_REPEAT            7
#define ENTER_LOOP                8
#define ENTER_WAIT                9

#define DBGU_L2_REPEAT            12
#define PREPARE_BUFFER            1
#define FINISH_BUFFER            2
#define START_PROC_REPEAT        3
#define END_PROC_REPEAT            4

#define DBGU_L2_LOOP            13
#define PREPARE_BUFFER            1
#define FINISH_BUFFER            2
#define START_PROC_LOOP            3
#define END_PROC_LOOP            4

/* Error Code */
#define ERROR_INIT_ALGO            -1
#define ERROR_INIT_DATA            -2
#define ERROR_INIT_VERSION        -3
#define ERROR_INIT_CHECKSUM        -4
#define ERROR_INIT_SPI            -5
#define ERROR_INIT                -6
#define ERROR_IDCODE            -7
#define ERROR_USERCODE            -8
#define ERROR_SED                -9
#define ERROR_TAG                -10
#define ERROR_PROC_ALGO            -11
#define ERROR_PROC_DATA            -12
#define ERROR_PROC_HARDWARE        -13
#define ERROR_LOOP_COND            -14
#define ERROR_VERIFICATION        -20

#endif
