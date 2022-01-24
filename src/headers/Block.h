#include "../classes/Coords.cpp"
#include <iostream>
#include <vector>

class Block {
  Coords prevCoords;
  Coords coords;
  std::vector<Coords> shape;
  std::vector<Coords> prevShape;
  std::vector<Coords> nextShape;

public:
  Block();
  void Move(char c, std::vector<std::vector<std::string>> board);
  Coords GetCoords();
  Coords GetPrevCoords();
  void Frame(std::vector<std::vector<std::string>>);
  bool CheckCollision(std::vector<std::vector<std::string>> board);
  std::vector<Coords> GetShape();
  std::vector<Coords> GetPrevShape();
  void Snapshot();
  void RotateBlock(std::vector<std::vector<std::string>> board);
  void GenerateBlock();
  std::vector<Coords> GetNextShape();
};
