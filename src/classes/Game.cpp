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

void Game::ChangePosition(Block block) {
  //  && board[std::min(block.GetCoords().GetY() + 1, 19)][block.GetCoords().GetX()] != "*"
  // block.GetPrevCoords().GetY() < 19
  if (block.GetPrevCoords().GetY() < 19 && board[std::min(block.GetPrevCoords().GetY() + 1, 19)][block.GetPrevCoords().GetX()] != "*") {
    board[block.GetPrevCoords().GetY()][block.GetPrevCoords().GetX()] = "#";
  }
  board[block.GetCoords().GetY()][block.GetCoords().GetX()] = "*";
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
