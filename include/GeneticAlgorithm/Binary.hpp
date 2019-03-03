//
// Created by dzordzu on 28.02.19.
//

#ifndef GENETIC_ALGORITHM_BINARY_HPP
#define GENETIC_ALGORITHM_BINARY_HPP

#include "Core.hpp"
#include <algorithm>
#include <vector>


namespace GeneticAlgorithm {
    namespace Binary {

        typedef typename std::vector<int> Genotype;
        typedef typename GeneticAlgorithm::Core::Evaluator<Genotype> Evaluator;
        typedef typename GeneticAlgorithm::Core::Individual<Genotype> Individual;
        typedef typename GeneticAlgorithm::Core::Population<Genotype> Population;
        typedef typename GeneticAlgorithm::Core::Algorithm<Genotype> Algorithm;


        namespace Populations {
            class VectorPopulation : public Population {
                std::vector<Individual> population;
            public:
                void add(Genotype i) override;
                void fillRandom(int toSize) override;
                Individual getBest() override;
                Individual &getRandomReference() override;
                Individual removeRandom() override;
                Evaluator *getEvaluatorPointer() override;
            };
        }

        namespace Operations {
            namespace Crossover {
                void standardCrossover(Individual &target, Individual &source);
                void betterOneCrossover(Individual &target, Individual &source, Evaluator *evaluator);
                void firstImprovementCrossover(Individual &target, Individual &source, Evaluator *evaluator);
            }
        }

        namespace Algorithms {

            class SimpleAlgorithm : public Algorithm {
            public:
                SimpleAlgorithm(Population *population, GeneticAlgorithm::Core::Settings *settings);
                void iterate() override;
                Population *getPopulation() override;
                Core::Settings *getSettings() override;
            };

        }





    }
}


#endif //GENETIC_ALGORITHM_BINARY_HPP
