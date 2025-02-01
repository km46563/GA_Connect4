#include "GAPopulation.h"

#include<algorithm>
#include<random>
#include <chrono>

#include "GAOperators.h"
#include "MoveDiscoverer.h"
#include "Connect4Game.h"

GAPopulation::GAPopulation(GAConfig &config) : config(config) {}


void GAPopulation::initialize(int pop_sz, int n_cols, int simGameCount, PopInitType init_type) {
	this->simGameCount = simGameCount;
	std::random_device r;
	std::mt19937 rand_engine(r());
	std::uniform_real_distribution<float> dist(0.f, 1.f);

	population.clear();
	population.resize(pop_sz);

	switch ( init_type ) {
		case PopInitType::RANDOM:
			for ( auto &[chromosome, wc, dc, fitness] : population ) {
				fitness = 0.f;
				chromosome.resize(MoveDiscoverer::MOVE_TYPE_COUNT);
				for ( auto &gene : chromosome ) {
					gene = dist(rand_engine);
				}
			}
			break;

		case PopInitType::FLAT:
			const float weight = 1.f / (float) n_cols;
			for ( auto &[chromosome, wc, dc, fitness] : population ) {
				fitness = 0.f;
				chromosome.resize(MoveDiscoverer::MOVE_TYPE_COUNT);
				for ( auto &gene : chromosome ) {
					gene = weight;
				}
			}
			break;
	}
}

// [x] TODO: 1. Simulate one game and save it somewhere
// [x] TODO: 2. Simulate whole population
// [x] TODO: 3. Calculate fitness from simulation stats
// [x] TODO: 4. Implement selection mechanism
// [x] TODO: 5. Implement crossover and mutation operators
// [x] TODO: 6. Implement advancement of the population
void GAPopulation::advancePopulation() {
	auto startTime = std::chrono::high_resolution_clock::now();

	while (true) {
		std::vector<Individual> newPopulation;
		simulateGames();
		calculatePopFitness();
		GAOperators::tournamentSelection(population, config.tournamentSize);
		while (newPopulation.size() < population.size()) {
			Individual parent1 = population[rand() % population.size()];
			Individual parent2 = population[rand() % population.size()];

			auto [child1, child2] = GAOperators::crossover(parent1, parent2);

			GAOperators::mutate(child1, config.mutationRate, config.mutationPower);
			GAOperators::mutate(child2, config.mutationRate, config.mutationPower);

			newPopulation.push_back(child1);
			if (newPopulation.size() < population.size()) {
				newPopulation.push_back(child2);
			}
		}
		population = std::move(newPopulation);

		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = currentTime - startTime;

		if (diff.count() > config.timeLimit) {
			break;
		}
	}
}

void GAPopulation::simulateGames() {
	for ( int i = 0; i < population.size(); ++i ) {
		for ( int j = i + 1; j < population.size(); ++j ) {
			for ( int gameN = 0; gameN < simGameCount; ++gameN ) {
				Connect4Game game;
				if ( gameN % 2 ) {
					game.botVsBot(moveDiscoverer, population.at(i), population.at(j));
				} else {
					game.botVsBot(moveDiscoverer, population.at(j), population.at(i));
				}
			}
		}
	}
}

void GAPopulation::resetPopStats(bool gameStats, bool fitness) {
	for ( auto& individual : population ) {
		if ( gameStats ) {
			individual.winCount = 0;
			individual.drawCount = 0;
		}
		if ( fitness ) {
			individual.fitness = 0;
		}
	}
}

void GAPopulation::calculatePopFitness() {
	for ( auto& individual : population ) {
		individual.fitness = WIN_SCORE * individual.winCount + DRAW_SCORE * individual.drawCount;
	}
}

std::vector<Individual> GAPopulation::getBest(int count) const {
	count = (count > population.size()) ? population.size() : count;
	std::vector<Individual> bestIndividuals(count);
	std::partial_sort_copy(population.begin(), population.begin() + count,
	                       bestIndividuals.begin(), bestIndividuals.end(),
	                       [](const Individual &i1, const Individual &i2) {
		                       return i1.fitness < i2.fitness;
	                       });

	return bestIndividuals;
}

