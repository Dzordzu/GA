//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_CORE_HPP
#define GENETIC_ALGORITHM_CORE_HPP

#include <vector>
#include <typeinfo>

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
            double getFitness();
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
            this->fitness = evaluator->calculateFitness(evaluator);
        }

        template<typename Genotype>
        void Individual<Genotype>::recalculateFitness(Evaluator<Genotype> *evaluator) {
            this->fitness = evaluator->calculateFitness(this->genotype);
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
