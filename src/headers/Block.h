#include "../classes/Coords.cpp"
#include <iostream>
#include <vector>

class Block {
  Coords prevCoords;
  Coords coords;
  std::vector<Coords> shape;
  std::vector<Coords> prevShape;

public:
  Block();
  void Move(char c);
  Coords GetCoords();
  Coords GetPrevCoords();
  void Frame(std::vector<std::vector<std::string>>);
  bool CheckCollision(std::vector<Coords> localShape);
  std::vector<Coords> GetShape();
  std::vector<Coords> GetPrevShape();
};
