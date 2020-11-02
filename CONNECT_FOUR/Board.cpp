
#include <iostream>
#include <string>
#include "Board.h"

std::ostream &operator<<(std::ostream &out, const Board &bd)
{
    for (int i = bd.numRows() - 1; i >= 0; i--)
    {
        for (signed int j = 0; j < bd.numColumns(); j++)
        {
            out << bd.values[i][j];
            if (j != bd.numColumns() - 1)
                out << ' ';
        }
        out << std::endl;
    }
    return out;
}
/*
Board::Board()
{
    values = NULL;
    rows = 0;
    cols = 0;
    red = "a";
    yellow = "a";
    fill = "a";
}
*/
Board::Board(std::string r, std::string y, std::string f)
{
    rows = 5;
    cols = 4;
    red = r;
    yellow = y;
    fill = f;

    values = new std::string *[rows];
    for (unsigned int i = 0; i < rows; i++)
    {
        values[i] = new std::string[cols];
    }

    for (unsigned int i = 0; i < rows; ++i)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            values[i][j] = fill;
        }
    }
}

//template <class T>
int Board::compute_numTokensInRow(int r)
{
    if (unsigned(r + 1) > rows)
    {
        return -1;
    }
    int count = 0;
    for (unsigned int i = 0; i < cols; i++)
    {

        if ((values[r][i] == red) | (values[r][i] == yellow))
        {
            count++;
        }
    }
    return count;
}

//template <class T>
int Board::compute_numTokensInColumn(int c)
{
    int count = 0;
    if (unsigned(c + 1) > cols)
    {
        return -1;
    }
    else
    {
        for (unsigned int i = 0; i < rows; i++)
        {

            if ((values[i][c] == red) | (values[i][c] == yellow))
            {
                count++;
            }
        }
    }
    return count;
}

//template <class T>
bool Board::check_board_by_row()
{
    bool result = false;
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < (cols - 3); j++)
        {
            if ((values[i][j] == red) && (values[i][j + 1] == red) && (values[i][j + 2] == red) && (values[i][j + 3] == red))
            {
                result = true;
                winner = red;
            }
            if ((values[i][j] == yellow) && (values[i][j + 1] == yellow) && (values[i][j + 2] == yellow) && (values[i][j + 3] == yellow))
            {
                result = true;
                winner = yellow;
            }
        }
    }

    for (unsigned int i = 0; i < cols; i++)
    {
        for (unsigned int j = 0; j < (rows - 3); j++)
        {
            if ((values[j][i] == red) && (values[j + 1][i] == red) && (values[j + 2][i] == red) && (values[j + 3][i] == red))
            {
                result = true;
                winner = red;
            }
            if ((values[j][i] == yellow) && (values[j + 1][i] == yellow) && (values[j + 2][i] == yellow) && (values[j + 3][i] == yellow))
            {
                result = true;
                winner = yellow;
            }
        }
    }
    return result;
}

//template <class T>
std::string Board::insert(unsigned int c, bool player)
{
    if ((c < cols) && (compute_numTokensInColumn(c) < (signed)rows))
    {
        if (player == true)
        {
            values[compute_numTokensInColumn(c)][c] = red;
        }
        if (player == false)
        {
            values[compute_numTokensInColumn(c)][c] = yellow;
        }
        if (check_board_by_row() == true)
        {
            return winner;
        }
        else
        {
            return fill;
        }
    }
    else
    {

        int x = rows;
        int y = cols;
        if (c >= cols)
        {
            y = c + 1;
        }

        if (compute_numTokensInColumn(c) >= (signed)rows)
        {
            x = rows + 1;
        }

        std::string **temp;
        temp = new std::string *[x];
        for (signed int i = 0; i < x; i++)
        {
            temp[i] = new std::string[y];
        }

        for (signed int i = 0; i < x; ++i)
        {
            for (signed int j = 0; j < y; j++)
            {
                if ((i < (signed)rows) && (j < (signed)cols))
                {
                    temp[i][j] = values[i][j];
                }
                else
                {
                    temp[i][j] = fill;
                }
            }
        }

        std::string **dl = values;
        for (size_t i = 0; i < rows; i++)
        {
            delete[] * (dl + i); // DELETE THE INDIVIDUAL ROW USING A LOOP.
        }
        delete[] values;

        rows = x;
        cols = y;
        values = temp;
        //add
        if (player == true)
        {
            values[compute_numTokensInColumn(c)][c] = red;
        }
        if (player == false)
        {
            values[compute_numTokensInColumn(c)][c] = yellow;
        }
        if (check_board_by_row() == true)
        {
            return winner;
        }
        else
        {
            return fill;
        }
    }
    return fill;
}

//template <class T>
Board::~Board()
{
    std::string **dl = values;
    for (size_t i = 0; i < rows; i++)
    {
        delete[] * (dl + i); // DELETE THE INDIVIDUAL ROW USING A LOOP.
    }
    delete[] values;
}

void Board::clear()
{
    std::string **dl = values;
    for (size_t i = 0; i < rows; i++)
    {
        delete[] * (dl + i); // DELETE THE INDIVIDUAL ROW USING A LOOP.
    }
    delete[] values;

    values = new std::string *[rows];
    for (unsigned int i = 0; i < rows; i++)
    {
        values[i] = new std::string[cols];
    }

    for (unsigned int i = 0; i < rows; ++i)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            values[i][j] = fill;
        }
    }
}