//
// Created by jun zhao on 2018/12/19.
//

#ifndef PROJ_SNAKE_GAMEDEFINE_H
#define PROJ_SNAKE_GAMEDEFINE_H

#define GRID_SIZE 33
#define FENCE_ROW 15  //从屏幕中心(0,0)开始 距离中心点rowBound 上或下有多少格子
#define FENCE_COL 18  //从屏幕中心(0,0)开始 距离中心点colBound 左或右有多少格子
#define GAME_OVER 0
#define GAME_RUNING 1

namespace snake {

    enum class MOVE_DIR {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
}

#endif //PROJ_SNAKE_GAMEDEFINE_H
