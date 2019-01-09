//
// Created by dzordzu on 09.01.19.
//

#include "gmock/gmock.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Genotype.h"
#include "Linkage.h"
#include <vector>
#include <utility>

#pragma once

class MyEvaluator : public GeneticAlgorithms::Evaluator {
public:
    inline size_t getGenotypeSize() override{return 500;}
    inline double getMaxFitness() override {return 500;}
    inline double evaluate(Genotype::Genotype &genotype) override{
        int fitness = 0;
        for(size_t i : genotype.getGenesCopy())  {
            fitness += i;
        }
        return fitness;
    }
};

TEST(Manual, FixedSizeGA_ENORMOUS) {
MyEvaluator myEvaluator;
typedef GeneticAlgorithms::FixedSizeGA<GeneticAlgorithms::Constants::Population::SMALL> algo;

algo a1(myEvaluator);
algo a2(myEvaluator);
GeneticAlgorithms::FixedSizeGA<GeneticAlgorithms::Constants::Population::ENORMOUS> algo2(myEvaluator);
GeneticAlgorithms::GAManager manager;
//manager.addAlgorithm(a1);
//manager.addAlgorithm(a2);
manager.addAlgorithm(algo2);

double bestFitness = 0;

for(int i=0; i<200; i++) {

manager.iterate();
bestFitness = std::max(manager.getBestFitness(), bestFitness);
std::cout<<manager.getBestFitness()<<std::endl;

//        algo.iterate();
//        //algo2.iterate();
//
//        bestFitness = std::max(algo.getBestFitness(), bestFitness);
//        //bestFitness = std::max(algo2.getBestFitness(), bestFitness);
//
//        //std::cout<<algo.getBestFitness()<<std::endl;
//        if(bestFitness == myEvaluator.getMaxFitness()) break;
}

//std::cout<<manager.getBestFitness();



}
