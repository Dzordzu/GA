//
// Created by dzordzu on 22.02.19.
//

#ifndef GENETIC_ALGORITHM_OPERATIONS_HPP
#define GENETIC_ALGORITHM_OPERATIONS_HPP

#include "Core.hpp"

namespace GeneticAlgorithm {
    namespace Core {

        template<typename Genotype>
        class Mutation {public: virtual void mutate(Individual<Genotype> &individual) = 0;};

        template<typename Genotype>
        class Crossover {
        public:
            virtual void cross(Individual<Genotype> &target, Individual<Genotype> &source) = 0;
        };
    }

    namespace Binary {
        namespace Crossover {

            using GeneticAlgorithm::Core::Crossover;
            class Genotype;

            class SimpleCrossover : public Crossover<Genotype> {
            public:
                virtual void cross(Core::Individual<Genotype> &target, Core::Individual<Genotype> &source);
            };

        }
    }
}


#endif //GENETIC_ALGORITHM_OPERATIONS_HPP
