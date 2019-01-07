//
// Created by dzordzu on 02.01.19.
//

#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_H
#define GENETIC_ALGORITHM_GENETICALGORITHM_H

#include "Constants.h"
#include "Genotype.h"
#include "Linkage.h"
#include "Utils.h"
#include <array>
#include <vector>

namespace GeneticAlgorithms {

    class Evaluator {
    public:
        virtual inline bool isEmpty() {return false;}
        virtual size_t getGenotypeSize() = 0;
        virtual double getMaxFitness() = 0;
        virtual double evaluate(Genotype::Genotype &genotype) = 0;
    };

    class EmptyEvaluator : public Evaluator{
        inline bool isEmpty() final {return true;}
        inline size_t getGenotypeSize() override { return 0;}
        inline double getMaxFitness() override { return 0; }
        inline double evaluate(Genotype::Genotype &genotype) override { return 0; }
    };

    EmptyEvaluator EMPTY_EVALUATOR;



    class Individual {
    protected:
        Genotype::Genotype genotype;
        double fitness;
        Evaluator& evaluator;
    public:
        inline Individual() : evaluator(EMPTY_EVALUATOR) { fitness = evaluator.evaluate(genotype); }
        inline Individual(Evaluator &evaluator, Genotype::Genotype &genotype) : evaluator(evaluator) {
            this->genotype = genotype;
            fitness = evaluator.evaluate(this->genotype);
        }

        inline double getFitness() const {return fitness;};
        inline Evaluator & getEvaluator() {return evaluator;}
    };

    class GABase {
    protected:
        Evaluator& evaluator;
        double bestFitness;
        Individual bestIndividual;
    public:
        inline explicit GABase(Evaluator &evaluator) : evaluator(evaluator) {}

        virtual bool iterate() = 0;
        virtual bool populate() = 0;
        virtual bool addCluster(Linkage::Cluster &cluster) = 0;
        virtual bool replaceClusters(std::vector<Linkage::Cluster> clusters) = 0;
        virtual bool addIndividual(Individual &individual) = 0;

        inline double getBestFitness() const { return bestFitness; }
        inline Individual& getBestIndividual() { return bestIndividual; }

    };


    template<std::size_t SIZE>
    class FixedSizeGA : public GABase {
        std::array<Individual, SIZE> population;
        Linkage::Algorithm linkageAlgorithm;
        std::vector<Linkage::Cluster> clusters;
        Genotype::LinkageStandardCrossover linkageStandardCrossover;

    public:
        inline FixedSizeGA() {populate();};
        bool populate() override;
        bool iterate() override;
        inline bool addCluster(Linkage::Cluster &cluster) override { clusters.emplace_back(cluster); return true;}
        inline bool replaceClusters(std::vector<Linkage::Cluster> clusters) override {this->clusters = clusters; return true;}
        bool addIndividual(Individual &individual) override {return false;};
    };











    template<size_t SIZE>
    bool FixedSizeGA<SIZE>::populate() {
        for(size_t i=0; i<SIZE; i++) {
            population[i] = Individual(evaluator, Utils::getRandomGenotype(evaluator.getGenotypeSize()));
        }
        return true;
    }

    template<size_t SIZE>
    bool FixedSizeGA<SIZE>::iterate() {

        if(Utils::getRandomPercentage() < Constants::Probability::LINKIN_TREE_GENERATION) {
            linkageAlgorithm.clear();
            linkageAlgorithm.calculate(population);
            this->replaceClusters(linkageAlgorithm.getClusters());
        }

        for(size_t i=0; i<SIZE/2; i++) {
            if(Utils::getRandomPercentage() < Constants::Probability::CROSSOVER_STANDARD) {

                


            }
        }
    }


};

#endif //GENETIC_ALGORITHM_GENETICALGORITHM_H
