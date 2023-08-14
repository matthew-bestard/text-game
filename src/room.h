#ifndef ROOM_H
#define ROOM_H

#include "position.h"

typedef struct Room { // defines a struct for Rooms 
  Position position;
  int height;
  int width;
  Position ** doors; // array of pointers to the Position struct type to keep track of where the doors are in a given room
  // Monster ** monsters;
  // Item ** items;
} Room;

Room * createRoom(int x, int y, int height, int width);

#endif	/* ROOM_H */
