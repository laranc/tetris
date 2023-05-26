#pragma once

#include "board.h"
#include "tetromino.h"

typedef struct Game {
  Vector2 screen_size;
  char *title;
  int fps;
  Board board;
  Tetromino current_tetromino;
} Game;

Game gameInit(Vector2 screen_size, char *title, int fps, Vector2 board_pos,
              Vector2 board_size, int tile_size, int tile_padding);
void gameStart(Game *game);
void gameRun(Game *game);
void gameTick(Game *game);
void gameClose(Game *game);

static void update(Game *game);
static void draw(Game *game);
