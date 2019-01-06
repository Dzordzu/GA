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

TEST(LinkageTest, ConnectivityMatrix) {

    // Results for getMinimums
    typedef std::pair<size_t, double> VECTOR_PAIR;

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

    Linkage::ConnectivityMatrix matrix(4);

    EXPECT_EQ(matrix.getSize(), 4);

    // Default value
    double def;
    matrix.get(2, 3, def);
    EXPECT_EQ(def, 0);

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

    // Getters
    double get_1_2, get_2_1, get_1_1;

    EXPECT_TRUE(matrix.get(1, 2, get_1_2));
    EXPECT_EQ(get_1_2, 0.9);

    EXPECT_TRUE(matrix.get(2, 1, get_2_1));
    EXPECT_EQ(get_1_2, get_2_1);

    // Invalid get on the decreasing diagonal
    EXPECT_FALSE(matrix.get(1, 1, get_1_1));

    // Minimums
    EXPECT_EQ(matrix.getMinimums(), expected1);

    matrix.insert(0, 1, 0.1);
    matrix.insert(0, 2, 0.2);
    matrix.insert(0, 3, 0.3);

    matrix.insert(1, 3, 0.5);
    matrix.insert(2, 3, 0.6);

    EXPECT_EQ(matrix.getMinimums(), expected2);


}

TEST(LinkageTest, Algorithm) {

    using Genotype::Genotype;
    using Linkage::Cluster;

    std::vector<Genotype> genotypes_9 {
            Genotype({1, 1, 1, 0, 0, 0, 1, 1, 1}),
            Genotype({0, 0, 0, 1, 1, 1, 1, 1, 1}),
            Genotype({0, 1, 1, 0, 0, 0, 1, 1, 1}),
            Genotype({0, 1, 0, 1, 1, 1, 1, 1, 1}),
            Genotype({1, 0, 1, 0, 0, 0, 1, 1, 1}),
            Genotype({0, 0, 1, 1, 1, 1, 1, 1, 1}),
            Genotype({1, 1, 1, 0, 0, 0, 1, 1, 1}),
            Genotype({1, 0, 0, 1, 1, 1, 1, 1, 1}),
    };

    Linkage::Algorithm algo;
    algo.calculate(genotypes_9);

    EXPECT_THAT(algo.getClusters(), testing::ElementsAre(
            Cluster({1}),
            Cluster({2}),
            Cluster({3}),
            Cluster({4}),
            Cluster({5}),
            Cluster({6}),
            Cluster({7}),
            Cluster({8}),
            Cluster({0}),
            Cluster({3, 4}),
            Cluster({6, 7}),
            Cluster({3, 4, 5}),
            Cluster({6, 7, 8}),
            Cluster({2, 3, 4, 5}),
            Cluster({0, 2, 3, 4, 5}),
            Cluster({0, 1, 2, 3, 4, 5})
            ));
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
