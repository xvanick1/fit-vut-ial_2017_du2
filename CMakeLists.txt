cmake_minimum_required(VERSION 3.8)
project(ial_2017_du2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        c016/c016-test.c
        c016/c016-test.output
        c016/c016.c
        c016/c016.h
        c016/Makefile
        c401/c401-test.c
        c401/c401-test.output
        c401/c401.c
        c401/c401.h
        c401/Makefile
        c402/c402-test.c
        c402/c402-test.output
        c402/c402.c
        c402/c402.h
        c402/Makefile)

add_executable(ial_2017_du2 ${SOURCE_FILES})