#include "tetromino.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "board.h"

Tetromino initTetromino(Board *board, Shape shape) {
  Tetromino tetromino;
  tetromino.shape = shape;
  tetromino.board = board;
  tetromino.rotation = UP;
  tetromino.speed = 0.5;
  tetromino.moving = true;

  switch (shape) {
  case STRAIGHT: {
    tetromino.color = SKYBLUE;
    tetromino.dimension = 4;
    tetromino.offset.top = 1;
    tetromino.offset.bottom = 2;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SQUARE: {
    tetromino.color = YELLOW;
    tetromino.dimension = 2;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 0;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {1, 1, 1, 1};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case TEE: {
    tetromino.color = MAGENTA;
    tetromino.dimension = 3;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 1;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case JAY: {
    tetromino.color = DARKBLUE;
    tetromino.dimension = 3;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 1;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {1, 0, 0, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case ELL: {
    tetromino.color = ORANGE;
    tetromino.dimension = 3;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 1;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 0, 1, 1, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SKEWS: {
    tetromino.color = GREEN;
    tetromino.dimension = 3;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 1;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {0, 1, 1, 1, 1, 0, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  case SKEWZ: {
    tetromino.color = RED;
    tetromino.dimension = 3;
    tetromino.offset.top = 0;
    tetromino.offset.bottom = 1;
    tetromino.offset.left = 0;
    tetromino.offset.right = 0;
    tetromino.tiles =
        malloc(sizeof(bool) * tetromino.dimension * tetromino.dimension);
    bool arr[] = {1, 1, 0, 0, 1, 1, 0, 0, 0};
    for (int i = 0; i < tetromino.dimension * tetromino.dimension; i++) {
      tetromino.tiles[i] = arr[i];
    }
    break;
  }
  default:
    break;
  }

  tetromino.position = (Vector2){
      floor((double)(board->size.x / 2 - (float)tetromino.dimension / 2)), 0};

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

void moveTetrominoLeft(Tetromino *tetromino) {
  if (tetromino->position.x > 0) {
    tetromino->position.x--;
  } else {
    bool can_move = true;
    int x = -tetromino->position.x;
    for (int y = 0; y < tetromino->dimension; y++) {
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
        can_move = false;
      }
    }
    if (can_move) {
      tetromino->position.x--;
    }
  }
}

void moveTetrominoRight(Tetromino *tetromino) {
  if (tetromino->position.x + tetromino->dimension < tetromino->board->size.x) {
    tetromino->position.x++;
  } else {
    bool can_move = true;
    int x = tetromino->board->size.x -
            (tetromino->position.x + tetromino->dimension);
    for (int y = 0; y < tetromino->dimension; y++) {
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
        can_move = false;
      }
    }
    if (can_move) {
      tetromino->position.x++;
    }
  }
}

void rotateTetrominoClockwise(Tetromino *tetromino) {
  if (tetromino->position.x < 0) {
    tetromino->position.x = 0;
  } else if (tetromino->position.x >
             tetromino->board->size.x - tetromino->dimension) {
    tetromino->position.x = tetromino->board->size.x - tetromino->dimension;
  }
  tetromino->rotation = (Rotation)(((int)tetromino->rotation + 1) % 4);
}

void rotateTetrominoCounterClockwise(Tetromino *tetromino) {
  if (tetromino->position.x < 0) {
    tetromino->position.x = 0;
  } else if (tetromino->position.x >
             tetromino->board->size.x - tetromino->dimension) {
    tetromino->position.x = tetromino->board->size.x - tetromino->dimension;
  }
  switch (tetromino->rotation) {
  case UP:
    tetromino->rotation = LEFT;
    break;
  default:
    tetromino->rotation = (Rotation)((int)tetromino->rotation - 1);
    break;
  }
}

void dropTetromino(Tetromino *tetromino) {
  tetromino->position.y = tetromino->board->size.y - tetromino->dimension;
  tetromino->moving = false;
  for (int x = tetromino->offset.left;
       x < tetromino->dimension - tetromino->offset.right; x++) {
    for (int y = tetromino->offset.top;
         y < tetromino->dimension - tetromino->offset.bottom; y++) {
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
        tetromino->board
            ->tiles[(int)tetromino->position.x + x]
                   [(int)tetromino->position.y + y]
            .exists = true;
        tetromino->board
            ->tiles[(int)tetromino->position.x + x]
                   [(int)tetromino->position.y + y]
            .color = tetromino->color;
      }
    }
  }
}

void switchTetromino(Tetromino *current_tetromino, Tetromino *next_tetromino) {
  Board *board = current_tetromino->board;
  current_tetromino[0] = *next_tetromino;
  current_tetromino->board = board;
  current_tetromino->position =
      (Vector2){floor((double)(current_tetromino->board->size.x / 2 -
                               (float)current_tetromino->dimension / 2)),
                0};
  current_tetromino->moving = true;
  next_tetromino[0] =
      initTetromino(next_tetromino->board, (Shape)(rand() % NUM_SHAPES));
}

void deleteTetromino(Tetromino *tetromino) { free(tetromino->tiles); }
