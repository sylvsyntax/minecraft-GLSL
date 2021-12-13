#ifndef BLOCK_ENUMS_H
#define BLOCK_ENUMS_H

enum class blockType {
    air = -1, dirt = 0, stone = 1, grass = 2, sideGrass = 3, wood = 4, woodEnd = 5, leaves = 6
};

const int numOfBlocktypes = 6;
const float BLOCK_SIZE = 0.2;

enum class blockPos {
    front = 0, bottom = 1, top = 2, back = 3, sideLeft = 4, sideRight = 5
};

#endif /* BLOCK_ENUMS_H */