//
// Created by maciej on 09.01.25.
//
#include "Connect4Game.h"
#include "GeneticAlgorithm.h"
#include "GAPopulation.h"
#include "MoveDiscoverer.h"
#include <iomanip>
#include <fstream>
#include <filesystem>

Connect4Game::Connect4Game() : board(BOARD_ROWS, std::vector<char>(BOARD_COLS, ' ')), currentPlayer('X') {}

void Connect4Game::displayBoard() {
    system("clear");
    std::cout<<"   ";
    for (int i = 0; i < BOARD_COLS; i++) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < BOARD_COLS; i++) {
        std::cout << std::setw(2) << i << "|";
        for (int j = 0; j < BOARD_ROWS; j++) {
            std::cout << std::setw(2) << board[i][j] << " |";
        }
        std::cout << std::endl;
    }
}

void Connect4Game::board2txt() {
    std::filesystem::path filepath("../board_debug.txt");
    std::ofstream file(filepath, std::ios::trunc); // Open in append mode
    if (!file) {
        std::cerr << "Error: Unable to open file " << filepath.string() << " for writing.\n";
        return;
    }

    for (const auto& row : board) {
        for (char cell : row) {
            file << "|" << (cell == ' ' ? '.' : cell); // Use '.' for empty spaces for better visibility
        }
        file << "|\n";
    }
    file << std::string(BOARD_COLS * 2 + 1, '-') << "\n"; // Divider line
    file.close();
}

bool Connect4Game::makeMove(int col) {
    if (col < 0 || col >= BOARD_COLS) {
        std::cout<<"Niepoprawny ruch!"<<std::endl;
        return false;
    }
    for (int i = BOARD_ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = currentPlayer;
            return true;
        }
    }
    std::cout<<"Niepoprawny ruch, kolumna jest pełna!"<<std::endl;
    return false;
}

void Connect4Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool Connect4Game::isDraw() {
    for (int i = 0; i < BOARD_COLS; i++) {
        if(board[0][i] == ' ') return false;
    }
    return true;
}

bool Connect4Game::checkWinner(int lastRow, int lastCol) {
    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {0, 1}, {1, 1}, {1, -1}
//     pionowo, poziomo,   przekątne
    };

    for (auto [dr, dc] : directions) {
        int count = 1;

        for (int step = 1; step < WIN_COND; ++step) {
            int r = lastRow + dr * step;
            int c = lastCol + dc * step;
            if (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS && board[r][c] == currentPlayer) {
                count++;
            } else {
                break;
            }
        }
        for (int step = 1; step < WIN_COND; ++step) {
            int r = lastRow - dr * step;
            int c = lastCol - dc * step;
            if (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS && board[r][c] == currentPlayer) {
                count++;
            } else {
                break;
            }
        }
        if (count >= WIN_COND) return true;
    }
    return false;
}

void Connect4Game::play() {
    while(true) {
        displayBoard();
        std::cout <<currentPlayer<<" wykonuje ruch!"<< std::endl;
        int col;
        std::cin >> col;

        if (!makeMove(col)) continue;

        int lastRow = -1;
        for(int i = BOARD_ROWS - 1; i >= 0; i--) {
            if (board[i][col] == currentPlayer) {
                lastRow = i;
                break;
            }
        }

        if (checkWinner(lastRow, col)) {
            displayBoard();
            std::cout<<currentPlayer<<" wygrywa!"<< std::endl;
            break;
        }

        if (isDraw()) {
            displayBoard();
            std::cout<<"Remis!"<<std::endl;
            break;
        }

        switchPlayer();
    }
}

void Connect4Game::playAgainstComputer(GeneticAlgorithm &ga, char computerMarker) {
    bool game_over = false;
    while(!game_over) {
        displayBoard();

        if (currentPlayer == 'X') {
            // Tura gracza
            std::cout<<"Wybierz kolumnę: ";
            int col;
            std::cin >> col;

            if (!makeMove(col)) {
                std::cout<<"Niepoprawny ruch!"<<std::endl;
                continue;
            }
        } else {
            // Tura komputera
            std::cout<<"Następuje myślenie komputera\n"<<std::endl;
            auto fitnessFunction = [this, computerMarker](int col) {
                Connect4Game gameCopy = *this;
                if (gameCopy.makeMove(col)) {
                    //return ga.heuristic_evaluation(gameCopy.board, computerMarker);
                }
                return -1e6;
            };
            int bestCol = 0;
            double bestFitness = -1e6;

            for (int col = 0; col < BOARD_COLS; ++ col) {
                //double fitness = ga.calculate_fitness()
            }
        }
    }
}

void Connect4Game::botVsBot(MoveDiscoverer& md, Individual& bot1, Individual& bot2) {
    int round = 0;
    while (true) {
        Individual& currentBot = (round % 2 == 0) ? bot1 : bot2;
        char opponentMark = currentPlayer == 'X' ? 'O' : 'X';

        auto moves = md.discoverMoves(board, currentPlayer, opponentMark);
        int moveCol = md.getBestMove(moves, currentBot.chromosome);
        makeMove(moveCol);

        board2txt();

        int lastRow = -1;
        for(int i = BOARD_ROWS - 1; i >= 0; i--) {
            if (board[i][moveCol] == currentPlayer) {
                lastRow = i;
                break;
            }
        }

        if (checkWinner(lastRow, moveCol)) {
            currentBot.winCount++;
            break;
        }

        if (isDraw()) {
            bot1.drawCount++;
            bot2.drawCount++;
            break;
        }

        switchPlayer();
        ++round;
    }
}
