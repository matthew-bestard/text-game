#define _XOPEN_SOURCE_EXTENDED // required for UTF-8 encoding
#include <ncursesw/curses.h> // required for UTF-8 encoding
#include <locale.h> // required for UTF-8 encoding
#include <stdlib.h> // required for malloc
#include <time.h>

typedef struct Position {
  int x;
  int y;
  // TILE_TYPE
} Position;

typedef struct Monster { // defines a struct for monster npcs
  int xPosition;
  int yPosition;
  int health;
} Monster;

typedef struct Room { // defines a struct for Rooms 
  Position position;
  int height;
  int width;
  Position ** doors;
  // Monster ** monsters;
  // Item ** items;
} Room;

typedef struct Player { // defines a struct for Players 
  Position position;
  int health;
  // Room * room;
} Player;

int screenSetup();
Room ** mapSetup();
Player * playerSetup();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition();
int drawRoom();

// room creation function definitions
Room * createRoom(int x, int y, int height, int width);

int main () {
	setlocale(LC_ALL, ""); // required for UTF-8 encoding, MUST BE CALLED BEFORE ANYTHING ELSE!
  srand(time(NULL)); // seeds random number generator with time from the operating system
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

Room ** mapSetup () {
	Room ** rooms;
  rooms = malloc(sizeof(Room)*6);
  // mvprintw(13, 13, "--------------------");
  // mvprintw(14, 13, "|..................|");
  // mvprintw(15, 13, "|..................|");
  // mvprintw(16, 13, "|..................|");
  // mvprintw(17, 13, "|..................|");
  // mvprintw(18, 13, "--------------------");

  rooms[0] = createRoom(13, 13, 6, 8);
  drawRoom(rooms[0]);
  
  // mvprintw(2, 44, "--------------------");
  // mvprintw(3, 44, "|..................|");
  // mvprintw(4, 44, "|..................|");
  // mvprintw(5, 44, "|..................|");
  // mvprintw(6, 44, "|..................|");
  // mvprintw(7, 44, "--------------------");

  rooms[1] = createRoom(40, 2, 6, 8);
  drawRoom(rooms[1]);

  // mvprintw(10, 40, "--------------------");
  // mvprintw(11, 40, "|..................|");
  // mvprintw(12, 40, "|..................|");
  // mvprintw(13, 40, "|..................|");
  // mvprintw(14, 40, "|..................|");
  // mvprintw(15, 40, "--------------------");

  rooms[2] = createRoom(40, 10, 6, 12);
  drawRoom(rooms[2]);

  return rooms;
}

Player * playerSetup() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
  newPlayer->health = 20;
  playerMove(16, 16, newPlayer); // player start position
  return newPlayer;
}

int handleInput(int input, Player * user) {
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
  checkPosition(newY, newX, user);
}

int checkPosition(int newY, int newX, Player * user) { // Check what character is at next intended move position(y and x coordinates), if that word is a period, move the player using playerMove function, else do not move player but move cursor back to position over player @ symbol
  int space;
  switch (mvinch(newY, newX)) { // this switch statement is evaluating the character at the next intended Player position using the mvinch ncurses function with the next intened y and x coordinates passed in. If  mvinch returns a . character then the playerMove function is run with the newY, newX positions and the user pointer, pointing to the Player struct passed in
    case '.':
      playerMove(newY, newX, user);
      break;
		case '+':
      playerMove(newY, newX, user);
      break;
    default:
      move(user->position.y, user->position.x); // this case is used to move the cursor back onto the Player if when a user types in a command, the mvinch function determines that the intened move coordinates contain a character that the Player cannot move onto
      break;
  }
}

int playerMove(int y, int x, Player * user) { // this command is run to move, the Player(or user) to their new intended move coordinates, whose direction and distance are determined by the switch in handleInput as well as the newY and newX variables being assigned in such a was as to increase the characters position 1 unit in the selected direction as controlled by the WASD keys
  mvprintw(user->position.y, user->position.x, "."); 
  user->position.y = y;
  user->position.x = x;

  mvprintw(user->position.y, user->position.x, "@");
  move(user->position.y, user->position.x);
}

Room * createRoom(int x, int y, int height, int width) {
  Room * newRoom;
  newRoom = malloc(sizeof(Room));
  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;

  // srand(time(NULL));
  newRoom->doors = malloc(sizeof(Position) * 4);

  // top door
  newRoom->doors[0] = malloc(sizeof(Position));
  newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[0]->y = newRoom->position.y;

  // bottom door
  newRoom->doors[1] = malloc(sizeof(Position));
  newRoom->doors[1]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[1]->y = newRoom->position.y + newRoom->height - 1;

  // left door
  newRoom->doors[2] = malloc(sizeof(Position));
  newRoom->doors[2]->y = rand() % (height - 2) + newRoom->position.y + 1;
  newRoom->doors[2]->x = newRoom->position.x;

  // right door
  newRoom->doors[3] = malloc(sizeof(Position));
  newRoom->doors[3]->y= rand() % (height - 2) + newRoom->position.y + 1;
	newRoom->doors[3]->x = newRoom->position.x + width - 1;
  return newRoom;
}

int drawRoom(Room * room) {
  int x;
  int y;
  // draw top and bottom of a room
  for (x = room->position.x; x < room->position.x + room->width; x++) {
    mvprintw(room->position.y, x, "-"); // drawing top of room
    mvprintw(room->position.y + room->height - 1, x, "-"); // drawing bottom of room
  }

  // drawing walls here
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");
    // drawing floors in between walls here
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }

  // draw doors here
  mvprintw(room->doors[0]->y, room->doors[0]->x, "+" );
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+" );
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+" );
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+" );
  return 1;
}
