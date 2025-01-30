#include "GAPopulation.h"

#include<algorithm>
#include<random>

#include "MoveDiscoverer.h"
#include "Connect4Game.h"

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
	std::vector<Individual> newPopulation;
	tournamentSelection(5);
	while (newPopulation.size() < population.size()) {
		Individual parent1 = population[rand() % population.size()];
		Individual parent2 = population[rand() % population.size()];
		crossover(parent1, parent2);

		mutate(parent1, 0.05f, 0.1f);
		mutate(parent2, 0.05f, 0.1f);

		newPopulation.push_back(parent1);
		newPopulation.push_back(parent2);
	}
	population = newPopulation;
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

void GAPopulation::tournamentSelection(int tournamentSize) {
	std::vector<Individual> newPopulation;
	std::random_device rd;
	std::mt19937 rand_engine(rd());

	while (newPopulation.size() < population.size()) {
		std::vector<Individual> tournament;
		std::sample(population.begin(), population.end(), std::back_inserter(tournament),tournamentSize, rand_engine);

		auto best = std::max_element(tournament.begin(), tournament.end(),
									[](const Individual &a, const Individual &b) {
										return a.fitness < b.fitness;
									});

		newPopulation.push_back(*best);
	}
	population = std::move(newPopulation);
}

void GAPopulation::crossover(Individual &parent1, Individual &parent2) {
	std::random_device rd;
	std::mt19937 rand_engine(rd());

	int size = parent1.chromosome.size();
	std::uniform_int_distribution<int> distribution(0, size - 1);

	int start = distribution(rand_engine);
	int end = distribution(rand_engine);

	if (start > end) {
		std::swap(start, end);
	}

	Individual child1 = parent1;
	Individual child2 = parent2;

	for (int i = start; i < end; ++i) {
		std::swap(child1.chromosome[i], child2.chromosome[i]);
	}

	population.push_back(child1);
	population.push_back(child2);
}

void GAPopulation::mutate(Individual &individual, float mutationRate, float mutationPower) {
	std::random_device rd;
	std::mt19937 rand_engine(rd());
	std::uniform_int_distribution<int> mutationChance(0.f, 1.f);
	std::uniform_int_distribution<int> mutationAmount(-mutationPower, mutationPower);

	for (auto &gene : individual.chromosome) {
		if (mutationChance(rand_engine) < mutationRate) {
			gene += mutationPower(rand_engine);
			gene = std::clamp(gene, 0.f, 1.f);
		}
	}
}
