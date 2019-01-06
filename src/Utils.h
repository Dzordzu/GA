//
// Created by dzordzu on 06.01.19.
//

#pragma once
#ifndef GENETIC_ALGORITHM_UTILS_H
#define GENETIC_ALGORITHM_UTILS_H

#include <random>

namespace GeneticAlgorithms {

    struct Utils {
        inline static double getRandomPercentage() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(0, 1);

            return dis(gen);
        }
    };




}

#endif //GENETIC_ALGORITHM_UTILS_H
