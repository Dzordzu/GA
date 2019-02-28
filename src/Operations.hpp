//
// Created by dzordzu on 22.02.19.
//

#ifndef GENETIC_ALGORITHM_OPERATIONS_HPP
#define GENETIC_ALGORITHM_OPERATIONS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {
    namespace Operations {

        using GeneticAlgorithm::Core::Individual;

        template<typename Genotype>
        class Mutation {public: virtual void mutate(Individual<Genotype> &individual) = 0;};

        template<typename Genotype>
        class Crossover {
        public:
            virtual void cross(Individual<Genotype> &target, Individual<Genotype> &source) = 0;
        };
    }
}


#endif //GENETIC_ALGORITHM_OPERATIONS_HPP
