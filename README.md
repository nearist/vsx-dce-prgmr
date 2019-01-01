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
	<tr> <th>flag</th> <th>description</th> <th>normal value</th> <th>accepted range</th> </tr>
	<tr> <th>-h</th> <th> help, displays above</th> <th>n/a</th> <th>n/a</th> </tr>
	<tr> <th>-b</th> <th>board #, determines the set of device files the utility will hook to in a multiVSX system (mandatory argument)</th> <th>0</th> <th>0-99</th> </tr>
	<tr> <th>-l</th> <th>lane #, selects between the 3 lanes of the DCEs on the board selected (mandatory argument)</th> <th>0</th> <th>0-2</th> </tr>
	<tr> <th>-c</th> <th>command, see table below for more information (mandatory argument)</th> <th>n/a</th> <th>n/a</th> </tr>
	<tr> <th>-a</th> <th>fully qualified path to Algorithm file to be programmed</th> <th>n/a</th> <th>n/a</th> </tr>
	<tr> <th>-d</th> <th>fully qualified path to Data file to be programmed</th> <th>n/a</th> <th>n/a</th> </tr>
	<tr> <th>-m</th> <th>selects which of the 7 DCE fpgas of the lane and board selected will be programmed with the SED file</th> <th>0x7f</th> <th>0x01-0x7f</th> </tr>
	<tr> <th>-f</th> <th>SPI sck Frequency </th> <th>10</th> <th>2-10</th> </tr>
	<tr> <th>-p</th> <th>SPI Polarity</th> <th>0</th> <th>0-1</th> </tr>
	<tr> <th>-o</th> <th>SPI Phase</th> <th>0</th> <th>0-1</th> </tr>
</table>
DCE FPGA mask (-m)
	This is a binary mask. the values in the above table are hexadecimal values. 0x7F in binary is 0111 1111. The value is in big-endian format. 

Command Options (-c)
<table>
	<tr> <th>Command</th> <th>Description</th> <th>Req Arguments</th></tr>
	<tr> <th>reset_all</th> <th>sends a reset command that puts all selected DCE FPGAs into a null state (-m has no effect)</th> <th>n/a</th></tr>
	<tr> <th>spi_cfg</th> <th>configure setting of the SPI controller in the Artix 7 Agent FPGA</th> <th>-f,-p,-o</th></tr>
	<tr> <th>prog_pulse</th> <th>sends a test pulse down the SPI lines to ensure everything is initialized correctly</th> <th>n/a</th></tr>
	<tr> <th>prog_fpga</th> <th>programs the selected DCE FPGAs with the programming files</th> <th>-a,-d,-m</th></tr>
</table>
flag, desription, normal value, accepted range, default value
## Examples

see scripts in `/bin` for usage examples
