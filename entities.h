#ifndef ENTITES_H
#define ENTITES_H
#include "collison.h"

class world;
struct cell;
class entity_t : public collison {
public:
    enum Direction {
        Up, Right, Down, Left
    };
    enum ObjectType { 
        Player, Object, Bullet, Invalid
    };
    entity_t();
    entity_t(const entity_t& objB);
    char model() const;
    int speed() const;
    virtual int whatAmI() const;

    cell* curPos{ NULL };
    int lastDir{ Up };
    int ID{ -1 };
    int dirEntered{ -1 };
protected:
    char m_model{ ' ' };
    int m_type{ Invalid };
    int m_speed{ 0 };
private:
    friend world;
    static int entCnt;
};

class bomb : public entity_t {
public:
    bomb();
    bomb(bool p);
    int countdown(bool ticking);
    int diffuse(bool ticking);
    bool isPlanted() const;
    bool isDiffused() const;
private:
    bool m_planted{ false };
    bool m_diffused{ false };
    bool m_explode{ false };
    int m_time{ 10 }; //in ticks
    int m_timeDiffuse { DIFFUSE_TIME };
    const int DIFFUSE_TIME { 5 };
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
        Do_Nothing, Get_Bomb, Planting, Diffusing
    };
    player();
    player(const player& ent);
    player(cell* pos);
    bullet* shoot(int dir = -1);
    bool plantBomb();
    void takeDamage(int amount);
    void death();
    int thinkAi() const;
    int thinkAi(int newStatus);
    bool isAlive() const;
    int health() const;
    int priorStatus() const;
    int curStatus{ Do_Nothing };
    bool hasBomb { false };
private:
    bool m_alive{ true };
    int m_diffuseTime{ 5 };
    int m_health{ 100 };
    int m_priorStatus{ Do_Nothing };
};

#endif