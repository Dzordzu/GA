cmake_minimum_required(VERSION 3.13)
project(genetic-algorithm VERSION 1.0.0 )

#
# Include cmake scripts
#
include(cmake/GTest.cmake)

add_library(GeneticAlgorithm src/GeneticAlgorithm.cpp src/Linkage.cpp src/Linkage.h src/Genotype.cpp src/Genotype.h)

target_include_directories(GeneticAlgorithm
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
target_compile_features(GeneticAlgorithm PRIVATE cxx_std_17)

add_subdirectory(tests)
