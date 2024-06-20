cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(led-game)

target_include_directories(app PRIVATE "include")

file(GLOB SRC_FILES "src/*.c")
file(GLOB SRC_COMMAND_FILES "src/command/*.c")
file(GLOB SRC_STATE_FILES "src/state/*.c")
file(GLOB SRC_STRATEGY_FILES "src/strategy/*.c")
target_sources(app PRIVATE 
               ${SRC_FILES} ${SRC_COMMAND_FILES} 
               ${SRC_STATE_FILES} ${SRC_STRATEGY_FILES})

