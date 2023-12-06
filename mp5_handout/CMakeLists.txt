cmake_minimum_required(VERSION 3.13.4)
project(unit-mp5)
set(CMAKE_CXX_STANDARD 20 CACHE STRING "")

find_package(LLVM 15 REQUIRED CONFIG)

add_library(UnitProject SHARED UnitLICM.cpp UnitLoopInfo.cpp UnitSCCP.cpp RegisterPasses.cpp)
target_include_directories(UnitProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_INCLUDE_DIRS})
if(NOT LLVM_ENABLE_RTTI)
  target_compile_options(UnitProject PUBLIC "-fno-rtti")
endif()
