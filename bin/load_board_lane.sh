#!/bin/bash

CMD_SPI_CFG="/srv/nearist.iflex/trunk/iflex/sw/spi_cfg_tool/bin/spi_cfg"

let "rc=0"

if [ $# -eq 4 ]; then
    $CMD_SPI_CFG -b $1 -l $2 -c reset_all
let "rc+=$?"

    $CMD_SPI_CFG -b $1 -l $2 -c spi_config -f 10 -p 0 -o 0
let "rc+=$?"

    $CMD_SPI_CFG -b $1 -l $2 -c prog_pulse
let "rc+=$?"

    sleep 2

    $CMD_SPI_CFG -b $1 -l $2 -c prog_fpga -a $3 -d $4 -m 7f
let "rc+=$?"

else
    echo "ERROR! : No algorithm and/or data file(s) provided."
let "rc=-1"
fi

exit $rc


