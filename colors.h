#ifndef COLORS_H
#define COLORS_H
#include <ncurses.h> 
struct colors {
    colors() { defineColorPairs(); }
    enum ColorPair {
        Color_Pair_Default = 1, Color_Pair_Player, Color_Pair_CT, Color_Pair_T, 
        Color_Pair_Bomb, Color_Pair_Bullet, Color_Pair_Wall
    };

    enum Colors { // Skips over def colors and background colors
        Color_Player = 9, Color_CT, Color_T, Color_Bomb, Color_Bullet, Color_Wall, Color_Invalid
    };
    void defineColorPairs();
    int colorPair(int objColor) const;
    bool init_pairBG(int color, int foreground); // Initiates with deafluat background

    const int Color_BG{ COLOR_BLACK };
};
#endif