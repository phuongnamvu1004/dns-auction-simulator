# 🧮 DNS Auction Simulator

A C++ implementation of the **Dobzinski-Nisan-Schapira (DNS)** randomized mechanism for combinatorial auctions with submodular (XOS-style) bidders.

This simulator supports both DNS and VCG mechanisms, allowing side-by-side comparison of social welfare and allocation behavior. It was developed as part of a CS385 final project at Oberlin College.

---

## 📦 Project Structure

- `dns_auction`: Main executable for DNS auction logic and input generation.
- `simulate_dns`: Batch simulator for running multiple randomized DNS trials.
- `simulate_vcg`: Batch simulator using the VCG mechanism for comparison.

---

## 🔧 Build Instructions

To compile all binaries:

```bash
make all
```

or to compile individual binary
```bash
make dns_auction # for DNS auction logic
make simulate_dns # for DNS simulator
make simulate_vcg # for VCG simulator
```

## ▶️ Run Instructions

After building, run the desired executable directly:
```bash
./dns_auction
./simulate_dns # after running, check for output in results/results_dns.csv
./simulate_vcg # after running, check for output in results/results_vcg.csv
```


## 🧹 Clean up

To remove all compiled binaries:
```bash
make clean
```

## Visualization

Python setup and run analyze:
```bash
# Change working directory to python/
cd python

# Create virtual environment with Python3
python3 -m venv venv

# Activate virtual environment
# On Windows:
venv\Scripts\activate
# On macOS/Linux:
source venv/bin/activate

# Upgrade pip
python3 -m pip install --upgrade pip

# Install dependencies
python3 -m pip install -r requirements.txt

# Running Python Scripts: Make sure venv is activated, then
python3 analyze.py # inside python/
```

After running `analyze.py`, check for outputs in `results/summary.txt` and `results/plots`



