#include <iostream>
#include <random>
#include <cmath>

int main() {
    std::mt19937 rng(42);  // random number engine, fixed seed so runs are repeatable
    std::uniform_real_distribution<double> uni(0.0, 1.0);

    double mu = 0.5;         // attenuation coefficient (per cm)
    double thickness = 2.0;  // slab thickness (cm)

    long N = 1000000;        // number of photons
    long transmitted = 0;    // how many got through

    for (long i = 0; i < N; i++) {
        double r = 1.0 - uni(rng);       // never exactly 0, so log is safe
        double x = -std::log(r) / mu;
        if (x > thickness) {
           transmitted++;
        }
    }

    double fraction = (double)transmitted/N;
    double exact = std::exp(-mu*thickness);

    std::cout << "Simulated: " << fraction << "\n";
    std::cout << "Exact:     " << exact << "\n";
    return 0;
}
