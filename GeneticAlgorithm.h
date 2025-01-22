//
// Created by maciej on 13.01.25.
//

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include<functional>

class GeneticAlgorithm {
private:
    int depth = 10;
    int pop_size = 150;
    int eval = 250000;
    float px = 0.7;
    float pm = 0.02;
    int tour = 5;
    char computer_marker = 'X';

public:
    double heuristic_evaluation(const std::vector<std::vector<int>>& board);
    bool make_move(std::vector<std::vector<int>>& board, int column);
};



#endif //GENETICALGORITHM_H
