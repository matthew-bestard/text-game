#include <curses.h> // includes ncurses
#include <locale.h> // includes functions to set locale to UTF-8 supported one
#include <stdlib.h> // includes malloc
#include <time.h>   // includes function rand and srand to create random numbers
#include "level.h"
#include "player.h"
#include "game.h"


int main () {
  setlocale(LC_ALL, "en_US.UTF-8");
  srand(time(NULL));

  initscr(); // required for ncurses to work
  noecho();
  refresh();
  
  Level *generatedLevel;
  generatedLevel = mapSetup();
  Player *user = playerSetup(generatedLevel);

  int ch;
  while ((ch = getch()) != 'q') {
    handleInput(ch, user, generatedLevel);
  }
    
  getch();
  endwin();
  return 0;
}
