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

namespace Linkage {

    class Cluster {
        std::vector<size_t> mask;
    public:

        enum class Type {
            EMPTY,
            SINGLE,
            MULTIPLE
        };

        Cluster();
        Cluster(std::vector<size_t> mask);
        std::vector<size_t> getMask();
    };

    class Matrix;
    class Tree;
    class Algorithm;


};

namespace Genotype {
    class LinkageStandardCrossover : public StandardCrossover {};
};


#endif //GENETIC_ALGORITHM_LINKAGE_H
