//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
#include "GeneticAlgorithm/Algorithms.hpp"

TEST(BinaryAlgorithms, SimpleAlgorithm) {

    GeneticAlgorithm::Core::Settings settings;
    settings.mutationProbability = 0.05;
    settings.crossoverProbability = 0.4;

    GeneticAlgorithm::Binary::VectorPopulation vectorPopulation;
    GeneticAlgorithm::Binary::SimpleAlgorithm algorithm(*population, *settings);

    for(int i=0; i<100; i++) {
        algorithm.iterate();
    }

    algorithm.getPopulation()->getBest();
}