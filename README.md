![alt text](http://nearist.sightbox.io/wp-content/uploads/2017/04/nearist.svg)

Nearist greatly accelerates big data searches through a revolutionary new hardware platform specifically engineered to handle the computationally demanding task of performing Nearest Neighbor Search on vector representations of content—enabling your search routines to deliver results several orders of magnitude faster than anything else on the market.

## Structure

This repository contains the tool required to program the 21 Distance Calculation Engines (DCEs) via the host instead of JTAG. for more information about the DCE see the !!!vsx-core-dce repository!!! 
spi_cfg hooks onto the VSX spi programming device files. 

## Build

Run CMake
  `cmake CMakeLists.txt`
Run make
  `make`
spi_cfg executable will be in './bin'

## Arguments

Usage example:
spi_cfg (-b|--board) integer (-l|--lane) integer (-c|--cmd) string [(-h|--help)] [(-a|--sea) string] [(-d|--sed) string] [(-m|--mask) integer] [(-f|--freq) integer] [(-p|--pol) integer] [(-o|--phase) integer]

Options:
-h or --help: Displays this information.
-b or --board integer: Board number. Required.
-l or --lane integer: Lane number. Required.
-c or --cmd string: Command. Required.
-a or --sea string: SEA file.
-d or --sed string: SED file.
-m or --mask integer: FPGA Select.
-f or --freq integer: SPI Frequency.
-p or --pol integer: SPI Polarity.
-o or --phase integer: SPI Phase.

<table>
	<tr> <tc>flag</tc> <tc>description</tc> <tc>normal value</tc> <tc>accepted range</tc> </tr>
	<tr> <tc>-h</tc> <tc> help, displays above</tc> <tc>n/a</tc> <tc>n/a</tc> </tr>
	<tr> <tc>-b</tc> <tc>board #, determines the set of device files the utility will hook to in a multiVSX system (mandatory argument)</tc> <tc>0</tc> <tc>0-99</tc> </tr>
	<tr> <tc>-l</tc> <tc>lane #, selects between the 3 lanes of the DCEs on the board selected (mandatory argument)</tc> <tc>0</tc> <tc>0-2</tc> </tr>
	<tr> <tc>-c</tc> <tc>command, see table below for more information (mandatory argument)</tc> <tc>n/a</tc> <tc>n/a</tc> </tr>
	<tr> <tc>-a</tc> <tc>fully qualified path to Algorithm file to be programmed</tc> <tc>n/a</tc> <tc>n/a</tc> </tr>
	<tr> <tc>-d</tc> <tc>fully qualified path to Data file to be programmed</tc> <tc>n/a</tc> <tc>n/a</tc> </tr>
	<tr> <tc>-m</tc> <tc>selects which of the 7 DCE fpgas of the lane and board selected will be programmed with the SED file</tc> <tc>0x7f</tc> <tc>0x01-0x7f</tc> </tr>
	<tr> <tc>-f</tc> <tc>SPI sck Frequency </tc> <tc>10</tc> <tc>2-10</tc> </tr>
	<tr> <tc>-p</tc> <tc>SPI Polarity</tc> <tc>0</tc> <tc>0-1</tc> </tr>
	<tr> <tc>-o</tc> <tc>SPI Phase</tc> <tc>0</tc> <tc>0-1</tc> </tr>
</table>
DCE FPGA mask (-m)
	This is a binary mask. the values in the above table are hexadecimal values. 0x7F in binary is 0111 1111. The value is in big-endian format. 

Command Options (-c)
<table>
	<tr> <tc>Command</tc> <tc>Description</tc> <tc>Req Arguments</tc></tr>
	<tr> <tc>reset_all</tc> <tc>sends a reset command that puts all selected DCE FPGAs into a null state (-m has no effect)</tc> <tc>n/a</tc></tr>
	<tr> <tc>spi_cfg</tc> <tc>configure setting of the SPI controller in the Artix 7 Agent FPGA</tc> <tc>-f,-p,-o</tc></tr>
	<tr> <tc>prog_pulse</tc> <tc>sends a test pulse down the SPI lines to ensure everything is initialized correctly</tc> <tc>n/a</tc></tr>
	<tr> <tc>prog_fpga</tc> <tc>programs the selected DCE FPGAs with the programming files</tc> <tc>-a,-d,-m</tc></tr>
</table>
flag, desription, normal value, accepted range, default value
## Examples

see scripts in `/bin` for usage examples
