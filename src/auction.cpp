#include "auction.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

DNSAuction::DNSAuction(int bidders, int items)
    : n_bidders(bidders), m_items(items) {
    generateSubmodularValuations();
}

void DNSAuction::generateSubmodularValuations() {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    valuations.resize(n_bidders, std::vector<double>(m_items));
    for (int i = 0; i < n_bidders; ++i) {
        double marginal = dist(gen);
        for (int j = 0; j < m_items; ++j) {
            valuations[i][j] = marginal;
            marginal *= 0.8;  // diminishing returns
        }
    }
}

void DNSAuction::randomPartition(std::vector<int>& pricingGroup, std::vector<int>& allocationGroup) {
    std::vector<int> all_bidders(n_bidders);
    std::iota(all_bidders.begin(), all_bidders.end(), 0);

    std::shuffle(all_bidders.begin(), all_bidders.end(), std::default_random_engine{});
    int half = n_bidders / 2;
    pricingGroup.assign(all_bidders.begin(), all_bidders.begin() + half);
    allocationGroup.assign(all_bidders.begin() + half, all_bidders.end());
}

std::vector<double> DNSAuction::computeItemPrices(const std::vector<int>& pricingGroup) {
    std::vector<double> prices(m_items, 0.0);
    for (int item = 0; item < m_items; ++item) {
        for (int b : pricingGroup) {
            prices[item] += valuations[b][item];
        }
        prices[item] /= pricingGroup.size();  // average price
    }
    return prices;
}

void DNSAuction::allocateItems(const std::vector<int>& allocationGroup, const std::vector<double>& prices) {
    std::vector<bool> item_taken(m_items, false);
    for (int b : allocationGroup) {
        std::vector<int> bundle;
        for (int item = 0; item < m_items; ++item) {
            if (!item_taken[item] && valuations[b][item] > prices[item]) {
                bundle.push_back(item);
                item_taken[item] = true;
            }
        }
        allocation[b] = bundle;
    }
}

void DNSAuction::runSimulation() {
    std::vector<int> pricingGroup, allocationGroup;
    randomPartition(pricingGroup, allocationGroup);
    std::vector<double> prices = computeItemPrices(pricingGroup);
    allocateItems(allocationGroup, prices);
}

void DNSAuction::printResults() {
    std::cout << "\nFinal Allocation:\n";
    for (const auto& pair : allocation) {
        std::cout << "Bidder " << pair.first << ": ";
        for (int item : pair.second) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
}
