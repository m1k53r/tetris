#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/Block.h"
#include <math.h>
#define PI 3.14159265

const std::vector<Coords> LBLOCK = {Coords(0,0), Coords(0,1), Coords(1,1), Coords(2,1)};
const std::vector<Coords> TBLOCK = {Coords(0,1), Coords(1,1), Coords(2,1), Coords(1,0)};
const std::vector<Coords> SQUAREBLOCK = {Coords(0,0), Coords(0,1), Coords(1,0), Coords(1,1)};
const std::vector<Coords> LONGBLOCK = {Coords(0,0), Coords(1,0), Coords(2,0), Coords(3,0), Coords(4,0)};
const std::vector<Coords> ZBLOCK = {Coords(0,0), Coords(1,0), Coords(1,1), Coords(2,1)};

Block::Block() {
  GenerateBlock();
  shape = nextShape;
  prevShape = shape;
}

void Block::Move(char c, std::vector<std::vector<std::string>> board) {
  // Save previous position of the shape
  for (int i = 0; i < shape.size(); i++) {
    prevShape[i].ChangeX(shape[i].GetX());
  }

  Coords smallest(100, 100);
  Coords biggest(-1, -1);
  bool foundCollision = false;

  switch(c) {
    case 'a':
      //coords.ChangeX( std::max(0, coords.GetX() - 1) );
      for (int i = 0; i < shape.size(); i++) {
        if (shape[i].GetX() < smallest.GetX()) {
          smallest.ChangeX(shape[i].GetX());
          smallest.ChangeY(shape[i].GetY());
        }
        if (board[shape[i].GetY()][std::max(shape[i].GetX() - 1, 0)] == "*") {
          foundCollision = true;
          break;
        }
      }

      if (smallest.GetX() > 0 && !foundCollision) {
        for (int i = 0; i < shape.size(); i++) {
          shape[i].ChangeX(shape[i].GetX() - 1);
        }
      }
      break;

    case 'd':
      //coords.ChangeX( std::min(9, coords.GetX() + 1) );
      for (int i = 0; i < shape.size(); i++) {
        if (shape[i].GetX() > biggest.GetX()) {
          biggest.ChangeX(shape[i].GetX());
          biggest.ChangeY(shape[i].GetY());
        }
        if (board[shape[i].GetY()][std::min(shape[i].GetX() + 1, 9)] == "*") {
          foundCollision = true;
          break;
        }
      }

      if (biggest.GetX() < 9 && !foundCollision) {
        for (int i = 0; i < shape.size(); i++) {
          shape[i].ChangeX(shape[i].GetX() + 1);
        }
      }
      break;

    case 'r':
      RotateBlock(board);
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
  if (CheckCollision(board)) {
    for (int i = 0; i < shape.size(); i++) {
      shape[i].ChangeY(shape[i].GetY() + 1);
    }
  }
  else {
    shape = nextShape;
    prevShape = shape;
    GenerateBlock();
  }
}

bool Block::CheckCollision(std::vector<std::vector<std::string>> board) {
  int maxY = 0;
  for (int i = 0; i < shape.size(); i++) {
    if (board[std::min(shape[i].GetY() + 1, 19)][shape[i].GetX()] != "#") {
      return false;
    }
    maxY = std::max(shape[i].GetY(), maxY);
  }
  return maxY < 19;
}

std::vector<Coords> Block::GetShape() {
  return shape;
}

std::vector<Coords> Block::GetPrevShape() {
  return prevShape;
}

void Block::RotateBlock(std::vector<std::vector<std::string>> board) {
  Snapshot();
  std::vector<Coords> tempShape;
  int degrees = 90;
  for (int j = 0; j < shape.size(); j++) {
    tempShape.clear();
    int centerx = shape[j].GetX();
    int centery = shape[j].GetY();

    for (int i = 0; i < shape.size() * 2; i++) {
      if (tempShape.size() == shape.size()) {
        break;
      }
      if (i > shape.size()) degrees = degrees * -1;

      int x = shape[i].GetX();
      int y = shape[i].GetY();

      int newx = (x - centerx) * cos(degrees * PI / 180) - (y - centery) * sin(degrees * PI / 180) + centerx + 0.5;
      int newy = (x - centerx) * sin(degrees * PI / 180) + (y - centery) * cos(degrees * PI / 180) + centery + 0.5;

      if ((newx > -1 && newx < 10) && (newy > -1 && newy < 20)) {
        if (board[newy][newx] == "#") {
          tempShape.push_back(Coords(newx, newy));
        }
        else break;
      }
      else break;
    }
    if (tempShape.size() == shape.size()) {
        shape = tempShape;
        break;
    }
  }
}

void Block::GenerateBlock() {
  int i = rand() % 5;
  if (i == 0) {
    nextShape = LBLOCK;
  }
  if (i == 1) {
    nextShape = TBLOCK;
  }
  if (i == 2) {
    nextShape = SQUAREBLOCK;
  }
  if (i == 3) {
    nextShape = LONGBLOCK;
  }
  if (i == 4) {
    nextShape = ZBLOCK;
  }
}

std::vector<Coords> Block::GetNextShape() {
  return nextShape;
}
