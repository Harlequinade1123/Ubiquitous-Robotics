# testVelocity2D CMake config file
#
# This file sets the following variables:
# testVelocity2D_FOUND - Always TRUE.
# testVelocity2D_INCLUDE_DIRS - Directories containing the testVelocity2D include files.
# testVelocity2D_IDL_DIRS - Directories containing the testVelocity2D IDL files.
# testVelocity2D_LIBRARIES - Libraries needed to use testVelocity2D.
# testVelocity2D_DEFINITIONS - Compiler flags for testVelocity2D.
# testVelocity2D_VERSION - The version of testVelocity2D found.
# testVelocity2D_VERSION_MAJOR - The major version of testVelocity2D found.
# testVelocity2D_VERSION_MINOR - The minor version of testVelocity2D found.
# testVelocity2D_VERSION_REVISION - The revision version of testVelocity2D found.
# testVelocity2D_VERSION_CANDIDATE - The candidate version of testVelocity2D found.

message(STATUS "Found testVelocity2D-1.0.0")
set(testVelocity2D_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(testVelocity2D_INCLUDE_DIRS
#    "/usr/local/include/testvelocity2d-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(testVelocity2D_IDL_DIRS
#    "/usr/local/include/testvelocity2d-1/idl")
set(testVelocity2D_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(testVelocity2D_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(testVelocity2D_LIBRARIES
        "/usr/local//libtestvelocity2d.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(testVelocity2D_LIBRARIES
        "/usr/local//libtestvelocity2d.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(testVelocity2D_DEFINITIONS ${<dependency>_DEFINITIONS})

set(testVelocity2D_VERSION 1.0.0)
set(testVelocity2D_VERSION_MAJOR 1)
set(testVelocity2D_VERSION_MINOR 0)
set(testVelocity2D_VERSION_REVISION 0)
set(testVelocity2D_VERSION_CANDIDATE )

