//
// Created by maciej on 09.01.25.
//

#ifndef CONNECT4GAME_H
#define CONNECT4GAME_H

#include<vector>
#include<iostream>
#include "GeneticAlgorithm.h"

class Connect4Game {
public:
    static const int BOARD_ROWS = 8;
    static const int BOARD_COLS = 8;
    static const int WIN_COND = 4;

    std::vector<std::vector<char>> board;
    char currentPlayer;

    bool checkWinner(int last_row, int last_col);
    bool isDraw();
    void displayBoard();
    bool makeMove(int col);
    void switchPlayer();
    void play();
    void playAgainstComputer(GeneticAlgorithm& ga, char computerMarker);
    char getCurrentPlayer() const;
    const std::vector<std::vector<char>>& getBoard() const;
};

#endif //CONNECT4GAME_H
