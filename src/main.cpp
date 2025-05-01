#include <iostream>
#include "auction.hpp"

int main() {
    std::cout << "=== DNS Auction Simulator ===" << std::endl;

    // Example setup: 4 bidders, 5 items
    int num_bidders = 4;
    int num_items = 5;

    DNSAuction auction(num_bidders, num_items);
    auction.runSimulation();

    auction.printResults();
    return 0;
}
