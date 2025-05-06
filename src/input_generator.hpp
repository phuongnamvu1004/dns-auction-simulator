#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <random>

using namespace std;

struct Bidder {
    string name;
    unordered_map<string, double> itemValues;  // key = "clause0_Item2", value = score
};

vector<Bidder> generateRandomBidders(int numBidders, int numItems, int clauses, int seed);
vector<string> generateItemNames(int numItems);
