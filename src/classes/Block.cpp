#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/Block.h"

Block::Block() {
  shape.push_back(Coords(0, 0));
  shape.push_back(Coords(0, 1));
  shape.push_back(Coords(1, 1));
  shape.push_back(Coords(2, 1));

  prevShape.push_back(Coords(0, 0));
  prevShape.push_back(Coords(0, 1));
  prevShape.push_back(Coords(1, 1));
  prevShape.push_back(Coords(2, 1));
}

void Block::Move(char c) {
  // Save previous position of the shape
  for (int i = 0; i < shape.size(); i++) {
    prevShape[i].ChangeX(shape[i].GetX());
  }

  switch(c) {
    case 'a':
      coords.ChangeX( std::max(0, coords.GetX() - 1) );

      for (int i = 0; i < shape.size(); i++) {
        shape[i].ChangeX(shape[i].GetX() - 1);
      }
      break;
    case 'd':
      coords.ChangeX( std::min(9, coords.GetX() + 1) );
      for (int i = 0; i < shape.size(); i++) {
        shape[i].ChangeX(shape[i].GetX() + 1);
      }
      break;
  }
}

Coords Block::GetCoords() {
  return coords;
}

Coords Block::GetPrevCoords() {
  return prevCoords;
}

void Block::Snapshot() {
  for (int i = 0; i < shape.size(); i++) {
    prevShape[i].ChangeY(shape[i].GetY());
  }
}

void Block::Frame(std::vector<std::vector<std::string>> board) {
  if (CheckCollision(shape, board)) {
    for (int i = 0; i < shape.size(); i++) {
      shape[i].ChangeY(shape[i].GetY() + 1);
    }
  }
  else {
    shape = std::vector<Coords> {Coords(0, 0), Coords(0, 1), Coords(1, 1), Coords(2, 1)};
    prevShape = std::vector<Coords> {Coords(0, 0), Coords(0, 1), Coords(1, 1), Coords(2, 1)};
  }
}

bool Block::CheckCollision(std::vector<Coords> localShape, std::vector<std::vector<std::string>> board) {
  int maxY;
  for (int i = 0; i < localShape.size(); i++) {
    if (board[std::min(localShape[i].GetY() + 1, 19)][localShape[i].GetX()] != "#") {
      return false;
    }
    maxY = std::max(localShape[i].GetY(), maxY);
  }
  return maxY < 19;
}

std::vector<Coords> Block::GetShape() {
  return shape;
}

std::vector<Coords> Block::GetPrevShape() {
  return prevShape;
}
