//
// Created by dzordzu on 02.01.19.
//

#ifndef GENETIC_ALGORITHM_GENOTYPE_H
#define GENETIC_ALGORITHM_GENOTYPE_H

#include <vector>
#include <string>

namespace Genotype {

    /**
     * Immutable genotype
     */
    class Genotype {
    protected:
        std::vector<int> genes;
    public:
        Genotype();
        Genotype(std::vector<int> genes);
        std::vector<int> getGenesCopy();

    };


    class Operation {};

    class Crossover : public Operation {
    protected:
        std::vector<Genotype> result;
    public:
        enum class ParentType {
            DEFAULT,
            PRIMARY,
            SECONDARY
        };
        virtual void addParent(const Genotype &a, ParentType type = ParentType::DEFAULT) = 0;
        virtual void calculate() = 0;
        std::vector<Genotype> getResult();
        virtual void clear() = 0;
    };



};


#endif //GENETIC_ALGORITHM_GENOTYPE_H
