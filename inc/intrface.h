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
#ifndef _INTRFACE_H_
#define _INTRFACE_H_

#include "util.h"

/************************************************************************
* function definition
*************************************************************************/

/************************************************************************
* algorithm utility functions		
*************************************************************************/
int algoPreset(const char algoFileName[]);

int algoInit();

int algoGetByte(unsigned char *byteOut);

int algoFinal();

/************************************************************************
* data utility functions
*************************************************************************/
typedef struct toc {
    unsigned char ID;
    unsigned int uncomp_size;
    unsigned char compression;
    unsigned int address;
} DATA_TOC;

typedef struct dataPointer {
    unsigned char ID;
    unsigned int address;
} DATA_BUFFER;

int dataPreset(const char dataFileName[]);

int dataInit();            // initialize data
int
dataGetByte(unsigned char *byteOut, short int incCurrentAddr, CSU *checksumUnit);    // get one byte from current column
int dataReset(unsigned char isResetBuffer);    // reset data pointer
int dataFinal();

int HLDataGetByte(unsigned char dataSet, unsigned char *dataByte, unsigned int uncomp_bitsize);

int dataReadthroughComment();

unsigned char getRequestNewData();

int dataLoadTOC(short int storeTOC);

int dataRequestSet(unsigned char dataSet);

/************************************************************************
* decompression utility functions
*************************************************************************/

void set_compression(unsigned char cmp);

unsigned char get_compression();

short int decomp_initFrame(int bitSize);

short int decomp_getByte(unsigned char *byteOut);

short int decomp_getNum();

#endif