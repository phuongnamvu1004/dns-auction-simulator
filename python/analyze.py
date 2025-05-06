
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path

# Load files from results directory
results_dir = Path(__file__).resolve().parent.parent / "results"
dns_file = results_dir / "results_dns.csv"
vcg_file = results_dir / "results_vcg.csv"

# Read data
print("Loading result files...")
dns_df = pd.read_csv(dns_file)
vcg_df = pd.read_csv(vcg_file)

# Merge for comparison
merged = pd.merge(dns_df, vcg_df, on="seed", suffixes=("_dns", "_vcg"))
merged["welfare_diff"] = merged["total_welfare_dns"] - merged["total_welfare_vcg"]
merged["winner_diff"] = merged["winners_dns"] - merged["winners_vcg"]

# Summary stats
summary = merged[["total_welfare_dns", "total_welfare_vcg", "welfare_diff"]].describe()
print("\nSummary Statistics:")
print(summary)

# Output summary to text file
summary_file = results_dir / "summary.txt"
with open(summary_file, "w") as f:
    f.write("DNS vs VCG Summary Statistics\n")
    f.write(summary.to_string())
    f.write("\n")
print(f"Summary written to {summary_file}")

# Plotting setup
plot_dir = results_dir / "plots"
plot_dir.mkdir(parents=True, exist_ok=True)

# Box plot of total welfare
plt.figure(figsize=(8, 5))
sns.boxplot(data=merged[["total_welfare_dns", "total_welfare_vcg"]])
plt.title("Total Social Welfare: DNS vs VCG")
plt.ylabel("Total Welfare")
plt.xticks([0, 1], ["DNS", "VCG"])
plt.grid(True)
plt.tight_layout()
plt.savefig(plot_dir / "welfare_boxplot.png")

# Histogram of welfare differences
plt.figure(figsize=(8, 5))
sns.histplot(merged["welfare_diff"], bins=20, kde=True, color="skyblue")
plt.axvline(0, color="red", linestyle="--")
plt.title("Distribution of Welfare Differences (DNS - VCG)")
plt.xlabel("Welfare Difference")
plt.ylabel("Frequency")
plt.tight_layout()
plt.savefig(plot_dir / "welfare_diff_hist.png")

# Box plot of winners
plt.figure(figsize=(8, 5))
sns.boxplot(data=merged[["winners_dns", "winners_vcg"]])
plt.title("Number of Winners: DNS vs VCG")
plt.ylabel("Number of Bidders Receiving Items")
plt.xticks([0, 1], ["DNS", "VCG"])
plt.grid(True)
plt.tight_layout()
plt.savefig(plot_dir / "winner_boxplot.png")

print(f"Plots saved in {plot_dir}")
