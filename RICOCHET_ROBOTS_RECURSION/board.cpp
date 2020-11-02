#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <sstream>

#include "board.h"

// ==================================================================
// ==================================================================
// Implementation of the Position class


// allows a position to be output to a stream
std::ostream& operator<<(std::ostream &ostr, const Position &p) {
  ostr << '(' << p.row << "," << p.col << ')';
  return ostr;
}


// equality and inequality comparision of positions
bool operator==(const Position &a, const Position &b) {
  return (a.row == b.row && a.col == b.col);
}
bool operator!=(const Position &a, const Position &b) {
  return !(a==b);
}


// ==================================================================
// ==================================================================
// Implementation of the Board class


// ===================
// CONSTRUCTOR
// ===================

Board::Board(int r, int c) { 
  // initialize the dimensions
  rows = r; 
  cols = c; 

  // allocate space for the contents of each grid cell
  board = std::vector<std::vector<char> >(rows,std::vector<char>(cols,' '));

  // allocate space for booleans indicating the presense of each wall
  // by default, these are false == no wall
  // (note that there must be an extra column of vertical walls
  //  and an extra row of horizontal walls)
  vertical_walls = std::vector<std::vector<bool> >(rows,std::vector<bool>(cols+1,false));
  horizontal_walls = std::vector<std::vector<bool> >(rows+1,std::vector<bool>(cols,false));

  // initialize the outermost edges of the grid to have walls
  for (int i = 0; i < rows; i++) {
    vertical_walls[i][0] = vertical_walls[i][cols] = true;
  }
  for (int i = 0; i < cols; i++) {
    horizontal_walls[0][i] = horizontal_walls[rows][i] = true;
  }
}


// ===================
// ACCESSORS related to board geometry
// ===================

// Query the existance of a horizontal wall
bool Board::getHorizontalWall(double r, int c) const {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0.4 && r <= rows+0.6);
  assert (c >= 1 && c <= cols);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return horizontal_walls[floor(r)][c-1];
}

// Query the existance of a vertical wall
bool Board::getVerticalWall(int r, double c) const {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0.4 && c <= cols+0.6);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return vertical_walls[r-1][floor(c)];
}


// ===================
// MODIFIERS related to board geometry
// ===================

// Add an interior horizontal wall
void Board::addHorizontalWall(double r, int c) {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0 && r <= rows);
  assert (c >= 1 && c <= cols);
  // verify that the wall does not already exist
  assert (horizontal_walls[floor(r)][c-1] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  horizontal_walls[floor(r)][c-1] = true;
}

// Add an interior vertical wall
void Board::addVerticalWall(int r, double c) {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0 && c <= cols);
  // verify that the wall does not already exist
  assert (vertical_walls[r-1][floor(c)] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  vertical_walls[r-1][floor(c)] = true;
}


// ===================
// PRIVATE HELPER FUNCTIONS related to board geometry
// ===================

char Board::getspot(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  return board[p.row-1][p.col-1];
}


void Board::setspot(const Position &p, char a) {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <=  rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  board[p.row-1][p.col-1] = a;
}

char Board::isGoal(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // loop over the goals, see if any match this spot
  for (unsigned int i = 0; i < goals.size(); i++) {
    if (p == goals[i].pos) { return goals[i].which; }
  }
  // else return space indicating that no goal is at this location
  return ' ';
}


// ===================
// MODIFIERS related to robots
// ===================

// for initial placement of a new robot
void Board::placeRobot(const Position &p, char a) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  assert (getspot(p) == ' ');
  
  // robots must be represented by a capital letter
  assert (isalpha(a) && isupper(a));

  // make sure we don't already have a robot with the same name
  for (unsigned int i = 0; i < robots.size(); i++) {
    assert (robots[i].which != a);
  }

  // add the robot and its position to the vector of robots
  robots.push_back(Robot(p,a));

  // mark the robot on the board
  setspot(p,a);
}


bool Board::moveRobot(int i, const std::string &direction) {

  //
  //
  // YOU NEED TO WRITE THIS FUNCTION
  //
  //
  int row = robots[i].pos.row;
  int col = robots[i].pos.col;
  if (direction == DIRECTION_EAST) {
    for (; col < cols; col++) {
      if (getVerticalWall(row, col + 0.5)) break;
      if (getspot(Position(row, col + 1)) != ' ') break;
    }
  } else if (direction == DIRECTION_WEST) {
    for (; col > 1; col--) {
      if (getVerticalWall(row, col - 0.5)) break;
      if (getspot(Position(row, col - 1)) != ' ') break;
    }
  } else if (direction == DIRECTION_NORTH) {
    for (; row > 1; row--) {
      if (getHorizontalWall(row - 0.5, col)) break;
      if (getspot(Position(row - 1, col)) != ' ') break;
    }
  } else if (direction == DIRECTION_SOUTH) {
    for (; row < rows; row++) {
      if (getHorizontalWall(row + 0.5, col)) break;
      if (getspot(Position(row + 1, col)) != ' ') break;
    }
  } else return false;

  if (row != robots[i].pos.row || col != robots[i].pos.col) {
    setspot(robots[i].pos, ' ');
    robots[i].pos.row = row;
    robots[i].pos.col = col;
    setspot(robots[i].pos, robots[i].which);
    return true;
  }

  return false;
}


