import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("results/convergence.csv")

mu, thickness = 0.5, 2.0
p = np.exp(-mu * thickness)                 # exact transmission probability
sigma = np.sqrt(p * (1 - p) / df["N"])

plt.figure(figsize=(8, 5))
plt.plot(df["N"], df["rms_error"], "o", label="Monte Carlo error")
plt.plot(df["N"], sigma, "-", label=r"Expected $\sqrt{p(1-p)/N}$")

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Number of photons N")
plt.ylabel("RMS error")
plt.legend()
plt.savefig("results/convergence.png", dpi=150)
plt.show()