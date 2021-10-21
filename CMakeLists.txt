cmake_minimum_required(VERSION 3.16)
project(opdrachten C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_FLAGS "--pthread")

#add_executable(opdrachten main_1a.c)
#add_executable(opdrachten main_1b.c)
#add_executable(opdrachten main_1c.c)
#add_executable(opdrachten main_1d.c)
#add_executable(opdrachten main_2a.c)
#add_executable(opdrachten main_2b.c)
#add_executable(opdrachten main_2c.c)
add_executable(opdrachten main_3a.c)
#add_executable(opdrachten main_3b.c)

target_link_libraries(${PROJECT_NAME} pthread rt)