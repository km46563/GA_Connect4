//
// Created by maciej on 01.02.25.
//

#ifndef GACONFIG_H
#define GACONFIG_H


enum class FitnessCalcType {
    VS_POPULATION,
    VS_TEST_BOTS
};

struct GAConfig {
    int populationSize;
    int tournamentSize;
    float mutationRate;
    float mutationPower;
    double timeLimit;

    FitnessCalcType fcType;
    int battleRepeatN;

    GAConfig(int popSize, int tourSize, float mutRate, float mutPower, double time, FitnessCalcType fcType, int battleRepeatN)
        : populationSize(popSize), tournamentSize(tourSize),
          mutationRate(mutRate), mutationPower(mutPower), timeLimit(time),
          fcType(fcType), battleRepeatN(battleRepeatN) {}
};



#endif //GACONFIG_H
