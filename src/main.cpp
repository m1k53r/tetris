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
  main.HandleDB();

  main.Draw(block.GetNextShape()); 
  while (main.IsPlaying()) {
    timeout(1000);
    main.Draw(block.GetNextShape()); 
    //napms(1000);
    c = getch();
    block.Move(c, main.GetCopyBoard());
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
  return 0;
}
