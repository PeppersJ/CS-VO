// Fix bomb planting to include collison
// Fix running out of memory space (Crashes on 52 entitiy)
// Add corpses
// SegFalt on shooting w/o moving
// Fix double damge when shooting adjacant
// Fix incositant spawning of players
// Fix getting stuck after bomb has been planted
// Throw error for missing map
// Fix diffusing
// Fix deuque
// Fix enquenext
// Make node subscript operator a const function
// Possibly assign internal pointer in player function to reference world
// Moving left at start into AI causes crash

//CS:VO created by Rishawn Peppers Johnson
//Complie as: ./csvo.sh
//#include <stdlib.h>     //srand
//#include <cstdlib>      //rand
#include "world.h"

// *****************************
// Main Code
// *****************************

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
        move(0,0);  // reset "cursor"
    }

    endwin();
    return 0;
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
