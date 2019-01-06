//
// Created by dzordzu on 02.01.19.
//

/**
 *
 *
 * NOTES:
 *
 ********************************************************
 *				  reduction formula:					*
 *				 D({1, 2, 3, 4}, {6})					*
 *						  =								*
 *														*
 *		 D(1, 6) + D(2, 6) + D(3, 6) + D(4, 6)			*
 *		 -------------------------------------			*
 *			 		 	   4							*
 *														*
 ********************************************************
 *
 *	Simplifies the recurency formula D(K, {L, M}) =
 *		|L| * D(K, L) + |M| * D(K, M)
 *		-----------------------------
 *				  |L| + |M|
 *
 *		=
 *
 *		|L| * D(K, L) + |M| * D(K, M)
 *		-----------------------------
 *				  |{L, M}|
 */


#ifndef GENETIC_ALGORITHM_LINKAGE_H
#define GENETIC_ALGORITHM_LINKAGE_H

#include "Genotype.h"
#include <vector>
#include <utility> // CAREFUL: std::swap belongs here ONLY since C++11. If needed use #include <algorithm>
#include <algorithm>
#include <limits>
#include <map>

namespace Linkage {

    class Cluster {
    private:
        std::vector<size_t> mask;
    public:
        enum class Type {EMPTY, SINGLE, MULTIPLE};
        Cluster();
        explicit Cluster(std::vector<size_t> mask, Type type = Type::MULTIPLE);
        inline std::vector<size_t> getMask() {return this->mask;};

        bool operator==(const Cluster& c) {
            if(mask.size() != c.mask.size()) return false;
            for(int i=0; i<mask.size(); i++) if(c.mask.size() != mask.size()) return false;
            return true;
        }
    };

    // Handles transitive, anti-reflexive relation
    // Data is stored in a triangle, and accessible as in a regular matrix
    class ConnectivityMatrix {
        size_t size;
        std::vector<std::vector<double>> elements;
    public:
        ConnectivityMatrix() = default;
        explicit ConnectivityMatrix(size_t size, double defaultValue = 0);
        bool insert(size_t x, size_t y, double value);
        bool get(size_t x, size_t y, double &result);
        std::vector<std::pair<size_t, double>> getMinimums(); // <row_id, min_value>
        inline size_t getSize() { return size; };
    };

    class Algorithm {

        ConnectivityMatrix dsm;
        ConnectivityMatrix distanceMeasure;
        std::vector<Cluster> result;

        double reductionFormula(Cluster a, Cluster b);

    public:
        void calculate(std::vector<Genotype::Genotype> &genotypes);
        inline std::vector<Linkage::Cluster> getClusters() { return result; };
    };


};

namespace Genotype {
    class LinkageStandardCrossover : public StandardCrossover {};
};


#endif //GENETIC_ALGORITHM_LINKAGE_H
