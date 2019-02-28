//
// Created by dzordzu on 20.02.19.
//

#include "Algorithms.hpp"

void GeneticAlgorithm::Binary::VectorPopulation::add(Genotype i) {

}

void GeneticAlgorithm::Binary::VectorPopulation::fillRandom(int toSize) {

}

GeneticAlgorithm::Core::Individual<GeneticAlgorithm::Binary::Genotype>
GeneticAlgorithm::Binary::VectorPopulation::getBest() {
    return Individual();
}

GeneticAlgorithm::Core::Individual<GeneticAlgorithm::Binary::Genotype> &
GeneticAlgorithm::Binary::VectorPopulation::getRandomReference() {
    return <#initializer#>;
}

GeneticAlgorithm::Core::Individual<GeneticAlgorithm::Binary::Genotype>
GeneticAlgorithm::Binary::VectorPopulation::removeRandom() {
    return Individual<Genotype>();
}

GeneticAlgorithm::Core::Evaluator<GeneticAlgorithm::Binary::Genotype> *
GeneticAlgorithm::Binary::VectorPopulation::getEvaluatorPointer() {
    return nullptr;
}

GeneticAlgorithm::Core::Individual<GeneticAlgorithm::Binary::Genotype>
GeneticAlgorithm::Binary::VectorPopulation::getBest(int amount) {
    return Individual();
}

GeneticAlgorithm::Core::Individual<GeneticAlgorithm::Binary::Genotype>
GeneticAlgorithm::Binary::VectorPopulation::getRandom() {
    return Individual();
}

void GeneticAlgorithm::Binary::VectorPopulation::remove() {

}

void GeneticAlgorithm::Binary::VectorPopulation::remove(int amount) {

}

void GeneticAlgorithm::Binary::SimpleAlgorithm::iterate() {

}

GeneticAlgorithm::Core::Population<GeneticAlgorithm::Binary::Genotype> *
GeneticAlgorithm::Binary::SimpleAlgorithm::getPopulation() {
    return nullptr;
}

GeneticAlgorithm::Core::Settings *GeneticAlgorithm::Binary::SimpleAlgorithm::getSettings() {
    return nullptr;
}
