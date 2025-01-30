#ifndef GAPOPULATION_HPP
#define GAPOPULATION_HPP


#include<vector>

#include "MoveDiscoverer.h"

// [random_move, make_row_2, make_row_3, make_row_4, disrupt_2, disrupt_3, disrupt_4]
// [0.0, 1.0]
struct Individual {
	std::vector<float> chromosome;
	int winCount;
	int drawCount;
	float fitness;
};

enum class PopInitType {
	RANDOM,
	FLAT
};

class GAPopulation {
private:
	MoveDiscoverer moveDiscoverer;
	std::vector<Individual> population;
	int simGameCount;

	void resetPopStats(bool gameStats = true, bool fitness = true);
	void calculatePopFitness();
	void tournamentSelection(int tournamentSize);
	void crossoverPMX(Individual &parent1, Individual &parent2);
	void mutate(Individual &individual, float mutationRate, float mutationPower);
	int getBestMove(const std::vector<Move>& moves);

public:
	void initialize(int pop_sz, int n_cols, int simGameCount, PopInitType init_type);
	void advancePopulation();
	void simulateGames();
	std::vector<Individual> getBest(int count) const;

	static constexpr int WIN_SCORE = 100;
	static constexpr int DRAW_SCORE = 20;

};


#endif //GAPOPULATION_HPP
