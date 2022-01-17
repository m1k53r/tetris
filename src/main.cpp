#include <iostream>
#include "classes/Game.cpp"
#include <locale.h>
#include "ncursesw/ncurses.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  // intro
  srand (time(NULL));
  // ncurses setup
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);

  Game main; 
  Block block;
  char c;
  main.Start();

  timeout(1000);
  while (main.IsPlaying()) {
    main.Draw(); 
    //napms(1000);
    c = getch();
    block.Move(c);
    if (c == 'r') main.SwitchBoards();

    block.Snapshot();
    block.Frame(main.GetCopyBoard());
    main.RemoveLast(block);
    main.ChangePosition(block);
    main.CheckWin();
    main.CheckLose();
  }

  // outro
  getch();
  endwin();
}
