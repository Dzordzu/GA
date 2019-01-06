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
                break;
            case Type::EMPTY:
                mask.clear();
                break;
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

    std::vector<std::pair<size_t, double>> ConnectivityMatrix::getMinimums() {

        typedef std::pair<size_t, double> pair_min;
        std::vector<pair_min> result;

        for (size_t i = 0; i < getSize(); i++) {

            double localMin = std::numeric_limits<double>::max();

            for (size_t j = 0; j < getSize(); j++) {
                if (i == j) continue;
                double minHelper;
                get(i, j, minHelper);
                localMin = std::min(minHelper, localMin);
            }
            result.emplace_back(pair_min(i, localMin));
        }
        std::sort(result.begin(), result.end(), [](pair_min a, pair_min b){
            return a.second == b.second ? a.first < b.first : a.second < b.second;
        });
        return result;
    }

    double Algorithm::reductionFormula(Cluster a, Cluster b) {

        if(a.getMask().size() == 0 || b.getMask().size() == 0 || (a.getMask().size() > 1 && b.getMask().size() > 1))
            return -(std::numeric_limits<double>::max());

        if(b.getMask().size() < a.getMask().size()) std::swap(a, b);

        double result = 0;
        for (int i = 0; i < b.getMask().size(); i++) {
            double helper;
            if(distanceMeasure.get(b.getMask()[i], a.getMask()[0], helper)) result += helper;
            else return -(std::numeric_limits<double>::max());
        }
        return result / b.getMask().size();
    }

    void Algorithm::calculate(std::vector<Genotype::Genotype> &genotypes) {

        dsm = ConnectivityMatrix(genotypes.size());
        distanceMeasure = ConnectivityMatrix(genotypes.size());




    }
};