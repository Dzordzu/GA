//
// Created by dzordzu on 03.01.19.
//

#include "gmock/gmock.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include <vector>

TEST(CrossoverTest, StandardCrossover) {
    using Genotype::StandardCrossover;
    using Genotype::Genotype;

    std::vector<int> test = {1, 1, 1, 1, 1};

    Genotype g1(test);
    Genotype g2({0, 0, 0, 0, 0});

    StandardCrossover standardCrossover;
    standardCrossover.addParent(g1);
    standardCrossover.addParent(g2);

    ASSERT_TRUE(standardCrossover.calculate());
    std::vector<Genotype> result = standardCrossover.getResult();

    std::vector<int> expected0 = {0, 0, 1, 1, 1};
    std::vector<int> expected1 = {1, 1, 0, 0, 0};

    for(int i=0; i<2; i++) {
        std::vector<int> given = result[i].getGenesCopy();
        EXPECT_THAT(given, testing::AnyOf(expected0, expected1));
    }

}

TEST(CrossoverTest, LinkageCrossover) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
