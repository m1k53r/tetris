#include <vector>
#include <algorithm>
#include "../headers/Game.h"
#include "ncursesw/ncurses.h"
#include <sqlite3.h>

Game::Game() {
  width = 10;
  height = 20;
  gameLoop = false; 
  points = 0;
  tries = 0;
  board = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
  copyBoard = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
}

void Game::Start() {
  gameLoop = true;
}

void Game::Stop() {
  gameLoop = false;
}

void Game::Draw() {
  clear();
  addch(ACS_ULCORNER);
  for (int i = 0; i < 30; i++) addch(ACS_HLINE);
  addch(ACS_URCORNER);
  printw("\n");

  for (auto columns : board) {
    addch(ACS_VLINE);

    for (auto cells : columns) {
      printw(" ");

      if (cells == "#") printw(" ");
      if (cells == "*") addch(ACS_CKBOARD);

      printw(" ");
      //printw(cells.c_str());
    }

    addch(ACS_VLINE);
    printw("\n");
  }

  addch(ACS_LLCORNER);
  for (int i = 0; i < 30; i++) addch(ACS_HLINE);
  addch(ACS_LRCORNER);
  printw("\nPoints: %i\n", points);
}

void Game::RemoveLast(Block block) {
  for (int i = 0; i < block.GetPrevShape().size(); i++) {
    board[block.GetPrevShape()[i].GetY()][block.GetPrevShape()[i].GetX()] = "#";
  }

  copyBoard = board;
}

void Game::ChangePosition(Block block) {
  for (int i = 0; i < block.GetShape().size(); i++) {
    board[block.GetShape()[i].GetY()][block.GetShape()[i].GetX()] = "*";
  }
}

void Game::CheckWin() {
  int blocks;
  int pos = -1;
  for (int i = 0; i < copyBoard.size(); i++) {
    blocks = 0;

    for (int j = 0; j < copyBoard[i].size(); j++) {
      if (copyBoard[i][j] == "*") blocks++;
    }

    if (blocks == 10) {
      points += 10;
      board[i] = std::vector<std::string>{"#","#","#","#","#","#","#","#","#","#"};
      pos = i;
      break;
    }
  }
  for (int i = pos-1; i > 0; i--){
    for (int j = 0; j < board[i].size(); j++) {
      if (copyBoard[i][j] == "*") {
        board[i][j] = "#";
        board[i+1][j] = "*";
      }
    } 
  }
}

bool Game::IsPlaying() {
  return gameLoop;
}

std::vector<std::vector<std::string>> Game::GetBoard() {
  return board;
}

std::vector<std::vector<std::string>> Game::GetCopyBoard() {
  return copyBoard;
}

void Game::CheckLose() {
  bool found = false;
  for (int i = 0; i < board[0].size(); i++) {
    if (board[0][i] == "*") {
      found = true;
      tries += 1;
      break;
    }
  }
  if (!found) {
    tries = 0;
  }

  if (tries > 1) {
    nodelay(stdscr, FALSE);
    gameLoop = false;
    printw("\nYou lost");
    printw("\nWanna continue? (y/n) ");
    char c = getch();
    if (c == 'y') {
      Restart(); 
    }
    else {
      endwin();
    }
  }
}

void Game::Restart() {
  nodelay(stdscr, TRUE);
  gameLoop = true;
  points = 0;
  tries = 0;
  board = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
  copyBoard = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
}

void Game::SwitchBoards() {
  board = copyBoard; 
}

void Game::HandleDB() {
  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open("highscores.db", &DB);

  if (exit) {
    printw("Error open DB");
  }
  else {
    printw("Database opened successfully");
  }
  sqlite3_close(DB);
}
