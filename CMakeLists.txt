cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0048 NEW)
PROJECT(jemu65c02 VERSION 0.5.1)

string(REPLACE "." ";" JEMU_VERSION_LIST "${CMAKE_PROJECT_VERSION}")
list(GET JEMU_VERSION_LIST 0 JEMU_VERSION_MAJOR)
list(GET JEMU_VERSION_LIST 1 JEMU_VERSION_MINOR)
list(GET JEMU_VERSION_LIST 2 JEMU_VERSION_REL)

INCLUDE(CheckSymbolExists)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

#Are we building an ARM firmware image?
option(arm_firmware "Build ARM firmware image.")

#build unit tests option
option(unit_test "Build unit tests" ON)

if(arm_firmware)
    set(unit_test OFF)
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
    set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif(arm_firmware)

option(MODELCHECK_REQUIRED "Require Model Checking")

#minunit package
find_package(minunit REQUIRED)

#Build config.h
configure_file(config.h.cmake include/jemu65c02/config.h)

#includes
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

#source files
AUX_SOURCE_DIRECTORY(src JEMU_SOURCES)

#test source files
AUX_SOURCE_DIRECTORY(test JEMU_TEST_SOURCES)

ADD_LIBRARY(jemu65c02 STATIC ${JEMU_SOURCES})
TARGET_COMPILE_OPTIONS(
    jemu65c02 PRIVATE -fPIC -O2
    -Wall -Werror -Wextra -Wpedantic -Wno-unused-command-line-argument)

if(NOT arm_firmware)
    ADD_LIBRARY(jemu65c02-${CMAKE_PROJECT_VERSION} SHARED ${JEMU_SOURCES})
    TARGET_COMPILE_OPTIONS(
        jemu65c02-${CMAKE_PROJECT_VERSION} PRIVATE -fPIC -O2
        -Wall -Werror -Wextra -Wpedantic -Wno-unused-command-line-argument)
endif(NOT arm_firmware)

if(unit_test)
    ADD_EXECUTABLE(testjemu65c02 ${JEMU_SOURCES} ${JEMU_TEST_SOURCES})

    TARGET_COMPILE_OPTIONS(
        testjemu65c02 PRIVATE -g -O0 --coverage ${MINUNIT_CFLAGS}
                         -Wall -Werror -Wextra -Wpedantic
                         -Wno-unused-command-line-argument)
    TARGET_LINK_LIBRARIES(
        testjemu65c02 PRIVATE -g -O0 --coverage ${MINUNIT_LDFLAGS})
    set_source_files_properties(
        ${JEMU_TEST_SOURCES} PROPERTIES COMPILE_FLAGS "${STD_CXX_20}")

    ADD_CUSTOM_TARGET(
        test
        COMMAND testjemu65c02
        DEPENDS testjemu65c02)
endif(unit_test)

ADD_CUSTOM_TARGET(
    model_checks
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/models)

if (MODELCHECK_REQUIRED)
    ADD_DEPENDENCIES(testjemu65c02 model_checks)
endif()

#Build a pkg-config file
SET(JEMU_PC "${CMAKE_BINARY_DIR}/jemu65c02.pc")
FILE(WRITE  ${JEMU_PC} "Name: jemu65c02")
FILE(APPEND ${JEMU_PC} "\nDescription: JEMU 65C02 Emulator")
FILE(APPEND ${JEMU_PC} "\nVersion: ${CMAKE_PROJECT_VERSION}")
FILE(APPEND ${JEMU_PC} "\nURL: https://github.com/nanolith/jemu65c02")
FILE(APPEND ${JEMU_PC} "\nprefix=${CMAKE_INSTALL_PREFIX}")
FILE(APPEND ${JEMU_PC} "\nlibdir=\${prefix}/lib")
FILE(APPEND ${JEMU_PC} "\nincludedir=\${prefix}/include")
FILE(APPEND ${JEMU_PC} "\nLibs: -L\${libdir} -ljemu65c02")
FILE(APPEND ${JEMU_PC} "\nCflags: -I\${includedir}")
INSTALL(FILES ${JEMU_PC} DESTINATION lib/pkgconfig)

#Install headers
FILE(GLOB JEMU_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include/jemu65c02/*.h")
INSTALL(FILES ${JEMU_INCLUDES} DESTINATION include/jemu65c02)
INSTALL(
    FILES ${CMAKE_BINARY_DIR}/include/jemu65c02/config.h
    DESTINATION include/jemu65c02)

#Install library
INSTALL(TARGETS jemu65c02
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
if(NOT arm_firmware)
    INSTALL(TARGETS jemu65c02-${CMAKE_PROJECT_VERSION}
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)
endif(NOT arm_firmware)
