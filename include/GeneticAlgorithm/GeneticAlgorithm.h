//
// Created by dzordzu on 02.01.19.
//

#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_H
#define GENETIC_ALGORITHM_GENETICALGORITHM_H

#include "Constants.h"
#include "Genotype.h"
#include "Linkage.h"
#include "Utils.h"

namespace GeneticAlgorithms {

    class Individual {
    protected:
        Genotype::Genotype genotype;
    public:
        virtual double getFitness() = 0;
    };

    class GABase {
    protected:
        double fitness;
        Individual * individual;
    public:
        virtual bool iterate() = 0;
        virtual bool populate() = 0;
        virtual bool getClusters(std::vector<Linkage::Cluster> clusters) = 0;
        virtual bool getIndividual(Individual &individual) = 0;
    };


    template<typename SIZE>
    class FixedSizeGA : public GABase{

    };


};

#endif //GENETIC_ALGORITHM_GENETICALGORITHM_H
