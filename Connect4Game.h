//
// Created by maciej on 09.01.25.
//

#ifndef CONNECT4GAME_H
#define CONNECT4GAME_H

#include<vector>
#include<iostream>
#include "GAPopulation.h"

class Connect4Game {
public:
    static const int BOARD_ROWS = 8;
    static const int BOARD_COLS = 8;
    static const int WIN_COND = 4;

    std::vector<std::vector<char>> board;
    char currentPlayer;

    bool checkWinner(int last_row, int last_col);
    bool isDraw();

    Connect4Game();

    void displayBoard();
    void board2txt();
    bool makeMove(int col);
    void switchPlayer();
    void play();
    void playAgainstComputer(int pop_sz, int n_cols, int simGameCount, ChromosomeInitType init_type);
    char getCurrentPlayer() const;

    void botVsBot(MoveDiscoverer& md, Individual& bot1, Individual& bot2);

    const std::vector<std::vector<char>>& getBoard() const;
};

#endif //CONNECT4GAME_H
