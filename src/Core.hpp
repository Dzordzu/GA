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
            Genotype &getGenotype();
            double getFitness();
        };
    }
}


#endif //GENETIC_ALGORITHM_CORE_HPP
