#pragma once

#include <random>

namespace bb {

class RNG {
public:
    RNG();

    static void setSeed( uint32_t seed );
    static uint32_t getSeed();

    template <class IntType = int>
    static IntType randomInt( IntType from = 0, IntType to = std::numeric_limits<IntType>::max() );

    template <class RealType = float>
    static RealType randomReal( RealType from = 0, RealType to = std::numeric_limits<RealType>::max() );

    static float randomNormal();
    static double randomNormalDouble();

private:
    static uint32_t m_seed;
    static std::mt19937 m_generator;
};

template <class IntType>
IntType RNG::randomInt( IntType from /* = 0 */,
                        IntType to /* = std::numeric_limits<IntType>::max() */ )
{
    std::uniform_int_distribution<IntType> dist( from, to );
    return dist( m_generator );
}

template <class RealType /* = float*/>
RealType RNG::randomReal( RealType from /* = 0 */,
                          RealType to /* = std::numeric_limits<RealType>::max() */ )
{
    std::uniform_real_distribution<RealType> dist( from, to );
    return dist( m_generator );
}


} // namespace bb
