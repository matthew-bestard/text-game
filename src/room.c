#include "room.h"
#include <stdlib.h>
#include <curses.h>

/* Implementations of functions declared in room.h */
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
