//
// Created by maciej on 01.02.25.
//

#include<vector>
#include "Individual.h"

#ifndef GAOPERATORS_H
#define GAOPERATORS_H



class GAOperators {
public:
    static void tournamentSelection(std::vector<Individual>& population, int tournamentSize);
    static std::pair<Individual, Individual> crossover(Individual& parent1, Individual& parent2);
    static void mutate(Individual& individual, float mutationRate, float mutationPower);
};

#endif //GAOPERATORS_H
