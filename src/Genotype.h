//
// Created by dzordzu on 02.01.19.
//

#ifndef GENETIC_ALGORITHM_GENOTYPE_H
#define GENETIC_ALGORITHM_GENOTYPE_H

#include "GeneticAlgorithm/Constants.h"
#include "Utils.h"
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
        explicit Genotype(std::vector<int> genes);
        std::vector<int> getGenesCopy();
        const bool operator==(const Genotype& g) const;
        inline const bool operator!=(const Genotype& g) const {return !(*this == g);}
    };


    class Operation {};

    class Mutation : public Operation {
    protected:
        Genotype result;
        Genotype target;
    public:
        inline Genotype &getResult() {return result;}
        virtual bool mutate() = 0;
        inline void setTarget(const Genotype& target) {this->target = target;}
    };

    class StandardMutation : public Mutation {
    public:
        bool mutate() override {
            std::vector<int> genotype = target.getGenesCopy();
            for(size_t i=0; i<genotype.size(); i++) {
                if(GeneticAlgorithms::Utils::getRandomPercentage() < GeneticAlgorithms::Constants::Probability::MUTATION_SINGLE_GENE)
                    genotype[i] = genotype[i] == 0 ? 1 : 0;
            }
            this->result = Genotype(genotype);
            return true;
        }
    };



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
        void clear() override;
    };



};


namespace GeneticAlgorithms {
    namespace Utils {
        inline static Genotype::Genotype getRandomGenotype(size_t length) {
            std::vector<int> genotype;
            genotype.resize(length);
            for(size_t i=0; i<length; i++) {
                genotype[i] = getRandomBool();
            }
            return Genotype::Genotype(genotype);
        }
    };
};


#endif //GENETIC_ALGORITHM_GENOTYPE_H
