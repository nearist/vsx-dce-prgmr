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
/************************************************************************
* Lattice Semiconductor Corp. Copyright 2011
*
* SSPI Embedded System
*
* Version: 4.0.0
*		Add SSPIEm_preset() function prototype 
*
*
* Main processing engine
*
*************************************************************************/
#include "SSPIEm.h"
#include "intrface.h"
#include "core.h"

/*********************************************************************
*
* SSPIEm_preset()
*
* This function calls algoPreset and dataPreset to set which algorithm
* and data files are going to be processed.  Input(s) to the function
* may depend on configuration.
*
*********************************************************************/

int SSPIEm_preset(const char algoFileName[], const char dataFileName[]) {
    int retVal = algoPreset(algoFileName);
    if (retVal)
        retVal = dataPreset(dataFileName);
    return retVal;
}

/************************************************************************
* Function SSPIEm
* The main function of the processing engine.  During regular time,
* it automatically gets byte from external storage.  However, this 
* function requires an array of buffered algorithm during 
* loop / repeat operations.  Input bufAlgo must be 0 to indicate
* regular operation.
*
* To call the VME, simply call SSPIEm(int debug);
*************************************************************************/
int SSPIEm(unsigned int algoID) {
    int retVal = 0;
    retVal = SSPIEm_init(algoID);
    if (retVal <= 0)
        return 1;// retVal;
    retVal = SSPIEm_process(0, 0);
    return retVal;
}

