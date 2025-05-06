# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Paths
SRC_DIR = src
TARGETS = dns_auction simulate_dns simulate_vcg

# Source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(SRC_DIR)/*.hpp)

# Default build: all targets
all: $(TARGETS)

# Main DNS Auction binary
dns_auction: $(SRC_DIR)/main.cpp $(SRC_DIR)/auction.cpp $(SRC_DIR)/input_generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o dns_auction

# Simulate DNS target
simulate_dns: $(SRC_DIR)/simulate_dns.cpp $(SRC_DIR)/auction.cpp $(SRC_DIR)/input_generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o simulate_dns

# Simulate VCG target
simulate_vcg: $(SRC_DIR)/simulate_vcg.cpp $(SRC_DIR)/input_generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o simulate_vcg

# Run DNS Auction
run: dns_auction
	./dns_auction

# Clean all built binaries
clean:
	rm -f $(TARGETS)
