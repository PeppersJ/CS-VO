#ifndef CHARMAP_H
#define CHARMAP_H
#include <string>
#include <fstream>
#include "collison.h"
#include "entities.h"

class entity_t;
class charMap;
struct cell : public collison {
    char model() const;
    cell(int p);
    cell(const cell& objB);
    int col() const;

    entity_t* ent{ NULL };
    char obj{ ' ' };
    int y{ 0 }, x{ 0 };
    int pathID{ -1 };

    cell* above{ NULL };
    cell* below{ NULL };
    cell* left{ NULL };
    cell* right{ NULL };
};

class charMap {
public:
    charMap();
    charMap(std::string mapName);
    ~charMap();
    void printMap() const;
    bool inBounds(cell* c) const;
    char neighborDir(int a, int b) const;

    std::string name() const;
    cell* tSpawn() const;
    cell* ctSpawn() const;
    cell* siteA() const;
    cell* siteB() const;
    cell* siteC() const;
    cell* bombSpawn() const;
    int width() const;
    int height() const;

    cell*& operator [](int i);
    cell** map{ NULL };

private:
    std::string mapName { "" };
    int m_width{ 0 }, m_height{ 0 };
    cell* m_tSpawn{ NULL };
    cell* m_ctSpawn{ NULL };
    cell* m_siteA{ NULL };
    cell* m_siteB{ NULL };
    cell* m_siteC{ NULL };
    cell* m_bombSpawn{ NULL };
    int cellCnt{ 0 };
};
#endif
