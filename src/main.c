#include <raylib.h>

#include "game.h"
#include "settings.h"

int main(void) {
  const Vector2 screen_size = {SCREEN_WIDTH, SCREEN_HEIGHT};
  const Vector2 board_size = {BOARD_WIDTH, BOARD_HEIGHT};
  const Vector2 board_pos = {BOARD_POS_X, BOARD_POS_Y};

  Game game = gameInit(screen_size, "Tetris", GAME_FPS, board_pos, board_size,
                       TILE_SIZE, TILE_PADDING);

  gameStart(&game);

  gameRun(&game);

  gameClose(&game);

  return 0;
}
