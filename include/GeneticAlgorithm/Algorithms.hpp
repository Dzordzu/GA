//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_ALGORITHMS_HPP
#define GENETIC_ALGORITHM_ALGORITHMS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {


    namespace Core {
        template <typename Genotype>
        class Population {
        public:
            virtual void add(Individual<Genotype> i) = 0;
            virtual void fillRandom(int toSize) = 0;
            virtual Individual<Genotype> getBest() = 0;
            virtual Individual<Genotype> getBest(int amount) = 0;
            virtual Individual<Genotype> getRandom() = 0;
            virtual void remove() = 0;
            virtual void remove(int amount) = 0;
        };

        struct Settings {
            double crossoverProbability;
            double mutationProbability;
            double singleGeneMutationProbability;
        };
    }

    namespace Binary {

    }

    namespace Algorithms {
        using GeneticAlgorithm::Core::Individual;
        using GeneticAlgorithm::Core::Population;

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
