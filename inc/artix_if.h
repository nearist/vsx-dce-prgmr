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
#include <stdlib.h>
#include <stdio.h>

#define PCIE_WR_FILE_NAME      "/dev/xillybus_%02d_write_spi"
#define PCIE_RD_FILE_NAME      "/dev/xillybus_%02d_read_spi"


#define LANE_NUM_OFFSET       29
#define READ_OFFSET           28
#define WRITE_OFFSET          27
#define REG_ADDR_OFFSET       24

#define SPI_DATA_REG_ADDR     0x0
#define DELAY_REG_ADDR        0x1
#define RST_FPGA_REG_ADDR     0x2
#define SPI_TX_END_REG_ADDR   0x3
#define SPI_MODE_REG_ADDR     0x4
#define FPGA_SELECT_REG_ADDR  0x5
#define PROG_PULSE_REG_ADDR   0x6


int artix_if_init(unsigned int board_num);

void artix_if_spi_reset_lane();

void artix_if_spi_init(unsigned int lane_num,
                       unsigned int frequency,
                       unsigned int polarity,
                       unsigned int phase);

void artix_if_spi_delay(unsigned int delay_ms);

void artix_if_spi_wr_data(unsigned char wr_data);

void artix_if_spi_delay(unsigned int delay_ms);

void artix_if_spi_tx_start();

void artix_if_spi_tx_end();

void artix_if_spi_prog_pulse();

void artix_if_spi_fpga_select(unsigned int fpga_select);

void artix_if_finish();

void set_lane_num(unsigned int lane_num);



