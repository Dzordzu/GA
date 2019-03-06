//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "GeneticAlgorithm/Binary.hpp"

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

        double calculateFitness(GeneticAlgorithm::Binary::Genotype &i) override {
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

    MAX0::Evaluator evaluator;

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


}

/*
TEST(BinaryAlgorithms, SimpleAlgorithm) {

    GeneticAlgorithm::Core::Settings settings{};
    settings.mutationProbability = 0.05;
    settings.crossoverProbability = 0.4;
    settings.singleGeneMutationProbability = 0.1;

    MAX0::Evaluator evaluator(30);

    GeneticAlgorithm::Binary::Populations::VectorPopulation vectorPopulation(&evaluator);
    vectorPopulation.fillRandom(-1);

    GeneticAlgorithm::Binary::Algorithms::SimpleAlgorithm algorithm(&vectorPopulation, &settings);

    for(int i=0; i<100; i++) {
        algorithm.iterate();
    }

    algorithm.getPopulation()->getBest();
}
 */