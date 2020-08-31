#ifndef CHARMAP_H
#define CHARMAP_H
#include <string>
#include <fstream>
#include "collison.h"
#include "entities.h"

class entity_t;
class charMap;
struct cell : public collison {
    cell(int p);
    cell(const cell& objB);

    int col() const;
    int color() const;
    char model() const;

    entity_t* ent{ NULL };
    char obj{ ' ' };
    int y{ 0 }, x{ 0 };
    int pathID{ -1 };

    cell* above{ NULL };
    cell* below{ NULL };
    cell* left{ NULL };
    cell* right{ NULL };
private:
    friend charMap;
    int m_color{ COLOR_WHITE };
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
    int siteAWidth() const;
    int siteAHeight() const;
    int siteBWidth() const;
    int siteBHeight() const;
    cell*& operator [](int i) const;
    cell** map{ NULL };

private:
    std::string mapName { "" };
    int m_height{ 0 }, m_width{ 0 }; // Dimensions of map
    int m_siteA_height{ 0 }, m_siteA_width{ 0 }; // Dimensions of plant sites
    int m_siteB_height{ 0 }, m_siteB_width{ 0 };
    cell* m_siteA{ NULL }, *m_siteB{ NULL }, *m_siteC{ NULL };
    cell* m_tSpawn{ NULL }, *m_ctSpawn{ NULL };
    cell* m_bombSpawn{ NULL };
    int cellCnt{ 0 };
};
#endif
