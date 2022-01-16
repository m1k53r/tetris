#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/Block.h"

Block::Block() {
  prevCoords.ChangeX(-1);
  prevCoords.ChangeY(-1);

  coords.ChangeX(0);
  coords.ChangeY(0);
}

void Block::Move(char c) {
  prevCoords.ChangeX(coords.GetX());

  switch(c) {
    case 'a':
      coords.ChangeX( std::max(0, coords.GetX() - 1) );
      break;
    case 'd':
      coords.ChangeX( std::min(9, coords.GetX() + 1) );
      break;
  }
}

Coords Block::GetCoords() {
  return coords;
}

Coords Block::GetPrevCoords() {
  return prevCoords;
}

void Block::Frame(std::vector<std::vector<std::string>> board) {
  prevCoords.ChangeY(coords.GetY());

  if (coords.GetY() < 19 && board[std::min(coords.GetY() + 1, 19)][coords.GetX()] != "*") {
    coords.ChangeY(coords.GetY() + 1);
  } 
  else {
    coords.ChangeX(0);
    coords.ChangeY(0);
  }
}
