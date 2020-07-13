#include "charMap.h"

char cell::model() const { 
    if ( ent == NULL )
        return obj;
    else
        return ent->model();
}
cell::cell(int p = -1) : pathID(p) {}
cell::cell(const cell& objB) {
    ent = objB.ent;
    obj = objB.obj;
    y = objB.y;
    x = objB.x;
    pathID = objB.pathID;
}
int cell::col() const {
    if (ent == NULL)
        return colType;
    else 
        return ent->colType;
}


bool charMap::inBounds(cell* c) const { // returns true when the cell is in bounds
    if( c == NULL )
        return false;
    return true;
}
char charMap::neighborDir(int a, int b) const{
    int scale = 1;
    if( a < 0 || b < 0 || a > height() * width() || b > height() * width())
        return 'n';

    if (a - b == 1 && a % (width()) != 0) //Right
        return 'd';
    else if (a - b == -1 && a % width() != 0 ) //Left
        return 'a';
    else if (a - b == width() && a <= (width() * height()) - width() - 1) //Below
        return 's';
    else if (a - b == width() * -1 && a >= width()) //Above
        return 'w';

    return 'n';
}
charMap::charMap() { /*Empty*/ }
charMap::charMap(std::string fileName) {
    std::ifstream inFile(fileName);
    char temp;
    if(inFile) {
        inFile >> mapName;
        inFile >> m_height >> temp >> m_width;

        map = new cell*[m_height];
        for (int i = 0; i < m_height; i++) {
            map[i] = new cell[m_width];
            for (int j = 0; j < m_width; j++) {
                inFile >> map[i][j].obj >> std::noskipws;
                map[i][j].y = i;
                map[i][j].x = j;
                map[i][j].pathID = cellCnt++;

                if (map[i][j].obj == 'C'){
                    map[i][j].colType = collison::No_Collision;
                    m_ctSpawn = &map[i][j];
                }
                else if (map[i][j].obj == 'T'){
                    map[i][j].colType = collison::No_Collision;
                    m_tSpawn = &map[i][j];
                }
                else if (map[i][j].obj == '#') {
                    map[i][j].colType = collison::Player_Pass_Through;
                }
                else if (map[i][j].obj == 'o') {
                    map[i][j].colType = collison::Bullet_Pass_Through;  
                }
                else if (map[i][j].obj == 'x' ) {
                    map[i][j].colType = collison::Solid_Collision;
                }
                else if (map[i][j].obj == 'n') {
                    map[i][j].colType = collison::Solid_Collision;
                }
                else if (map[i][j].obj == 'B') {
                    map[i][j].obj = ' ';
                    map[i][j].colType = collison::No_Collision;
                    m_bombSpawn = &map[i][j];
                }
                else if (map[i][j].obj == '1') {
                    map[i][j].colType = collison::No_Collision;
                    m_siteA = &map[i][j];
                }
                else if (map[i][j].obj == '2') {
                    map[i][j].colType = collison::No_Collision;
                    m_siteB = &map[i][j];
                }
                else if (map[i][j].obj == '3') {
                    map[i][j].colType = collison::No_Collision;
                    m_siteC = &map[i][j];
                }
                else
                    map[i][j].colType = collison::No_Collision;           
            }
            inFile >> std::skipws;
        }
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++) {
                if ( j > 0 )
                    map[i][j].left = &map[i][j - 1];
                if ( j < m_width )
                    map[i][j].right = &map[i][j + 1];
                if ( i > 0 )
                    map[i][j].above = &map[i - 1][j];
                if ( i < m_height )
                    map[i][j].below = &map[i + 1][j];
            }
        inFile.close();
    } else { printf("Error Opening File\n"); }
}

charMap::~charMap(){
    if(map == NULL) return;
    for(int i = 0; i < m_height; i++)
        delete[] map[i];
    delete[] map;
}

void charMap::printMap() const {
    printw("Map: '%s' with dimensions %dx%d!\n", 
            mapName.c_str(), m_height, m_width);
    
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++)
            printw("%c", map[i][j].obj);
        printw("\n");
    }   
}

std::string charMap::name() const { return mapName; }
cell* charMap::tSpawn() const { return m_tSpawn; }
cell* charMap::ctSpawn() const { return m_ctSpawn; }
cell* charMap::siteA() const { return m_siteA; }
cell* charMap::siteB() const { return m_siteB; }
cell* charMap::siteC() const { return m_siteC; }
cell* charMap::bombSpawn() const { return m_bombSpawn; }
int charMap::width() const { return m_width; }
int charMap::height() const { return m_height; }

cell*& charMap::operator [](int i) {
    return map[i];
}
