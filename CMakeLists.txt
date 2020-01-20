#cmake_minimum_required(VERSION 2.8.4)
##name=CAMI qibanca nectis series nRF52840 Boards
#
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_/DIR}/cmake/ArduinoToolchain.cmake)
##set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/hardware/cami/nrf52/cmake/ArduinoToolchain.cmake)
#
#set(PROJECT_HARDWARE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#set(PROJECT_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libraries)
## ToDO: Set the sketch file to build.
## ToDO: 引数としてスケッチ名を取れるようにする。
#set(PROJECT_SKETCHES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../sketches)
#set(PROJECT_CORE_PATH ${PROJECT_HARDWARE_DIR}/cores/nRF5)
#
#set(PROJECT_NAME nectis_nRF52840_hardware)
#set(PROJECT_CORE_VERSION 0.4.3)
#project(${PROJECT_NAME})
#
#
#set(ARDUINO_SDK_PATH ${PROJECT_HARDWARE_DIR})
#set(ARDUINO_CORES_PATH ${PROJECT_CORE_PATH})
#set(ARDUINO_VARIANTS_PATH ${PROJECT_HARDWARE_DIR}/variants/nectis_nrf52840)
#set(ARDUINO_BOOTLOADERS_PATH ${PROJECT_HARDWARE_DIR}/bootloader/nectis_nrf52840)
#set(ARDUINO_LIBRARIES_PATH ${PROJECT_HARDWARE_DIR}/libraries)
#
#register_hardware_platform(${ARDUINO_SDK_PATH})
#
#
### Uncomment below additional settings as needed.
#set(${CMAKE_PROJECT_NAME}_BOARD nectis)
#set(${CMAKE_PROJECT_NAME}_PORT /dev/tty.usbmodem143101)
#
#set(nectis.build.mcu cortex-m4)
#set(nectis.build.f_cpu 64000000)
#set(nectis.build.board NRF52840_NECTIS)
#set(nectis.build.core nRF5)
#set(nectis.build.core.path ${ARDUINO_CORES_PATH})
#set(nectis.build.variant nectis_nRF52840)
#set(nectis.build.usb_manufacturer "CAMI and Co.")
#set(nectis.build.extra_flags "")
#set(nectis.build.usb_product "CAMI qibanca nectis series")
#set(nectis.build.extra_flags "")
#set(nectis.build.ldscript nrf52840_s140_v6.ld)
#set(nectis.build.vid 0x239A)
#set(nectis.build.pid 0x8029)
#
## nectis.menu.softdevice.s140v6=0.4.0 (s140 6.1.1)
#set(nectis.build.sd_flags -DS140)
#set(nectis.build.sd_name s140)
#set(nectis.build.sd_version 6.1.1)
#set(nectis.build.sd_fwid 0x00B6)
#set(nectis.build.ldscript nrf52840_s140_v6.ld)
#set(nectis.build.sd_name s140)
#set(nectis.upload.protocol wiring)
#set(nectis.upload.speed 115200)
#set(nectis.upload.maximum_size 815104)
#set(nectis.upload.maximum_data_size 248832)
#
#set(runtime.ide.version 1.10.8)
#
#
## Core Libraries
#set(RTOS_PATH ${nectis.build.core.path}/freertos)
#set(NORDIC_PATH ${nectis.build.core.path}/nordic)
#set(SEGGER_PATH ${nectis.build.core.path}/sysview)
#set(TINYUSB_PATH ${nectis.build.core.path}/Adafruit_TinyUSB_Core)
#
#include_directories(${nectis.build.core.path}/cmsis/include)
#
#include_directories(${NORDIC_PATH})
#include_directories(${NORDIC_PATH}/nrfx)
#include_directories(${NORDIC_PATH}/nrfx/hal)
#include_directories(${NORDIC_PATH}/nrfx/mdk)
#include_directories(${NORDIC_PATH}/nrfx/soc)
#include_directories(${NORDIC_PATH}/nrfx/drivers/include)
#include_directories(${NORDIC_PATH}/nrfx/drivers/src)
#include_directories(${NORDIC_PATH}/softdevice/drivers/src)
#include_directories(${NORDIC_PATH}/softdevice/${nectis.build.sd_name}_nrf52_${nectis.build.sd_version}_API/include)
#
#include_directories(${RTOS_PATH}/Source/include)
#include_directories(${RTOS_PATH}/config)
#include_directories(${RTOS_PATH}/portable/GCC/nrf52)
#include_directories(${RTOS_PATH}/portable/CMSIS/nrf52)
#
#include_directories(${SEGGER_PATH}/SEGGER)
#include_directories(${SEGGER_PATH}/Config)
#
#include_directories(${TINYUSB_PATH})
#include_directories(${TINYUSB_PATH}/tinyusb)
#include_directories(${TINYUSB_PATH}/tinyusb/src)
#
#include_directories(${ARDUINO_VARIANTS_PATH})
#
#
## Project Libraries
#set(CORE_LIB_PATH ${ARDUINO_LIBRARIES_PATH})
#
#include_directories(${CORE_LIB_PATH}/Adafruit_LittleFS/src)
#include_directories(${CORE_LIB_PATH}/Adafruit_LittleFS/src/littlefs)
#
#include_directories(${CORE_LIB_PATH}/BG96_LibForArduino/src)
#include_directories(${CORE_LIB_PATH}/BG96_LibForArduino/src/internal)
#
#include_directories(${CORE_LIB_PATH}/Nectis52840_LibForArduino/src)
#
#include_directories(${CORE_LIB_PATH}/SPI)
#
#include_directories(${CORE_LIB_PATH}/Wire)
#
#
## Additional Libraries
#set(ADD_LIB_PATH ${PROJECT_LIBRARIES_DIR})
#
#include_directories(${ADD_LIB_PATH}/Adafruit_SPIFlash/src)
#include_directories(${ADD_LIB_PATH}/Adafruit_SPIFlash/qspi)
#include_directories(${ADD_LIB_PATH}/Adafruit_SPIFlash/spi)
#
#include_directories(${ADD_LIB_PATH}/CustomerMngt_LibForArduino/src)
#
#include_directories(${ADD_LIB_PATH}/SdFat-master/src)
#
#
## Compiler Flags
#set(CMAKE_COMPILER_WARNING_FLAGS "-Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-pointer-arith")
#set(CMAKE_COMPILER_FLOAT_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -u _printf_float")
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set(CMAKE_COMPILER_DEBUG_FLAGS "-DCFG_DEBUG=2 -Os")
#    set(CMAKE_VERBOSE_MAKEFILE ON)
#endif ()
#if (CMAKE_BUILD_TYPE STREQUAL "Release")
#    set(CMAKE_COMPILER_DEBUG_FLAGS "-DCFG_DEBUG=0 -Os")
#    set(CMAKE_VERBOSE_MAKEFILE OFF)
#endif ()
#set(build.flags.nrf "-Ofast")
#add_definitions(-DLFS_NAME_MAX=64)
#add_definitions(-DSOFTDEVICE_PRESENT -DARDUINO_NECTIS -DNRF52840_XXAA -DNRF52_SERIES -DNRF52840_XXAA -DARDUINO_FEATHER52 -DARDUINO_NRF52_ADAFRUIT -DARDUINO_NRF52_FEATHER)
#add_definitions(-DUSBCON -DUSE_TINYUSB -DUSB_VID=${nectis.build.vid} -DUSB_PID=${nectis.build.pid} -DUSB_MANUFACTURER="${nectis.build.usb_manufacturer}" -DUSB_PRODUCT="${nectis.build.usb_product}")
#add_definitions(-DF_CPU=${nectis.build.f_cpu} -DARDUINO=${runtime.ide.version} -DARDUINO_${nectis.build.board} -DARDUINO_ARCH_NRF52 -DARDUINO_BSP_VERSION="${PROJECT_CORE_VERSION}")
#
#
## Compiler
#set(CMAKE_COMPILER_DIR $ENV{HOME}/Library/Arduino15/packages/adafruit/tools/gcc-arm-none-eabi/5_2-2015q4/bin)
#
## C Compiler
#set(CMAKE_C_COMPILER ${CMAKE_COMPILER_DIR}/arm-none-eabi-gcc)
#set(CMAKE_C_FLAGS "-mcpu=${nectis.build.mcu} -mthumb -g ${CMAKE_COMPILER_WARNING_FLAGS} ${CMAKE_COMPILER_FLOAT_FLAGS} -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD ${build.flags.nrf} ${CMAKE_COMPILER_DEBUG_FLAGS}")
#set(ARDUINO_C_FLAGS "-g -Os -w -ffunction-sections -fdata-sections -MMD")
##set(ARDUINO_C_FLAGS ${CMAKE_C_FLAGS})
#
## C++ Compiler
#set(CMAKE_CXX_COMPILER ${CMAKE_COMPILER_DIR}/arm-none-eabi-g++)
#set(CMAKE_CXX_FLAGS "-mcpu=${nectis.build.mcu} -mthumb -g ${CMAKE_COMPILER_WARNING_FLAGS} ${CMAKE_COMPILER_FLOAT_FLAGS} -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD ${build.flags.nrf} ${CMAKE_COMPILER_DEBUG_FLAGS}")
#set(ARDUINO_CXX_FLAGS "-g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD")
##set(ARDUINO_CXX_FLAGS ${CMAKE_CXX_FLAGS})
#
## Linker
#set(CMAKE_LINKER_FLAGS "-mcpu=${nectis.build.mcu} -mthumb ${CMAKE_COMPILER_FLOAT_FLAGS} -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align --specs=nano.specs --specs=nosys.specs ${build.flags.nrf}")
#set(ARDUINO_LINKER_FLAGS ${CMAKE_LINKER_FLAGS})
#
#
#
#
##/Users/Tachikoma/Library/Arduino15/packages/adafruit/tools/gcc-arm-none-eabi/5_2-2015q4/bin/arm-none-eabi-g++  -mcpu=cortex-m4 -mthumb -c -g -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-pointer-arith -mfloat-abi=hard -mfpu=fpv4-sp-d16 -u _printf_float -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -Ofast -DCFG_DEBUG=2 -Os -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD  -w -Os -Wl,--gc-sections -w -Os -Wl,--gc-sections   CMakeFiles/nectis_nRF52840.dir/nectis_nRF52840_WeightMeter.ino.cpp.obj  -o nectis_nRF52840.elf libnectis_CORE.a -lc -lm -Os -Wl,--gc-sections -save-temps
##arm-none-eabi-g++: warning: CMakeFiles/nectis_nRF52840.dir/nectis_nRF52840_WeightMeter.ino.cpp.obj: linker input file unused because linking not done
##arm-none-eabi-g++: warning: libnectis_CORE.a: linker input file unused because linking not done
##Generating EEP image
##/Users/Tachikoma/Library/Arduino15/packages/adafruit/tools/gcc-arm-none-eabi/5_2-2015q4/bin/arm-none-eabi-objcopy "-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0" /Users/Tachikoma/My_Project/ArduinoCore-nRF52840/hardware/cami/nrf52/cmake-build-debug/nectis_nRF52840.elf /Users/Tachikoma/My_Project/ArduinoCore-nRF52840/hardware/cami/nrf52/cmake-build-debug/nectis_nRF52840.eep
##/Users/Tachikoma/Library/Arduino15/packages/adafruit/tools/gcc-arm-none-eabi/5_2-2015q4/bin/arm-none-eabi-objcopy: '/Users/Tachikoma/My_Project/ArduinoCore-nRF52840/hardware/cami/nrf52/cmake-build-debug/nectis_nRF52840.elf': No such file
##make[3]: *** [nectis_nRF52840.elf] Error 1
##make[2]: *** [CMakeFiles/nectis_nRF52840.dir/all] Error 2
##make[1]: *** [CMakeFiles/upload.dir/rule] Error 2
##make: *** [upload] Error 2
#
#
##compiler.cpp.elf.cmd=arm-none-eabi-g++
##compiler.cpp.elf.flags=-Os -Wl,--gc-sections -save-temps
##compiler.cpp.elf.extra_flags=
##recipe.c.combine.pattern="{compiler.path}{compiler.cpp.elf.cmd}" "-L{build.path}" {compiler.cpp.elf.flags} {compiler.cpp.elf.extra_flags} "-L{build.core.path}/linker" "-T{build.ldscript}" "-Wl,-Map,{build.path}/{build.project_name}.map" {compiler.ldflags} -lstdc++ -o "{build.path}/{build.project_name}.elf" {object_files} -Wl,--start-group -lm "{build.path}/{archive_file}" -Wl,--end-group
#
#set(CMAKE_ELF ${CMAKE_COMPILER_DIR}/arm-none-eabi-g++)
#set(CMAKE_ELF_FLAGS -Os -Wl,--gc-sections -save-temps)
#
#
#set(CMAKE_OBJCOPY ${CMAKE_COMPILER_DIR}/arm-none-eabi-objcopy)
#set(ARDUINO_OBJCOPY_EEP_FLAGS "-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0")
#
#
##set(ARDUINO_AVRDUDE_PROGRAM ${CMAKE_COMPILER_DIR})
#
##compiler.ar.cmd=arm-none-eabi-ar
##compiler.ar.flags=rcs
##compiler.c.elf.cmd=arm-none-eabi-gcc
##compiler.c.elf.flags=-Ofast -Wl,--gc-sections -save-temps
##compiler.elf2bin.flags=-O binary
##compiler.elf2bin.cmd=arm-none-eabi-objcopy
##compiler.elf2hex.flags=-O ihex
##compiler.elf2hex.cmd=arm-none-eabi-objcopy
#
#
#
#
#set(AVRSIZE_PROGRAM ${${CMAKE_COMPILER_DIR}/arm-none-eabi-size})
#
#
#
## ARDUINO_SDK_PATH            - Arduino SDK Path
## ARDUINO_AVRDUDE_PROGRAM     - Full path to avrdude programmer
## ARDUINO_AVRDUDE_CONFIG_PATH - Full path to avrdude configuration file
##
## ARDUINO_C_FLAGS             - C compiler flags
## ARDUINO_CXX_FLAGS           - C++ compiler flags
## ARDUINO_LINKER_FLAGS        - Linker flags
##
## ARDUINO_DEFAULT_BOARD      - Default Arduino Board ID when not specified.
## ARDUINO_DEFAULT_PORT       - Default Arduino port when not specified.
## ARDUINO_DEFAULT_SERIAL     - Default Arduino Serial command when not specified.
## ARDUINO_DEFAULT_PROGRAMMER - Default Arduino Programmer ID when not specified.
##
##
## ARDUINO_FOUND       - Set to True when the Arduino SDK is detected and configured.
## ARDUINO_SDK_VERSION - Set to the version of the detected Arduino SDK (ex: 1.0)
#
#
##    mark_as_advanced(
##        ARDUINO_CORES_PATH
##        ARDUINO_VARIANTS_PATH
##        ARDUINO_BOOTLOADERS_PATH
##        ARDUINO_LIBRARIES_PATH
##        ARDUINO_BOARDS_PATH
##        ARDUINO_PROGRAMMERS_PATH
##        ARDUINO_VERSION_PATH
##        ARDUINO_AVRDUDE_FLAGS
##        ARDUINO_AVRDUDE_PROGRAM
##        ARDUINO_AVRDUDE_CONFIG_PATH
##        ARDUINO_OBJCOPY_EEP_FLAGS
##        ARDUINO_OBJCOPY_HEX_FLAGS
##        AVRSIZE_PROGRAM)
#
#
#set(${CMAKE_PROJECT_NAME}_SKETCH ${PROJECT_SKETCHES_DIR}/CustomerSketches/CocaCola_SA/WeightMeter/WeightMeter.ino)
#
#generate_arduino_firmware(${CMAKE_PROJECT_NAME})
#



