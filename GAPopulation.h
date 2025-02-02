#ifndef GAPOPULATION_HPP
#define GAPOPULATION_HPP


#include<vector>
#include<iostream>
#include "GAConfig.h"
#include "MoveDiscoverer.h"
#include "Individual.h"
#include "GAOperators.h"

// [random_move, make_row_2, make_row_3, make_row_4, disrupt_2, disrupt_3, disrupt_4]
// [0.0, 1.0]

enum class PopInitType {
	RANDOM,
	FLAT
};

class GAPopulation {
private:
	MoveDiscoverer moveDiscoverer;
	std::vector<Individual> population;
	GAConfig config;
	int simGameCount;

	std::vector<double> bestFitnesses;
	std::vector<double> avgFitnesses;
	std::vector<double> worstFitnesses;

	void resetPopStats(bool gameStats = true, bool fitness = true);
	void calculatePopFitness();
	int getBestMove(const std::vector<Move>& moves);

public:
	GAPopulation(GAConfig& config);
	void initialize(int pop_sz, int n_cols, int simGameCount, PopInitType init_type);
	void advancePopulation();
	void simulateGames();
	std::vector<Individual> getBest(int count) const;

	void plotDrawer() const;

	static constexpr int WIN_SCORE = 100;
	static constexpr int DRAW_SCORE = 20;

};


#endif //GAPOPULATION_HPP
