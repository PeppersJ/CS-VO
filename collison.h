#ifndef COLLISON_CLASS
#define COLLISON_CLASS
#include <stdlib.h>

class collison {
public:
    enum Collison {
        No_Collision, Player_Pass_Through, Bullet_Pass_Through,    
        Player_Collison, Bullet_Collison, Object_Collison, Solid_Collision
    }; 
    int collide(int colT);
    int colType{ No_Collision };
};

#endif
