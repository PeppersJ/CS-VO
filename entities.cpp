#include "entities.h"
// ----  ---- //
//	entity_t  //
// ----  ---- //
entity_t::entity_t() : ID(entCnt++) { }
entity_t::entity_t(const entity_t& objB) : ID(entCnt++) {
    if (this != &objB) {
        colType = objB.colType;
        curPos =  objB.curPos;
        lastDir = objB.lastDir;
        m_model = objB.model();
        m_speed = objB.speed();
        m_color = objB.color();
        m_type = whatAmI();
    }
}
entity_t::~entity_t() = default;
entity_t& entity_t::operator = (const entity_t& objB) {
    if (this != &objB) {
        colType = objB.colType;
        curPos = objB.curPos;
        lastDir = objB.lastDir;
        m_model = objB.model();
        m_speed = objB.speed();
        m_color = objB.color();
        m_type = whatAmI();
    }
    return *this;
}

char entity_t::model() const { return m_model; }
int entity_t::speed() const { return m_speed; }
int entity_t::whatAmI() const { return m_type; }
int entity_t::color () const { return m_color; }

int entity_t::entCnt = 0;

// ---- //
// bomb //
// ---- //
bomb::bomb() {
        m_type = Object;
        colType = Object_Collison;
        m_model = 'B';
        m_speed = 0;
        m_color = colors::Color_Bomb;
}
bomb::bomb(bool p) : m_planted(p) {
        m_type = Object;
        colType = Object_Collison;
        m_model = 'B';
        m_speed = 0;
        m_color = colors::Color_Bomb;
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
bullet::bullet (entity_t e){
    m_type = e.whatAmI();
    colType = e.colType;
    m_model = e.model();
    lastDir = e.lastDir;
    m_speed = e.speed();
    curPos = e.curPos;
    dirEntered = e.dirEntered;
    m_color = e.color();
}
bullet::bullet(int d, cell* pos, int dirEntered) {
    m_type = Bullet;
    colType = Bullet_Collison;
    curPos = pos;
    lastDir = d;
    m_model = '.';
    m_speed = 3;
    this->dirEntered = dirEntered;
    m_color = colors::Color_Bullet;
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
    if (!isAi())
        m_color = colors::Color_Player;
    if (isTerrorist())
        m_color = colors::Color_T;
    else
        m_color = colors::Color_CT;
}
player::player(bool ai = false, bool t = false) : m_isAi(ai), m_isTerrorist(t) {
    m_type = Player;
    colType = Player_Collison;
    m_model = '@';
    m_speed = 1;
    if (!isAi())
        m_color = colors::Color_Player;
    if (isTerrorist())
        m_color = colors::Color_T;
    else
        m_color = colors::Color_CT;
}

player::player(const player& ent) {
    m_type = ent.whatAmI();
    colType = ent.colType;
    m_model = ent.model();
    m_speed = ent.speed();
    lastDir = ent.lastDir;
    curPos = ent.curPos;
    dirEntered = ent.dirEntered;
    m_health = ent.health();
    m_alive = ent.isAlive();
    m_isAi = isAi();
    m_isTerrorist = isTerrorist();
    *path = *ent.path;
    m_color = ent.color();
}
player::player(cell* pos) { 
    m_type = Player;
    colType = Player_Collison;
    m_model = '@';
    curPos = pos;
    m_speed = 1;
    if (!isAi())
        m_color = colors::Color_Player;
    if (isTerrorist())
        m_color = colors::Color_T;
    else
        m_color = colors::Color_CT;
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
int player::moveDest() const { return m_moveDest; }
char player::moveDir(const charMap* world) {
// Returns the action needed to reach next cell in path
    return world->neighborDir(path->peek(), curPos->pathID);
}
int player::think(const charMap* world, bomb* bmb) {
    srand(time(NULL));
    if (isAi()) {
        if (isTerrorist()) {
            if (bmb && bmb->isPlanted() == false) { 
                if (bmb->beingGrabed == false) { //Check if bomb is dropped
                    bmb->beingGrabed = true; // True when AI intends to grab bomb
                    m_moveDest = bmb->curPos->pathID;
                    return updateStatus(Get_Bomb);
                } else if ( status() == Get_Bomb ) {
                    return updateStatus(Get_Bomb);
                }

            } else { //Bomb isn't dropped
                if (hasBomb && status() != Planting) { 
                    if (rand() % 2  >= 1) {  // Choose random plant site
                        int Y = rand() % world->siteAHeight() + world->siteA()->y;
                        int X = rand() % world->siteAWidth() + world->siteA()->x;
                        cell* temp = &(*world)[Y][X];
                        m_moveDest = temp->pathID;
                        while(temp->model() != 'P') {
                            Y = rand() % world->siteAHeight() + world->siteA()->y;
                            X = rand() % world->siteAWidth() + world->siteA()->x;
                            printf("Y:%d X:%d\n", Y, X);
                            *temp = (*world)[Y][X];
                            m_moveDest = temp->pathID;
                        }
                    }
                    else {                    
                        int Y = rand() % world->siteBHeight() + world->siteB()->y;
                        int X = rand() % world->siteBWidth() + world->siteB()->x;
                        cell* temp = &(*world)[Y][X];
                        m_moveDest = temp->pathID;
                        while(temp->model() != 'P') {
                            Y = rand() % world->siteBHeight() + world->siteB()->y;
                            X = rand() % world->siteBWidth() + world->siteB()->x;
                            *temp = (*world)[Y][X];
                            m_moveDest = temp->pathID;
                        }
                    }
                    return updateStatus(Planting);
                } else if (hasBomb && status() == Planting) {
                    //if (curPos->pathID == m_moveDest)
                       // plantBomb(bmb);
                    return updateStatus(Planting);
                }
                //if (status() == Plant_Fail)
                //m_moveDest = world->siteA()->pathID;
                return updateStatus(Moving);
            }
        }
        if (!isTerrorist()) {
            if(bmb && bmb->isPlanted() == true) {
                if(bmb->beingDiffused == false) {
                    bmb->beingDiffused = true;
                    m_moveDest = bmb->curPos->pathID;
                    return updateStatus(Diffusing);
                } else if ( status() == Diffusing ){
                    return updateStatus(Diffusing);
                }
            }
        }
    }
    return -1;
}
int player::status() const { return m_priorStatus; }
int player::updateStatus(int newStatus) {
    curStatus = newStatus;
    m_priorStatus = newStatus;
}
bool player::isAi() const { return m_isAi; }
bool player::isAlive() const { return m_alive; }
bool player::isTerrorist() const { return m_isTerrorist ? true : false; }
int player::health() const { return m_health; }
int player::priorStatus() const { return m_priorStatus; }
bool player::plantBomb(bomb* b){
    if (hasBomb == true) {
        printw("PLANTING");
        return true;
        //hasBomb = false;
        //b = new bomb(true);
        //return b;
    }
    return false;
}