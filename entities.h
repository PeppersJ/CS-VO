#ifndef ENTITES_H
#define ENTITES_H
#include <cstdlib>  //Rand
#include <time.h>     //Rand
#include "colors.h"
#include "collison.h"
#include "charMap.h"
#include "queue.h"

class charMap;
class world;
struct cell;
class entity_t : public collison {
public:
    enum Direction {
        Up, Right, Down, Left   //Order important for line world.cpp:337
    };
    enum ObjectType { 
        Player, Object, Bullet, Invalid
    };

    entity_t();
    entity_t(const entity_t& objB);
    virtual ~entity_t();
    entity_t& operator =(const entity_t& objB);

    int whatAmI() const;
    char model() const;
    int speed() const;
    int color() const;

    cell* curPos{ NULL };
    int lastDir{ Up };
  // const int ID{ -1 } 
    int ID{ -1 }; 
    int dirEntered{ -1 };
protected:
    char m_model{ ' ' };
    int m_color{ COLOR_BLACK };
    int m_type{ Invalid };
    int m_speed{ 0 };
private:
    friend world;

    void defineColors();

    static int entCnt;
};

class bomb : public entity_t {
public:
    bomb();
    bomb(bool planted);

    int countdown(bool ticking);
    int diffuse(bool ticking);

    bool isPlanted() const;
    bool isDiffused() const;

    bool beingGrabed{ false };  //for use with player AI
    bool beingDiffused{ false };
private:
    bool m_planted{ false };
    bool m_diffused{ false };
    bool m_explode{ false };
    bool m_dropped{ true };
    int m_time{ 120 }; //in ticks to explode
    int m_timeDiffuse { DIFFUSE_TIME };
    const int DIFFUSE_TIME { 20 };
};

class bullet : public entity_t {
public:
    bullet();
    bullet (entity_t e);
    bullet(int d, cell* pos, int dirEntered);

    int damage() const;
private:
    int m_damage{ 25 };
};

class player : public entity_t {
public:
    enum Status{
        Do_Nothing, Get_Bomb, Moving, Planting, Plant_Fail, Diffusing
    };

    player();
    player(bool ai, bool terrorist);
    player(const player& ent);
    player(cell* pos);

    bullet* shoot(int dir = -1);
    bool plantBomb(bomb* );
    void takeDamage(int amount);
    void death();
    int updateStatus(int newStatus);
    int think(const charMap* wolrd, bomb* bmb);
    char moveDir(const charMap*);

    int moveDest() const;
    int status() const;
    bool isAi() const;
    bool isAlive() const;
    bool isTerrorist() const;
    int health() const;
    int priorStatus() const;

    int curStatus{ Do_Nothing };
    bool hasBomb { false };
    queue* path{ NULL }; 

    cell* randCell(int height, int width) const;
private:
    bool m_isAi{ true };
    bool m_alive{ true };
    bool m_isTerrorist{ false };
    int m_diffuseTime{ 5 };
    int m_health{ 100 };
    int m_moveDest{ -1 };
    int m_priorStatus{ -1 };
};

#endif
