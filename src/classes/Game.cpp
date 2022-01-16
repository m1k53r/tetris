#include <vector>
#include <algorithm>
#include <curses.h>
#include "../headers/Game.h"

Game::Game() {
  width = 10;
  height = 20;
  gameLoop = false; 
  points = 0;
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
  for (auto columns : board) {
    for (auto cells : columns) {
      printw(cells.c_str());
    }
    printw("\n");
  }
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

bool Game::CheckWin() {
  return false;
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
