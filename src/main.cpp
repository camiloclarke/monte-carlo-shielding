#include <iostream>
#include <random>
#include <cmath>
#include <fstream>   // lets you write files

int main() {
    std::mt19937 rng(42);  // random number engine, fixed seed so runs are repeatable
    std::uniform_real_distribution<double> uni(0.0, 1.0);

    double mu = 0.5;       // attenuation coefficient (per cm)
    long N = 1000000;      // photons per thickness

    std::ofstream out("results/transmission.csv");
    out << "thickness,simulated,exact\n";

    for (double thickness = 0.0; thickness <= 10.0; thickness += 0.5) {
        long transmitted = 0;

        for (long i = 0; i < N; i++) {
            double r = 1.0 - uni(rng);       // never exactly 0, so log is safe
            double x = -std::log(r) / mu;
            if (x > thickness) {
                transmitted++;
            }
        }

        double fraction = (double)transmitted / N;
        double exact = std::exp(-mu * thickness);

        out << thickness << "," << fraction << "," << exact << "\n";
    }

    std::cout << "Saved results/transmission.csv\n";
    return 0;
}
