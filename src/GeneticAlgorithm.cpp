//
// Created by dzordzu on 02.01.19.
//

#include <GeneticAlgorithm/GeneticAlgorithm.h>

namespace GeneticAlgorithms {

    void GAManager::checkStagnation(GAManager::Algo &a) {
        double lastFitness = (*a.bestInstances.rend()).getFitness();
        double veryLastFitness = (*(a.bestInstances.rend() + 1)).getFitness();
        size_t stagnation;
        if(1 - (veryLastFitness/lastFitness) < Constants::GA_MANAGER::FITNESS_DIFERENCE_LIMIT) stagnation += Constants::GA_MANAGER::CHECK_FREQUENCY;

        a.stagnation = stagnation;
    }

    void GAManager::runEach() {
        for(Algo &a : algos) a.algorithm.iterate();
    }

    void GAManager::getBest(Algo &a) {
        a.bestInstances.emplace_back(a.algorithm.getBestIndividual());
    }

    void GAManager::getBests() {
        for(Algo &a : algos) getBest(a);
    }
}

