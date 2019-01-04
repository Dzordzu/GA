//
// Created by dzordzu on 02.01.19.
//

#include "Linkage.h"

namespace Linkage {
    Cluster::Cluster() = default;
    Cluster::Cluster(std::vector<size_t> mask, Type type) {
        switch(type) {
            case Type::SINGLE:
                mask.erase(mask.begin() + 1, mask.end());
                mask.resize(1);
                mask.reserve(1);
            case Type::EMPTY:
                mask.clear();
            default:
                break;
        }

        this->mask = mask;
    }
};