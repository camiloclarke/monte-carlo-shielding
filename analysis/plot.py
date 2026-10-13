import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("results/transmission.csv")

plt.figure(figsize=(8, 5))
plt.plot(df["thickness"], df["simulated"], "o", label="Monte Carlo")
plt.plot(df["thickness"], df["exact"], "-", label="Exact exp(-μx)")

plt.xlabel("Shield thickness (cm)")
plt.ylabel("Fraction transmitted")
plt.yscale("log")        # makes exp(-mu x) a straight line
plt.legend()
plt.savefig("results/transmission.png", dpi=150)
plt.show()