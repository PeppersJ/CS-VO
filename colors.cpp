#include "colors.h"
bool colors::init_pairBG(int color, int fgColor) {
    return init_pair(color, fgColor, Color_BG);
}
void colors::defineColorPairs() {
    // Defines colors
    init_color(Color_Player, 1000, 1000, 1000);
    init_color(Color_CT, 0, 500, 0);
    init_color(Color_T, 1000, 0, 0);
    init_color(Color_Bomb, 1000, 750, 0);
    init_color(Color_Bullet, 50, 750, 0);
    init_color(Color_Wall, 500, 0, 500);
    
    // Defines color pairs
    init_pair(Color_Pair_Default, COLOR_WHITE, Color_BG);
    init_pair(Color_Pair_Player, Color_Player, Color_BG);// entity_t::Color_Player);
    init_pair(Color_Pair_CT, Color_CT, Color_BG);
    init_pair(Color_Pair_T, Color_T, Color_BG);
    init_pair(Color_Pair_Bomb, Color_Bomb, Color_BG);
    init_pair(Color_Pair_Bullet, Color_Bullet, Color_BG);
    init_pair(Color_Pair_Wall, Color_Wall, Color_BG);
}
int colors::colorPair(int objColor) const {
    switch(objColor) {
        case Color_Player: return Color_Pair_Player;
        case Color_CT: return Color_Pair_CT;
        case Color_T: return Color_Pair_T;
        case Color_Bomb: return Color_Pair_Bomb;
        case Color_Bullet: return Color_Pair_Bullet;
        case Color_Wall: return Color_Pair_Bullet;
        default: return Color_Pair_Default;
    }
}