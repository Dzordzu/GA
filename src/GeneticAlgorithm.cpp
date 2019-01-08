//
// Created by dzordzu on 02.01.19.
//

#include <GeneticAlgorithm/GeneticAlgorithm.h>

namespace GeneticAlgorithms {

    void GAManager::checkStagnation(GAManager::Algo &a) {
        double lastFitness = (*a.bestIndividuals.rbegin()).getFitness();
        double veryLastFitness = (*(a.bestIndividuals.rbegin() + 1)).getFitness();
        size_t stagnation;
        if(1 - (veryLastFitness/lastFitness) < Constants::GA_MANAGER::FITNESS_DIFERENCE_LIMIT) stagnation += Constants::GA_MANAGER::CHECK_FREQUENCY;

        a.stagnation = stagnation;
    }

    void GAManager::runEach() {
        for(Algo &a : algos) {
            if(a.disabled) continue;
            a.algorithm->iterate();
            a.bestIndividuals.emplace_back(a.algorithm->getBestIndividual());
        }
    }

    void GAManager::getBest(Algo &a) {
        a.bestIndividuals.emplace_back(a.algorithm->getBestIndividual());
        bestIndividualsGlobal.insert(a.algorithm->getBestIndividual());
        if(bestIndividualsGlobal.size() > 40) bestIndividualsGlobal.erase(bestIndividualsGlobal.begin());
    }

    void GAManager::getBests() {
        for(Algo &a : algos) getBest(a);
    }

    void GAManager::checkProgress() {

        using Constants::GA_MANAGER::CHOICES::LINKAGE_TRANSFER;
        using Constants::GA_MANAGER::CHOICES::INDIVIDUALS_TRANSFER;
        using Constants::GA_MANAGER::CHOICES::DISABLE;
        using Constants::GA_MANAGER::CHOICES::REMOVE;
        using Constants::GA_MANAGER::CHOICES::NOTHING;

        for(size_t index = 0; index < algos.size(); index++) {
            Algo &a = algos[index];
            checkStagnation(a);

            if(a.stagnation > Constants::GA_MANAGER::STAGNATION_LIMIT) {
                double choice = Utils::getRandomPercentage();

                if(NOTHING  < choice && choice < LINKAGE_TRANSFER) {
                    std::vector<Genotype::Genotype> genotypes;
                    for(Individual i : bestIndividualsGlobal) genotypes.emplace_back(i.getGenotype());
                    linkageAlgo.clearResult();
                    linkageAlgo.calculate(genotypes);
                    a.algorithm->setClusters(linkageAlgo.getClusters());
                }
                else if(LINKAGE_TRANSFER  < choice && choice < INDIVIDUALS_TRANSFER) {
                    for(Individual i : bestIndividualsGlobal) a.algorithm->transferIndividual(i);
                }
                else if(INDIVIDUALS_TRANSFER < choice && choice < DISABLE) {
                    a.disabled = true;
                }
                else if(DISABLE < choice && choice < REMOVE) algos.erase(algos.begin()+index);
            }
        }
    }

    void GAManager::iterate() {
        runEach();
        if(iterations % Constants::GA_MANAGER::CHECK_FREQUENCY == 0) {
            getBests();
            checkProgress();
        }
        iterations++;
    }

    Individual GAManager::getBestIndividual() {
        return (*bestIndividualsGlobal.rbegin());
    }

    double GAManager::getBestFitness() {
        return getBestIndividual().getFitness();
    }
}

