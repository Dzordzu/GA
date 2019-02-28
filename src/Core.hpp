//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_CORE_HPP
#define GENETIC_ALGORITHM_CORE_HPP

#include <vector>

namespace GeneticAlgorithm {

    namespace Binary {
        typedef typename std::vector<int> Genotype;
    }

    namespace Core {
        template <typename Genotype>
        class Individual {
        protected:
            Genotype genotype;
            double fitness;
        public:
            void setGenotype(Genotype genotype, double fitness);
            Genotype &getGenotypeReference();
            double &getFitnessReference();
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
        double &Individual<Genotype>::getFitnessReference() {
            return this->fitness;
        }
    }
}


#endif //GENETIC_ALGORITHM_CORE_HPP
