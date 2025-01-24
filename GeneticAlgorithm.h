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
    char player_marker = 'O';
    std::vector<std::vector<int>> board;

public:
    double heuristic_evaluation(const std::vector<std::vector<int>>& board, char player) const;
    bool make_move(std::vector<std::vector<int>>& board, int column, char player) const;
    double evaluate_fitness(std::vector<std::vector<int>> board, const std::vector<int>& moves, char player) const;
};



#endif //GENETICALGORITHM_H
