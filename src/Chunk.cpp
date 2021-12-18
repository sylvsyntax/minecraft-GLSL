#include "Chunk.h"
#include "Structures.h"

vec3 Chunk::getTop(int x, int y){
    vec3 pos;
    for(int i = 0; i < MAX_HEIGHT; i++)
        if(blocks[x][i][y] == (int)blockType::grass)
            pos = vec3(position.x * (CHUNK_SIZE * BLOCK_SIZE) + (x * BLOCK_SIZE), i * BLOCK_SIZE, position.y * (CHUNK_SIZE * BLOCK_SIZE) + (y * BLOCK_SIZE));
    return pos;
}

vec3 Chunk::getLocalTop(int x, int y){
    vec3 pos;
    for(int i = 0; i < MAX_HEIGHT; i++)
        if(blocks[x][i][y] == (int)blockType::grass)
            pos = vec3(x, i, y);
    return pos;
}

Chunk::Chunk(int x, int y) : position(glm::ivec2(x,y))
{
    PerlinNoise perlinNoise(80085);
    position = glm::vec2(x, y);
    vector<float> maxHeights;
    int goodNoiseValue = 64;
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            //float val = perlin(.1f * (x * CHUNK_SIZE + i), .1f * (y * CHUNK_SIZE + j));
            float val = perlinNoise.noise(((double)i / (double)goodNoiseValue + (double)x * CHUNK_SIZE / (double)goodNoiseValue), ((double)j / (double)goodNoiseValue + (double)y * CHUNK_SIZE / (double)goodNoiseValue), 0.5);
            maxHeights.push_back(val * MAX_HEIGHT/*CHANGE LEFT TO WHATEVER + MAX_HEIGHT / 4*//* * .1f * MAX_HEIGHT + MAX_HEIGHT / 2*/);
        }
    }

    for (size_t xx = 0; xx < CHUNK_SIZE; xx++)
    {
        for (size_t zz = 0; zz < CHUNK_SIZE; zz++)
        {
            for (size_t yy = 0; yy < MAX_HEIGHT; yy++)
            {
                blockType BlockType = blockType::dirt;
                if (yy == (int)round(maxHeights[xx * CHUNK_SIZE + zz]))
                    BlockType = blockType::grass;
                else if (yy < maxHeights[xx * CHUNK_SIZE + zz] - 4)
                    BlockType = blockType::stone;
                else if (yy > (int)round(maxHeights[xx * CHUNK_SIZE + zz]))
                    BlockType = blockType::air;
                glm::vec3 blockPosition = glm::vec3(xx + CHUNK_SIZE * x, yy, zz + CHUNK_SIZE * y) * BLOCK_SIZE;
                vec3 newPos = vec3(blockPosition.x, blockPosition.y, blockPosition.z);
                //Moves over the position
                Block newBlock(newPos, BlockType);
                newBlock.type = BlockType;
                blocks[xx][yy][zz] = (int)newBlock.type;
            }
        }
    }
    if ((x == 0) && (y == 0)){
        Structures house = Structures(House, getLocalTop(8, 8));
        house.ApplyBuildWithoutTranslation();
        
        for(auto & i : house.blockArray){
            if((i.pos.gety() < MAX_HEIGHT) && (i.pos.getx() < CHUNK_SIZE) && (i.pos.getz() < CHUNK_SIZE)){
                blocks[(int)(i.pos.getx())][(int)(i.pos.gety()) + 1][(int)(i.pos.getz())] = (int)i.type;
            }
        }
        
    }
    else {
        Structures tree = Structures(Tree, getLocalTop(8, 8));
        tree.ApplyBuildWithoutTranslation();
        for(auto & i : tree.blockArray){
            if((i.pos.gety() < MAX_HEIGHT) && (i.pos.getx() < CHUNK_SIZE) && (i.pos.getz() < CHUNK_SIZE)){
                blocks[(int)(i.pos.getx())][(int)(i.pos.gety()) + 1][(int)(i.pos.getz())] = (int)i.type;
            }
        }
    }
    

    /*Structures tree = Structures(Tree, vec3(0, 20, 0));
    tree.ApplyBuild();
    for(int i = 0; i < tree.blockArray.size(); i++)
        blocks[0] [0] [(int)tree.blockArray[i].pos.getz()] = (int)tree.blockArray[i].type;*/
}
