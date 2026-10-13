#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

int main() {
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> uni(0.0, 1.0);

    double mu = 0.5;
    double thickness = 2.0;
    double exact = std::exp(-mu * thickness);

    std::ofstream out("results/convergence.csv");
    out << "N,rms_error\n";

    int repeats = 50;

    for (long N = 100; N <= 10000000; N *= 10) {
        double sumSq = 0.0;                       // running total of error²

        for (int k = 0; k < repeats; k++) {
            long transmitted = 0;

            for (long i = 0; i < N; i++) {
                double r = 1.0 - uni(rng);       // never exactly 0, so log is safe
                double x = -std::log(r) / mu;
                if (x > thickness) {
                    transmitted++;
                }
            }

            double fraction = (double)transmitted / N;
            double error = fraction - exact;
            sumSq += error * error;               // add this run's error²
        }

        double rms = std::sqrt(sumSq / repeats);  // root of the mean of the squares
        out << N << "," << rms << "\n";
    }

    std::cout << "Saved results/convergence.csv\n";
    return 0;
}