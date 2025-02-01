#include "Connect4Game.cpp"
#include "GAPopulation.cpp"
#include "MoveDiscoverer.cpp"


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
	gap.initialize(50, Connect4Game::BOARD_COLS, 10, PopInitType::RANDOM);
	gap.advancePopulation(60);
	gap.simulateGames();

	std::cout << "end of sim\n";

	return 0;
}
