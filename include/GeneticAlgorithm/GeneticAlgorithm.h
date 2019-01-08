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
#include <set>

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
        Evaluator * evaluator;
    public:
        inline Individual() : evaluator(&EMPTY_EVALUATOR) { fitness = evaluator->evaluate(genotype); }
        inline Individual(Evaluator &evaluator, Genotype::Genotype &genotype) : evaluator(&evaluator) {
            this->genotype = genotype;
            fitness = evaluator.evaluate(this->genotype);
        }

        inline double getFitness() const {return fitness;};
        inline Evaluator & getEvaluator() {return *evaluator;}
        inline Genotype::Genotype getGenotype() {return genotype;}

        bool operator<(const Individual &rhs) const {return fitness < rhs.fitness;}
        bool operator>(const Individual &rhs) const {return rhs < *this;}
        bool operator<=(const Individual &rhs) const {return !(rhs < *this);}
        bool operator>=(const Individual &rhs) const {return !(*this < rhs);}
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
        virtual bool setClusters(std::vector<Linkage::Cluster> clusters) = 0;
        virtual inline bool setPopulation(std::vector<Individual> &individuals) = 0;
        virtual inline bool setPopulation(std::vector<Genotype::Genotype> &genotypes) {
            std::vector<Individual> toSet;
            toSet.resize(genotypes.size());
            for(size_t i=0; i<genotypes.size(); i++) {
                toSet[i] = Individual(evaluator, genotypes[i]);
            }
            return setPopulation(toSet);
        }
        virtual bool transferIndividual(Individual &individual) = 0;

        inline double getBestFitness() const { return bestFitness; }
        inline Individual& getBestIndividual() { return bestIndividual; }

    };



    template<std::size_t SIZE>
    class FixedSizeGA : public GABase {

        std::set<Individual> linkageSet;
        std::vector<Linkage::Cluster> clusters;
        Linkage::Algorithm linkageAlgorithm;

        std::array<Individual, SIZE> population;
        Genotype::StandardMutation mutation;
        Genotype::LinkageStandardCrossover linkageStandardCrossover;

        void addToLinkageSet(Individual &i) {
            linkageSet.insert(i);
            if(linkageSet.size() > 20) linkageSet.erase(linkageSet.begin());
        }

        inline bool findMax(Individual &i) {
            if(i.getFitness() < this->bestIndividual.getFitness()) return false;
            this->bestIndividual = i;
            bestFitness = bestIndividual.getFitness();

            addToLinkageSet(i);
            return true;
        }

        void LTG();
        void Crossover();


    public:
        inline explicit FixedSizeGA(Evaluator& evaluator) : GABase(evaluator) {populate();};
        bool populate() override;
        bool iterate() override;
        inline bool addCluster(Linkage::Cluster &cluster) override { clusters.emplace_back(cluster); return true;}
        inline bool setClusters(std::vector<Linkage::Cluster> clusters) override {this->clusters = clusters; return true;}
        inline bool transferIndividual(Individual &individual) override {return false;};
        inline bool setPopulation(std::vector<Individual> &individuals) override { this->population = individuals; }
    };



    class GAManager {

        struct Algo {
            bool disabled;
            GABase& algorithm;
            std::vector<Individual> bestInstances;
            size_t stagnation;
        };

        size_t iterations;
        std::vector<Algo> algos;

        void checkStagnation(Algo &a);

        void runEach();
        void getBest(Algo &a);
        void getBests();
        void checkProgress();

    public:
        void iterate();

    };







    template<size_t SIZE>
    bool FixedSizeGA<SIZE>::populate() {
        for(size_t i=0; i<SIZE; i++) {
            Genotype::Genotype genotype = Utils::getRandomGenotype(evaluator.getGenotypeSize());
            population[i] = Individual(evaluator, genotype);
            findMax(population[i]);
        }
        LTG();
        return true;
    }

    template<size_t SIZE>
    bool FixedSizeGA<SIZE>::iterate() {

        if(Utils::getRandomPercentage() < Constants::Probability::LINKIN_TREE_GENERATION) {
            LTG();
        }

        for(size_t i=0; i<SIZE/2; i++) {
            if(Utils::getRandomPercentage() < Constants::Probability::CROSSOVER_STANDARD) {
                Crossover();
            }
        }

        for(size_t i=0; i<SIZE; i++) {
            if(Utils::getRandomPercentage() < Constants::Probability::MUTATION) {
                mutation.setTarget(population[i].getGenotype());
                mutation.mutate();
                population[i] = Individual(evaluator, mutation.getResult());
                findMax(population[i]);
            }
        }
        return true;
    }

    template<size_t SIZE>
    void FixedSizeGA<SIZE>::LTG() {
        linkageAlgorithm.clearResult();

        std::vector<Genotype::Genotype> genotypes_temp;
        for(size_t i = 0; i<linkageSet.size(); i++) {
            genotypes_temp.emplace_back(population[i].getGenotype());
        }

        linkageAlgorithm.calculate(genotypes_temp);
        this->setClusters(linkageAlgorithm.getClusters());
    }

    template<size_t SIZE>
    void FixedSizeGA<SIZE>::Crossover() {
        //std::cout<<"Started crossover"<<std::endl;

        std::array<size_t, 2> parents = {0,1};
        for(int j=0; j<4; j++) {
            for(int k=0; k<2; k++) {
                size_t random = Utils::getRandomSize(SIZE-1);
                parents[k] = population[parents[k]].getFitness() < population[random].getFitness() ? random : parents[k];
            }
        }

        this->linkageStandardCrossover.clear();
        this->linkageStandardCrossover.restartLooping();
        this->linkageStandardCrossover.addParent(population[parents[0]].getGenotype(), Genotype::LinkageStandardCrossover::ParentType::PRIMARY);
        this->linkageStandardCrossover.addParent(population[parents[1]].getGenotype(), Genotype::LinkageStandardCrossover::ParentType::SECONDARY);

        this->linkageStandardCrossover.setClusters(this->clusters);
        if(!this->linkageStandardCrossover.isFinished()) {

            size_t index_i = 0;

            while(this->linkageStandardCrossover.nextCalculation() && !clusters.empty()) {
                Individual result(evaluator, this->linkageStandardCrossover.getResult()[index_i++]);

                if(result.getFitness() > population[parents[0]].getFitness()) {
                    population[parents[0]] = result;
                    findMax(result);
                    break;
                }
                else if(result.getFitness() > population[parents[1]].getFitness()) {
                    population[parents[1]] = result;
                    findMax(result);
                    break;
                }
            }
        }

        //std::cout<<"Finished crossover"<<std::endl;
    }


};

#endif //GENETIC_ALGORITHM_GENETICALGORITHM_H
