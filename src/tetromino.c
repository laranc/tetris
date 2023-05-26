#include "tetromino.h"

#include <assert.h>
#include <stdlib.h>

#include <raylib.h>

#include "board.h"

Tetromino initTetromino(Board *board, Shape shape) {
  Tetromino tetromino;
  tetromino.shape = shape;
  tetromino.board = board;

  switch (shape) {
  case STRAIGHT: {
    tetromino.color = SKYBLUE;
    tetromino.dimension = 4;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SQUARE: {
    tetromino.color = YELLOW;
    tetromino.dimension = 2;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {1, 1, 1, 1};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case TEE: {
    tetromino.color = MAGENTA;
    tetromino.dimension = 3;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case JAY: {
    tetromino.color = DARKBLUE;
    tetromino.dimension = 3;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case ELL: {
    tetromino.color = ORANGE;
    tetromino.dimension = 3;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);

    bool arr[] = {1, 0, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SKEWS: {
    tetromino.color = GREEN;
    tetromino.dimension = 3;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SKEWZ: {
    tetromino.color = RED;
    tetromino.dimension = 3;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  }

  tetromino.position =
      (Vector2){board->size.x / 2 - (float)tetromino.dimension / 2, 0};

  return tetromino;
}

void drawTetromino(const Tetromino *tetromino) {
  for (int x = 0; x < tetromino->dimension; x++) {
    for (int y = 0; y < tetromino->dimension; y++) {
      bool tile = tetromino->tiles[x * tetromino->dimension + y];
      if (tile) {
        drawTileC(tetromino->board, (Vector2){x, y}, tetromino->color);
      }
    }
  }
}

void deleteTetromino(Tetromino *tetromino) {
  free(tetromino->tiles);
  free(tetromino->board);
}
