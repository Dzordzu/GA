//
// Created by dzordzu on 02.01.19.
//

#ifndef GENETIC_ALGORITHM_GENOTYPE_H
#define GENETIC_ALGORITHM_GENOTYPE_H

#include <vector>
#include <array>
#include <utility>
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
            SECONDARY,
            ORDERED
        };
        virtual void addParent(const Genotype &a, ParentType type) = 0;
        virtual bool calculate() = 0;
        virtual std::vector<Genotype> getResult();
        virtual void clear() = 0;
    };

    class StandardCrossover : public Crossover {
    protected:
        std::array<std::pair<Genotype, bool>, 2> parents;
        uint_fast16_t insertIndex = 0; // Should be changed only in addParent
    public:
        StandardCrossover();
        void addParent(const Genotype &a, ParentType type = ParentType::DEFAULT) final;
        bool calculate() override;
        void clear();
    };



};


#endif //GENETIC_ALGORITHM_GENOTYPE_H
