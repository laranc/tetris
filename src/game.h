#pragma once

#include <stdlib.h>

#include "board.h"
#include "game.h"
#include "tetromino.h"

typedef struct Timer {
  double start_time;
  double lifetime;
} Timer;

typedef struct Game {
  Vector2 screen_size;
  char *title;
  int fps;
  Board board;
  Board upcoming_board;
  Tetromino current_tetromino;
  Tetromino next_tetromino;
  Timer timer;
} Game;

Game gameInit(Vector2 screen_size, char *title, int fps, Vector2 board_pos,
              Vector2 board_size, int tile_size, int tile_padding);
void gameStart(Game *game);
void gameRun(Game *game);
void gameClose(Game *game);

static void tick(Game *game);
static void update(Game *game);
static void draw(Game *game);

inline static void startTimer(Timer *timer, double lifetime) {
  timer->start_time = GetTime();
  timer->lifetime = lifetime;
}
inline static bool timerDone(Timer timer) {
  return GetTime() - timer.start_time >= timer.lifetime;
}
inline static double getElapsed(Timer timer) {
  return GetTime() - timer.start_time;
}
