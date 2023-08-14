#include "level.h"
#include "room.h"
#include <stdlib.h>
#include <curses.h>

/* Implementations of functions declared in level.h */
Level *mapSetup () {
  Level *newLevel = malloc(sizeof(Level));
  if (newLevel == NULL) {
    return NULL;
  }

  newLevel->rooms = malloc(sizeof(Room) * 6);
  if (newLevel->rooms == NULL) {
    free(newLevel);
    return NULL;
  }

  newLevel->ySize = 25;
  newLevel->xSize = 100;
  newLevel->levelMap = malloc(sizeof(char *) * newLevel->ySize);
  if (newLevel->levelMap == NULL) {
    free(newLevel->rooms);
    free(newLevel);
  }

  for (int y = 0; y < newLevel->ySize; y++) {
    newLevel->levelMap[y] = malloc(sizeof(char * ) * newLevel->xSize);
    if (newLevel->levelMap[y] == NULL) {
      freeLevel(newLevel);
      return NULL;
    }

     for(int x = 0; x < newLevel->xSize; x++) {
       newLevel->levelMap[y][x] = 1;
     }
  }

  newLevel->rooms[0] = createRoom(14, 13, 6, 8);
  newLevel->rooms[1] = createRoom(34, 5, 6, 8); // middle room
  newLevel->rooms[2] = createRoom(61, 15, 6, 12);
  drawRoom(newLevel->rooms[0], newLevel);
  drawRoom(newLevel->rooms[1], newLevel);
  drawRoom(newLevel->rooms[2], newLevel);
  connectDoors(newLevel->rooms[0]->doors[3], newLevel->rooms[2]->doors[1], newLevel);
  connectDoors(newLevel->rooms[1]->doors[2], newLevel->rooms[0]->doors[0], newLevel);
  return newLevel; // returns the rooms array of type Room struct
}

void freeLevel(Level *level) {
  for (int y = 0; y < level->ySize; y++) {
    free(level->levelMap[y]);
  }
  free(level->levelMap);
  free(level->rooms);
  free(level);
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
