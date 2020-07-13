// Finish working on path queue
// Fix running out of memory space (Crashes on 52 entitiy)
// Add corpses
// SegFalt on shooting w/o moving
// Fix double damge when shooting adjacant
// Fix incositant spawning of t side players
// Fix getting stuck after bomb has been planted
// Throw error for missing m
// Fix diffusing
// Fix deuque
// Fix enquenext
// Make node subscript operator a const function
// Possibly assign internal pointer in player function to reference world

//CS:VO created by Rishawn Peppers Johnson
//Complie as: ./csvo.sh
#include <stdlib.h>     //srand
#include <vector>       //vector
#include <cstdlib>      //rand
#include "queue.h"
#include "collison.h"
#include "entities.h"
#include "charMap.h"

// *****************************
// Main Code
// *****************************

class world {
public:
    enum Direction {
        Up, Right, Down, Left
    };
    world();
    world(std::string mapName);
    ~world();
    void printMap() const;
    entity_t* spawn(entity_t* e, cell* c) {
        e->curPos = c;
        m_ent[entity_t::entCnt - 1] = e;
        c->ent = e;
        return c->ent;
    }
    player* spawn(player* e, cell* c) {
        e->curPos = c;
        m_ent[entity_t::entCnt - 1] = e;
        c->ent = e;
        return static_cast<player*>(c->ent);
    }
    bomb* spawn(bomb* e, cell* c) {
        e->curPos = c;
        m_ent[entity_t::entCnt - 1] = e;
        c->ent = e;
        return static_cast<bomb*>(c->ent);
    }
    entity_t* shoot(player* e) {
        bullet* b = e->shoot();
        if ( e->lastDir == Up ) {
            move(b, Up, b->speed());
            spawn(b, b->curPos);
        }
        else if ( e->lastDir == Down ) {
            move(b, Down, b->speed());
            spawn(b, b->curPos);
        }
        else if ( e->lastDir == Left ) {
            move(b, Left, b->speed());
            spawn(b, b->curPos);
        }
        else if ( e->lastDir == Right ) {
            move(b, Right, b->speed());
            spawn(b, b->curPos);
        }
        e->curPos->ent = e;
    }
/*    void entityCntReset() {
        entity_t::entCnt = 0;
    }*/
    bool swap(int* a, int* b){
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
        return true;
    }
    queue& pathFinding(int source, int dest) {
        int bound = worldMap->width() * worldMap->height();
        std::vector<int> map(bound, std::numeric_limits<int>::max());  // Every cell on map
        std::vector<int> traverse(bound, false);
        std::vector<bool> shortest(bound, false);
        std::vector<int> parent(bound, -1);
        std::vector<char> dir(bound, 'n');
        queue* path = new queue(bound);

        for(int i = 0; i < worldMap->height(); i++) {
            for (int j = 0; j < worldMap->width(); j++) {
                traverse[(*worldMap)[i][j].pathID] = (*worldMap)[i][j].col();
             //   if ((*worldMap)[i][j].colType != (*worldMap)[i][j].col()){
             //       printw("ColType %d Col %d", (*worldMap)[i][j].colType, (*worldMap)[i][j].col() );
             //   }
                if((*worldMap)[i][j].pathID == source)
                    traverse[(*worldMap)[i][j].pathID] = entity_t::No_Collision;
            }
        }

        map[source] = 0; // distance from self is 0

        int count = 0;
        char enterDir = 'n';
        int ndx = 0;
        int min;
        int min_pos;
        // Find shortest path
        for(int i = 0; i < bound; i++) {
            min = std::numeric_limits<int>::max();
            // Find closests cell
            for(int j = 0; j < bound; j++)
                if(shortest[j] == false && map[j] <= min) {
                        ndx = j;
                        min = map[j];
                    }

            shortest[ndx] = true; // Mark closest cell as visted

            char dir_temp;
            for (int j = 0; j < bound; j++) {
                dir_temp = worldMap->neighborDir(ndx, j); /**** May cause problems ****/
                if(dir_temp != 'n' && map[ndx] != std::numeric_limits<int>::max()) {
                    if(map[ndx] + 1 < map[j] && !shortest[j]) {
                        if( traverse[j] == collison::Player_Pass_Through ) {
                            dir[j] = dir_temp;
                            map[j] = map[ndx] + 1;
                            parent[j] = ndx;
                            if (enterDir == 'n')
                                enterDir = dir_temp;
                        }
                        else if ( traverse[ndx] == collison::No_Collision ) {
                            if (enterDir == 'w' || enterDir == 's'){
                                if (dir_temp == 'w' || dir_temp == 's'){
                                    dir[j] = dir_temp;
                                    map[j] = map[ndx] + 1;
                                    parent[j] = ndx;
                                    enterDir = 'n';
                                }
                            }
                            else if (enterDir == 'a' || enterDir == 'd'){
                                if (dir_temp == 'a' || dir_temp == 'd'){
                                    dir[j] = dir_temp;
                                    map[j] = map[ndx] + 1;
                                    parent[j] = ndx;
                                    enterDir = 'n';
                                }
                            }
                            else {
                                    dir[j] = dir_temp;
                                    map[j] = map[ndx] + 1;
                                    parent[j] = ndx;
                            }
                        }
                    }
                }
            }
        }

        int cur = dest;
        path->enqueue(dest);
        while(parent[cur] != -1){
            //printw("%d[%c]->", cur, dir[cur]);
            path->enqueue(cur);
            cur = parent[cur];
        }

        return *path;
/*     int cur = dest;
        while(parent[cur].data != -1) {
        //   printw("%d[%c]->", cur, dir[cur]);
            for(int i = 0; i < worldMap->height(); i++) {
                for (int j = 0; j < worldMap->width(); j++) {
                    if ((*worldMap)[i][j].pathID == cur)
                        (*worldMap)[i][j].obj = '*';

                    if ((*worldMap)[i][j].pathID == source)
                        (*worldMap)[i][j].obj = 'S';

                    if ((*worldMap)[i][j].pathID == dest)
                        (*worldMap)[i][j].obj = 'D';

                    //if ((*worldMap)[i][j].pathID == 1229)     
                  //      (*worldMap)[i][j].obj = '+';
                }
            }
            cur = parent[cur].data;
        }*/
    }
    queue& pathFinding(cell* s, cell* d) {
        pathFinding( s->pathID, d->pathID);
    }
    void victory(bool tSideWin) {
 //       win = true;
        if (tSideWin == true)
            printw("T WINS");
        else
            printw("CT WINS");
    }
    void plantBomb(entity_t* e) {
        if(player* p = dynamic_cast<player*>(e))
            if (p->plantBomb()) {
                switch (p->lastDir){
                    case Up:
                        theBomb = spawn(new bomb(true), p->curPos->above);
                        break;
                    case Down:
                        theBomb = spawn(new bomb(true), p->curPos->below);
                        break;
                    case Left:
                        theBomb = spawn(new bomb(true), p->curPos->left);
                        break;
                    case Right:
                        theBomb = spawn(new bomb(true), p->curPos->right);
                        break;
                }
            }
    }
    void diffuse(entity_t* e) {
        if (player* p = dynamic_cast<player*>(e)){
            if(p->curPos->above->ent)
                if(p->curPos->above->ent->whatAmI() == entity_t::Object)
                    static_cast<bomb*>(p->curPos->above->ent)->diffuse(true);
            else if(p->curPos->below->ent)
                if(p->curPos->below->ent->whatAmI() == entity_t::Object)
                    static_cast<bomb*>(p->curPos->below->ent)->diffuse(true);
            else if(p->curPos->left->ent)
                if(p->curPos->left->ent->whatAmI() == entity_t::Object)
                    static_cast<bomb*>(p->curPos->left->ent)->diffuse(true);
            else if(p->curPos->right->ent)  
                if(p->curPos->right->ent->whatAmI() == entity_t::Object)  
                    static_cast<bomb*>(p->curPos->right->ent)->diffuse(true);
        }     
    }
    void update(char usrIn) {
        if( win == false ){
            if ( usrIn == 'W' || usrIn == 'w' )
                move(human, Up);
            else if ( usrIn == 'S' || usrIn == 's' )
                move(human, Down);
            else if ( usrIn == 'A' || usrIn == 'a' )
                move(human, Left);
            else if ( usrIn == 'D' || usrIn == 'd' )
                move(human, Right);
            else if ( usrIn == ' ')
                shoot(human);
            else if ( usrIn == 'P' || usrIn == 'p' )
                plantBomb(human);
            else if ( usrIn == 'E' || usrIn == 'e')
                diffuse(human);
        }
    } 
    void refresh() {
        for ( int i = 0; i < entity_t::entCnt; i++) {
            if ( m_ent[i] != NULL ) {
                if ( m_ent[i]->whatAmI() == entity_t::Object ) {
                    if ( bomb* b = dynamic_cast<bomb*>(m_ent[i]) ){
                        if ( b->isPlanted() && b->isDiffused() == false) {
                            if (b->countdown(true) == 0)
                                victory(true);// Victory T 1
                        }
                        else if (b->isPlanted() && b->isDiffused() == true)
                            victory(false);// Victory CT 1
                    }

                }
                else if ( m_ent[i]->whatAmI() == entity_t::Bullet )
                    move(m_ent[i], m_ent[i]->lastDir, m_ent[i]->speed());
                else if ( m_ent[i]->whatAmI() == entity_t::Player ) {
                    player* p = static_cast<player*>(m_ent[i]);
                    p->think(worldMap, theBomb);

                    if (p->status() == player::Moving) {
                        if(p->path == NULL)
                            *p->path = pathFinding(p->curPos->pathID, p->moveDest());

                        else if(p->path->tail() == p->moveDest()) { // Check if same dest
                            if( move(m_ent[i], p->moveDir(worldMap)) ) //Check if traversable
                                p->path->dequeue();
                        } else {
                            delete p->path; /****Check functionality****/
                            *p->path = pathFinding(p->curPos->pathID, p->moveDest());
                            move(m_ent[i], p->path->dequeue());
                        }
                    }
                }
            }
        }
    }
    bool move(entity_t* e, int dir, int dist) {
        for ( int i = 0; i < dist; i++ )
            if ( move(e, dir) == false)
                return false;
        return true;
    }

