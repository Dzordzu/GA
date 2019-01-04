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

    ConnectivityMatrix::ConnectivityMatrix(size_t size, double defaultValue) {
        this->size = size;
        elements.resize(size-1);
        for(size_t i=0; i<size-1; i++) {
            elements[i] = std::vector<double>(size-1-i, defaultValue);
        }
    }

    bool ConnectivityMatrix::insert(size_t x, size_t y, double value) {
        if(x == y || x > size || y > size) return false;
        if (y < x) std::swap(x, y);
        elements[x][y-(x+1)] = value;
        return true;
    }

    bool ConnectivityMatrix::get(size_t x, size_t y, double &result) {
        if (x == y || x>this->size || y>this->size) return false;
        if (y < x) std::swap(x, y);
        result = elements[x][y-(x+1)];
        return true;
    }
};