# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Paths
SRC_DIR = src
TARGET = dns_auction

# Source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(SRC_DIR)/*.hpp)

# Build target
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f $(TARGET)

# Simulate DNS target
simulate_dns: src/simulate_dns.cpp src/auction.cpp src/input_generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o simulate_dns

# Simulate VCG target
simulate_vcg: src/simulate_vcg.cpp src/input_generator.cpp
	$(CXX) $(CXXFLAGS) $^ -o simulate_vcg
