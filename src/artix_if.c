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
* File description: The file contains SPI command needed to configure Lattice FPGA
*/
#include "artix_if.h"

FILE *wr_file_ptr;
FILE *rd_file_ptr;
unsigned int g_lane_num;

/**************************************************************************
* Function set_lane_num()
* Set global lane number
**************************************************************************/
void set_lane_num(unsigned int lane_num) {
    g_lane_num = lane_num;
}

/**************************************************************************
* Function artix_if_write()
* Write to PCIE device file
**************************************************************************/
void artix_if_write(unsigned int data) {
    //fprintf(wr_file_ptr, "%.8X\n", data);
    fwrite((unsigned char *) &data, sizeof(char), sizeof(data), wr_file_ptr);
}

/**************************************************************************
* Function SSPIEm_init()
* Read from PCIE device file
**************************************************************************/
unsigned int artix_if_read() {
    return 1;
}

/**************************************************************************
* Function artix_if_spi_reset_lane()
* SPI Reset lane
**************************************************************************/
void artix_if_spi_reset_lane() {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (RST_FPGA_REG_ADDR << REG_ADDR_OFFSET);
    data |= 0x7F7F7F;
    artix_if_write(data);

}

/**************************************************************************
* Function artix_if_spi_wr_data()
* SPI write data
**************************************************************************/
void artix_if_spi_wr_data(unsigned char wr_data) {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (SPI_DATA_REG_ADDR << REG_ADDR_OFFSET);
    data |= (((unsigned int) wr_data << 16) | ((unsigned int) wr_data << 8) | ((unsigned int) wr_data << 0));
    artix_if_write(data);
}

/**************************************************************************
* Function artix_if_spi_rd_data()
* SPI read data
**************************************************************************/
unsigned char artix_if_spi_rd_data() {
    return (unsigned char) (artix_if_read() >> (8 * g_lane_num));
}

/**************************************************************************
* Function artix_if_spi_delay()
* Set SPI delay
**************************************************************************/
void artix_if_spi_delay(unsigned int delay_ms) {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (DELAY_REG_ADDR << REG_ADDR_OFFSET);
    data |= ((delay_ms << 16) | (delay_ms << 8) | (delay_ms << 0));
    artix_if_write(data);
}

/**************************************************************************
* Function artix_if_spi_tx_start()
* SPI transaction start
**************************************************************************/
void artix_if_spi_tx_start() {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (SPI_TX_END_REG_ADDR << REG_ADDR_OFFSET);
    data |= 0x000000;
    artix_if_write(data);
}


/**************************************************************************
* Function artix_if_spi_tx_end()
* SPI transaction end
**************************************************************************/
void artix_if_spi_tx_end() {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (SPI_TX_END_REG_ADDR << REG_ADDR_OFFSET);
    data |= 0x010101;
    artix_if_write(data);
}

/**************************************************************************
* Function artix_if_spi_mode()
* Initialize SPI mode
**************************************************************************/
void artix_if_spi_mode(unsigned int frequency, unsigned int polarity, unsigned int phase) {
    unsigned int data = 0;
    unsigned int div_val = 100 / frequency;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (SPI_MODE_REG_ADDR << REG_ADDR_OFFSET);
    data |= ((((div_val << 2) | (polarity << 1) | phase) << 16) | (((div_val << 2) | (polarity << 1) | phase) << 8) |
             (((div_val << 2) | (polarity << 1) | phase) << 0));
    artix_if_write(data);
}

/**************************************************************************
* Function artix_if_spi_fpga_select()
* Select FPGA for programming
**************************************************************************/
void artix_if_spi_fpga_select(unsigned int fpga_select) {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (FPGA_SELECT_REG_ADDR << REG_ADDR_OFFSET);
    data |= ((fpga_select << 16) | (fpga_select << 8) | (fpga_select << 0));
    artix_if_write(data);
}

/**************************************************************************
* Function artix_if_spi_prog_pulse()
* Send SPI program pulse
**************************************************************************/
void artix_if_spi_prog_pulse() {
    unsigned int data = 0;
    data |= ((1 << g_lane_num) << LANE_NUM_OFFSET);
    data |= (1 << WRITE_OFFSET);
    data |= (PROG_PULSE_REG_ADDR << REG_ADDR_OFFSET);
    artix_if_write(data);
}


/**************************************************************************
* Function artix_if_spi_init()
* Select lane and initialize SPI mode
**************************************************************************/
void artix_if_spi_init(unsigned int lane_num,
                       unsigned int frequency,
                       unsigned int polarity,
                       unsigned int phase) {
    set_lane_num(lane_num);
    artix_if_spi_mode(frequency, polarity, phase);

}

/**************************************************************************
* Function artix_if_init()
* Initialize PCIE device files for read/write
**************************************************************************/
int artix_if_init(unsigned int board_num) {
    char *pcie_wr_file_name;
    char *pcie_rd_file_name;

    asprintf(&pcie_wr_file_name, PCIE_WR_FILE_NAME, board_num);
    asprintf(&pcie_rd_file_name, PCIE_RD_FILE_NAME, board_num);

    wr_file_ptr = fopen(pcie_wr_file_name, "wb");
    rd_file_ptr = fopen(pcie_rd_file_name, "rb");

    free(pcie_wr_file_name);
    free(pcie_rd_file_name);

    if (wr_file_ptr == NULL || rd_file_ptr == NULL) {
        return -1;
    } else {
        return 0;
    }
}

/**************************************************************************
* Function artix_if_finish()
* Close PCIE device files for read/write
**************************************************************************/
void artix_if_finish() {
    if (wr_file_ptr) {
        fclose(wr_file_ptr);
    }
    if (rd_file_ptr) {
        fclose(rd_file_ptr);
    }
}
