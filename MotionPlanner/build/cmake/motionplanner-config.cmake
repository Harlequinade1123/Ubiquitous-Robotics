# MotionPlanner CMake config file
#
# This file sets the following variables:
# MotionPlanner_FOUND - Always TRUE.
# MotionPlanner_INCLUDE_DIRS - Directories containing the MotionPlanner include files.
# MotionPlanner_IDL_DIRS - Directories containing the MotionPlanner IDL files.
# MotionPlanner_LIBRARIES - Libraries needed to use MotionPlanner.
# MotionPlanner_DEFINITIONS - Compiler flags for MotionPlanner.
# MotionPlanner_VERSION - The version of MotionPlanner found.
# MotionPlanner_VERSION_MAJOR - The major version of MotionPlanner found.
# MotionPlanner_VERSION_MINOR - The minor version of MotionPlanner found.
# MotionPlanner_VERSION_REVISION - The revision version of MotionPlanner found.
# MotionPlanner_VERSION_CANDIDATE - The candidate version of MotionPlanner found.

message(STATUS "Found MotionPlanner-")
set(MotionPlanner_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(MotionPlanner_INCLUDE_DIRS
#    "/usr/local/include/motionplanner-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(MotionPlanner_IDL_DIRS
#    "/usr/local/include/motionplanner-/idl")
set(MotionPlanner_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(MotionPlanner_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(MotionPlanner_LIBRARIES
        "/usr/local//libmotionplanner.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(MotionPlanner_LIBRARIES
        "/usr/local//libmotionplanner.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(MotionPlanner_DEFINITIONS ${<dependency>_DEFINITIONS})

set(MotionPlanner_VERSION )
set(MotionPlanner_VERSION_MAJOR )
set(MotionPlanner_VERSION_MINOR )
set(MotionPlanner_VERSION_REVISION )
set(MotionPlanner_VERSION_CANDIDATE )

