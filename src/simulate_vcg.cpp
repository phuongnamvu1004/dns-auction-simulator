// simulate_vcg.cpp: Brute-force VCG simulator for small m (with winners column)

#include "input_generator.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

void generateAllSubsets(int m, std::vector<std::vector<int>>& subsets) {
    int total = 1 << m;
    for (int mask = 0; mask < total; ++mask) {
        std::vector<int> subset;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) subset.push_back(i);
        }
        subsets.push_back(subset);
    }
}

// Compute value of a bundle for a bidder (XOS max over clauses)
double valueOfBundle(const Bidder& b, int clauses, const std::vector<int>& bundle) {
    double max_val = 0;
    for (int k = 0; k < clauses; ++k) {
        double sum = 0;
        for (int item : bundle) {
            std::string key = "clause" + std::to_string(k) + "_Item" + std::to_string(item);
            auto it = b.itemValues.find(key);
            if (it != b.itemValues.end()) sum += it->second;
        }
        max_val = std::max(max_val, sum);
    }
    return max_val;
}

int main() {
    int num_bidders = 5;
    int num_items = 6;
    int clauses = 4;
    int num_runs = 30;
    int base_seed = 100;
    cout << "=== VCG Brute-force Simulator ===\n";
    cout << "Number of bidders: " << num_bidders << "\n";
    cout << "Number of items: " << num_items << "\n";
    cout << "Number of clauses per bidder: " << clauses << "\n";
    cout << "Number of runs: " << num_runs << "\n";
    cout << "Base seed: " << base_seed << "\n";
    cout << "Generating random bidders...\n";

    std::ofstream file("results_vcg.csv");
    file << "seed,num_bidders,num_items,num_clauses,total_welfare,winners\n";

    for (int run = 0; run < num_runs; ++run) {
        int seed = base_seed + run;
        auto bidders = generateRandomBidders(num_bidders, num_items, clauses, seed);

        std::vector<std::vector<int>> all_subsets;
        generateAllSubsets(num_items, all_subsets);

        double best_welfare = 0;
        std::vector<std::vector<int>> best_allocation(num_bidders);

        for (const auto& perm : all_subsets) {
            std::vector<bool> used(num_items, false);
            std::vector<std::vector<int>> allocation(num_bidders);
            double total = 0;

            for (int i = 0; i < num_bidders; ++i) {
                double max_val = 0;
                std::vector<int> best_bundle;
                for (const auto& bundle : all_subsets) {
                    bool valid = true;
                    for (int item : bundle) if (used[item]) valid = false;
                    if (!valid) continue;
                    double val = valueOfBundle(bidders[i], clauses, bundle);
                    if (val > max_val) {
                        max_val = val;
                        best_bundle = bundle;
                    }
                }
                total += max_val;
                allocation[i] = best_bundle;
                for (int item : best_bundle) used[item] = true;
            }

            if (total > best_welfare) {
                best_welfare = total;
                best_allocation = allocation;
            }
        }

        // Count winners
        int winners = 0;
        for (int i = 0; i < num_bidders; ++i) {
            double val = valueOfBundle(bidders[i], clauses, best_allocation[i]);
            if (val > 0) winners++;
        }

        file << seed << "," << num_bidders << "," << num_items << "," << clauses << ","
             << best_welfare << "," << winners << "\n";
    }

    std::cout << "Completed VCG brute-force simulations.\n";
    return 0;
}
