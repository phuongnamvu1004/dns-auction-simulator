#include <iostream>
#include "auction.hpp"
#include "input_generator.hpp"

using namespace std;

int main() {
    cout << "=== DNS Auction Simulator ===" << endl;

    int num_bidders, num_items, clauses_per_bidder, seed;

    cout << "Enter number of bidders: ";
    cin >> num_bidders;

    cout << "Enter number of items: ";
    cin >> num_items;

    cout << "Enter number of XOS clauses per bidder: ";
    cin >> clauses_per_bidder;

    cout << "Enter random seed: ";
    cin >> seed;

    auto bidders = generateRandomBidders(num_bidders, num_items, clauses_per_bidder, seed);

    DNSAuction auction(num_bidders, num_items, clauses_per_bidder, bidders);
    auction.runSimulation();
    auction.printResults();

    return 0;
}