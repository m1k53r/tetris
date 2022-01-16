#include "../classes/Coords.cpp"
#include <iostream>
#include <vector>

class Block {
  Coords prevCoords;
  Coords coords;

public:
  Block();
  void Move(char c);
  Coords GetCoords();
  Coords GetPrevCoords();
  void Frame(std::vector<std::vector<std::string>>);
};
