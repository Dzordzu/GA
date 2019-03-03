//
// Created by dzordzu on 28.02.19.
//

#include "GeneticAlgorithm/Binary.hpp"

namespace GeneticAlgorithm {
    namespace Binary {

        bool Generator::generateRandomBool() {
            return (bool)(rand() % 2);
        }

        Genotype Generator::generateRandomGenotype(int genotypeLength) {

            Genotype genotype;
            genotype.resize(genotypeLength);

            for(int i=0; i<genotypeLength; i++) {
                genotype.at(i) = generateRandomBool();
            }

            return genotype;
        }

        namespace Populations {

            void VectorPopulation::add(Genotype i) {

                Individual individual;
                individual.setGenotype(Generator::getInstance().generateRandomGenotype(this->evaluator->getGenotypeLength()), this->evaluator);

                this->population.push_back(individual);
            }
        }
    }
}