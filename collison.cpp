#include "collison.h"
int collison::collide(int colT) const {
    if ( colType == No_Collision ) 
        return No_Collision;

   else if ( colType == Player_Pass_Through ) {
        if ( colT == No_Collision )
            return No_Collision;
            else if ( colT == Player_Pass_Through )
                return Solid_Collision;
            else if ( colT == Bullet_Pass_Through )
                return Solid_Collision;
            else if ( colT == Solid_Collision )
                return Solid_Collision;
            else if ( colT == Player_Collison )
                return Player_Pass_Through;
            else if ( colT == Bullet_Collison )
                return Player_Pass_Through;
            else if ( colT == Object_Collison )
                return Player_Pass_Through;

   } else if ( colType == Bullet_Pass_Through ) {
        if ( colT == No_Collision )
            return No_Collision;
            else if ( colT == Player_Pass_Through )
                return Solid_Collision;
            else if ( colT == Bullet_Pass_Through )
                return Solid_Collision;
            else if ( colT == Solid_Collision )
                return Solid_Collision;
            else if ( colT == Player_Collison )
                return Player_Collison;
            else if ( colT == Bullet_Collison )
                return Bullet_Pass_Through;
            else if ( colT == Object_Collison )
                return Bullet_Pass_Through;

   } else if ( colType == Solid_Collision ) {
        if ( colT == No_Collision )
            return No_Collision;
        else
            return Solid_Collision;


   } else if ( colType == Player_Collison ) {
        if ( colT == No_Collision )
            return No_Collision;
            else if ( colT == Player_Pass_Through )
                return Player_Pass_Through;
            else if ( colT == Bullet_Pass_Through )
                return Player_Collison;
            else if ( colT == Solid_Collision )
                return Solid_Collision;
            else if ( colT == Player_Collison )
                return Player_Collison;
            else if ( colT == Bullet_Collison )
                return Bullet_Collison;
            else if ( colT == Object_Collison )
                return Object_Collison;

   } else if ( colType == Bullet_Collison ) {
        if ( colT == No_Collision )
            return No_Collision;
            else if ( colT == Player_Pass_Through )
                return Player_Pass_Through;
            else if ( colT == Bullet_Pass_Through )
                return Bullet_Pass_Through;
            else if ( colT == Solid_Collision )
                return Solid_Collision;
            else if ( colT == Player_Collison )
                return Player_Collison;
            else if ( colT == Bullet_Collison )
                return No_Collision;
            else if ( colT == Object_Collison )
                return No_Collision;

   } else if ( colType == Object_Collison ) {
        if ( colT == No_Collision )
            return No_Collision;
            else if ( colT == Player_Pass_Through )
                return Solid_Collision;
            else if ( colT == Bullet_Pass_Through )
                return Solid_Collision;
            else if ( colT == Solid_Collision )
                return Solid_Collision;
            else if ( colT == Player_Collison )
                return Player_Collison;
            else if ( colT == Bullet_Collison )
                return Bullet_Pass_Through;
            else if ( colT == Object_Collison )
                return Object_Collison;
    } 
}