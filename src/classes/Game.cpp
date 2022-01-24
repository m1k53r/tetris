#include <vector>
#include <algorithm>
#include "../headers/Game.h"
#include "ncursesw/ncurses.h"
#include <sqlite3.h>

Game::Game() {
  width = 10;
  height = 20;
  gameLoop = false; 
  points = 0;
  highscore = 0;
  tries = 0;
  board = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
  copyBoard = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
}

void Game::Start() {
  gameLoop = true;
}

void Game::Stop() {
  gameLoop = false;
}

void Game::Draw(std::vector<Coords> nextShape) {
  clear();
  addch(ACS_ULCORNER);
  for (int i = 0; i < 30; i++) addch(ACS_HLINE);
  addch(ACS_URCORNER);
  printw("\n");

  for (auto columns : board) {
    addch(ACS_VLINE);

    for (auto cells : columns) {
      printw(" ");

      if (cells == "#") printw(" ");
      else addch(ACS_CKBOARD);

      printw(" ");
      //printw(cells.c_str());
    }

    addch(ACS_VLINE);
    printw("\n");
  }

  addch(ACS_LLCORNER);
  for (int i = 0; i < 30; i++) addch(ACS_HLINE);
  addch(ACS_LRCORNER);

  printw("\n\t    Points: %i", points);
  printw("\n\t    Highscore: %i", highscore);
  printw("\n\t    Next shape:");
  printw("\n\n\t    ");
  for (auto rows : DrawNextShape(nextShape)) {
    for (auto cells : rows) {
      printw(" ");

      if (cells == "#") printw(" ");
      else addch(ACS_CKBOARD);

      printw(" ");
    }
    printw("\n\t    ");
  }
}

void Game::RemoveLast(Block block) {
  for (int i = 0; i < block.GetPrevShape().size(); i++) {
    board[block.GetPrevShape()[i].GetY()][block.GetPrevShape()[i].GetX()] = "#";
  }

  copyBoard = board;
}

void Game::ChangePosition(Block block) {
  for (int i = 0; i < block.GetShape().size(); i++) {
    board[block.GetShape()[i].GetY()][block.GetShape()[i].GetX()] = "*";
  }
}

void Game::CheckWin() {
  int blocks;
  int pos = -1;
  for (int i = 0; i < copyBoard.size(); i++) {
    blocks = 0;

    for (int j = 0; j < copyBoard[i].size(); j++) {
      if (copyBoard[i][j] == "*") blocks++;
    }

    if (blocks == 10) {
      points += 10;
      if (points > highscore) highscore = points;
      board[i] = std::vector<std::string>{"#","#","#","#","#","#","#","#","#","#"};
      pos = i;
      break;
    }
  }
  for (int i = pos-1; i > 0; i--){
    for (int j = 0; j < board[i].size(); j++) {
      if (copyBoard[i][j] == "*") {
        board[i][j] = "#";
        board[i+1][j] = "*";
      }
    } 
  }
}

bool Game::IsPlaying() {
  return gameLoop;
}

std::vector<std::vector<std::string>> Game::GetBoard() {
  return board;
}

std::vector<std::vector<std::string>> Game::GetCopyBoard() {
  return copyBoard;
}

void Game::CheckLose() {
  bool found = false;
  for (int i = 0; i < board[0].size(); i++) {
    if (board[0][i] == "*") {
      found = true;
      tries += 1;
      break;
    }
  }
  if (!found) {
    tries = 0;
  }

  if (tries > 2) {
    nodelay(stdscr, FALSE);
    gameLoop = false;
    printw("\nYou lost");
    printw("\nWanna continue? (y/n) ");
    char c = getch();
    if (c == 'y') {
      Restart(); 
    }
    else {
      clear();
      //OutputScoreboard();
      getch();
      endwin();
    }
  }
}

void Game::Restart() {
  nodelay(stdscr, TRUE);
  gameLoop = true;
  points = 0;
  tries = 0;
  board = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
  copyBoard = std::vector<std::vector<std::string>>(height, std::vector<std::string> (width, "#"));
}

void Game::SwitchBoards() {
  board = copyBoard; 
}

void Game::HandleDB() {
  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open("highscores.db", &DB);

  if (exit) {
    printw("Error open DB");
  }
  else {
    printw("Database opened successfully");
  }
  sqlite3_close(DB);
}

std::vector<std::vector<std::string>> Game::DrawNextShape(std::vector<Coords> nextShape) {
  std::vector<std::vector<std::string>> shapeBoard = {5, std::vector<std::string> (5, "#")};
  for (auto x : nextShape) {
    shapeBoard[x.GetY()][x.GetX()] = "*";
  }

  return shapeBoard;
}

static int PrintScoreboard(void* data, int argc, char** argv, char** azColName)
{
  int i;
  //fprintf(stderr, "%s: ", (const char*)data);

  addch(ACS_ULCORNER);
  for (int i = 0; i < 14; i++) addch(ACS_HLINE);
  addch(ACS_URCORNER);
  printw("\n| NAME | SCORE |\n");
  printw("|");
  for (int i = 0; i < 14; i++) addch(ACS_HLINE);
  printw("|\n");

  for (i = 0; i < argc; i++) {
    printw("| %s ", argv[i] ? argv[i] : "NULL");
  }
  printw("  |\n");

  addch(ACS_LLCORNER);
  for (int i = 0; i < 14; i++) addch(ACS_HLINE);
  addch(ACS_LRCORNER);

  printw("\n");
  return 0;
}

void Game::OutputScoreboard() {
  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open("highscores.db", &DB);
  std::string data = "CALLBACK FUNCTION";

  std::string sql = "SELECT * FROM scores ORDER BY score DESC;";
  if (exit) {
      std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
      return;
  }
  else
      std::cout << "Opened Database Successfully!" << std::endl;

  int rc = sqlite3_exec(DB, sql.c_str(), PrintScoreboard, (void*)data.c_str(), NULL);

  if (rc != SQLITE_OK)
      std::cerr << "Error SELECT" << std::endl;
  else {
    std::cout << "Operation OK!" << std::endl;
  }

  sqlite3_close(DB);
  return;
}

static int UpdateHighscore(void* data, int argc, char** argv, char** azColName) {
  return 0; 
}

void Game::GetName() {
  char* name;
  getstr(name);
  std::string newName(name);

  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open("highscores.db", &DB);
  std::string data = "CALLBACK FUNCTION";

  std::string sql = "SELECT * FROM scores WHERE name = " + newName;
  if (exit) {
      std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
      return;
  }
  else
      printw("\nOpened Database Successfully!");

  int rc = sqlite3_exec(DB, sql.c_str(), UpdateHighscore, (void*)data.c_str(), NULL);

  if (rc != SQLITE_OK)
      std::cerr << "Error SELECT" << std::endl;
  else {
    std::cout << "Operation OK!" << std::endl;
  }

  sqlite3_close(DB);
  return;
}
