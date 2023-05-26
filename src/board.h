#pragma once

#include <raylib.h>

typedef struct Tile {
  bool exists;
  Color color;
} Tile;

typedef struct Board {
  Tile **tiles;
  Vector2 position;
  Vector2 size;
  int tile_size;
  int padding;
} Board;

Board initBoard(Vector2 pos, Vector2 size, int tile_size, int padding);
void drawBoard(const Board *board);
void drawBorder(const Board *board);
void deleteBoard(Board *board);

void setTile(Board *board, Vector2 pos, Color color);
void drawTile(const Board *board, Vector2 pos);
void drawTileC(const Board *board, Vector2 pos, Color color);
bool tileExists(const Board *board, Vector2 pos);
void removeTile(Tile *tile);
