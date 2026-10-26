# Monte Carlo Photon Shielding

A Monte Carlo simulation of gamma-ray photons passing through a shielding slab. The simulation is written in C++, with analysis and plots in Python.

## What it does

A gamma-ray photon entering a shield either passes straight through or interacts with the material, by absorption or scattering. In this version, any interaction removes the photon from the beam, so the simulation counts the uncollided (narrow-beam) photons.

For this simple case there is an exact answer, the Beer–Lambert law. Once photons can scatter and change direction, or the shield has several layers, there's no neat formula any more, but a simulation still works. Checking the code against the simple case first means I can trust it before extending it to the harder ones.

Each photon travels a random distance before it interacts with the material. The distance is sampled from an exponential distribution:

x = −ln(r) / μ, where r is a uniform random number in (0, 1] and μ is the attenuation coefficient.

If the photon travels further than the slab is thick, it is transmitted. Firing a million photons and counting how many get through gives the transmitted fraction, which should match the Beer–Lambert law, exp(−μx).

## Results

### 1. Transmission vs thickness

![Transmission](results/transmission.png)

The simulated transmission (1 million photons per thickness, μ = 0.5 cm⁻¹) matches exp(−μx) from 0 to 10 cm, over nearly three orders of magnitude.

Taking the log of T = exp(−μx) gives ln T = −μx, so on a log scale the transmission is a straight line with slope −μ. The points get slightly noisier for thick shields because so few photons survive: at 10 cm only about 6,700 of the million get through, so the relative error is about 1/√6700 ≈ 1.2%, compared with about 0.13% at 1 cm.

### 2. Convergence

![Convergence](results/convergence.png)

Each transmission count is a binomial process, so the expected statistical error is σ = √(p(1−p)/N). I ran each photon count 50 times and took the RMS error. It follows the predicted 1/√N scaling from N = 100 to N = 10,000,000, staying within about 15% of σ at every N (the scatter you'd expect from 50 repeats).

This is how I know the remaining gap is statistics, not a bug. A bug, such as a wrong μ, would add a fixed offset: the error would fall with N at first, then flatten out at that offset. My error keeps falling all the way to 10 million photons with no floor.

## How to run

```
# Simulation (C++)
clang++ -std=c++17 -O2 src/main.cpp -o mc && ./mc
clang++ -std=c++17 -O2 src/convergence.cpp -o conv && ./conv

# Plots (Python)
python3 analysis/plot.py
python3 analysis/convergence_plot.py
```

Run from the project folder. Requires a C++17 compiler and Python with NumPy, pandas and Matplotlib.

## Structure

- `src/main.cpp`: transmission vs thickness sweep
- `src/convergence.cpp`: error vs number of photons, repeated runs
- `analysis/`: Python plotting scripts
- `results/`: CSV output and figures

## Next steps

- Add Compton scattering, so photons can change direction and lose energy
- Multi-layer shields of different materials
