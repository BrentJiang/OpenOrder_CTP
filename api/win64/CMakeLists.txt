# CMake file for OrderRouter
# ref: cmake file for duilib.
cmake_minimum_required(VERSION 3.5)

###################################################################################
project(OpenOrder)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(UNIX)
    #if(__linux__)
    #else()
    add_definitions (-D__linux__)
    #endif()
else()
    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        add_definitions (-DWIN64)
        add_definitions (-D_WIN64)
        #set( BOOST_LIBRARY "/boost/win64/lib" )
    else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        set( BOOST_LIBRARY "/boost/win32/lib" )
    endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    add_definitions (-DWIN32)
	add_definitions (-D_WIN32_WINNT=0x0600)
	if(_CRT_NO_TIME_T)
		add_definitions(-D_CRT_NO_TIME_T)
	endif()
endif()

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message(STATUS," CMake project files for OpenOrder, 2019-11-02")
message("------------ Options -------------")
message("  PROJECT_SOURCE_DIR: 			${PROJECT_SOURCE_DIR}")
message("  CMAKE_CURRENT_SOURCE_DIR: 	${CMAKE_CURRENT_SOURCE_DIR}")
message("  PROJECT_BINARY_DIR:			${PROJECT_BINARY_DIR}")
message("  CMAKE_BUILD_TYPE:			${CMAKE_BUILD_TYPE}")
message("  CMAKE_TOOLCHAIN_FILE:		${CMAKE_TOOLCHAIN_FILE}")

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_definitions (-DNOMINMAX)
add_definitions (-DUNICODE)
add_definitions (-DSPDLOG_FMT_EXTERNAL)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (UNIX)
    add_compile_options(-g -fPIC -shared -std=c++11 -Wno-unused-variable -Wno-unknown-pragmas -Wno-unused-value
            -Wno-sign-compare -Wno-pragmas -Wno-pointer-arith -Wno-write-strings -Wno-main -Wno-unused-result
            -Wl,-Bsymbolic,--unresolved-symbols=ignore-in-object-files)
else()
#if (MSVC_VERSION GREATER_EQUAL "1900")
#    include(CheckCXXCompilerFlag)
#    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
#    if (_cpp_latest_flag_supported)
#        add_compile_options("/std:c++latest")
#    endif()
#endif()
	add_compile_options("/std:c++11")
endif()

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

if (UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
else ()
    if(WIN32MT)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /EHsc /wd4275 /wd4251 /wd4819")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /EHsc")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /EHsc /wd4275 /wd4251 /wd4819")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /EHsc")
    endif()
endif()

# Properties->C/C++->General->Additional Include Directories
include_directories (${PROJECT_SOURCE_DIR})

##### ctpwrapper_demo tool
file(GLOB_RECURSE ctpwrapper_demo_SRC
	"${PROJECT_SOURCE_DIR}/*.h"
	"${PROJECT_SOURCE_DIR}/ctpwrapper_demo.cc"
)

find_library(CTP_TDLIB thosttraderapi_se
    "${PROJECT_SOURCE_DIR}/"
    NO_DEFAULT_PATH
)
find_library(CTP_MDLIB thostmduserapi_se
    "${PROJECT_SOURCE_DIR}/"
    NO_DEFAULT_PATH
)
link_directories(${PROJECT_SOURCE_DIR})
add_executable(ctpwrapper_demo ${ctpwrapper_demo_SRC})
set_property(TARGET ctpwrapper_demo PROPERTY FOLDER "demo")
set_target_properties(ctpwrapper_demo PROPERTIES OUTPUT_NAME "ctpwrapper_demo$<$<CONFIG:Debug>:d>")
#add_dependencies(ctpwrapper_demo )
#set_target_properties(ctpwrapper_demo PROPERTIES COMPILE_DEFINITIONS "LIBOR_STATIC")
target_link_libraries(ctpwrapper_demo ctp_wrapper$<$<CONFIG:Debug>:d> OpenOrder$<$<CONFIG:Debug>:d> ${CTP_TDLIB} ${CTP_MDLIB} fmt$<$<CONFIG:Debug>:d>)
if(UNIX)
	target_link_libraries(ctpwrapper_demo pthread dl)
	#INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/$<CONFIG>/ctpwrapper_demo$<$<CONFIG:Debug>:d> DESTINATION ${PROJECT_SOURCE_DIR})
else()
	set_target_properties(ctpwrapper_demo PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE" VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
	add_custom_command(TARGET ctpwrapper_demo POST_BUILD
	        COMMAND ${CMAKE_COMMAND} -E copy_if_different
	        ${PROJECT_BINARY_DIR}/$<CONFIG>/ctpwrapper_demo$<$<CONFIG:Debug>:d>.exe ${PROJECT_SOURCE_DIR})
endif()

