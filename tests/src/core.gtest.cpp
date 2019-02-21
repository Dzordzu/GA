//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
#include "Core.hpp"

TEST(Test1, Test2) {
    GeneticAlgorithm::Genotype g;
    g.push_back(2);
    EXPECT_EQ(g.at(0), 2);
}