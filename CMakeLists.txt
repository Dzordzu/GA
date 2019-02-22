cmake_minimum_required(VERSION 3.13)
project(genetic-algorithm VERSION 1.0.0 )

#
# Include cmake scripts
#
include(cmake/GTest.cmake)

add_library(GeneticAlgorithm SHARED
        include/GeneticAlgorithm/Algorithms.cpp
        src/Core.cpp
        src/Operations.cpp
        )

target_include_directories(GeneticAlgorithm
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
target_compile_features(GeneticAlgorithm PRIVATE cxx_std_17)

add_subdirectory(tests)
