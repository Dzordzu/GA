//
// Created by dzordzu on 02.01.19.
//

#include "Genotype.h"

namespace Genotype {
    Genotype::Genotype() {
        this->genes = std::vector<int>();
    }

    Genotype::Genotype(std::vector<int> genes) {
        this->genes = genes;
    }

    std::vector<int> Genotype::getGenesCopy() {
        return genes;
    }

    std::vector<Genotype> Crossover::getResult() {
        return result;
    }


    StandardCrossover::StandardCrossover() {
        std::pair<Genotype, bool> falsy(Genotype(), false);
        for(int i=0; i<parents.size(); i++) parents[i] = falsy;
    }

    void StandardCrossover::addParent(const Genotype & a, ParentType type) {
        std::pair<Genotype, bool> toAdd(a, true);
        if (type == ParentType::PRIMARY) parents[0] = toAdd;
        else if (type == ParentType::SECONDARY) parents[1] = toAdd;
        else {
            parents[insertIndex] = toAdd;
            insertIndex = insertIndex == 0 ? 1 : 0;
        }
    }

    bool StandardCrossover::calculate() {

        std::array<std::vector<int>, 2> parentGenotypes;

        for(int i=0;i<parents.size(); i++) {
            if(!parents[i].second) return false;
            parents[i].first.getGenesCopy();
        }


        std::array<std::vector<int>, 2> childrenGenotypes;

        for (int i = 0; i < 2; i++) {

            std::copy(
                    parentGenotypes[i].begin(),
                    parentGenotypes[i].begin() + (parentGenotypes[i].size()/2),
                    std::back_inserter(childrenGenotypes[i])
            );

            std::copy(
                    parentGenotypes[(i + 1) % 2].begin() + (parentGenotypes[i].size() / 2),
                    parentGenotypes[(i + 1) % 2].end(),
                    std::back_inserter(childrenGenotypes[i])
            );
        }

        this->result.clear();
        this->result.resize(2);
        for (int i = 0; i < 2; i++)
            this->result[i] = Genotype(childrenGenotypes[i]);

        return true;
    }

    void StandardCrossover::clear() {
        this->result.clear();
        for(int i=0; i<parents.size(); i++) parents[i].second = false;
    }


}
