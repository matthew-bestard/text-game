#include <curses.h>
#include "game.h"
#include "level.h"
#include "player.h"

/* Implementations of functions declared in game.h */

void handleInput(int input, Player * user, Level * newLevel) {
  int newY;
  int newX;
  switch (input) {
    case 'w':
      newY = user->position.y - 1;
      newX = user->position.x;
      break;
    case 'a':
      newY = user->position.y;
      newX = user->position.x - 1;
      break;
    case 's':
      newY = user->position.y + 1;
      newX = user->position.x;
      break;
    case 'd':
      newY = user->position.y;
      newX = user->position.x + 1;
      break;
    default:
      break;
  }
  
  checkPosition(newY, newX, user, newLevel);
}

void checkPosition(int newY, int newX, Player * user, Level * newLevel) { // Check what character is at next intended move position(y and x coordinates), if that word is a period, move the player using playerMove function, else do not move player but move cursor back to position over player @ symbol
  switch (mvinch(newY, newX)) { // this switch statement is evaluating the character at the next intended Player position using the mvinch ncurses function with the next intened y and x coordinates passed in. If  mvinch returns a . character then the playerMove function is run with the newY, newX positions and the user pointer, pointing to the Player struct passed in
    case '.':
      playerMove(newY, newX, user, newLevel);
      break;
		case '+':
      playerMove(newY, newX, user, newLevel);
      break;
    case '#':
      playerMove(newY, newX, user, newLevel);
      break;
    default:
      move(user->position.y, user->position.x); // this case is used to move the cursor back onto the Player if when a user types in a command, the mvinch function determines that the intened move coordinates contain a character that the Player cannot move onto
      break;
  }
}

void playerMove(int newY, int newX, Player * user, Level * newLevel) {
  char buffer[8];
  sprintf(buffer, "%c", newLevel->levelMap[user->position.y][user->position.x]);
  mvprintw(user->position.y, user->position.x, buffer); // first replace the player's current position with a . symbol
  user->position.y = newY; // set passed in user's new y position
  user->position.x = newX; // set passed in user's new x position
  mvprintw(user->position.y, user->position.x, "@"); // print @ symbol at the user's new position defined inside the user struct
  move(user->position.y, user->position.x); // finally move cursor back on top of the player's @ character by using the position data in the passed in user's struct
}
