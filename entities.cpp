#include <ncurses.h>    //I/O to terminal
#include "entities.h"
// ----  ---- //
//	entity_t  //
// ----  ---- //
entity_t::entity_t() : ID(entCnt++) {}
entity_t::entity_t(const entity_t& objB) : ID(entCnt++) {
    colType = objB.colType;
    curPos = objB.curPos;
    m_model = objB.model();
    lastDir = objB.lastDir;
    m_speed = objB.speed();
    path = objB.path;
}
char entity_t::model() const { return m_model; }
int entity_t::speed() const { return m_speed; }
int entity_t::whatAmI() const { return m_type; }
int entity_t::entCnt = 0;

// ---- //
// bomb //
// ---- //
bomb::bomb() {
        m_type = Object;
        colType = Object_Collison;
        m_model = 'B';
        m_speed = 0;
    }
bomb::bomb(bool p) : m_planted(p) {
        m_type = Object;
        colType = Object_Collison;
        m_model = 'B';
        m_speed = 0;
    }
int bomb::countdown(bool ticking) {
    if (m_planted == true) {
        if (ticking == true && m_time > 0){
            m_time--;
            printw("TICK: %d", m_time);
        }
        else if (m_time == 0)
            m_explode = true;
        return m_time;
    }
    return -1;
}
int bomb::diffuse(bool ticking) {
    if(m_planted == true) { 
        if(ticking == true && m_time > 0 && m_timeDiffuse > 0){
            m_timeDiffuse--;
        }
        else if (m_timeDiffuse == 0)
            m_diffused = true;
        else
            m_timeDiffuse = DIFFUSE_TIME;
    }
}
bool bomb::isPlanted() const { return m_planted; }
bool bomb::isDiffused() const { return m_diffused; }

// ----  ---- //
//   bullet   //
// ----  ---- //
bullet::bullet (entity_t e) {
    m_type = e.whatAmI();
    colType = e.colType;
    m_model = e.model();
    curPos = e.curPos;
    lastDir = e.lastDir;
    m_speed = e.speed();
    dirEntered = e.dirEntered;
    path = e.path;
}
bullet::bullet(int d, cell* pos, int dirEntered) {
    m_type = Bullet;
    colType = Bullet_Collison;
    lastDir = d;
    m_model = '.';
    curPos = pos;
    m_speed = 3;
    this->dirEntered = dirEntered;
}
int bullet::damage() const { return m_damage; }

// ----  ---- //
//   player   //
// ----  ---- //
player::player() {
    m_type = Player;
    colType = Player_Collison;
    m_model = '@';
    m_speed = 1;
}
player::player(const player& ent){
    m_type = ent.whatAmI();
    colType = ent.colType;
    m_model = ent.model();
    curPos = ent.curPos;
    lastDir = ent.lastDir;
    m_speed = ent.speed();
    dirEntered = ent.dirEntered;
    m_health = ent.health();
    m_alive = ent.isAlive();
    path = ent.path;
}
player::player(cell* pos) { 
    m_type = Player;
    colType = Player_Collison;
    m_model = '@';
    curPos = pos;
    m_speed = 1;
}
bullet* player::shoot(int dir) {
    if (dir == -1)
        dir = lastDir;
    return new bullet(dir, curPos, dirEntered);
}
void player::takeDamage(int amount) {
    if (amount < 0) // No negative damage
        amount *= -1;
    if (amount > m_health) // No negaative health
        m_health = 0;
    else
        m_health -= amount;
    if (m_health == 0)
        death();
}
void player::death() {
    m_alive = false;
    m_model = 'q';
    m_speed = 0;
    colType = No_Collision;
}
int player::move() {

}
int player::thinkAi() const { return m_priorStatus; }
int player::thinkAi(int newStatus) {
    curStatus = newStatus;
    m_priorStatus = newStatus;
    switch(curStatus) {
        case Do_Nothing:
            return Do_Nothing;
        case Get_Bomb:
            return Get_Bomb;
    }
}
bool player::isAlive() const { return m_alive; }
int player::health() const { return m_health; }
int player::priorStatus() const { return m_priorStatus; }
bool player::plantBomb() {
    if (hasBomb == true) {
        m_priorStatus = curStatus;
        curStatus = Planting;
        hasBomb = false;
        printw("Planting");
        return true;
    }
    return false;
}