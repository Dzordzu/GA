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

}
