/*
 * Copyright (C) 2021-2022 Parallel Realities.
 */

#include "common.h"

#include "atlas.h"
#include "demo.h"
#include "draw.h"

#define NUM_SPHERES		 5
#define NUM_TILES		 11
#define TILE_WIDTH		 42
#define TILE_HEIGHT		 20
#define MAP_OFFSET_X	 -70
#define MAP_OFFSET_Y	 350
#define NUM_BLOCK_IMAGES 3
#define NUM_BLOCKS		 12
#define MAP_SIZE		 35

extern App app;

static void logic(void);
static void draw(void);
static void doSpheres(void);
static void drawSpheres(void);
static void drawTiles(void);
static void drawBlocks(void);
static int	blockComparator(const void *a, const void *b);

static AtlasImage *sphereAtlasImages[NUM_SPHERES];
static AtlasImage *tileAtlasImages[NUM_TILES];
static AtlasImage *blockAtlasImages[NUM_BLOCK_IMAGES];
static SDL_Point   spheres[NUM_SPHERES];
static SDL_Point   blocks[NUM_BLOCKS];
static int		   map[MAP_SIZE * MAP_SIZE];

void initDemo(void)
{
	int	 i;
	char filename[MAX_FILENAME_LENGTH];

	sphereAtlasImages[0] = getAtlasImage("gfx/spheres/blue.png");
	sphereAtlasImages[1] = getAtlasImage("gfx/spheres/lime.png");
	sphereAtlasImages[2] = getAtlasImage("gfx/spheres/orange.png");
	sphereAtlasImages[3] = getAtlasImage("gfx/spheres/purple.png");
	sphereAtlasImages[4] = getAtlasImage("gfx/spheres/red.png");

	for (i = 0; i < NUM_SPHERES; i++)
	{
		spheres[i].x = rand() % SCREEN_WIDTH;
		spheres[i].y = 50 + (rand() % (SCREEN_HEIGHT - 100));
	}

	blockAtlasImages[0] = getAtlasImage("gfx/cubes/bigGreen.png");
	blockAtlasImages[1] = getAtlasImage("gfx/cubes/bigGrey.png");
	blockAtlasImages[2] = getAtlasImage("gfx/cubes/bigRed.png");

	for (i = 0; i < NUM_BLOCKS; i++)
	{
		blocks[i].x = rand() % (MAP_SIZE - 4);
		blocks[i].y = rand() % (MAP_SIZE - 4);
	}

	qsort(blocks, sizeof(SDL_Point), NUM_BLOCKS, blockComparator);

	for (i = 0; i < NUM_TILES; i++)
	{
		sprintf(filename, "gfx/tiles/%d.png", i + 1);

		tileAtlasImages[i] = getAtlasImage(filename);
	}

	for (i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		map[i] = rand() % NUM_TILES;
	}

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	doSpheres();
}

static void doSpheres(void)
{
	int i;

	for (i = 0; i < NUM_SPHERES; i++)
	{
		spheres[i].x += 4;

		if (spheres[i].x >= (SCREEN_WIDTH + sphereAtlasImages[i]->rect.w))
		{
			spheres[i].x = -sphereAtlasImages[i]->rect.w;
		}
	}
}

static void draw(void)
{
	drawTiles();

	drawBlocks();

	drawSpheres();
}

static void drawSpheres(void)
{
	int i;

	for (i = 0; i < NUM_SPHERES; i++)
	{
		blitAtlasImage(sphereAtlasImages[i], spheres[i].x, spheres[i].y, 1);
	}
}

static void toISO(int x, int y, int *sx, int *sy)
{
	*sx = MAP_OFFSET_X + ((x * TILE_WIDTH / 2) + (y * TILE_WIDTH / 2));
	*sy = MAP_OFFSET_Y + ((y * TILE_HEIGHT / 2) - (x * TILE_HEIGHT / 2));
}

static void drawTiles(void)
{
	int y, x, sx, sy, i;

	i = 0;

	for (x = MAP_SIZE; x > 0; x--)
	{
		for (y = 0; y < MAP_SIZE; y++)
		{
			toISO(x, y, &sx, &sy);

			blitAtlasImage(tileAtlasImages[map[i]], sx, sy, 0);

			i++;
		}
	}
}

static void drawBlocks(void)
{
	int sx, sy, i;

	for (i = 0; i < NUM_BLOCKS; i++)
	{
		toISO(blocks[i].x, blocks[i].y, &sx, &sy);

		blitAtlasImage(blockAtlasImages[i % NUM_BLOCK_IMAGES], sx, sy, 0);
	}
}

static int blockComparator(const void *a, const void *b)
{
	SDL_Point *p1 = (SDL_Point *)a;
	SDL_Point *p2 = (SDL_Point *)b;

	return p1->y - p2->y;
}
