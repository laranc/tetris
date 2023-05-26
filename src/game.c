#include "game.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "board.h"
#include "tetromino.h"

Game gameInit(Vector2 screen_size, char *title, int fps, Vector2 board_pos,
              Vector2 board_size, int tile_size, int padding) {
  Game game;
  game.screen_size = screen_size;
  game.title = title;
  game.fps = fps;
  game.board = initBoard(board_pos, board_size, tile_size, padding);

  return game;
}

void gameStart(Game *game) {
  printf("Starting...");
  assert(!GetWindowHandle());
  InitWindow(game->screen_size.x, game->screen_size.y, game->title);
  SetTargetFPS(game->fps);
}

void gameRun(Game *game) {
  while (!WindowShouldClose()) {
    gameTick(game);
  }
}

void gameTick(Game *game) {
  BeginDrawing();
  update(game);
  draw(game);
  EndDrawing();
}

void gameClose(Game *game) {
  printf("Closing...");
  deleteBoard(&game->board);
  assert(GetWindowHandle());
  CloseWindow();
}

static void update(Game *game) {}

static void draw(Game *game) {
  ClearBackground(BLACK);
  Tetromino test = initTetromino(&game->board, TEE);
  drawTetromino(&test);
  drawBoard(&game->board);
  drawBorder(&game->board);
}
