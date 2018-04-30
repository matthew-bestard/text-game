#define _XOPEN_SOURCE_EXTENDED // required for UTF-8 encoding, contains functions to deal with wide characters
#include <ncursesw/curses.h> // required for UTF-8 encoding, wide character ncurses
#include <locale.h> // required for UTF-8 encoding
#include <stdlib.h> // required for malloc
#include <time.h> // required for rand and srand functions to create random numbers

typedef struct Position { // defines a struct for a coordinate position
  int x;
  int y;
} Position;

typedef struct Room { // defines a struct for Rooms 
  Position position;
  int height;
  int width;
  Position ** doors; // array of pointers to the Position struct type to keep track of where the doors are in a given room
  // Monster ** monsters;
  // Item ** items;
} Room;

typedef struct Level { // defines a struct for a level
  Room ** rooms; // an array of pointers that will hold all of the instances of the Room struct associated with a particular level
  int xSize;
  int ySize;
  char ** levelMap; // going to hold an array of characters, that will be generated by mapSetup function that will be used to draw the level and refresh when characters, npc's and other entities move
} Level;

typedef struct Player { // defines a struct for Players 
  Position position;
  int health;
  int attack;
  int defense;
  // Room * room;
} Player;

typedef struct Monster { // defines a struct for monster npcs
  Position position;
  int health;
  int attack;
  int defense;
} Monster;

int screenSetup();
Level* mapSetup();
Player * playerSetup(Level * newLevel);
int handleInput(int input, Player * user, Level * newLevel);
int playerMove(int y, int x, Player * user, Level * newLevel);
int checkPosition(int newY, int newX, Player * user, Level * newLevel);

// room creation function definitions
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room, Level * newLevel);
int connectDoors(Position * doorOne, Position * doorTwo, Level * newLevel);

int main () {
	setlocale(LC_ALL, ""); // required for UTF-8 encoding, MUST BE CALLED BEFORE ANYTHING ELSE!
  srand(time(NULL)); // seeds random number generator with time from the operating system
  screenSetup(); // initializes ncurses terminal screen
  Level * generatedLevel;
  generatedLevel = mapSetup(); // creates rooms
  Player * user; // variable that will hold the new user
	int ch; // variable used to get input from terminal for use in gameloop and handleInput functions
  user = playerSetup(generatedLevel);
	while ((ch = getch()) != 'q') {
		handleInput(ch, user, generatedLevel);
	}
  getch();
  endwin(); // required for ncurses to work
  return 0;
}

int screenSetup() { // initializes ncurses terminal screen 
  initscr(); // required for ncurses to work
  noecho();
  refresh();
  return 0;
}

Level * mapSetup () { // this function generates the map for a level and draws it to the ncurses screen and also returns an array of rooms that will be used later for a level struct
  Level * newLevel;
  newLevel = malloc(sizeof(Level));
  newLevel->rooms = malloc(sizeof(Room)*6);
  newLevel->ySize = 25;
  newLevel->xSize = 100;
  newLevel->levelMap = malloc(sizeof(char * ) * 25);
  int y;
  int x;
  for (y = 0; y < newLevel->ySize; y++) {
    newLevel->levelMap[y] = malloc(sizeof(char * ) * 100);
     for(x = 0; x < newLevel->xSize; x++) {
       newLevel->levelMap[y][x] = 1;
     }
  }
  newLevel->rooms[0] = createRoom(14, 13, 6, 8);
  newLevel->rooms[1] = createRoom(34, 5, 6, 8); // middle room
  newLevel->rooms[2] = createRoom(61, 15, 6, 12);
  drawRoom(newLevel->rooms[0], newLevel); // these functions need to be rewritten to write to the map character array in level and then be drawn later
  drawRoom(newLevel->rooms[1], newLevel); // these functions need to be rewritten to write to the map character array in level and then be drawn later
  drawRoom(newLevel->rooms[2], newLevel); // these functions need to be rewritten to write to the map character array in level and then be drawn later
  connectDoors(newLevel->rooms[0]->doors[3], newLevel->rooms[2]->doors[1], newLevel); // these functions need to be rewritten to write to the map character array in level and then be drawn later
  connectDoors(newLevel->rooms[1]->doors[2], newLevel->rooms[0]->doors[0], newLevel); // these functions need to be rewritten to write to the map character array in level and then be drawn later
  return newLevel; // returns the rooms array of type Room struct
}

Player * playerSetup(Level * newLevel) {
  Player * newPlayer; // creates a variable that will hold the yet uncreated new player of the struct type Player
  newPlayer = malloc(sizeof(Player)); // allocates enough memory to hold a player of type struct Player
  newPlayer->position.x = 14; // sets starting x position in newPlayer x position member
  newPlayer->position.y = 14; // sets starting x position in newPlayer y position member
  newPlayer->health = 20; // sets player starting health
  playerMove(16, 16, newPlayer, newLevel); // player start position
  return newPlayer;
}

int handleInput(int input, Player * user, Level * newLevel) { // this function takes the input character from the ch variable in the main method, creates a newX newY set of coordinates based on that input character and then call checkPosition function and pass the new coordinates into that. If the new coordinates are valid, then the checkPosition function will call the playerMove function using the new coordinates
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
  checkPosition(newY, newX, user, newLevel); // checkPosition function is called with the new coordinates created by the handleInput function
}

