#ifndef AUCTION_HPP
#define AUCTION_HPP

#include <vector>
#include <string>
#include <unordered_map>

class DNSAuction {
public:
    DNSAuction(int bidders, int items);

    void runSimulation();
    void printResults();

private:
    int n_bidders;
    int m_items;

    std::vector<std::vector<double>> valuations;
    std::unordered_map<int, std::vector<int>> allocation;

    void generateSubmodularValuations();
    void randomPartition(std::vector<int>& pricingGroup, std::vector<int>& allocationGroup);
    std::vector<double> computeItemPrices(const std::vector<int>& pricingGroup);
    void allocateItems(const std::vector<int>& allocationGroup, const std::vector<double>& prices);
};

#endif
