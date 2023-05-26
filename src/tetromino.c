#include "tetromino.h"

#include <assert.h>
#include <stdlib.h>

#include <raylib.h>

#include "board.h"

Tetromino initTetromino(Board *board, Shape shape) {
  Tetromino tetromino;
  tetromino.shape = shape;
  tetromino.board = board;
  tetromino.rotation = UP;

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
    bool arr[] = {1, 0, 0, 1, 1, 1, 0, 0, 0};
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

    bool arr[] = {0, 0, 1, 1, 1, 1, 0, 0, 0};
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
    bool arr[] = {0, 1, 1, 1, 1, 0, 0, 0, 0};
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
    bool arr[] = {1, 1, 0, 0, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  default:
    break;
  }

  tetromino.position =
      (Vector2){board->size.x / 2 - (float)tetromino.dimension / 2, 0};

  return tetromino;
}

void drawTetromino(const Tetromino *tetromino) {
  for (int y = 0; y < tetromino->dimension; y++) {
    for (int x = 0; x < tetromino->dimension; x++) {
      bool tile;
      switch (tetromino->rotation) {
      case UP:
        tile = tetromino->tiles[y * tetromino->dimension + x];
        break;
      case RIGHT:
        tile =
            tetromino->tiles[tetromino->dimension * (tetromino->dimension - 1) -
                             tetromino->dimension * x + y];
        break;
      case DOWN:
        tile =
            tetromino->tiles[(tetromino->dimension * tetromino->dimension - 1) -
                             tetromino->dimension * y - x];
        break;
      case LEFT:
        tile = tetromino->tiles[tetromino->dimension - 1 +
                                tetromino->dimension * x - y];
        break;
      default:
        break;
      }
      if (tile) {
        drawTileC(
            tetromino->board,
            (Vector2){tetromino->position.x + x, tetromino->position.y + y},
            tetromino->color);
      }
    }
  }
}

void rotateClockwise(Tetromino *tetromino) {
  tetromino->rotation = (Rotation)(((int)tetromino->rotation + 1) % 4);
}

void rotateCounterClockwise(Tetromino *tetromino) {
  switch (tetromino->rotation) {
  case UP:
    tetromino->rotation = LEFT;
    break;
  default:
    tetromino->rotation = (Rotation)((int)tetromino->rotation - 1);
    break;
  }
}

void deleteTetromino(Tetromino *tetromino) { free(tetromino->tiles); }
