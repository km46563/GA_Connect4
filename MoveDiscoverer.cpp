#include "MoveDiscoverer.h"
#include "Connect4Game.h"
#include <algorithm>

int MoveDiscoverer::placeMark(std::vector<std::vector<char> > &board, int col, char mark) {
	for ( int row = board.size() - 1; row >= 0; --row ) {
		if ( board[row][col] == emptyField ) {
			board[row][col] = mark;
			return row;
		}
	}

	return -1;
}

void MoveDiscoverer::undoMove(std::vector<std::vector<char> > &board, int row, int col) {
	board[row][col] = emptyField;
}

int MoveDiscoverer::countSequence(const std::vector<std::vector<char> > &board, int row, int col, int dRow, int dCol,
                                  char mark) {
	int count = 0;
	for ( int i = 0; i < 4; ++i ) {
		int nextRow = row + i * dRow;
		int nextCol = col + i * dCol;
		if ( inBounds(nextRow, nextCol, board.size(), board[0].size()) && board[nextRow][nextCol] == mark ) {
			++count;
		} else {
			break;
		}
	}
	return count;
}

bool MoveDiscoverer::inBounds(int row, int col, int row_n, int col_n) {
	return row >= 0 && row < row_n && col >= 0 && col < col_n;
}

std::vector<Move> MoveDiscoverer::discoverMoves(std::vector<std::vector<char> > &board, char player, char opponent) {
	std::vector<Move> moves;

	int cols = Connect4Game::BOARD_COLS;

	for ( int col = 0; col < cols; ++col ) {
		std::vector<MoveType> colMoves;
		if ( board[0][col] != emptyField ) continue;

		for ( int dRow = -1; dRow <= 1; ++dRow ) {
			for ( int dCol = -1; dCol <= 1; ++dCol ) {
				if ( dRow == 0 && dCol == 0 ) continue;

				int row = placeMark(board, col, opponent);
				int opponentCount = countSequence(board, row, col, dRow, dCol, opponent);
				if ( opponentCount == 2 ) colMoves.push_back(MoveType::DISRUPT_2);
				if ( opponentCount == 3 ) colMoves.push_back(MoveType::DISRUPT_3);
				if ( opponentCount == 4 ) colMoves.push_back(MoveType::DISRUPT_4);

				undoMove(board, row, col);

				row = placeMark(board, col, player);
				int botCount = countSequence(board, row, col, dRow, dCol, player);
				if ( botCount == 2 ) colMoves.push_back(MoveType::MAKE_2);
				if ( botCount == 3 ) colMoves.push_back(MoveType::MAKE_3);
				if ( botCount == 4 ) colMoves.push_back(MoveType::MAKE_4);

				undoMove(board, row, col);
			}
		}

		if ( colMoves.empty() ) {
			moves.push_back({col, std::vector {MoveType::RAND}});
		} else {
			moves.push_back({col, colMoves});
		}
	}

	return moves;
}

int MoveDiscoverer::getBestMove(const std::vector<Move> &moves, const std::vector<float> &weights) {
	std::vector<float> scores(Connect4Game::BOARD_COLS);
	for ( auto &move : moves ) {

		for ( auto &mt : move.move_types ) {
			switch ( mt ) {
				case MoveType::RAND:
					scores.at(move.column_num) += 10 * weights.at(0);
					break;
				case MoveType::MAKE_2:
					scores.at(move.column_num) += 20 * weights.at(1);
					break;
				case MoveType::MAKE_3:
					scores.at(move.column_num) += 40 * weights.at(2);
					break;
				case MoveType::MAKE_4:
					scores.at(move.column_num) += 80 * weights.at(3);
					break;
				case MoveType::DISRUPT_2:
					scores.at(move.column_num) += 20 * weights.at(4);
					break;
				case MoveType::DISRUPT_3:
					scores.at(move.column_num) += 40 * weights.at(5);
					break;
				case MoveType::DISRUPT_4:
					scores.at(move.column_num) += 80 * weights.at(6);
					break;
			}
		}
	}

	int bestMoveCol = (int) std::distance(
	                                      scores.begin(),
	                                      std::max_element(scores.begin(), scores.end())
	                                     );
	bestMoveCol += Connect4Game::BOARD_COLS - scores.size();

	return bestMoveCol;
}
