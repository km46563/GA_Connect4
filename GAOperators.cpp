//
// Created by maciej on 01.02.25.
//

#include "GAOperators.h"
#include "Individual.h"
#include <random>
#include <algorithm>

void GAOperators::tournamentSelection(std::vector<Individual>& population, int tournamentSize) {
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

std::pair<Individual, Individual> GAOperators::crossover(Individual& parent1, Individual& parent2) {
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

    return {child1, child2};
}

void GAOperators::mutate(Individual& individual, float mutationRate, float mutationPower) {
    std::random_device rd;
    std::mt19937 rand_engine(rd());
    std::uniform_real_distribution<float> mutationChance(0.f, 1.f);
    std::uniform_real_distribution<float> mutationAmount(-mutationPower, mutationPower);

    for (auto &gene : individual.chromosome) {
        if (mutationChance(rand_engine) < mutationRate) {
            gene += mutationAmount(rand_engine);
            gene = std::clamp(gene, 0.f, 1.f);
        }
    }
}
