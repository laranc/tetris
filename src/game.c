#include "game.h"

#include <assert.h>
#include <math.h>
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
  game.upcoming_board = initBoard(
      (Vector2){board_pos.x * 2 + board_size.x, board_pos.y},
      (Vector2){board_size.x / 2, board_size.y / 4}, tile_size, padding);
  game.timer = (Timer){0, 0};
  srand(random());

  return game;
}

void gameStart(Game *game) {
  printf("Starting...\n");
  assert(!GetWindowHandle());
  InitWindow(game->screen_size.x, game->screen_size.y, game->title);
  game->current_tetromino =
      initTetromino(&game->board, (Shape)(rand() % NUM_SHAPES));
  game->next_tetromino =
      initTetromino(&game->upcoming_board, (Shape)(random() % NUM_SHAPES));
  game->next_tetromino.position =
      (Vector2){floor((double)(game->next_tetromino.board->size.x / 2 -
                               (float)game->next_tetromino.dimension / 2)),
                floor((double)(game->next_tetromino.board->size.y / 2 -
                               (float)game->next_tetromino.dimension / 2))};
  SetTargetFPS(game->fps);
  startTimer(&game->timer, game->current_tetromino.speed);
}

void gameRun(Game *game) {
  while (!WindowShouldClose()) {
    tick(game);
  }
}

void gameClose(Game *game) {
  printf("Closing...\n");
  deleteBoard(&game->board);
  deleteBoard(&game->upcoming_board);
  deleteTetromino(&game->current_tetromino);
  deleteTetromino(&game->next_tetromino);
  assert(GetWindowHandle());
  CloseWindow();
}

static void tick(Game *game) {
  BeginDrawing();
  update(game);
  draw(game);
  EndDrawing();
}

static void update(Game *game) {
  if (IsKeyPressed(KEY_E)) {
    rotateTetrominoClockwise(&game->current_tetromino);
  }
  if (IsKeyPressed(KEY_Q)) {
    rotateTetrominoCounterClockwise(&game->current_tetromino);
  }
  if (IsKeyPressed(KEY_A)) {
    moveTetrominoLeft(&game->current_tetromino);
  }
  if (IsKeyPressed(KEY_D)) {
    moveTetrominoRight(&game->current_tetromino);
  }
  if (IsKeyPressed(KEY_S)) {
    dropTetromino(&game->current_tetromino);
  }
  if (timerDone(game->timer)) {
    if (game->current_tetromino.position.y + game->current_tetromino.dimension <
        game->board.size.y) {
      game->current_tetromino.position.y++;
    } else {
      dropTetromino(&game->current_tetromino);
    }
    startTimer(&game->timer, game->current_tetromino.speed);
  }
  if (!game->current_tetromino.moving) {
    switchTetromino(&game->current_tetromino, &game->next_tetromino);
  }
}

static void draw(Game *game) {
  ClearBackground(BLACK);
  drawBoard(&game->board);
  drawBorder(&game->board);
  drawBoard(&game->upcoming_board);
  drawBorder(&game->upcoming_board);
  drawTetromino(&game->current_tetromino);
  drawTetromino(&game->next_tetromino);
}
