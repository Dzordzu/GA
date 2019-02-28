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

        template<typename Genotype>
        class Evaluator {
        public:
            virtual size_t getGenotypeLength() = 0;
            virtual double calculateFitness(Individual<Genotype> &i) = 0;
            virtual double getMaxFitness() = 0;
        };

        template <typename Genotype>
        class Population {
        protected:
            Evaluator<Genotype> *evaluator;
        public:
            virtual void add(Genotype i) = 0;
            virtual void fillRandom(int toSize = -1) = 0;
            virtual Individual<Genotype> getBest() = 0;
            virtual Individual<Genotype> &getRandomReference() = 0; //Why not iterators? We do not want to obligate user to use specific structure
            virtual Individual<Genotype>  removeRandom() = 0; // Returns removed Individual

            virtual Evaluator<Genotype> *getEvaluatorPointer() = 0;
        };

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
