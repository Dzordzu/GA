//
// Created by dzordzu on 03.01.19.
//

#include "gtest/gtest.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

TEST(Test, Test2) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
