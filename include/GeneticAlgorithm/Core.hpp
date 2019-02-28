//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_CORE_HPP
#define GENETIC_ALGORITHM_CORE_HPP

#include <vector>

namespace GeneticAlgorithm {

    namespace Core {

        template <typename Genotype> class Evaluator;

        template <typename Genotype>
        class Individual {
        protected:
            Genotype genotype;
            double fitness;
        public:
            void setGenotype(Genotype genotype, double fitness);
            Genotype &getGenotypeReference();
            void recalculateFitness(Evaluator<Genotype> *evaluator);
            double getFitness();
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
        void Individual<Genotype>::setGenotype(Genotype genotype, double fitness) {
            this->genotype = genotype;
            this->fitness = fitness;
        }

        template<typename Genotype>
        void Individual<Genotype>::recalculateFitness(Evaluator<Genotype> *evaluator) {
            this->fitness = evaluator->calculateFitness(this->genotype);
        }
    }
}


#endif //GENETIC_ALGORITHM_CORE_HPP
