//
// Created by dzordzu on 20.02.19.
//

#include "Core.hpp"

namespace GeneticAlgorithm {
    namespace Core {

        Genotype &Individual::getGenotype() {
            return this->genotype;
        }

        double Individual::getFitness() {
            return fitness;
        }
    }
}