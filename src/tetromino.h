#pragma once

#include <raylib.h>

#include "board.h"

typedef enum Shape { STRAIGHT, SQUARE, TEE, JAY, ELL, SKEWS, SKEWZ } Shape;
typedef enum Rotation { UP, RIGHT, DOWN, LEFT } Rotation;

typedef struct Tetromino {
  Vector2 position;
  Shape shape;
  bool *tiles;
  int dimension;
  Color color;
  Rotation rotation;
  Board *board;
} Tetromino;

Tetromino initTetromino(Board *board, Shape shape);
void drawTetromino(const Tetromino *tetromino);
void rotateClockwise(Tetromino *tetromino);
void rotateCounterClockwise(Tetromino *tetromino);
void deleteTetromino(Tetromino *tetromino);
