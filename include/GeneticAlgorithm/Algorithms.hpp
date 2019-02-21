//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_ALGORITHMS_HPP
#define GENETIC_ALGORITHM_ALGORITHMS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {
    namespace Algorithms {

        using GeneticAlgorithm::Core::Individual;

        class Population {
        public:
            virtual void add(Individual i) = 0;

            virtual Individual getBest() = 0;
            virtual Individual getBest(int amount) = 0;

            virtual Individual getRandom() = 0;

            virtual void remove() = 0;
            virtual void remove(int amount) = 0;
        };

        class AlgorithmBase {
        protected:
            Population *population;
        public:
            virtual void iterate() = 0;
            virtual Population *getPopulation() = 0;

        };



    }
}


#endif //GENETIC_ALGORITHM_ALGORITHMS_HPP
