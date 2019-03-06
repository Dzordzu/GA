//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_CORE_HPP
#define GENETIC_ALGORITHM_CORE_HPP

#include <vector>
#include <typeinfo>
#include <float.h>

namespace GeneticAlgorithm {

    namespace Core {

        template<typename Genotype>
        class Evaluator {
        public:
            virtual std::size_t getGenotypeLength() = 0;
            virtual double calculateFitness(Genotype &i) = 0;
            virtual double getMaxFitness() = 0;
        };

        template <typename Genotype>
        class Individual {
        protected:
            Genotype genotype;
            double fitness;
        public:
            void setGenotype(Genotype genotype, Evaluator<Genotype> *evaluator);
            Genotype &getGenotypeReference();
            void recalculateFitness(Evaluator<Genotype> *evaluator);
            void zeroFitness();
            double getFitness();
        };

        template <typename Genotype>
        class Population {
        protected:
            Evaluator<Genotype> *evaluator;
        public:
            virtual void add(Genotype i) = 0;
            virtual void fillRandom(int toSize) = 0;
            virtual Individual<Genotype> getBest() = 0;
            virtual Individual<Genotype> *getRandomPointer() = 0; //Why not iterators? We do not want to obligate user to use specific structure

            inline Evaluator<Genotype> &getEvaluatorReference() const { return evaluator; }
        };

        template<typename Genotype>
        Genotype &Individual<Genotype>::getGenotypeReference() {
            return genotype;
        }

        template<typename Genotype>
        double Individual<Genotype>::getFitness() {
            return fitness;
        }

        template<typename Genotype>
        void Individual<Genotype>::setGenotype(Genotype genotype, Evaluator<Genotype> *evaluator) {
            this->genotype = genotype;
            this->fitness = evaluator->calculateFitness(genotype);
        }

        template<typename Genotype>
        void Individual<Genotype>::recalculateFitness(Evaluator<Genotype> *evaluator) {
            this->fitness = evaluator->calculateFitness(this->genotype);
        }

        template<typename Genotype>
        void Individual<Genotype>::zeroFitness() {
            this->fitness = -DBL_MAX;
        }

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

        template <typename Genotype>
        class Mutation {
        public:
            virtual void mutate(Individual<Genotype> &individual) = 0;
        };

        template <typename Genotype>
        class CrossoverMultipleSources {

        };
    }
}


#endif //GENETIC_ALGORITHM_CORE_HPP
