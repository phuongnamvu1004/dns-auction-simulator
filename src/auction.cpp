#include "auction.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

DNSAuction::DNSAuction(int bidders, int items, int clauses, int seed, const std::vector<Bidder>& input)
    : n_bidders(bidders), m_items(items), k_clauses(clauses), seed(seed) {
    setValuationsFromInput(input);
}

void DNSAuction::setValuationsFromInput(const vector<Bidder>& input) {
    valuations.resize(n_bidders);
    for (int i = 0; i < n_bidders; ++i) {
        valuations[i].resize(k_clauses);
        for (int k = 0; k < k_clauses; ++k) {
            for (int j = 0; j < m_items; ++j) {
                string key = "clause" + to_string(k) + "_Item" + to_string(j);
                valuations[i][k].push_back(input[i].itemValues.at(key));
            }
        }
    }
}

void DNSAuction::randomPartition(vector<int>& pricingGroup, vector<int>& allocationGroup) {
    vector<int> all(n_bidders);
    iota(all.begin(), all.end(), 0);
    shuffle(all.begin(), all.end(), default_random_engine(random_device{}()));

    int half = n_bidders / 2;
    pricingGroup.assign(all.begin(), all.begin() + half);
    allocationGroup.assign(all.begin() + half, all.end());
}

vector<double> DNSAuction::computeItemPrices(const vector<int>& pricingGroup) {
    vector<double> prices(m_items, 0.0);
    for (int item = 0; item < m_items; ++item) {
        for (int bidder : pricingGroup) {
            double max_val = 0;
            for (const auto& clause : valuations[bidder]) {
                max_val = max(max_val, clause[item]);
            }
            prices[item] += max_val;
        }
        prices[item] /= pricingGroup.size();
    }
    return prices;
}

void DNSAuction::allocateItems(const vector<int>& allocationGroup, const vector<double>& prices) {
    vector<bool> taken(m_items, false);
    for (int bidder : allocationGroup) {
        vector<int> bundle;
        for (int item = 0; item < m_items; ++item) {
            if (!taken[item]) {
                bool worth_it = false;
                for (const auto& clause : valuations[bidder]) {
                    if (clause[item] > prices[item]) {
                        worth_it = true;
                        break;
                    }
                }
                if (worth_it) {
                    bundle.push_back(item);
                    taken[item] = true;
                }
            }
        }
        allocation[bidder] = bundle;
    }
}

double DNSAuction::evaluateXOS(int bidder, const vector<int>& bundle) {
    double max_val = 0;
    for (const auto& clause : valuations[bidder]) {
        double sum = 0;
        for (int item : bundle) {
            sum += clause[item];
        }
        max_val = max(max_val, sum);
    }
    return max_val;
}

void DNSAuction::runSimulation() {
    vector<int> pricingGroup, allocationGroup;
    randomPartition(pricingGroup, allocationGroup);
    vector<double> prices = computeItemPrices(pricingGroup);
    allocateItems(allocationGroup, prices);


    double total_value = 0;
    for (const auto& pair : allocation) {
        total_value += evaluateXOS(pair.first, pair.second);
    }
    std::cout << "Total Social Welfare: " << total_value << "\n";
}

void DNSAuction::printResults() {
    cout << "\nFinal Allocation:\n";
    for (const auto& pair : allocation) {
        cout << "Bidder " << pair.first << " receives items: ";
        for (int item : pair.second) {
            cout << item << " ";
        }
        double value = evaluateXOS(pair.first, pair.second);
        cout << "\n  (Value: " << value << ")\n";
    }
}

vector<int> DNSAuction::getBundle(int bidder) const {
    auto it = allocation.find(bidder);
    if (it != allocation.end()) return it->second;
    return {};
}

