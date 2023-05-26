#include "board.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

Board initBoard(Vector2 pos, Vector2 size, int tile_size, int padding) {
  Board board;
  board.position = pos;
  board.size = size;
  board.tile_size = tile_size;
  board.padding = padding;

  assert(board.size.x > 0 && board.size.y > 0);
  assert(board.tile_size > 0);

  Tile **tiles = (Tile **)malloc(sizeof(Tile *) * size.x);

  for (int i = 0; i < size.x; i++) {
    tiles[i] = (Tile *)malloc(sizeof(Tile) * size.y);
  }

  for (int i = 0; i < size.x; i++) {
    for (int j = 0; j < size.y; j++) {
      tiles[i][j] = (Tile){false, BLACK};
    }
  }

  board.tiles = tiles;

  return board;
}

void drawBoard(const Board *board) {
  for (int x = 0; x < board->size.x; x++) {
    for (int y = 0; y < board->size.y; y++) {
      if (tileExists(board, (Vector2){x, y})) {
        drawTile(board, (Vector2){x, y});
      }
    }
  }
}

void drawBorder(const Board *board) {
  Rectangle rec = {board->position.x - (float)board->tile_size / 2,
                   board->position.y - (float)board->tile_size / 2,
                   (board->size.x * board->tile_size) + board->tile_size,
                   (board->size.y * board->tile_size) + board->tile_size};
  DrawRectangleLinesEx(rec, (float)board->tile_size / 2, WHITE);
}

void deleteBoard(Board *board) {
  for (int i = 0; i < board->size.x; i++) {
    free(board->tiles[i]);
  }
  free(board->tiles);
}

void setTile(Board *board, Vector2 pos, Color color) {
  assert(pos.x >= 0 && pos.y >= 0 && pos.x < board->size.x &&
         pos.y < board->size.y);
  board->tiles[(int)pos.x][(int)pos.y].color = color;
}

void drawTile(const Board *board, Vector2 pos) {
  drawTileC(board, pos, board->tiles[(int)pos.x][(int)pos.y].color);
}

void drawTileC(const Board *board, Vector2 pos, Color color) {
  assert(pos.x >= 0 && pos.y >= 0 && pos.x < board->size.x &&
         pos.y < board->size.y);
  Vector2 position = {
      board->position.x + board->padding + (pos.x * board->tile_size),
      board->position.y + board->padding + (pos.y * board->tile_size)};
  Vector2 size = {board->tile_size - board->padding,
                  board->tile_size - board->padding};
  DrawRectangleV(position, size, color);
}

bool tileExists(const Board *board, Vector2 pos) {
  assert(pos.x >= 0 && pos.y >= 0 && pos.x < board->size.x &&
         pos.y < board->size.y);
  return board->tiles[(int)pos.x][(int)pos.y].exists;
}

void removeTile(Tile *tile) { tile->exists = false; }
