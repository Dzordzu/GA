//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_ALGORITHMS_HPP
#define GENETIC_ALGORITHM_ALGORITHMS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {


    namespace Population {
        using GeneticAlgorithm::Core::Individual;

        class Population {
        public:
            virtual void add(Individual i) = 0;
            virtual void fillRandom(int toSize) = 0;
            virtual Individual getBest() = 0;
            virtual Individual getBest(int amount) = 0;
            virtual Individual getRandom() = 0;
            virtual void remove() = 0;
            virtual void remove(int amount) = 0;
        };
    }

    namespace Algorithms {
        using GeneticAlgorithm::Core::Individual;
        using GeneticAlgorithm::Population::Population;

        class Settings {};

        class Algorithm {
        protected:
            Population *population;
            Settings *settings;
        public:
            virtual void iterate() = 0;
            virtual Population *getPopulation() = 0;
            virtual Settings *getSettings() = 0;
        };

    }
}


#endif //GENETIC_ALGORITHM_ALGORITHMS_HPP
