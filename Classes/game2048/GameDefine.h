//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_ANDROID_GAMEDEFINE_H
#define PROJ_ANDROID_GAMEDEFINE_H

#define GAME_ROWS 4
#define GAME_COLS 4
#define GAME_TILED_WIDTH 64   // 64*4 + 2*(4+1) = 256+10 = 266
#define GAME_TILED_HEIGHT 64
#define GAME_TILED_BOARD_WIDTH 2  //格子间的 分界线 的宽度

enum class MOVE_DIR {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif //PROJ_ANDROID_GAMEDEFINE_H
