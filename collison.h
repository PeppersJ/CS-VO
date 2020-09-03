#ifndef COLLISON_H
#define COLLISON_H
#include <stdlib.h>

class collison {
public:
    enum Collison {
        No_Collision, Player_Pass_Through, Bullet_Pass_Through,    
        Bullet_Collison, Player_Collison, Object_Collison, Solid_Collision
    }; 

    int collide(int colT) const;

    int colType{ No_Collision };
};

#endif
