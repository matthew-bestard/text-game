#include <stdio.h>
#include <ncurses.h>

int main (void) {
  initscr(); // initializes the screen, sets up memory and clears the screen
  printw("Hello World !!!");
  refresh(); // refreshes screen to match what is in memory

  int c = getch();

  printw("%d", c);

  getch(); // Gets user input and returns int value of the key typed in
  endwin(); // Deallocates memory and ends ncurses 
  return 0;
}
