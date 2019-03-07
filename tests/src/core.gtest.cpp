//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "GeneticAlgorithm/Binary.hpp"
#include <ctime>

namespace MAX0 {
    class Evaluator : public GeneticAlgorithm::Binary::Evaluator {
        size_t genotypeLength;
    public:
        explicit Evaluator(size_t genotypeLength = 10) {
            this->genotypeLength = genotypeLength;
        }

        size_t getGenotypeLength() override {
            return genotypeLength;
        }

        double calculateFitness(GeneticAlgorithm::Binary::Genotype &i) const override {
            int zeros = 0;
            for(int j = 0; j< i.size(); j++) {
                if(i.at(j) == 0) zeros++;
            }
            return (double)zeros;
        }

        double getMaxFitness() override {
            return (double)genotypeLength;
        }
    };
}

TEST(BinaryCoreFunctionality, Individual) {
    using GeneticAlgorithm::Binary::Genotype;
    using GeneticAlgorithm::Binary::Individual;

    MAX0::Evaluator evaluator(5);

    Genotype genotype({0,1,1,0,1});
    Individual individual;
    individual.setGenotype(genotype, &evaluator);

    EXPECT_EQ(individual.getFitness(), 2);
    EXPECT_THAT(individual.getGenotypeReference(), ::testing::ElementsAre(0,1,1,0,1));
}

TEST(BinaryPopulations, VectorPopulation) {

    using GeneticAlgorithm::Binary::Genotype;

    MAX0::Evaluator evaluator;

    GeneticAlgorithm::Binary::Populations::VectorPopulation population(&evaluator);
    population.add(Genotype({0,1,1,0,1}));
    EXPECT_THAT(population.getBest().getGenotypeReference(), ::testing::ElementsAre(0,1,1,0,1));

    population.add(Genotype({0,0,0,0,0}));
    EXPECT_THAT(population.getBest().getGenotypeReference(), ::testing::ElementsAre(0,0,0,0,0));
    EXPECT_THAT(population.getRandomPointer()->getGenotypeReference(), ::testing::AnyOf(::testing::ElementsAre(0,0,0,0,0), ::testing::ElementsAre(0,1,1,0,1)));

    population.fillWithRandom(10);
    EXPECT_EQ(population.getBest().getFitness(), 5);
}


TEST(BinaryAlgorithms, SimpleAlgorithm) {

    srand(time(NULL));

    std::cout<<"str";

    GeneticAlgorithm::Core::Settings settings{};
    settings.mutationProbability = 0.05;
    settings.crossoverProbability = 0.4;
    settings.singleGeneMutationProbability = 0.1;

    MAX0::Evaluator evaluator(300);

    GeneticAlgorithm::Binary::Populations::VectorPopulation vectorPopulation(&evaluator);
    vectorPopulation.fillWithRandom(100);
    vectorPopulation.fillWithRandom(-1);

    GeneticAlgorithm::Binary::Algorithms::SimpleAlgorithm algorithm(&vectorPopulation, &settings);

    for(int i=0; i<1000; i++) {
        algorithm.iterate();
    }

    int help = 230;
    EXPECT_THAT(algorithm.getPopulation()->getBest().getFitness(), ::testing::Gt(help));
}
