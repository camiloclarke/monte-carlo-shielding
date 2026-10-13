#include <iostream>
#include <random>
#include <cmath>

int main() {
    std::mt19937 rng(42);  // random number engine, fixed seed so runs are repeatable
    std::uniform_real_distribution<double> uni(0.0, 1.0);

    double mu = 0.5;         // attenuation coefficient (per cm)
    double thickness = 2.0;  // slab thickness (cm)

    double r = uni(rng);     // one random number in (0,1)
    // TODO: turn r into a free path length
    // TODO: did this photon make it through the slab?

    std::cout << "r = " << r << "\n";
    return 0;
}
