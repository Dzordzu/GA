//
// Created by dzordzu on 22.02.19.
//

#ifndef GENETIC_ALGORITHM_OPERATIONS_HPP
#define GENETIC_ALGORITHM_OPERATIONS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {
    namespace Operations {

        using GeneticAlgorithm::Core::Individual;

        class Mutation {public: virtual void mutate(Individual &individual) = 0;};
        class Crossover {
        public:
            virtual void cross(Individual &target, Individual source) = 0;
        };
    }
}


#endif //GENETIC_ALGORITHM_OPERATIONS_HPP
