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

                if(toSize <= 0) toSize = this->population.size();
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

            bool VectorPopulation::checkQuality(Genotype &genotype) {
                Individual individual;
                individual.setGenotype(genotype, this->evaluator);
                if(individual.getFitness() > this->best.getFitness()) {
                    this->best = individual;
                    return true;
                }
                return false;
            }
        }

        namespace Algorithms {

            SimpleAlgorithm::SimpleAlgorithm(Population *population, GeneticAlgorithm::Core::Settings *settings) {
                this->population = population;
                this->settings = settings;

                this->mask = Operations::Mask();
                int genotypeLength = population->getEvaluatorReference().getGenotypeLength();
                mask.resize(genotypeLength);
                Operations::Mask::iterator maskIterator = mask.begin();

                for(int i=0; i<genotypeLength/2; i++) {
                    *maskIterator = 0;
                    maskIterator++;
                }

                for(int i=0; i<genotypeLength - genotypeLength/2; i++) {
                    *maskIterator = 1;
                    maskIterator++;
                }
            }

            void SimpleAlgorithm::iterate() {

                for(int i=0; i<this->population->getPopulationSize() / 2; i++) {

                    if(Generator::getInstance().generateRandomProbability() < this->settings->mutationProbability) mutate();

                    if(Generator::getInstance().generateRandomProbability() < this->settings->crossoverProbability) {
                        Individual * target = population->getRandomPointer();
                        Operations::Crossover::standardCrossover(*target, *population->getRandomPointer(), this->mask);
                        this->population->checkQuality(target->getGenotypeReference());
                    }

                }

            }

            void SimpleAlgorithm::setMask(Operations::Mask mask) {
                if(mask.size() != population->getEvaluatorReference().getGenotypeLength()) return;
                this->mask = mask;
            }

            void SimpleAlgorithm::mutate() {
                Individual * individual = population->getRandomPointer();
                int genLength = population->getEvaluatorReference().getGenotypeLength();

                for(int i=0; i<genLength/3; i++)
                    if (Generator::getInstance().generateRandomProbability() < this->settings->singleGeneMutationProbability)
                        individual->getGenotypeReference()[Generator::getInstance().generateRandomIndex(genLength)];
                individual->recalculateFitness(&this->population->getEvaluatorReference());
            }
        };

        namespace Operations {

            namespace Crossover {

                void standardCrossover(Individual &target, Individual &source, Mask &mask) {

                    Genotype::iterator targetIterator = target.getGenotypeReference().begin();
                    Genotype::iterator sourceIterator = source.getGenotypeReference().begin();
                    Mask::iterator maskIterator = mask.begin();

                    for(int i=0; i<mask.size(); i++) {
                        if(*maskIterator) *targetIterator = *sourceIterator;
                        maskIterator++;
                        targetIterator++;
                        sourceIterator++;
                    }

                }

            }

        }

    }
}