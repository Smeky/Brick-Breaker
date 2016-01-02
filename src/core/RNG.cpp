#include "RNG.hpp"

#include <chrono>

namespace bb {

// Initialize static members
// Setup seed and Pseudo-Random Generator
uint32_t RNG::m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 RNG::m_generator( RNG::m_seed );

RNG::RNG()
{}

void RNG::setSeed( uint32_t seed ) {
    m_seed = seed;

    m_generator.seed( m_seed );
}

uint32_t RNG::getSeed() {
    return m_seed;
}

float RNG::randomNormal() {
    std::uniform_real_distribution<float> dist( 0, 1 );
    return dist( m_generator );
}

double RNG::randomNormalDouble() {
    std::uniform_real_distribution<double> dist( 0, 1 );
    return dist( m_generator );
}

} // namespace bb