// ===================
// MODIFIER related to the puzzle goal
// ===================

void Board::addGoal(const std::string &gr, const Position &p) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);

  char goal_robot;
  if (gr == "any") {
    goal_robot = '?';
  } else {
    assert (gr.size() == 1);
    goal_robot = gr[0];
    assert (isalpha(goal_robot) && isupper(goal_robot));
  }

  // verify that a robot of this name exists for this puzzle
  if (goal_robot != '?') {
    int robot_exists = false;
    for (unsigned int i = 0; i < robots.size(); i++) {
      if (getRobot(i) == goal_robot) 
        robot_exists = true;
    }
    assert (robot_exists);
  }
  
  // make sure we don't already have a robot at that location
  assert (isGoal(p) == ' ');

  // add this goal label and position to the vector of goals
  goals.push_back(Goal(p,goal_robot));
}


// ==================================================================
// PRINT THE BOARD
// ==================================================================

void Board::print() {

  // print the column headings
  std::cout << " ";
  for (int j = 1; j <= cols; j++) {
    std::cout << std::setw(5) << j;
  }
  std::cout << "\n";
  
  // for each row
  for (int i = 0; i <= rows; i++) {

    // don't print row 0 (it doesnt exist, the first real row is row 1)
    if (i > 0) {
      
      // Note that each grid rows is printed as 3 rows of text, plus
      // the separator.  The first and third rows are blank except for
      // vertical walls.  The middle row has the row heading, the
      // robot positions, and the goals.  Robots are always uppercase,
      // goals are always lowercase (or '?' for any).
      std::string first = "  ";
      std::string middle;
      for (int j = 0; j <= cols; j++) {

        if (j > 0) { 
          // determine if a robot is current located in this cell
          // and/or if this is the goal
          Position p(i,j);
          char c = getspot(p);
          char g = isGoal(p);
          if (g != '?') g = tolower(g);
          first += "    ";
          middle += " "; 
          middle += c; 
          middle += g; 
          middle += " ";
        }

        // the vertical walls
        if (getVerticalWall(i,j+0.5)) {
          first += "|";
          middle += "|";
        } else {
          first += " ";
          middle += " ";
        }
      }

      // output the three rows
      std::cout << first << std::endl;
      std::cout << std::setw(2) << i << middle << std::endl;
      std::cout << first << std::endl;
    }

    // print the horizontal walls between rows
    std::cout << "  +";
    for (double j = 1; j <= cols; j++) {
      (getHorizontalWall(i+0.5,j)) ? std::cout << "----" : std::cout << "    ";
      std::cout << "+";
    }
    std::cout << "\n";
  }
}

// ==================================================================
// ==================================================================
void Board::visualize(int robot, int max_moves) {
  std::vector<std::pair<int, std::string>> moves;

  if (max_moves == -1) max_moves = MAX_MOVES;
  memorizedSearch(moves, 0, max_moves, false);

  std::vector<std::vector<int>> pos_moves;
  pos_moves.resize(rows + 1, std::vector<int>(cols + 1, MAX_MOVES));

  //can not use auto
  std::unordered_map<std::string,int>::iterator it;
  for ( it = searched_moves.begin(); it != searched_moves.end(); it++) {
    Position pos = getRobotPositionFromStr((std::string)it->first, robot);
    pos_moves[pos.row][pos.col] = std::min(it->second, pos_moves[pos.row][pos.col]);
  }

  std::cout << "Reachable by robot " << getRobot(robot) << ":" << std::endl;
  for (int row = 1; row <= rows; row++) {
    for (int col = 1; col <= cols; col++) {
      if (pos_moves[row][col] == MAX_MOVES) std::cout << "  .";
      else std::cout << std::setfill(' ') << std::setw(3) << pos_moves[row][col];
    }
    std::cout << std::endl;
  }
}

