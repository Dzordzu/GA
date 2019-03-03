//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
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

TEST(BinaryAlgorithms, SimpleAlgorithm) {

    GeneticAlgorithm::Core::Settings settings{};
    settings.mutationProbability = 0.05;
    settings.crossoverProbability = 0.4;
    settings.singleGeneMutationProbability = 0.1

    MAX0::Evaluator evaluator(30);

    GeneticAlgorithm::Binary::VectorPopulation vectorPopulation(*evaluator);
    vectorPopulation.fillRandom(-1);

    GeneticAlgorithm::Binary::SimpleAlgorithm algorithm(*population, *settings);

    for(int i=0; i<100; i++) {
        algorithm.iterate();
    }

    algorithm.getPopulation()->getBest();
}