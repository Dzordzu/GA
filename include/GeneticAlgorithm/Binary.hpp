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

        class Generator {
        public:
            inline static Generator &getInstance() {
                static Generator generator;
                return generator;
            }
        private:
            Generator() {};
            Generator(Generator const&);
            void operator=(Generator const&);
        public:
            bool generateRandomBool(); //C++98 Features
            Genotype generateRandomGenotype(int genotypeLength);
            int generateRandomIndex(int end); //C++98 Features
            double generateRandomProbability(); //C++98 Features
        };


        namespace Populations {
            class VectorPopulation : public Population {
                Individual best;
                std::vector<Individual> population;
            public:
                inline explicit VectorPopulation(Evaluator *evaluator) { this->getBest().zeroFitness(); this->evaluator = evaluator;};
                void add(Genotype i) override;
                void fillWithRandom(int toSize) override; //C++11 should have better implementation
                Individual getBest() override;
                Individual *getRandomPointer() override;
                void resize(int toSize) override;
                int getPopulationSize() override;
                bool checkQuality(Genotype &genotype) override;
            };
        }

        namespace Operations {

            typedef typename std::vector<int> Mask;

            namespace Crossover {
                void standardCrossover(Individual &target, Individual &source, Mask &mask);
                //void betterOneCrossover(Individual &target, Individual &source, Evaluator *evaluator, Mask &mask);
                //void firstImprovementCrossover(Individual &target, Individual &source, Evaluator *evaluator, Mask &mask);
            }
        }

        namespace Algorithms {

            class SimpleAlgorithm : public Algorithm {
            protected:
                Operations::Mask mask;
                void mutate();
            public:
                SimpleAlgorithm(Population *population, GeneticAlgorithm::Core::Settings *settings);
                void iterate() override;
                void setMask(Operations::Mask mask);
            };

        }





    }
}


#endif //GENETIC_ALGORITHM_BINARY_HPP
