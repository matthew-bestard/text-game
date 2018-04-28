#define _XOPEN_SOURCE_EXTENDED // required for UTF-8 encoding
#include <ncursesw/curses.h> // required for UTF-8 encoding
#include <locale.h> // required for UTF-8 encoding
#include <stdlib.h> // required for malloc

typedef struct Monster { // defines a struct for monster npcs
  int xPosition;
  int yPosition;
  int health;
} Monster;

typedef struct Room { // defines a struct for Rooms 
  int xPosition;
  int yPosition;
  int heigt;
  int width;
  Monster ** monsters;
} Room;

typedef struct Player { // defines a struct for Players 
  int xPosition;
  int yPosition;
  int health;
} Player;

int screenSetup();
int mapSetup();
Player * playerSetup();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition();

int main () {
	setlocale(LC_ALL, ""); // required for UTF-8 encoding, MUST BE CALLED BEFORE ANYTHING ELSE!
  Player * user; // variable that will hold the new user
	int ch; // variable used to get input from terminal for use in gameloop and handleInput functions
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
  mvprintw(14, 13, "|..................|");
  mvprintw(15, 13, "|..................|");
  mvprintw(16, 13, "|..................|");
  mvprintw(17, 13, "|..................|");
  mvprintw(18, 13, "--------------------");
  
  mvprintw(2, 44, "--------------------");
  mvprintw(3, 44, "|..................|");
  mvprintw(4, 44, "|..................|");
  mvprintw(5, 44, "|..................|");
  mvprintw(6, 44, "|..................|");
  mvprintw(7, 44, "--------------------");

  mvprintw(10, 40, "--------------------");
  mvprintw(11, 40, "|..................|");
  mvprintw(12, 40, "|..................|");
  mvprintw(13, 40, "|..................|");
  mvprintw(14, 40, "|..................|");
  mvprintw(15, 40, "--------------------");
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;
  playerMove(16, 16, newPlayer); // player start position
  return newPlayer;
}

int handleInput(int input, Player * user) {
  int newY;
  int newX;
  switch (input) {
    case 'w':
      newY = user->yPosition - 1;
      newX = user->xPosition;
      break;
    case 'a':
      newY = user->yPosition;
      newX = user->xPosition - 1;
      break;
    case 's':
      newY = user->yPosition + 1;
      newX = user->xPosition;
      break;
    case 'd':
      newY = user->yPosition;
      newX = user->xPosition + 1;
      break;
    default:
      break;
  }
  checkPosition(newY, newX, user);
}

int checkPosition(int newY, int newX, Player * user) { // Check what character is at next intended move position(y and x coordinates), if that word is a period, move the player using playerMove function, else do not move player but move cursor back to position over player @ symbol
  int space;
  switch (mvinch(newY, newX)) { // this switch statement is evaluating the character at the next intended Player position using the mvinch ncurses function with the next intened y and x coordinates passed in. If  mvinch returns a . character then the playerMove function is run with the newY, newX positions and the user pointer, pointing to the Player struct passed in
    case '.':
      playerMove(newY, newX, user);
      break;
    default:
      move(user->yPosition, user->xPosition); // this case is used to move the cursor back onto the Player if when a user types in a command, the mvinch function determines that the intened move coordinates contain a character that the Player cannot move onto
      break;
  }
}

int playerMove(int y, int x, Player * user) { // this command is run to move, the Player(or user) to their new intended move coordinates, whose direction and distance are determined by the switch in handleInput as well as the newY and newX variables being assigned in such a was as to increase the characters position 1 unit in the selected direction as controlled by the WASD keys
  mvprintw(user->yPosition, user->xPosition, "."); 
  user->yPosition = y;
  user->xPosition = x;

  mvprintw(user->yPosition, user->xPosition, "@");
  move(user->yPosition, user->xPosition);
}
