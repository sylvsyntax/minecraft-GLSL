//
//  World.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <unordered_map>
#include "Mesh.h"
#include "Chunk.h"
#include "Cube.h"

struct Vector2Key {

    int x;
    int y;

    bool operator==(const Vector2Key &other) const {
        return (x == other.x && y == other.y);
    }
};

template<>
struct std::hash<Vector2Key> {
    std::size_t operator()(const Vector2Key &k) const {
        using std::size_t;
        using std::hash;
        using std::string;

        // Compute individual hash values for first,
        // second and combine them using XOR
        // and bit shifting:

        return ((hash<int>()(k.x)
                 ^ (hash<int>()(k.y) << 1)));
    }
};

class World
{
public:
    World();
    LightingCube sun;
    double worldTime = 0;
    std::vector<Mesh> sceneMeshes;
    std::vector<Mesh> sceneLights;
    std::unordered_map<Vector2Key, Chunk> chunks;
    Shader shaderProgram;
    Shader lightShader;

    void generateChunk(int x, int y);
    void updateChunks();
    void updateSpecial();
};

#endif /* WORLD_CLASS_H */
