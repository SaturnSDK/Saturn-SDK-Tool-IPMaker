cmake_minimum_required(VERSION 3.0)

set(IPMAKER_DESTINATION IPMaker)

project( Saturn-SDK-Tool-IPMaker VERSION 1.0
        DESCRIPTION "Saturn-SDK-Tool-IPMaker"
        LANGUAGES C)

set(SOURCES
        Source/Common/Source/Main.c
        Source/Common/Source/SystemID.c
        Source/Common/Headers/Utils.h)

add_executable( IPMaker ${SOURCES} )

target_include_directories(IPMaker PUBLIC
        Source/Common/Headers/)

target_compile_options(IPMaker PUBLIC -g -Wall)

install(TARGETS IPMaker DESTINATION ${IPMAKER_DESTINATION}/ )
