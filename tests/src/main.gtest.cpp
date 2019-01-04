//
// Created by dzordzu on 03.01.19.
//

#include "gmock/gmock.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Genotype.h"
#include "Linkage.h"
#include <vector>
#include <utility>

TEST(LinkageTest, Clusters) {
    Linkage::Cluster empty;
    Linkage::Cluster single({1, 2}, Linkage::Cluster::Type::SINGLE);
    Linkage::Cluster multiple({1, 2, 3});
    Linkage::Cluster forceEmpty({1, 2}, Linkage::Cluster::Type::EMPTY);

    EXPECT_EQ(empty.getMask(), std::vector<size_t>());
    EXPECT_EQ(single.getMask(), std::vector<size_t>(1, 1));
    EXPECT_EQ(multiple.getMask(), std::vector<size_t>({1, 2, 3}));
    EXPECT_EQ(forceEmpty.getMask(), std::vector<size_t>());
}

TEST(LinkageTest, Matrix) {

    // Results for getMinimums
    #define VECTOR_PAIR std::pair<size_t, double>
        std::vector<VECTOR_PAIR> expected1 {
                VECTOR_PAIR(2, 0.1),
                VECTOR_PAIR(3, 0.1),
                VECTOR_PAIR(0, 0.15),
                VECTOR_PAIR(1, 0.15),
        };
        std::vector<VECTOR_PAIR> expected2 {
                VECTOR_PAIR(0, 0.1),
                VECTOR_PAIR(1, 0.1),
                VECTOR_PAIR(2, 0.2),
                VECTOR_PAIR(3, 0.3)
        };
    #undef VECTOR_PAIR

    Linkage::Matrix matrix(4);

    EXPECT_EQ(matrix.getSize(), 4);

    // Default value
    EXPECT_EQ(matrix.get(2, 3), 0);

    // Insertions
    EXPECT_TRUE(matrix.insert(1, 2, 0.4));
    EXPECT_TRUE(matrix.insert(1, 2, 0.9));

    // Invalid insertion on the decreasing diagonal
    EXPECT_FALSE(matrix.insert(1, 1, 0.1));

    matrix.insert(0, 1, 0.15);
    matrix.insert(0, 2, 0.5);
    matrix.insert(0, 3, 0.3);

    matrix.insert(1, 3, 0.2);
    matrix.insert(2, 3, 0.1);

    // Getter
    EXPECT_EQ(matrix.get(1, 2), 0.4);
    EXPECT_EQ(matrix.get(1, 2), matrix.get(2, 1));

    // Invalid get on the decreasing diagonal
    EXPECT_ANY_THROW(matrix.get(1, 1));

    EXPECT_EQ(matrix.getMinimums(), expected1);

    matrix.insert(0, 1, 0.1);
    matrix.insert(0, 2, 0.2);
    matrix.insert(0, 3, 0.3);

    matrix.insert(1, 3, 0.5);
    matrix.insert(2, 3, 0.6);

    EXPECT_EQ(matrix.getMinimums(), expected2);


}

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
