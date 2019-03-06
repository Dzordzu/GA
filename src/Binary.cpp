//
// Created by dzordzu on 28.02.19.
//

#include <GeneticAlgorithm/Binary.hpp>


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

        int Generator::generateRandomIndex(int end) {
            return rand() % end;
        }

        double Generator::generateRandomProbability() {
            return rand() / RAND_MAX;
        }

        namespace Populations {

            void VectorPopulation::add(Genotype i) {

                Individual individual;
                individual.setGenotype(i, this->evaluator);
                this->population.push_back(individual);

                if(individual.getFitness() > this->getBest().getFitness())
                    this->best = individual;
            }

            void VectorPopulation::fillWithRandom(int toSize) {

                if(this->population.size() < toSize) this->population.resize(toSize);

                for(int i=0; i<toSize; i++) {

                    Individual individual;
                    individual.setGenotype(Generator::getInstance().generateRandomGenotype(this->evaluator->getGenotypeLength()), this->evaluator);

                    this->population.at(i) = individual;
                }
            }

            Individual VectorPopulation::getBest() {
                return this->best;
            }

            Individual *VectorPopulation::getRandomPointer() {
                return &this->population.at(Generator::getInstance().generateRandomIndex(this->population.size()));
            }

            void VectorPopulation::resize(int toSize) {
                this->population.resize(toSize);
                this->fillWithRandom(toSize);
            }

            int VectorPopulation::getPopulationSize() {
                return this->population.size();
            }
        }

        namespace Algorithms {

            SimpleAlgorithm::SimpleAlgorithm(Population *population, GeneticAlgorithm::Core::Settings *settings) {
                this->population = population;
                this->settings = settings;
            }

            void SimpleAlgorithm::iterate() {

            }
        };

    }
}