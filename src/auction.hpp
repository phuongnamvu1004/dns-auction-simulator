#ifndef AUCTION_HPP
#define AUCTION_HPP

#include <vector>
#include <unordered_map>
#include "input_generator.hpp"

using namespace std;

class DNSAuction {
public:
    DNSAuction(int bidders, int items, int clauses, int seed, const std::vector<Bidder>& input);
    double evaluateXOS(int bidder, const vector<int>& bundle);
    void runSimulation();
    void printResults();
    vector<int> getBundle(int bidder) const;

private:
    int n_bidders;
    int m_items;
    int k_clauses;
    int seed;

    vector<vector<vector<double>>> valuations;
    unordered_map<int, vector<int>> allocation;

    void setValuationsFromInput(const vector<Bidder>& input);
    void randomPartition(vector<int>& pricingGroup, vector<int>& allocationGroup);
    vector<double> computeItemPrices(const vector<int>& pricingGroup);
    void allocateItems(const vector<int>& allocationGroup, const vector<double>& prices);
};

#endif