#ifndef MOVEDISCOVERER_HPP
#define MOVEDISCOVERER_HPP


#include<vector>

enum class MoveType {
	RAND,
	MAKE_2, MAKE_3, MAKE_4,
	DISRUPT_2, DISRUPT_3, DISRUPT_4
};

struct Move {
	int column_num;
	std::vector<MoveType> move_types;
};

class MoveDiscoverer {
private:
	const char emptyField = ' ';

	int placeMark(std::vector<std::vector<char>>& board, int col, char mark);
	void undoMove(std::vector<std::vector<char>>& board, int row, int col);
	int countSequence(const std::vector<std::vector<char>>& board, int row, int col, int dRow, int dCol, char mark);
	bool inBounds(int row, int col, int row_n, int col_n);

public:
	std::vector<Move> discoverMoves(std::vector<std::vector<char>>& board, char player, char opponent);
	int getBestMove(const std::vector<Move> &moves, const std::vector<float>& weights);

	static constexpr int MOVE_TYPE_COUNT = 7;

};


#endif //MOVEDISCOVERER_HPP