int checkPosition(int newY, int newX, Player * user, Level * newLevel) { // Check what character is at next intended move position(y and x coordinates), if that word is a period, move the player using playerMove function, else do not move player but move cursor back to position over player @ symbol
  int space;
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

int playerMove(int newY, int newX, Player * user, Level * newLevel) { // this command is run to move, the Player(or user) to their new intended move coordinates, whose direction and distance are determined by the switch in handleInput as well as the newY and newX variables being assigned in such a was as to increase the characters position 1 unit in the selected direction as controlled by the WASD keys player movement is mainly moved by this and is constrained by the checkposition function that will stop a player from being moved to a given postion if the tile does not allow a player to move there as set in the checkPosition function
  char buffer[8];
  sprintf(buffer, "%c", newLevel->levelMap[user->position.y][user->position.x]);
  mvprintw(user->position.y, user->position.x, buffer); // first replace the player's current position with a . symbol
  user->position.y = newY; // set passed in user's new y position
  user->position.x = newX; // set passed in user's new x position
  mvprintw(user->position.y, user->position.x, "@"); // print @ symbol at the user's new position defined inside the user struct
  move(user->position.y, user->position.x); // finally move cursor back on top of the player's @ character by using the position data in the passed in user's struct
}

Room * createRoom(int x, int y, int height, int width) { // this creates a room with the specified position and size, then generates four doors in random location along the room's four sides
  Room * newRoom;
  newRoom = malloc(sizeof(Room));
  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;
  newRoom->doors = malloc(sizeof(Position) * 4);
  // top door
  newRoom->doors[0] = malloc(sizeof(Position));
  newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[0]->y = newRoom->position.y;
  // left door
  newRoom->doors[1] = malloc(sizeof(Position));
  newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;
  newRoom->doors[1]->x = newRoom->position.x;
  // bottom door
  newRoom->doors[2] = malloc(sizeof(Position));
  newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
  newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;
  // right door
  newRoom->doors[3] = malloc(sizeof(Position));
  newRoom->doors[3]->y= rand() % (height - 2) + newRoom->position.y + 1;
	newRoom->doors[3]->x = newRoom->position.x + width - 1;
  return newRoom;
}

int drawRoom(Room * room, Level * newLevel) { // draws a room on the ncurses screen
  int x1;
  int y1;
  int x;
  int y;
  // -------------------------------------------------------------------------------------------------------
  // draw top and bottom of a room on the levelMap
  for (x1 = room->position.x; x1 < room->position.x + room->width; x1++) {
    newLevel->levelMap[room->position.y][x1] = '-'; // drawing top of room
    newLevel->levelMap[room->position.y + room->height - 1][x1] = '-'; // drawing bottom of room
  }
  // drawing walls here on the levelMap
  for (y1 = room->position.y + 1; y1 < room->position.y + room->height - 1; y1++) {
    newLevel->levelMap[y1][room->position.x] = '|';
    newLevel->levelMap[y1][room->position.x + room->width - 1] = '|';
    // drawing floors in between walls here on the levelMap
    for (x1 = room->position.x + 1; x1 < room->position.x + room->width - 1; x1++) {
       newLevel->levelMap[y1][x1] = '.';
    }
  }
  // draw doors here on the levelMap
  newLevel->levelMap[room->doors[0]->y][room->doors[0]->x] = '+';
  newLevel->levelMap[room->doors[1]->y][room->doors[1]->x] = '+';
  newLevel->levelMap[room->doors[2]->y][room->doors[2]->x] = '+';
  newLevel->levelMap[room->doors[3]->y][room->doors[3]->x] = '+';
  // -------------------------------------------------------------------------------------------------------
  // draw top and bottom of a room on the ncurses screen
  for (x = room->position.x; x < room->position.x + room->width; x++) {
    mvprintw(room->position.y, x, "-"); // drawing top of room
    mvprintw(room->position.y + room->height - 1, x, "-"); // drawing bottom of room
  }
  // drawing walls here on the ncurses screen
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");
    // drawing floors in between walls here on the ncurses screen
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }
  // draw doors here on the ncurses screen
  mvprintw(room->doors[0]->y, room->doors[0]->x, "+" );
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+" );
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+" );
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+" );
  return 1;
}

int connectDoors(Position * doorOne, Position * doorTwo, Level * newLevel) {
  int count = 0;
  Position temp;
  Position previous;
  temp.x = doorOne->x;
  temp.y = doorOne->y;
  previous = temp;
  while(1) {
    // step left
    if ((abs((temp.x - 1) - doorTwo->x ) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
      previous.x = temp.x;
      temp.x = temp.x - 1;
      // step right
    } else if ((abs((temp.x + 1) - doorTwo->x ) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
      previous.x = temp.x;
      temp.x = temp.x + 1;
      // step down
    } else if ((abs((temp.y + 1) - doorTwo->y ) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
      previous.y = temp.y;
      temp.y = temp.y + 1;
      // step up
    } else if ((abs((temp.y - 1) - doorTwo->y ) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
      previous.y = temp.y;
      temp.y = temp.y - 1;
    } else {
      if (count == 0) {
        temp = previous;
        count++;
        continue;
      } else {
        return 0;
      }
    }
    newLevel->levelMap[temp.y][temp.x] = '#';
    mvprintw(temp.y, temp.x, "#");
    // getch();
  }
  return 1;
}
