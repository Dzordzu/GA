//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_ALGORITHMS_HPP
#define GENETIC_ALGORITHM_ALGORITHMS_HPP

#include "Core.hpp"
#include <algorithm>
#include <vector>

namespace GeneticAlgorithm {


    namespace Core {


        struct Settings {
            double crossoverProbability;
            double mutationProbability;
            double singleGeneMutationProbability;
        };

        template <typename Genotype>
        class Algorithm {
        protected:
            Population<Genotype> *population;
            Settings *settings;
        public:
            virtual void iterate() = 0;
            virtual Population<Genotype> *getPopulation() = 0;
            virtual Settings *getSettings() = 0;
        };
    }

    namespace Binary {
        typedef typename std::vector<int> Genotype;
        typedef typename GeneticAlgorithm::Core::Evaluator<Genotype> Evaluator;
        typedef typename GeneticAlgorithm::Core::Individual<Genotype> Individual;
        typedef typename GeneticAlgorithm::Core::Population<Genotype> Population;
        typedef typename GeneticAlgorithm::Core::Algorithm<Genotype> Algorithm;

        class VectorPopulation : public Population {
            std::vector<Individual> population;
        public:
            void add(Genotype i) override;
            void fillRandom(int toSize) override;
            Individual getBest() override;
            Individual &getRandomReference() override;
            Individual removeRandom() override;
            Evaluator *getEvaluatorPointer() override;
        };

        class SimpleAlgorithm : public Algorithm {
        public:
            SimpleAlgorithm(Population *population, GeneticAlgorithm::Core::Settings *settings);
            void iterate() override;
            Population *getPopulation() override;
            Core::Settings *getSettings() override;
        };

    }
}


#endif //GENETIC_ALGORITHM_ALGORITHMS_HPP
