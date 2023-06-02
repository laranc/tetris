#pragma once

#include <stdlib.h>

#include <raylib.h>

#include "board.h"

#define NUM_SHAPES 5

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
  double speed;
  bool moving;
  struct {
    int top;
    int right;
    int bottom;
    int left;
  } offset;
} Tetromino;

Tetromino initTetromino(Board *board, Shape shape);
void drawTetromino(const Tetromino *tetromino);
void moveTetrominoLeft(Tetromino *tetromino);
void moveTetrominoRight(Tetromino *tetromino);
void rotateTetrominoClockwise(Tetromino *tetromino);
void rotateTetrominoCounterClockwise(Tetromino *tetromino);
void dropTetromino(Tetromino *tetromino);
void switchTetromino(Tetromino *current_tetromino, Tetromino *next_tetromino);
void deleteTetromino(Tetromino *tetromino);
