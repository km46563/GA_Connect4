//
// Created by maciej on 13.01.25.
//

#include "GeneticAlgorithm.h"
#include "Connect4Game.h"
#include<algorithm>
#include<iostream>
#include<vector>

double GeneticAlgorithm::heuristic_evaluation(const std::vector<std::vector<int>>& board) {
    int score = 0;

    const std::vector<std::pair<int, int>> directions{
        {1, 0}, {0, 1}, {1, 1}, {1, -1}
    };

    for (int r = 0; r < Connect4Game::BOARD_ROWS; r++) {
        for (int c = 0; c < Connect4Game::BOARD_COLS; c++) {
            if (board[r][c] != computer_marker) {
                continue;
            }

            for (auto [dr, dc] : directions) {
                int count = 1;

                for (int i = 1; i < Connect4Game::WIN_COND; i++) {
                    int nr = r + dr * i;
                    int nc = c + dc * i;
                    if (nr >= 0 && nr < Connect4Game::BOARD_ROWS && nc >= 0 && nc < Connect4Game::BOARD_COLS && board[nr][nc] == computer_marker) {
                        count++;
                    } else {
                        break;
                    }
                }

                if (score + count >= Connect4Game::WIN_COND) {
                    score += 1000;
                }
                else {
                    score += count * count;
                }
            }
        }
    }
    return score;
}

bool GeneticAlgorithm::make_move(std::vector<std::vector<int>>& board, int column) {
    for (int row = Connect4Game::BOARD_ROWS - 1; row >= 0; row--) {
        if (board[row][column] == 0) {
            board[row][column] = computer_marker;
            return true;
        }
    }
    return false;
}

