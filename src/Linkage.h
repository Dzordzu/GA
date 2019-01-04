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
#include <utility>

namespace Linkage {

    class Cluster {
    private:
        std::vector<size_t> mask;
    public:
        enum class Type {EMPTY, SINGLE, MULTIPLE};
        Cluster();
        explicit Cluster(std::vector<size_t> mask, Type type = Type::MULTIPLE);
        inline std::vector<size_t> getMask() {return this->mask;};
    };

    class Matrix {
        size_t size;
        std::vector<std::vector<double>> elements;
    public:
        explicit Matrix(size_t size, double defaultValue = 0);
        bool insert(size_t x, size_t y, double value);
        double get(size_t x, size_t y);
        std::vector<std::pair<size_t, double>> getMinimums(); // <row_id, min_value>
        size_t getSize();
    };
    class Tree;
    class Algorithm;


};

namespace Genotype {
    class LinkageStandardCrossover : public StandardCrossover {};
};


#endif //GENETIC_ALGORITHM_LINKAGE_H
