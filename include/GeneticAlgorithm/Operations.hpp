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

    }

    namespace Binary {
        namespace Crossover {

            class Genotype;
            class Individual;
            class Evaluator;

            void standardCrossover(Individual &target, Individual &source);
            void betterOneCrossover(Individual &target, Individual &source, Evaluator *evaluator);
            void firstImprovementCrossover(Individual &target, Individual &source, Evaluator *evaluator);
        }
    }
}


#endif //GENETIC_ALGORITHM_OPERATIONS_HPP
