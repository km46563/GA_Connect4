//
// Created by maciej on 01.02.25.
//

#ifndef GACONFIG_H
#define GACONFIG_H



struct GAConfig {
    int tournamentSize;
    float mutationRate;
    float mutationPower;
    double timeLimit;

    GAConfig(int tourSize, float mutRate, float mutPower, double time)
    : tournamentSize(tourSize), mutationRate(mutRate), mutationPower(mutPower), timeLimit(time) {}
};



#endif //GACONFIG_H