    bool move(entity_t* e, int dir) {
        charMap& worldMapRef = *worldMap;
           
        int cType = -1;
        cell* colCell = NULL;
        // Less than 3 because 0 - 3 collion types in enitity_t are allowed movement
        if ( dir == Up && worldMap->inBounds(e->curPos->above)) {
            cType = e->collide(e->curPos->above->col());
            colCell = e->curPos->above;
            printw("Col:%d", cType);
            if(cType < 3 || cType == entity_t::Object_Collison) {            
               // if ( cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through ) {
                if ( cType == entity_t::Player_Pass_Through ) {
                    if ( e->dirEntered == -1 ) //  == some invalid value
                        e->dirEntered = dir;
                }
                else if ( e->dirEntered == Up || e->dirEntered== Down )
                    e->dirEntered = -1;

                if ( e->dirEntered == -1 || cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison ) {
                    if (cType == entity_t::Object_Collison) {
                        if (static_cast<bomb*>(colCell->ent)->isPlanted() == true)
                            return false;
                        else {
                            static_cast<player*>(m_ent[e->ID])->hasBomb = true;
                            printw("DELETED");
                            delete m_ent[colCell->ent->ID];
                            m_ent[colCell->ent->ID] = NULL;
                            //delete theBomb;
                            theBomb = NULL;
                        }
                    }                  
                    e->curPos->above->ent = e;
                    e->curPos->ent = NULL;
                    e->curPos = e->curPos->above;
                    e->lastDir = Up;
                    return true;
                }
            }
        } else if ( dir == Down && worldMap->inBounds(e->curPos->below)) {
            cType = e->collide(e->curPos->below->col());
            colCell = e->curPos->below;
            printw("Col:%d", cType);
            if (cType < 3 || cType == entity_t::Object_Collison) {
                if ( cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison) {
                    if ( e->dirEntered == -1 ) //  == some invalid value
                        e->dirEntered = dir;
                }
                else if ( e->dirEntered == Up || e->dirEntered == Down )
                    e->dirEntered = -1;
                if ( e->dirEntered == -1 || cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison ) {
                    if (cType == entity_t::Object_Collison) {
                        if (static_cast<bomb*>(colCell->ent)->isPlanted() == true)
                            return false;
                        else {
                            static_cast<player*>(m_ent[e->ID])->hasBomb = true;
                            printw("DELETED");
                            delete m_ent[colCell->ent->ID];
                            m_ent[colCell->ent->ID] = NULL;
                            //delete theBomb;
                            theBomb = NULL;
                        }
                    }               
                    e->curPos->below->ent = e;
                    e->curPos->ent = NULL;
                    e->curPos = e->curPos->below;
                    e->lastDir = Down;
                    return true;
                }
            }
        } else if ( dir == Left && worldMap->inBounds(e->curPos->left)) {
            cType = e->collide(e->curPos->left->col());
            colCell = e->curPos->left;
            printw("Col:%d", cType);
            if (cType < 3 || cType == entity_t::Object_Collison) {
               // if ( cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison ) {
                if ( cType == entity_t::Player_Pass_Through ) {
                    if ( e->dirEntered == -1 ) //  == some invalid value
                        e->dirEntered = dir;
                }
                else if ( e->dirEntered == Left || e->dirEntered == Right )
                    e->dirEntered = -1;
                if ( e->dirEntered == -1 || cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison ) {
                    if (cType == entity_t::Object_Collison) {
                        if (static_cast<bomb*>(colCell->ent)->isPlanted() == true)
                            return false;
                        else {
                            static_cast<player*>(m_ent[e->ID])->hasBomb = true;
                            printw("DELETED");
                            delete m_ent[colCell->ent->ID];
                            m_ent[colCell->ent->ID] = NULL;
                            //delete theBomb;
                            theBomb = NULL;
                        }
                    }
                    colCell->ent = e;
                    e->curPos->ent = NULL; 
                    e->curPos = colCell;        
                    e->lastDir = Left;
                    return true;
                }
            }
        } else if ( dir == Right && worldMap->inBounds(e->curPos->right)) {
            cType = e->collide(e->curPos->right->col());
            colCell = e->curPos->right;
            printw("Col:%d", cType);
            if(cType < 3 || cType == entity_t::Object_Collison) {
                if ( cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison) {
                    if ( e->dirEntered == -1 ) //  == some invalid value
                        e->dirEntered = dir;
                }
                else if ( e->dirEntered == Left || e->dirEntered == Right )
                    e->dirEntered = -1;
                if ( e->dirEntered == -1 || cType == entity_t::Player_Pass_Through || cType == entity_t::Bullet_Pass_Through || cType == entity_t::Object_Collison ) {
                    if (cType == entity_t::Object_Collison) {
                        if (static_cast<bomb*>(colCell->ent)->isPlanted() == true)
                            return false;
                        else {
                            static_cast<player*>(m_ent[e->ID])->hasBomb = true;
                            printw("DELETED");
                            delete m_ent[colCell->ent->ID];
                            m_ent[colCell->ent->ID] = NULL;
                            //delete theBomb;
                            theBomb = NULL;
                        }
                    }                  
                    e->curPos->right->ent = e;
                    e->curPos->ent = NULL;
                    e->curPos = e->curPos->right;                     
                    e->lastDir = Right;
                    return true;
                }
            }
        }
        if ( e->whatAmI() == entity_t::Bullet ) {
            printw("BULLET: %d ", e->ID);
            if (cType == entity_t::Player_Collison) {
                player* colEnt = NULL;
                colEnt = static_cast<player*>(colCell->ent);
                colEnt->takeDamage(static_cast<bullet*>(e)->damage());
                printw("Target Health: %d ", colEnt->health());
            }
            delete m_ent[e->ID];
            m_ent[e->ID] = NULL;
            e->curPos->ent = NULL;
            //e->curPos->ent = e;
            return false;
        }
        return false;
    }

