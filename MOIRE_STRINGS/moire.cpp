/******************************************************************************/
// File: moire.cpp
// Purpose: Header file with declaration of the template Table.
// Created by Yudong Huang on 1/19/2020.
// Copyright © 2020 Yudong Huang. All rights reserved.
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

//function declaration
void square_generator(int width, int total_len, string content_string, char *name);
void right_triangle_generator(int c_height, int total_len, string content_string, char *name);
void isosceles_triangle_generator(int c_height,  string content_string, char *name);

/* 
0           1     2 3      4
./moire.exe abcde 9 square abcde_9_square.txt
./moire.exe abcde 9 right_triangle abcde_9_right_triangle.txt
./moire.exe abcde 9 isosceles_triangle abcde_9_isosceles_triangle.txt
./moire.exe ::....... 21 square dots_21_square.txt
./moire.exe '__hi!__' 21 right_triangle hi_21_right_triangle.txt
./moire.exe "|_| " 21 isosceles_triangle blocky_21_isosceles_triangle.txt
*/
int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cerr << "There are no enough parameters" << endl;
        exit(0);
    }
    char *name = argv[4];
    ofstream output_file(argv[4]);
    string base_string;
    base_string += (argv[1]);

    string arg2;
    arg2 += argv[2];
    int height = stoi(arg2);
    int total_len;


    if (string(argv[3]) == "square")
    {

        total_len = (height - 2) * (height - 2);
        string content_string = "";
        int repeat_time = total_len / (base_string.size());
        int last_len = total_len % (base_string.size());
        string last_one_string = base_string.substr(0, last_len);
        for (signed int i = 0; i < repeat_time; i++)
        {
            content_string += base_string;
        }
        content_string += last_one_string;

        square_generator(height, total_len, content_string, name);
    }

    else if (string(argv[3]) == "right_triangle")
    {
        total_len = ((height - 3) * (height - 2)) / 2;

        string content_string = "";
        int repeat_time = total_len / (base_string.size());
        int last_len = total_len % (base_string.size());
        string last_one_string = base_string.substr(0, last_len);
        for (signed int i = 0; i < repeat_time; i++)
        {
            content_string += base_string;
        }
        content_string += last_one_string;

        right_triangle_generator(height - 3, total_len, content_string, name);
    }

    else if (string(argv[3]) == "isosceles_triangle")
    {
        total_len = ((height - 2) * ((height - 2) * 2)) / 2;
        string content_string = "";
        int repeat_time = total_len / (base_string.size());
        int last_len = total_len % (base_string.size());
        string last_one_string = base_string.substr(0, last_len);
        for (signed int i = 0; i < repeat_time; i++)
        {
            content_string += base_string;
        }
        content_string += last_one_string;

        isosceles_triangle_generator(height - 2, content_string, name);
    }
    output_file.close();
    // fill the custom shape
}

//square
void square_generator(int width, int total_len, string content_string, char *name)
{
    //generate the top line '*' fill that out
    ofstream output_file(name);
    output_file << string(width, '*') << endl;//first line
    output_file << "*";
    int content_width = width - 2;
    for (signed int j = 0; j < total_len; j++)
    {

        if (((j + 1) % content_width) == 0)
        {
            output_file << content_string[j] << "*" << endl;
            output_file << "*";
        }
        else
        {
            output_file << content_string[j];
        }
    }
    output_file << string(width - 1, '*') << endl;//last line
}

//triangle
void right_triangle_generator(int c_height, int total_len, string content_string, char *name)
{
    ofstream output_file(name);

    signed int j = 0; // index for when to cout endl
    int incre = 2;    // a increment number to help define int j
    output_file << "*" << endl;
    output_file << "**" << endl;
    output_file << "*";
    for (signed int i = 0; i < total_len; i++)
    {
        if (j == i)
        {

            output_file << content_string[i];
            output_file << "*";
            output_file << endl;
            j += incre;
            incre++;
            output_file << "*";
        }
        else
        {
            output_file << content_string[i];
        }
    }
    output_file << string(c_height + 2, '*') << endl;
}

//isoceles_triangle
void isosceles_triangle_generator(int c_height, string content_string, char *name)
{
    ofstream output_file(name);

    int line_size = 1;
    int space = c_height;
    // top of triangle
    output_file << string(space +1,' ') << '*' << endl;
    output_file << string(space, ' ') << '*';
    output_file << content_string[0] << '*' << endl;
    space--;
    line_size += 2;
    content_string.erase(content_string.begin());
    while (content_string.size() != 0)
    {

        output_file << string(space, ' ') << '*';
        for (signed i = 0; i < line_size; i++)
        {
            output_file << content_string[i];
        }
        for (signed j = 0; j < line_size; j++)
        {
            content_string.erase(content_string.begin());
        }
        output_file << "*" << endl;
        line_size += 2;
        space--;
    }
    output_file << string(c_height*2 +3,'*') << endl;// last line
}
