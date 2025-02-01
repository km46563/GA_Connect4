//
// Created by maciej on 01.02.25.
//

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

struct Individual {
    std::vector<float> chromosome;
    int winCount;
    int drawCount;
    float fitness;
};


#endif //INDIVIDUAL_H
