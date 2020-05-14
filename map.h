//
// Created by Rafal on 5/14/20.
//

#ifndef MAIN_MAP_H
#define MAIN_MAP_H

#include "game_structure.h"
#include "graphics.h"

rect obstacles[19] = {
        (rect){{0,   0}, BOARD_WIDTH, 30},
        (rect){{0,   0}, 30, BOARD_HEIGHT},
        (rect){{BOARD_WIDTH-30,0}, 30, BOARD_HEIGHT},
        (rect){{0,   BOARD_HEIGHT-30}, BOARD_WIDTH, 30},
        (rect){{30,  270}, 60,  180},
        (rect){{390, 330}, 60,  120},
        (rect){{630, 330}, 60,  120},
        (rect){{510, 90},  60,  300},
        (rect){{270, 90},  60,  300},
        (rect){{750, 90},  60,  300}, //10
        (rect){{810, 90},  60,  60},
        (rect){{810, 330}, 60,  60},
        (rect){{870, 210}, 60,  60},
        (rect){{270, 150}, 540, 60},
        (rect){{90,  150}, 120, 60}, //15
        (rect){{210, 270}, 60,  120},
        (rect){{150, 330}, 60,  60},
        (rect){{390, 30},  60,  60},
        (rect){{630, 30},  60,  60}
};

game_object go = {19, obstacles, 1, NULL, BOARD_WIDTH, BOARD_HEIGHT};

#endif //MAIN_MAP_H
