#define _XOPEN_SOURCE_EXTENDED // required for UTF-8 encoding
#include <ncursesw/curses.h> // required for UTF-8 encoding
#include <locale.h> // required for UTF-8 encoding
#include <stdlib.h> // required for malloc

typedef struct Player {
  int xPosition;
  int yPosition;
  int health;
} Player;

int screenSetup();
int mapSetup();
Player * playerSetup();

int main () {
	setlocale(LC_ALL, ""); // required for UTF-8 encoding
  Player * user;
  screenSetup();
  mapSetup();
  user = playerSetup();
  getch();
  endwin(); // required for ncurses to work
  return 0;
}

int screenSetup() {
  initscr(); // required for ncurses to work
  printw("Setting up screen.");
  noecho();
  refresh();
  return 0;
}

int mapSetup () {
  mvprintw(13, 13, "--------------------");
  mvprintw(14, 13, "|------------------|");
  mvprintw(15, 13, "|------------------|");
  mvprintw(16, 13, "|------------------|");
  mvprintw(17, 13, "|------------------|");
  mvprintw(18, 13, "--------------------");
  
  mvprintw(2, 44, "--------------------");
  mvprintw(3, 44, "|------------------|");
  mvprintw(4, 44, "|------------------|");
  mvprintw(5, 44, "|------------------|");
  mvprintw(6, 44, "|------------------|");
  mvprintw(7, 44, "--------------------");

  mvprintw(10, 40, "--------------------");
  mvprintw(11, 40, "|------------------|");
  mvprintw(12, 40, "|------------------|");
  mvprintw(13, 40, "|------------------|");
  mvprintw(14, 40, "|------------------|");
  mvprintw(15, 40, "--------------------");
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;
  mvprintw(newPlayer->xPosition, newPlayer->yPosition, "@");
  move(newPlayer->xPosition, newPlayer->yPosition);
  return newPlayer;
}
