//
// Created by maciej on 13.01.25.
//

#include "GeneticAlgorithm.h"
#include "Connect4Game.h"
#include<algorithm>
#include<iostream>
#include<vector>

double GeneticAlgorithm::heuristic_evaluation(const std::vector<std::vector<int>>& board, char player) const {
    int score = 0;
    char opponent = 'O';
    if (player == 'O') {
        opponent = 'X';
    }

    const std::vector<std::pair<int, int>> directions{
        {1, 0}, {0, 1}, {1, 1}, {1, -1}
    };

    for (int r = 0; r < Connect4Game::BOARD_ROWS; r++) {
        for (int c = 0; c < Connect4Game::BOARD_COLS; c++) {
            if (board[r][c] == 0) {
                continue;
            }

            char current_marker = board[r][c];

            for (auto [dr, dc] : directions) {
                int count = 1;
                int empty = 0;

                for (int i = 1; i < Connect4Game::WIN_COND; i++) {
                    int nr = r + dr * i;
                    int nc = c + dc * i;
                    if (nr >= 0 && nr < Connect4Game::BOARD_ROWS && nc >= 0 && nc < Connect4Game::BOARD_COLS) {
                        if (board[nr][nc] == current_marker) {
                            count++;
                        }
                        else if (board[nr][nc] == 0) {
                            empty++;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                if (current_marker == player) {
                    if (count >= Connect4Game::WIN_COND) {
                        score += 1000;
                    }
                    else {
                        score += count * count + empty;
                    }
                }

                if (current_marker == opponent) {
                    if (count >= Connect4Game::WIN_COND - 1 && empty > 0) {
                        score -= 500;
                    }
                    else {
                        score -= count * count;
                    }
                }
            }
        }
    }
    return score;
}

bool GeneticAlgorithm::make_move(std::vector<std::vector<int>>& board, int column, char player) const {
    for (int row = Connect4Game::BOARD_ROWS - 1; row >= 0; row--) {
        if (board[row][column] == 0) {
            board[row][column] = player;
            return true;
        }
    }
    return false;
}

double GeneticAlgorithm::evaluate_fitness(std::vector<std::vector<int>> board, const std::vector<int>& moves, char player) const {
    double fitness = 0;
    char current_player = player;
    char opponent = 'O';
    if (player == 'O') {
        opponent = 'X';
    }

    for (int move : moves) {
        if (!make_move(board, move, player)) {
            break;
        }
        if (current_player == computer_marker) {
            fitness += heuristic_evaluation(board, player);
        }
        else {
            fitness -= heuristic_evaluation(board, opponent);
        }

        if (current_player == computer_marker) {
            current_player =player_marker;
        }
        else {
            current_player = computer_marker;
        }
    }
    return fitness;
}