void Board::findSolution(bool all_solutions, int max_moves) {
  std::vector<std::pair<int, std::string>> moves;
  std::vector<std::pair<int, std::string>> one_solution;
  unsigned int num_searched_moves = 1;

  if (max_moves == -1) max_moves = MAX_MOVES;

  // Slowly increase moves to find out shortest move
  for (int i = 1; i <= max_moves; ++i) {
    min_moves = MAX_MOVES;
    memorizedSearch(moves, 0, i, false);

    // Found solution
    if (min_moves != MAX_MOVES) {
      print();

      if (all_solutions) std::cout << num_solutions << " different " << min_moves << " move solutions:" << std::endl << std::endl;
      
      memorizedSearch(moves, 0, i, all_solutions);

      // Print detail solution
      if (!all_solutions) {
        for (unsigned int j = 0; j < solution.size(); ++j) {
          std::cout << "robot " << getRobot(solution[j].first) << " moves " << solution[j].second << std::endl;
          moveRobot(solution[j].first, solution[j].second);
          print();
        }
        std::cout << "All goals are satisfied after " << min_moves << " moves" << std::endl << std::endl;
      }
      return;
    }

    // All possible moves have been enumerated, no solutions
    if (searched_moves.size() == num_searched_moves) {
      std::cout << "no solutions" << std::endl;
      return;
    }
    num_searched_moves = searched_moves.size();
  }
}

void Board::memorizedSearch(std::vector<std::pair<int, std::string>> &moves, int move, int max_moves, bool print_all) {
  if (goalSatisfied()) {

    // Print solution
    if (print_all) {
      for (unsigned int i = 0; i < moves.size(); ++i)
        std::cout << "robot " << getRobot(moves[i].first) << " moves " << moves[i].second << std::endl;
      std::cout << "All goals are satisfied after " << move << " moves" << std::endl << std::endl;
    }

    // Record solution
    solution.clear();
    for (unsigned int i = 0; i < moves.size(); ++i) solution.push_back(moves[i]);

    // Update mininum moves number for solution and total solution number
    if (move < min_moves) {
      min_moves = move;
      num_solutions = 1;
    } else if (move == min_moves) num_solutions++;
  }

  // Check if not get position in a worse way
  std::string robot_pos = robotPositionsToStr();
  if (searched_moves.find(robot_pos) != searched_moves.end() && move > searched_moves[robot_pos]) return;
  searched_moves[robot_pos] = move;

  // Reached max moves
  if (move >= max_moves) return;

  // Emuerate all possible move
  for (unsigned int i = 0; i < numRobots(); ++i) {
    Position pos = getRobotPosition(i);
    if (moveRobot(i, DIRECTION_EAST)) {
      moves.push_back(std::pair<int, std::string>(i, DIRECTION_EAST));
      memorizedSearch(moves, move + 1, max_moves, print_all);
      restoreRobot(i, pos);
      moves.pop_back();
    }
    if (moveRobot(i, DIRECTION_WEST)) {
      moves.push_back(std::pair<int, std::string>(i, DIRECTION_WEST));
      memorizedSearch(moves, move + 1, max_moves, print_all);
      restoreRobot(i, pos);
      moves.pop_back();
    }
    if (moveRobot(i, DIRECTION_NORTH)) {
      moves.push_back(std::pair<int, std::string>(i, DIRECTION_NORTH));
      memorizedSearch(moves, move + 1, max_moves, print_all);
      restoreRobot(i, pos);
      moves.pop_back();
    }
    if (moveRobot(i, DIRECTION_SOUTH)) {
      moves.push_back(std::pair<int, std::string>(i, DIRECTION_SOUTH));
      memorizedSearch(moves, move + 1, max_moves, print_all);
      restoreRobot(i, pos);
      moves.pop_back();
    }
  }
}

std::string Board::robotPositionsToStr() {
  std::ostringstream ost;
  for (unsigned int i = 0; i < numRobots(); ++i) {
    ost << robots[i].which << " " <<robots[i].pos.row << " " << robots[i].pos.col << " ";
  }
  return ost.str();
}

Position Board::getRobotPositionFromStr(const std::string &str, int robot) {
  std::istringstream ist(str);
  char which;
  int row, col;
  for (int i = 0; i < robot + 1; ++i) {
    ist >> which >> row >> col;
  }
  return Position(row, col);
}

bool Board::goalSatisfied() {
  for (unsigned int i = 0; i < numGoals(); ++i) {
    bool satisfied = false;
    for (unsigned int j = 0; j < numRobots(); ++j) {
      if (getGoalRobot(i) == '?' || getGoalRobot(i) == getRobot(j))
        if (getGoalPosition(i) == getRobotPosition(j)) {
          satisfied = true;
          break;
        }
    }

    if (!satisfied) return false;
  }

  return true;
}

void Board::restoreRobot(int i, Position &p) {
  setspot(robots[i].pos, ' ');
  robots[i].pos = p;
  setspot(robots[i].pos, robots[i].which);
}

// ==================================================================
// ==================================================================
