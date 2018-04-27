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
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);

int main () {
	setlocale(LC_ALL, ""); // required for UTF-8 encoding
  Player * user;
	int ch;
  screenSetup();
  mapSetup();
  user = playerSetup();
	while ((ch = getch()) != 'q') {
		handleInput(ch, user);
	}
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

int handleInput(int input, Player * user) {
  switch (input) {
    case 'w':
      playerMove(user->yPosition - 1 , user->xPosition, user);
      break;
    case 'a':
      playerMove(user->yPosition, user->xPosition - 1, user);
      break;
    case 's':
      playerMove(user->yPosition + 1, user->xPosition, user);
      break;
    case 'd':
      playerMove(user->yPosition, user->xPosition + 1, user);
      break;
    default:
      break;
  }
}

int playerMove(int y, int x, Player * user) {
  mvprintw(user->yPosition, user->xPosition, ".");
  user->yPosition = y;
  user->xPosition = x;

  mvprintw(user->yPosition, user->xPosition, "@");
  move(user->yPosition, user->xPosition);
}
