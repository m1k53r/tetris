#include <iostream>
#include "classes/Game.cpp"
#include <curses.h>

int main() {
  // intro
  // ncurses setup
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);

  Game main; 
  Block block;
  timeout(3000);
  char c = getch();
  main.Start();

  while (main.IsPlaying()) {
    main.Draw(); 
    c = getch();
    //napms(1000);
    block.Move(c);
    block.Frame(main.GetBoard());
    main.ChangePosition(block);
  }

  // outro
  getch();
  endwin();
}
