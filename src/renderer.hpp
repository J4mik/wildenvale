#ifndef renderer_h
#define renderer_h

#include "level.hpp"

#define GENERATECHUNKOFSCREENOFSET 100

#define PLAYERSPEED 0.34

typedef struct spriteInstance
{
	float x, y, z;
	float rotation;
	float w, h, padding_a, padding_b;
	float tex_u, tex_v, tex_w, tex_h;
	float r, g, b, a;
} spriteInstance;

void spriteRender(spriteInstance spriteData);

struct playerPos
{
    int x;
    int y;
    int w;
    int h;
}playerPos;

void spriteRenderCall()
{
    // static float ofsetX, ofsetY = screen.tempOfsetX / screen.w, screen.tempOfsetY / screen.h;
    screen.posX -= (screen.posX - player.x) * 0.15 * deltaTime * (1 - decay.pow255[deltaTime]);
    screen.posY -= (screen.posY - player.y) * 0.15 * deltaTime * (1 - decay.pow255[deltaTime]);
    screen.ofsetX = screen.w * 0.5;
    screen.ofsetY = screen.h * 0.5;
    screen.tempOfsetX = std::floor(screen.ofsetX - screen.posX);
    screen.tempOfsetY = std::floor(screen.ofsetY - screen.posY);
    playerPos.x = player.x + screen.ofsetX - screen.posX;
    playerPos.y = player.y + screen.ofsetY - screen.posY;

    for (unsigned int i = 0; i < chunks.size(); ++i)
    {
        for (unsigned int x = 0; x < CHUNKSIZE; ++x)
        {
            for (unsigned int y = 0; y < CHUNKSIZE; ++y)
            if (chunks[i].m_tilegrid[x][y] > 0)
            {
                spriteRender(
                    spriteInstance{
                    (float)(std::floor(chunks[i].x * CHUNKSIZEPX + x * TILESIZE) + screen.tempOfsetX + HALFTILESIZE), 
                    (float)(std::floor(chunks[i].y * CHUNKSIZEPX + y * TILESIZE) + screen.tempOfsetY + HALFTILESIZE), 0, 
                    0, 
                    32, 32, 0, 0, 
                    (float)tilegridpos[chunks[i].m_tilegrid[x][y]].x, (float)tilegridpos[chunks[i].m_tilegrid[x][y]].y, 0.25f, 0.25f, 
                    1.0f, 1.0f, 1.0f, 1.0f
                    });
            }
        }
    }

    player.VectX *= decay.pow255[deltaTime * 3];
    player.VectY *= decay.pow255[deltaTime * 3];

    // player rendering
    player.VectX += ((keyboard.d || keyboard.rightArrow) - (keyboard.a || keyboard.leftArrow)) * deltaTime *
        (1 - decay.pow255[deltaTime]) * PLAYERSPEED;
    player.VectY += ((keyboard.s || keyboard.downArrow) - (keyboard.w || keyboard.upArrow)) * deltaTime *
        (1 - decay.pow255[deltaTime]) * PLAYERSPEED;


    // clamps the player speed
    if (abs((keyboard.d || keyboard.rightArrow) - (keyboard.a || keyboard.leftArrow)) +
            abs((keyboard.s || keyboard.downArrow) - (keyboard.w || keyboard.upArrow)) >
        1)
    {
        player.x += player.VectX * 0.72;
        player.y += player.VectY * 0.72;
    }
    else
    {
        player.x += player.VectX;
        player.y += player.VectY;
    }

    playerPos.x = player.x + screen.ofsetX - screen.posX;
    playerPos.y = player.y + screen.ofsetY - screen.posY;

}

#endif