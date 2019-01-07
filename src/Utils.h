//
// Created by dzordzu on 06.01.19.
//

#pragma once
#ifndef GENETIC_ALGORITHM_UTILS_H
#define GENETIC_ALGORITHM_UTILS_H

#include <random>

namespace GeneticAlgorithms {

    namespace Utils {
        inline static double getRandomPercentage() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(0, 1);

            return dis(gen);
        }

        inline static bool getRandomBool() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, 1);

            return (bool)dis(gen);
        }

        inline static size_t getRandomSize(size_t max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> dis(0, max);

            return dis(gen);
        }
    };




};

#endif //GENETIC_ALGORITHM_UTILS_H
