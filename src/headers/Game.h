#include <vector>
#include "../classes/Block.cpp"

class Game {
  int height;
  int width;
  bool gameLoop;
  int points;
  int highscore;
  int tries;
  std::vector<std::vector<std::string>> board;
  std::vector<std::vector<std::string>> copyBoard;

public:
  Game();
  void Start();
  void Stop();
  void Draw();
  void CheckWin();
  bool IsPlaying();
  void RemoveLast(Block block);
  void ChangePosition(Block block);
  std::vector<std::vector<std::string>> GetBoard();
  std::vector<std::vector<std::string>> GetCopyBoard();
  void CheckLose();
  void Restart();
  void SwitchBoards();
  void HandleDB();
};
