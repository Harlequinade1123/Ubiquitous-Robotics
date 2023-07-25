cmake_minimum_required (VERSION 3.0.2)
 
project (TimedVelocity2DTwistSerializer
    VERSION 1.0
    LANGUAGES CXX)


#OpenRTM-aistの検出
find_package(OpenRTM 2.0 REQUIRED)
find_package(ROSTransport REQUIRED)
#ROSの検出
find_package(PkgConfig REQUIRED)
pkg_check_modules(roscpp roscpp)

if(NOT roscpp_FOUND)
	message(FATAL_ERROR "can not find roscpp.")
endif()

#Boostの検出
find_package(Boost REQUIRED)

#インクルードディレクトリ、リンクディレクトリ、コンパイル時のフラグの設定
include_directories(${OPENRTM_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${roscpp_LIBRARY_DIRS})

#動的リンクライブラリの生成
add_library(${PROJECT_NAME} SHARED TimedVelocity2DTwistSerializer.cpp)


#生成するライブラリ名をTimedVelocity2DTwistSerializer.dll(もしくは.so)に設定
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

#OpenRTM-aist、ROS、Boostのライブラリとリンク
target_include_directories(${PROJECT_NAME} SYSTEM
		PRIVATE ${roscpp_INCLUDE_DIRS}
		PRIVATE ${Boost_INCLUDE_DIRS}
		PRIVATE ${ROSTRANSPORT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${roscpp_LIBRARIES} ${Boost_LIBRARIES} ${ROSTRANSPORT_LIBRARIES})

if(MSVC)
	set(INSTALL_ROSTRANSPORT_LIB_DIR ${OPENRTM_VERSION}/ext/${RTM_VC_VER}/transport)
elseif(UNIX)
	include(GNUInstallDirs)
	set(INSTALL_ROSTRANSPORT_LIB_DIR ${CMAKE_INSTALL_LIBDIR}/openrtm-${OPENRTM_VERSION_MAJOR}.${OPENRTM_VERSION_MINOR}/transport)
else()
	set(INSTALL_ROSTRANSPORT_LIB_DIR lib/openrtm-${OPENRTM_VERSION_MAJOR}.${OPENRTM_VERSION_MINOR}/transport)
endif(MSVC)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_ROSTRANSPORT_LIB_DIR}
			ARCHIVE DESTINATION ${INSTALL_ROSTRANSPORT_LIB_DIR}
			RUNTIME DESTINATION ${INSTALL_ROSTRANSPORT_LIB_DIR}
			COMPONENT ext)
