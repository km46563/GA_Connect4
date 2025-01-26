#include "Connect4Game.h"
#include "GAPopulation.h"
#include "MoveDiscoverer.h"


int main() {
	Connect4Game game;
	// game.play();
	// GAPopulation gap;
	// gap.initialize(20, 8, PopInitType::FLAT);

	// std::vector<std::vector<char> > board = {
	// 	{' ', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
	// 	{' ', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
	// 	{' ', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
	// 	{' ', ' ', ' ', 'X', ' ', ' ', ' ', ' '},
	// 	{' ', ' ', 'X', 'X', ' ', ' ', ' ', ' '},
	// 	{'X', 'O', 'X', 'O', ' ', ' ', ' ', ' '}
	// };

	// MoveDiscoverer md;
	GAPopulation gap;
	gap.initialize(10, 20, Connect4Game::BOARD_COLS, PopInitType::RANDOM);
	gap.simulateGames();

	std::cout << "end of sim\n";

	return 0;
}
