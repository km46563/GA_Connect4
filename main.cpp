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
	GAConfig config(100, 4, 0.05, 0.5, 60);
	GAPopulation gap(config);
	gap.initialize(50, Connect4Game::BOARD_COLS, 10, PopInitType::RANDOM);
	gap.advancePopulation();
	gap.simulateGames();

	std::cout << "end of sim\n";

	return 0;
}
