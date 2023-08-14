#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

typedef struct Monster { // defines a struct for monster npcs
  Position position;
  int health;
  int attack;
  int defense;
} Monster;

/* Function prototypes for monster-related logic */

#endif	/* MONSTER_H */
