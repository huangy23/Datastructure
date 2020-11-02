/******************************************************************************/
// File: Board.h
// Purpose: Header file with declaration of the template Table.
// Created by Yudong Huang on 2/9/2020.
// Copyright © 2020 Yudong Huang. All rights reserved.
/******************************************************************************/

#ifndef BOARD_
#define BOARD_

#include <iostream>
#include <fstream>
#include <string>

class Board
{
public:
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, & DESTRUCTOR
    //Board();
    Board(std::string r, std::string y, std::string f);
    ~Board(); // DEFAULT DESTRUCTOR.

    // ACCESSORS
    int numRows() const { return rows; }
    int numColumns() const { return cols; }
    std::string getfill() const { return fill; }
    //size_t numTokensInRow(size_t r);
    int numTokensInRow(int r) { return compute_numTokensInRow(r); }
    int numTokensInColumn(int c) { return compute_numTokensInColumn(c); }
    std::string insert(unsigned int c, bool player);
    friend std::ostream &operator<<(std::ostream &out, const Board &bd);
    void clear(); //clear operator
    int compute_numTokensInRow(int r);
    int compute_numTokensInColumn(int c);
    bool check_board_by_row();

private:
    std::string **values;
    unsigned int rows;
    unsigned int cols;
    std::string red;
    std::string yellow;
    std::string fill;
    std::string winner;
};

#endif