#include "../headers/Coords.h"

Coords::Coords() {
  x = 0;
  y = 0;
}

Coords::Coords(int x, int y) {
  this->x = x;
  this->y = y;
}

void Coords::ChangeX(int x) {
  this->x = x;
}

void Coords::ChangeY(int y) {
  this->y = y;
}

int Coords::GetX() {
  return x;
}

int Coords::GetY() {
  return y;
}
