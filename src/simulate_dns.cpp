#include "auction.hpp"
#include "input_generator.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int num_bidders = 5;
    int num_items = 6;
    int clauses_per_bidder = 4;
    int num_runs = 30;
    int base_seed = 100;
    cout << "=== DNS Auction Simulator ===\n";
    cout << "Number of bidders: " << num_bidders << "\n";
    cout << "Number of items: " << num_items << "\n";
    cout << "Number of clauses per bidder: " << clauses_per_bidder << "\n";
    cout << "Number of runs: " << num_runs << "\n";
    cout << "Base seed: " << base_seed << "\n";
    cout << "Generating random bidders...\n";

    ofstream file("results_dns.csv");
    file << "seed,num_bidders,num_items,num_clauses,total_welfare,winners\n";

    for (int i = 0; i < num_runs; ++i) {
        int seed = base_seed + i; // unique seed per run
        auto bidders = generateRandomBidders(num_bidders, num_items, clauses_per_bidder, seed);

        DNSAuction auction(num_bidders, num_items, clauses_per_bidder, seed, bidders);
        auction.runSimulation();

        // Capture welfare and winner count
        double total_value = 0;
        int winners = 0;
        for (int b = 0; b < num_bidders; ++b) {
            double val = auction.evaluateXOS(b, auction.getBundle(b));
            total_value += val;
            if (val > 0) winners++;
        }

        file << seed << "," << num_bidders << "," << num_items << "," << clauses_per_bidder
             << "," << total_value << "," << winners << "\n";
    }

    cout << "Completed " << num_runs << " DNS simulations.\n";
    return 0;
}