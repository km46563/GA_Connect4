//
// Created by maciej on 01.02.25.
//

#ifndef GACONFIG_H
#define GACONFIG_H



struct GAConfig {
    int populationSize;
    int tournamentSize;
    float mutationRate;
    float mutationPower;
    double timeLimit;

    GAConfig(int popSize, int tourSize, float mutRate, float mutPower, double time)
    : populationSize(popSize), tournamentSize(tourSize),
    mutationRate(mutRate), mutationPower(mutPower), timeLimit(time) {}
};



#endif //GACONFIG_H
