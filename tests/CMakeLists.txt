add_executable(GeneticAlgorithmTests src/core.gtest.cpp)
target_link_libraries(GeneticAlgorithmTests gmock_main GeneticAlgorithm)
add_test(NAME example_test COMMAND GeneticAlgorithmTests)

target_include_directories(GeneticAlgorithmTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        )