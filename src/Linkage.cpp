//
// Created by dzordzu on 02.01.19.
//

#include <cmath>
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

    ConnectivityMatrix::ConnectivityMatrix(size_t genesAmountInGenotype, double defaultValue) {
        this->size = genesAmountInGenotype;
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


        size_t genesAmount= genotypes[0].getGenesCopy().size();
        size_t genotypesAmount = genotypes.size();

        dsm = ConnectivityMatrix(genesAmount);
        distanceMeasure = ConnectivityMatrix(genesAmount);



        for (size_t x = 0; x < genesAmount - 1; x++) {
            for (size_t y = 0; y < genesAmount - (x+1); y++) {

                std::array<std::array<size_t, 2>, 2> genesCorrelation = {
                        std::array<size_t, 2> {0, 0},
                        std::array<size_t, 2> {0, 0}
                };

                std::array<size_t, 2> geneXval = {0, 0};
                std::array<size_t, 2> geneYval = {0, 0};

                for (int i = 0; i < genotypesAmount; i++) {

                    int geneX = genotypes[i].getGenesCopy()[x];
                    int geneY = genotypes[i].getGenesCopy()[ y + ( x + 1) ];

                    genesCorrelation[geneX != 0][geneY != 0]++;
                    geneXval[geneX != 0]++;
                    geneYval[geneY != 0]++;
                }


                double cell = 0;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        double numerator = (double) genesCorrelation[i][j] / (double) genotypesAmount;
                        double denominator = ((double) geneXval[i] / (double) genotypesAmount) * ((double) geneYval[j] / (double) genotypesAmount);
                        if (denominator == numerator || numerator == 0) {
                            cell += 0;
                            continue;
                        }
                        //std::cout << "Numerator: " << numerator << ", Denominator: " << denominator << std::endl;
                        double value = (numerator * std::log(numerator / denominator));
                        cell += value;
                    }
                }

                cell = std::max(cell, (double)0);
                dsm.insert(x, y, cell);

                // Here we start calculating distance from DSM
                double H = 0;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        double logarithmArgument = (double)genesCorrelation[i][j] / (double)genotypesAmount;
                        if (logarithmArgument == 0) {
                            H += 0;
                            continue;
                        }
                        H += logarithmArgument * log( logarithmArgument );
                    }
                }
                H = -H;

                if (H == 0) cell = 0;
                else {
                    cell = (H - cell) / H;
                }

                distanceMeasure.insert(x, y, cell);
            }
        }




    }
};