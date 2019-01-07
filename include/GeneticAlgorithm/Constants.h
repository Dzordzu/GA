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
            const size_t TINY = 20;
            const size_t SMALL = 40;
            const size_t NORMAL = 50;
            const size_t BIG = 100;
            const size_t HUGE = 150;
            const size_t ENORMOUS = 500;
        }

        namespace Probability {
            const double MUTATION = 0.1;
            const double MUTATION_SINGLE_GENE = 0.1;
            const double LINKIN_TREE_GENERATION = 0.2;
            const double P3_FEEDBACK = 0.01;

            const double CROSSOVER_STANDARD = 0.1;
            const double CROSSOVER_HARD = CROSSOVER_STANDARD * 2;
        }

        namespace Amounts {
            const size_t CROSSOVERS_MAX = 100;
            const size_t CHECK_FREQUENCY = 15;
        }



    };
};

#endif //GENETIC_ALGORITHM_CONSTANTS_H
