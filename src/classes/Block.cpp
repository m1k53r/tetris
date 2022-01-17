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
  /*
  shape.push_back(Coords(0, 0));
  shape.push_back(Coords(0, 1));
  shape.push_back(Coords(1, 1));
  shape.push_back(Coords(2, 1));

  prevShape.push_back(Coords(0, 0));
  prevShape.push_back(Coords(0, 1));
  prevShape.push_back(Coords(1, 1));
  prevShape.push_back(Coords(2, 1));

  shape.push_back(Coords(0, 1));
  shape.push_back(Coords(1, 1));
  shape.push_back(Coords(2, 1));
  shape.push_back(Coords(1, 0));

  prevShape.push_back(Coords(0, 1));
  prevShape.push_back(Coords(1, 1));
  prevShape.push_back(Coords(2, 1));
  prevShape.push_back(Coords(1, 0));
  */
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
    case 'r':
      RotateBlock();
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
    GenerateBlock();
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

void Block::RotateBlock() {
  // var newx = (x - centerx) * Math.cos(degrees * Math.PI / 180) - (y - centery) * Math.sin(degrees * math.PI / 180) + centerx;
  // var newy = (x - centerx) * Math.sin(degrees * Math.PI / 180) + (y - centery) * Math.cos(degrees * math.PI / 180) + centery;
  Snapshot();
  std::vector<Coords> tempShape;
  int centerx = shape[0].GetX();
  int centery = shape[0].GetY();
  int degrees = 90;

  for (int i = 0; i < shape.size(); i++) {
    int x = shape[i].GetX();
    int y = shape[i].GetY();
    int newx = (x - centerx) * cos(degrees * PI / 180) - (y - centery) * sin(degrees * PI / 180) + centerx;
    int newy = (x - centerx) * sin(degrees * PI / 180) + (y - centery) * cos(degrees * PI / 180) + centery;

    tempShape.push_back(Coords(newx, newy));
  }
  
  shape = tempShape;
}

void Block::GenerateBlock() {
  int i = rand() % 5;
  if (i == 0) {
    shape = LBLOCK;
    prevShape = LBLOCK;
  }
  if (i == 1) {
    shape = TBLOCK;
    prevShape = TBLOCK;
  }
  if (i == 2) {
    shape = SQUAREBLOCK;
    prevShape = SQUAREBLOCK;
  }
  if (i == 3) {
    shape = LONGBLOCK;
    prevShape = LONGBLOCK;
  }
  if (i == 4) {
    shape = ZBLOCK;
    prevShape = ZBLOCK;
  }
}
