cmake_minimum_required(VERSION  2.8)
project(spi_cfg C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include_directories(inc)

set(SOURCES
        src/main.c
        inc/debug.h
        inc/opcode.h
        src/artix_if.c
        inc/artix_if.h
        src/core.c
        inc/core.h
        src/hardware.c
        inc/hardware.h
        src/intrface.c
        inc/intrface.h
        src/SSPIEm.c
        inc/SSPIEm.h
        src/util.c
        inc/util.h
        )

add_executable(spi_cfg ${SOURCES})
