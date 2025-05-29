#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <stack>
#include <string>
#include <vector>

// points in a 2D graph
struct Point {
  int x = 0;
  int y = 0;
};

enum class CellState : short { EMPTY, P1, P2 };

// initialize CellState to EMPTY
struct Cell {
  CellState state = CellState::EMPTY;
};

// convert enum states to a comprehensive output
std::ostream &operator<<(std::ostream &os, CellState state) {
  switch (state) {
  case CellState::EMPTY:
    os << ".";
    break;
  case CellState::P1:
    os << "X";
    break;
  case CellState::P2:
    os << "O";
    break;
  }
  return os;
}

// Board::Board initializes every cells to . (CellState::EMPTY)
class Board {
public:
  Board(int size)
      : board_size(size),
        cells(size, std::vector<CellState>(size, CellState::EMPTY)) {}

  void add_point(int x, int y, CellState state) {
    if (x >= 0 && y >= 0 && x < board_size && y < board_size)
      cells[x][y] = state;
  }

  std::vector<Point> get_neighbors(int x, int y);
  bool check_win(CellState player);
  void print_board();

private:
  int board_size;
  std::vector<std::vector<CellState>> cells;
  std::string line;
};

// Check for neighbors in the surrounding points, add them to the returned
// "neighbors" vector if they exist
std::vector<Point> Board::get_neighbors(int x, int y) {
  std::vector<Point> neighbors;
  static const std::vector<std::pair<int, int>> directions = {
      {0, -1}, {-1, 0}, {-1, -1}, {0, -1}, {1, 1}, {1, -1}};

  for (auto [dx, dy] : directions) {
    int nx = x + dx;
    int ny = y + dy;
    if (nx >= 0 && ny >= 0 && nx < board_size && ny < board_size)
      neighbors.push_back({nx, ny});
  }

  return neighbors;
}

bool Board::check_win(CellState player) {
  std::stack<Point> stack;
  std::vector<std::vector<bool>> visited(board_size,
                                         std::vector<bool>(board_size, false));

  // add the player's cells to the stack (P1: Y axis, P2: X axis)
  for (int i = 0; i < board_size; ++i) {
    if (player == CellState::P1 && cells[i][0] == player)
      stack.push({i, 0});
    if (player == CellState::P2 && cells[0][i] == player)
      stack.push({0, i});
  }

  // DFS: Use the above stack to see if there's a connected path from one edge
  // to the opposite edge, using only that player's pieces
  while (!stack.empty()) {
    Point p = stack.top();
    stack.pop();
    int x = p.x, y = p.y;

    if (visited[x][y])
      continue;
    visited[x][y] = true;

    // Winning conditions for player 1 and 2
    if (player == CellState::P1 && y == board_size - 1)
      return true;
    if (player == CellState::P2 && x == board_size - 1)
      return true;

    for (Point n : get_neighbors(x, y)) {
      if (!visited[n.x][n.y] && cells[n.x][n.y] == player)
        stack.push(n);
    }
  }

  return false;
}

// Display the hex board to the terminal
void Board::print_board() {
  std::cout << "a is for Player 1, b is for Player 2.\n";
  std::string indent = "";
  std::string line = "\\";
  for (int i = 1; i < board_size; ++i)
    line += " / \\";

  std::cout << " 0";
  for (int i = 1; i < board_size; ++i)
    std::cout << " a " << i;
  std::cout << "\n";

  std::cout << "0 " << cells[0][0];
  for (int i = 1; i < board_size; ++i)
    std::cout << "---" << cells[0][i];
  std::cout << "\n";

  for (int i = 1; i < board_size; ++i) {
    indent += ' ';
    std::cout << indent << "b " << line << "\n";
    if (i < 10) {
      indent += ' ';
      std::cout << indent << i << ' ' << cells[i][0];
    } else {
      std::cout << indent << i << ' ' << cells[i][0];
      indent += ' ';
    }

    for (int j = 1; j < board_size; ++j)
      std::cout << "---" << cells[i][j];
    std::cout << "\n";
  }
};

// validate user input
int get_valid_num() {
  int value;
  while (true) {
    std::cout << "Please input a board size between 5 and 12: ";
    if (std::cin >> value && value >= 5 && value <= 12) {
      return value;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "That is not a valid number. Please make an effort.\n";
    }
  }
}

void play_game() {
  while (true) {
    std::cout << "(Player 1/2) input coordinates :";
    if (check_win) {
      std::cout << "Player 1 / 2 has won!\n";
      break;
    }
  }
}

int main() {
  int n = get_valid_num();
  Board game_board(n);
  game_board.print_board();
  return 0;
}
