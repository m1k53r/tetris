#include <vector>
#include "../classes/Block.cpp"

class Game {
  int height;
  int width;
  bool gameLoop;
  int points;
  std::vector<std::vector<std::string>> board;
  std::vector<std::vector<std::string>> copyBoard;

public:
  Game();
  void Start();
  void Stop();
  void Draw();
  bool CheckWin();
  bool IsPlaying();
  void RemoveLast(Block block);
  void ChangePosition(Block block);
  std::vector<std::vector<std::string>> GetBoard();
  std::vector<std::vector<std::string>> GetCopyBoard();
};
