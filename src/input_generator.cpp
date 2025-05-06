#include "input_generator.hpp"
#include <algorithm>
#include <random>

using namespace std;

vector<string> generateItemNames(int numItems)
{
    vector<string> items;
    for (int i = 0; i < numItems; ++i)
    {
        items.push_back("Item" + to_string(i));
    }
    return items;
}

vector<Bidder> generateRandomBidders(int numBidders, int numItems, int clauses, int seed)
{
    mt19937 rng(seed);
    uniform_real_distribution<> baseValueDist(3.0, 10.0); // base marginal value
    uniform_real_distribution<> decayDist(0.6, 0.9);      // decay factor per item

    auto items = generateItemNames(numItems);
    vector<Bidder> bidders;

    for (int i = 0; i < numBidders; ++i)
    {
        Bidder b;
        b.name = "Bidder" + to_string(i);

        for (int c = 0; c < clauses; ++c)
        {
            double marginal = baseValueDist(rng);
            double decay = decayDist(rng);
            for (int j = 0; j < numItems; ++j)
            {
                string key = "clause" + to_string(c) + "_" + items[j];
                b.itemValues[key] = marginal;
                marginal *= decay; // diminishing returns
            }
        }

        bidders.push_back(b);
    }

    return bidders;
}
