#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "queue.h"
#include "collison.h"
#include "entities.h"
#include "charMap.h"

class world {
public:
    enum Direction {
        Up, Right, Down, Left
    };

    world();
    world(std::string mapName);
    ~world();

    entity_t* shoot(player* e);
    entity_t* spawn(entity_t* e, cell* c);
    player* spawn(player* e, cell* c);
    bomb* spawn(bomb* e, cell* c);

    bool swap(int* a, int* b);
    queue& pathFinding(cell* s, cell* d);
    queue& pathFinding(int source, int dest);
    bool move(entity_t* e, int dir, int dist);
    bool move(entity_t* e, char dir);
    bool move(entity_t* e, int dir);
    void path(entity_t* e);

    void victory(bool tSideWin);
    bool plantBomb(entity_t* e);
    void diffuse(entity_t* e);

    void update(char usrIn);
    void refresh();

    bool bombPlanted() const;
    void printMap() const;

    bomb* theBomb{ NULL };
private:
    std::vector<entity_t*> m_ent{ NULL };
    charMap* worldMap{ NULL };
    player* human{ NULL };
    bool win{ false };
};

#endif
