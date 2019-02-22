//
// Created by dzordzu on 20.02.19.
//

#include "gtest/gtest.h"
#include "GeneticAlgorithm/Algorithms.hpp"

TEST(Algorithms, SimpleAlgorithm) {

    GeneticAlgorithm::Algorithms::Settings settings;
    settings.setMutationProbability(0.05);
    settings.setCrossoverProbability(0.4);

    GeneticAlgorithm::Population::SimplePopulation population;
    GeneticAlgorithm::Algorithms::Binary::SimpleAlgorithm algorithm(*population, *settings);

    for(int i=0; i<100; i++) {
        algorithm.iterate();
    }

    algorithm.getPopulation()->getBest();
}