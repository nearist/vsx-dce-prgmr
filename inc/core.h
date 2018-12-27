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
#ifndef _CORE_H_
#define _CORE_H_

#include "util.h"

#define PROC_FAIL        0
#define PROC_COMPLETE    1
#define PROC_OVER        2

/************************************************************************
*
* Function / struct definition
*
*************************************************************************/

/************************************************************************
* Processing functions
*************************************************************************/

int SSPIEm_process(unsigned char *bufAlgo, unsigned int bufAlgoSize);

int SSPIEm_init(unsigned int algoID);

int VME_getByte(unsigned char *byteOut,
                unsigned char *bufferedAlgo, unsigned int bufferedAlgoSize,
                unsigned int *bufferedAlgoIndex);

unsigned int VME_getNumber(unsigned char *bufAlgo, unsigned int bufAlgoSize,
                           unsigned int *bufAlgoIndex, unsigned int *byteCount);

/************************************************************************
* Function / struct definition
*************************************************************************/

int proc_TRANS(unsigned char *bufferedAlgo, unsigned int bufferedAlgoSize,
               unsigned int *absBufferedAlgoIndex, unsigned char channel, unsigned char currentByte);

int proc_REPEAT(unsigned char *bufferedAlgo, unsigned int bufferedAlgoSize,
                unsigned int *absBufferedAlgoIndex, unsigned int LoopMax);

int proc_LOOP(unsigned char *bufferedAlgo, unsigned int bufferedAlgoSize,
              unsigned int *absBufferedAlgoIndex, unsigned int LoopMax);

int proc_HCOMMENT(unsigned char *bufferedAlgo, unsigned int bufferedAlgoSize,
                  unsigned int *absBufferedAlgoIndex, CSU *headerCS);

#endif