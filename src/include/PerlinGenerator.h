#ifndef __PERLIN_GENERATOR_H
#define __PERLIN_GENERATOR_H

#include <utility>

#include <cmath>

class PerlinGenerator {
  public:
    PerlinGenerator(unsigned int seed = 0) : m_Seed(seed) {}

    // Compute Perlin noise at coordinates x, y
    float sample(float x, float y) const;

  private:
    /* Function to linearly interpolate between a0 and a1
       Weight w should be in the range [0.0, 1.0] */
    float interpolate(float a0, float a1, float w) const;

    // Create pseudorandom direction vector
    std::pair<float, float> randomGradient(int ix, int iy) const;

    // Computes the dot product of the distance and gradient vectors.
    float dotGridGradient(int ix, int iy, float x, float y) const;

    unsigned int m_Seed;
};

#endif