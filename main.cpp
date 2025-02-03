#include "Connect4Game.h"
#include "GAPopulation.h"

int main() {
	Connect4Game game;
	// game.play();

	GAConfig config(20, 3, 0.05, 0.5, 60 * 5, FitnessCalcType::VS_TEST_BOTS, 20);
	GAPopulation gap(config);
	gap.toggleCSVLogging("weight_results/pop_vs_random_bots.csv");
	gap.initialize(Connect4Game::BOARD_COLS, ChromosomeInitType::RANDOM, ChromosomeInitType::RANDOM);
	gap.advancePopulation();
	gap.plotDrawer();
	gap.simulateGames();

	std::cout << "end of sim\n";

	return 0;
}
