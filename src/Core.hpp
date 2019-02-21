//
// Created by dzordzu on 20.02.19.
//

#ifndef GENETIC_ALGORITHM_CORE_HPP
#define GENETIC_ALGORITHM_CORE_HPP

#include <vector>

namespace GeneticAlgorithm {
    namespace Core {
        typedef typename std::vector<int> Genotype;

        class Individual {
        protected:
            Genotype genotype;
            double fitness;
        public:
            Genotype &getGenotype();
            double getFitness();
        };
    }
}


#endif //GENETIC_ALGORITHM_CORE_HPP
