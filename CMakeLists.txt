cmake_minimum_required(VERSION 3.16)
project(cmake-template)

message(STATUS "====> [Notice] Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "====> [Notice] System Name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "====> [Notice] System Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "====> [Notice] System: ${CMAKE_SYSTEM}")

set(CMAKE_CXX_STANDARD 17)
OPTION(GTEST "Enable GTest" ON)

message(STATUS "====> [Notice] Option(GTest): ${GTEST}")

# Check Cmake Build type
# And set debug flag
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FLAG_DEBUG "")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FLAG_DEBUG "_d")
else()
    message(FATAL_ERROR "====> [Error] Unsupported CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()


if(WIN32)
    set(ARCHITECTURE "win-x64")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE})

    set(LIB_SUFFIX "lib")
else()
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(ARCHITECTURE "linux-x64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(ARCHITECTURE "linux-arm64")
    else()
        message(FATAL_ERROR "Unsupported CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE}/${CMAKE_BUILD_TYPE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE}/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE}/${CMAKE_BUILD_TYPE})

    set(LIB_PREFIX "lib")
    set(LIB_SUFFIX "so")
endif()
message(STATUS "====> [Notice] CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message(STATUS "====> [Notice] CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "====> [Notice] CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


# Set compile options
if(MSVC)
    set(CMAKE_CXX_FLAGS "/wd4013 /wd4018 /wd4028 /wd4530 /wd4047 /wd4068 /wd4090\
        /wd4101 /wd4113 /wd4133 /wd4190 /wd4244 /wd4267 /wd4305 /wd4477 /wd4996 /wd4819 /fp:fast")
else()
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wno-unused-result -Wno-unknown-pragmas \
        -Wfatal-errors -Wno-deprecated-declarations -Wno-write-strings -pthread -Wl,-Bsymbolic")
endif()




#############################################################################
#                           Start Build MyLib                               #
#############################################################################
set(TARGET_LIB "MyLib")
file(GLOB_RECURSE SOURCES ${CMAKE_HOME_DIRECTORY}/src/*.cpp)
message(STATUS "====> [Notice][${TARGET_LIB}] Build Target..")
message(STATUS "====> [Notice][${TARGET_LIB}] Target Source: ${SOURCES}")

add_library(${TARGET_LIB} SHARED ${SOURCES})

# 사전 컴파일 헤더 추가
target_precompile_headers(${TARGET_LIB} PRIVATE "${CMAKE_HOME_DIRECTORY}/src/pch.h")

#출력 파일 이름 설정
set_target_properties(${TARGET_LIB} PROPERTIES OUTPUT_NAME ${TARGET_LIB})
set_target_properties(${TARGET_LIB} PROPERTIES DEBUG_POSTFIX "_d")
#############################################################################


#############################################################################
#                          Start Build GTest                                #
#############################################################################
if (GTEST)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            # Specify the commit you depend on and update it regularly.
            URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    if(WIN32)
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)

    set(TARGET_TEST "MyTests")
    file(GLOB_RECURSE SOURCES ${CMAKE_HOME_DIRECTORY}/tests/*.cpp)
    message(STATUS "====> [Notice][${TARGET_TEST}] Build Target..")
    message(STATUS "====> [Notice][${TARGET_TEST}] Target Source: ${SOURCES}")

    add_executable(${TARGET_TEST} ${SOURCES})

    # TODO: Set Your library for link to test binary
    set(LIB_MyLib "${CMAKE_HOME_DIRECTORY}/RESULT/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}/${LIB_PREFIX}MyLib${FLAG_DEBUG}.${LIB_SUFFIX}")
    message(STATUS "====> [Notice][${TARGET_TEST}] Try to link MyLib to tests: ${LIB_MyLib}")
    target_include_directories(${TARGET_TEST} PRIVATE "${CMAKE_HOME_DIRECTORY}/src")
    target_link_libraries(${TARGET_TEST} PRIVATE "${LIB_MyLib}")

    # Link GTest
    target_link_libraries(${TARGET_TEST} PRIVATE gtest gtest_main)
endif()
#############################################################################
