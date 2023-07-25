# DynamixelController CMake config file
#
# This file sets the following variables:
# DynamixelController_FOUND - Always TRUE.
# DynamixelController_INCLUDE_DIRS - Directories containing the DynamixelController include files.
# DynamixelController_IDL_DIRS - Directories containing the DynamixelController IDL files.
# DynamixelController_LIBRARIES - Libraries needed to use DynamixelController.
# DynamixelController_DEFINITIONS - Compiler flags for DynamixelController.
# DynamixelController_VERSION - The version of DynamixelController found.
# DynamixelController_VERSION_MAJOR - The major version of DynamixelController found.
# DynamixelController_VERSION_MINOR - The minor version of DynamixelController found.
# DynamixelController_VERSION_REVISION - The revision version of DynamixelController found.
# DynamixelController_VERSION_CANDIDATE - The candidate version of DynamixelController found.

message(STATUS "Found DynamixelController-")
set(DynamixelController_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(DynamixelController_INCLUDE_DIRS
#    "/usr/local/include/dynamixelcontroller-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(DynamixelController_IDL_DIRS
#    "/usr/local/include/dynamixelcontroller-/idl")
set(DynamixelController_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(DynamixelController_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(DynamixelController_LIBRARIES
        "/usr/local//libdynamixelcontroller.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(DynamixelController_LIBRARIES
        "/usr/local//libdynamixelcontroller.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(DynamixelController_DEFINITIONS ${<dependency>_DEFINITIONS})

set(DynamixelController_VERSION )
set(DynamixelController_VERSION_MAJOR )
set(DynamixelController_VERSION_MINOR )
set(DynamixelController_VERSION_REVISION )
set(DynamixelController_VERSION_CANDIDATE )

