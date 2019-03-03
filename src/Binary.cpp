//
// Created by dzordzu on 28.02.19.
//

#include "GeneticAlgorithm/Binary.hpp"

namespace GeneticAlgorithm {
    namespace Binary {

        bool Generator::generateRandomBool() {
            std::mt19937 gen(rd());
        }

        namespace Populations {

            void VectorPopulation::add(Genotype i) {

                Individual individual;
                individual.setGenotype()

                this->population.push_back();
            }
        }
    }
}