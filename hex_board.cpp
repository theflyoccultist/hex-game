#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>

// struct Point {
//   int x = 0;
//   int y = 0;
// };

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

class Board {
public:
  Board(int size)
      : board_size(size),
        cells(size, std::vector<CellState>(size, CellState::EMPTY)) {}
  void add_point(int x, int y, CellState state) {
    if (x >= 0 && y >= 0 && x < board_size && y < board_size)
      cells[x][y] = state;
  }
  // std::vector<Point> get_neighbors(int x, int y);
  /* neighbors if not a cell in borders:
   * {0, -1}, {-1, 0}, {-1, -1}, {0, -1}, {1, 1}, {1, -1} */

  void print_board();

private:
  int board_size;
  std::vector<std::vector<CellState>> cells;
  std::string line;
};

// main function to display the hex board to the console
void Board::print_board() {
  std::string indent = "";
  std::string line = "\\";
  for (int i = 1; i < board_size; ++i)
    line += " / \\";

  std::cout << " 0";
  for (int i = 1; i < board_size; ++i)
    std::cout << "p1 " << i;
  std::cout << "\n";

  std::cout << "0 " << cells[0][0];
  for (int i = 1; i < board_size; ++i)
    std::cout << "---" << cells[0][i];
  std::cout << "\n";

  for (int i = 1; i < board_size; ++i) {
    indent += ' ';
    std::cout << indent << "p2" << line << "\n";
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

int main() {
  int n = get_valid_num();
  Board game_board(n);
  game_board.print_board();
  return 0;
}