    bool bombPlanted() const {
        if(theBomb != NULL)
            if (theBomb->isPlanted())
                return true;
        return false;
    }
private:
    std::vector<entity_t*> m_ent{ NULL };
    charMap* worldMap{ NULL };
    player* human{ NULL };
    bomb* theBomb{ NULL };
    bool win{ false };
};

int main() {
    initscr();

    // Generate world.
    world w("sjf_dust2.txt");

    char usrIn;
    while( usrIn != 'q' ) {
        w.printMap();
        usrIn = getch(); // wait for input to close
        w.update(usrIn);
        w.refresh();
        move(0,0);
    }

    endwin();
    return 0;
}
world::world(){ }
world::world(std::string mapName) {
    worldMap = new charMap(mapName);
    charMap& worldMapRef = *worldMap;

    m_ent.resize(50, NULL);
    human = spawn(new player, worldMap->tSpawn());

    // Generate random side
    int side[10]; // stores rand player side
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
        side[i] = rand() % 2;

    cell* tspawn = worldMap->tSpawn();
    cell* ctspawn = worldMap->ctSpawn();

    int tSideCount = 0;
    int ctSideCount = 0;

    for (int i = 0; i < 10; i++) {  // Spawn 10 palyers
        if (side[i] == 0 && tSideCount < 5) { //Assign t side
            spawn(new player, &worldMapRef[tspawn->y][tspawn->x + tSideCount]);
            tSideCount++;
        }
        else if (ctSideCount < 5){
            spawn(new player, &worldMapRef[ctspawn->y][ctspawn->x + ctSideCount]);
           // m_ent[i]->dirEntered = entity_t::Left;
            ctSideCount++;
        }
      //  printw("CNT: %d", entity_t::entCnt);
      //  getch();
    }
    //human = static_cast<player*>(m_ent[0]);
    theBomb = static_cast<bomb*>(spawn(new bomb, worldMap->bombSpawn()));

    //m_ent[0] = new spawn(new bomb, worldMap->tSpawn());
    //pathFinding(human->curPos, human->curPos);
    pathFinding(human->curPos, worldMap->ctSpawn());
    //pathFinding(human->curPos, &worldMapRef[41][67]);
    //pathFinding(&worldMapRef[42][46], &worldMapRef[12][63]);
    //pathFinding(&worldMapRef[42][46], &worldMapRef[13][63]);

}

world::~world() {
    if ( worldMap != NULL )
        delete worldMap;
}

void world::printMap() const {
    charMap& worldMapRef = *worldMap;
    for ( int i = 0; i < worldMap->height(); i++ ) {
        for ( int j = 0; j < worldMap->width(); j++ )
            printw("%c", worldMapRef[i][j].model());
        printw("\n");
    }
}

// Cool little window
/*
    int height = 10;
    int width = 10;
    int start_y = 10;
    int start_x = 10;

    WINDOW * win = newwin(height, width, start_x, start_x);
    refresh();

    box(win, 0, 0);
  //  wprintw(win, "this is my box");
    mvwprintw(win, 1, 1, "this is my box");
    wrefresh(win);
*/