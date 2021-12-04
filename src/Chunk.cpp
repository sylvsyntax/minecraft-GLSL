#include "Chunk.h"

float perlin(float x, float y);

Chunk::Chunk(int x, int y) : position(glm::vec2(x,y))
{
    position = glm::vec2(x, y);
    vector<float> maxHeights;
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            float val = perlin(.1f * (x * CHUNK_SIZE + i), .1f * (y * CHUNK_SIZE + j));
            maxHeights.push_back(val * .1f * MAX_HEIGHT + MAX_HEIGHT / 2);
            cout << val << " ";
        }
    }
    // [i * CHUNK_SIZE + j]

    for (int xx = 0; xx < CHUNK_SIZE; xx++)
    {
        for (int zz = 0; zz < CHUNK_SIZE; zz++)
        {
            for (int yy = 0; yy <= (int)round(abs(maxHeights[xx * CHUNK_SIZE + zz])); yy++)
            {
                int blockType = 0;
                if(yy == (int)round(abs(maxHeights[xx * CHUNK_SIZE + zz])))
                    blockType = 2;
                else if(yy < .5f * abs(maxHeights[xx * CHUNK_SIZE + zz]))
                    blockType = 1;
                else
                    blockType = 0;
                glm::vec3 position = glm::vec3(xx + CHUNK_SIZE * x, yy, zz + CHUNK_SIZE * y) * .2f;
                vec3 newPos = vec3(position.x, position.y, position.z);
                //Moves over the position
                Cube newBlock(blockType, newPos);
                blocks.push_back(newBlock);
                
            }
        }
    }
}

// YOINKED FROM WIKI 

/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
float interpolate(float a0, float a1, float w) {
    /* // You may want clamping by inserting:
     * if (0.0 > w) return a0;
     * if (1.0 < w) return a1;
     */
    return (a1 - a0) * w + a0;
    /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
     * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
     *
     * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
     * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
     */
}

typedef struct {
    float x, y;
} vector2;

/* Create pseudorandom direction vector
 */
vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w - s;
    b *= 1911520717; a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    vector2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y) {
    // Determine grid cell coordinates
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;
}
