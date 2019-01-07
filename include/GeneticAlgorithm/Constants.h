//
// Created by dzordzu on 06.01.19.
//

#ifndef GENETIC_ALGORITHM_CONSTANTS_H
#define GENETIC_ALGORITHM_CONSTANTS_H

#include <cstdint>
#include <cstddef>

namespace GeneticAlgorithms {
    namespace Constants {

        namespace Version {
            const uint_fast16_t major = 0;
            const uint_fast16_t minor = 1;
        }

        namespace Population {
            const size_t TINY = 200;
            const size_t SMALL = 400;
            const size_t NORMAL = 500;
            const size_t BIG = 1000;
            const size_t HUGE = 1500;
            const size_t ENORMOUS = 3000;
        }

        namespace Probability {
            const double MUTATION = 0.5;
            const double MUTATION_SINGLE_GENE = 0.1;
            const double LINKIN_TREE_GENERATION = 0.2;
            const double P3_FEEDBACK = 0.01;

            const double CROSSOVER_STANDARD = 0.5;
            const double CROSSOVER_HARD = CROSSOVER_STANDARD * 2;
        }

        namespace Amounts {
            const size_t CROSSOVERS_MAX = 100;
        }



    };
};

#endif //GENETIC_ALGORITHM_CONSTANTS_H
