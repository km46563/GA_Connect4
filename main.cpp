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
	GAConfig config(5, 4, 0.05, 0.5, 20, FitnessCalcType::VS_TEST_BOTS, 20);
	GAPopulation gap(config);
	gap.initialize(5, Connect4Game::BOARD_COLS, ChromosomeInitType::RANDOM, ChromosomeInitType::RANDOM);
	gap.advancePopulation();
	gap.plotDrawer();
	gap.simulateGames();

	std::cout << "end of sim\n";

	return 0;
}
