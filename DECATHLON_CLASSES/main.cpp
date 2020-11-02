/******************************************************************************/
// File: main.cpp
// Purpose: main file for the program
// Created by Yudong Huang by 1/20/2020
// Copyright © 2020 Yudong Huang. All rights reserved.
/******************************************************************************/

#include <iostream>
#include <fstream> //read write to files
#include <string>
#include <cstdlib> //convert str to int or float
#include <vector>
#include <stdlib.h> //atoi
#include "athelete.h"
#include <algorithm>
#include <iomanip> // std::setw
#include <cmath>   //using pow

using namespace std;

float round_to_2(float value)
{
    float rounded = ((int)(value * 100 + .5) / 100.0);
    return rounded;
}

bool has_any_digits(const std::string &s)
{
    return std::any_of(s.begin(), s.end(), ::isdigit);
}

int main(int argc, char *argv[])
{
    ifstream in_str(argv[1]);  // input file
    ofstream out_str(argv[2]); // output file
    std::string command = argv[3];

    //test input successfully opened
    if (!in_str.good())
    {
        cerr << "Can't open " << argv[1] << " to read." << endl;
        exit(1);
    }

    //test output successfully opened
    if (!out_str.good())
    {
        cerr << "Can't open " << argv[2] << " to write." << endl;
        exit(1);
    }

    vector<string> content;
    vector<Player> player_container;
    string input; //input word by word

    while (in_str >> input)
    {
        content.push_back(input);
    }

    //determine players attended
    //determine event 100m index
    int ind_100;
    for (unsigned int f = 0; f < content.size(); f++)
    {
        if (content[f] == "100_METERS")
        {
            ind_100 = f - 1;
        }
    }

    int indi = content.size();
    for (signed int i = ind_100 + 2; i < indi; i += 4)
    {
        if (content[i] != "event")
        {
            Player temp_player;
            temp_player.setFirstName(content[i]);
            temp_player.setLastName(content[i + 1]);
            temp_player.setCountry(content[i + 2]);
            player_container.push_back(temp_player);
        }
        else
        {
            indi = 0;
        }
    }

    string current_event;
    string current_name_1;
    string current_name_2;
    string current_nation;
    unsigned int i = 0;
    while (i < content.size())
    {
        //determine the current content
        if (content[i] == "event")
        {
            current_event = content[i + 1];
        }

        if (has_any_digits(content[i + 3]))
        {
            current_name_1 = content[i];
            current_name_2 = content[i + 1];
            current_nation = content[i + 2];

            //find atheletes in player_container
            for (unsigned int j = 0; j < player_container.size(); j++)
            {
                if ((player_container[j].getFirstName() == current_name_1) &&
                    (player_container[j].getLastName() == current_name_2) &&
                    (player_container[j].getCountry() == current_nation) && (current_event != "1500_METERS"))
                {
                    player_container[j].addEvent(current_event, stof(content[i + 3]));
                }
                if ((player_container[j].getFirstName() == current_name_1) &&
                    (player_container[j].getLastName() == current_name_2) &&
                    (player_container[j].getCountry() == current_nation) && (current_event == "1500_METERS"))
                {
                    float temp_total_seconds;
                    string temp_sec = content[i + 3];
                    float min = stof(temp_sec.substr(0, 1));
                    float sec = stof(temp_sec.substr(2, 5));
                    temp_total_seconds = 60 * min + sec;
                    player_container[j].addEvent(current_event, temp_total_seconds);
                    player_container[j].set1500_METERS(temp_sec);
                }
            }
        }

        i++;
    }

    //determine which command score or points
    if (command == "scores")
    {
        sort(player_container.begin(), player_container.end(), sort_by_country_lastname);
        out_str << "DECATHLETE SCORES" << std::setw(24 - 7) << "100" << std::setw(7)
                << "LJ" << std::setw(7) << "SP" << std::setw(7) << "HJ" << std::setw(7)
                << "400" << std::setw(7) << "110H" << std::setw(7) << "DT"
                << std::setw(7) << "PV" << std::setw(7) << "JT" << std::setw(9) << "1500"
                << std::setw(7) << std::endl;

        for (unsigned int i = 0; i < player_container.size(); ++i)
        {
            //float a, b, c, d, e, f, g, h, i;
            vector<float> p_c;

            p_c.push_back(round_to_2(player_container[i].get100_METERS()));
            p_c.push_back(round_to_2(player_container[i].getLONG_JUMP()));
            p_c.push_back((round_to_2(player_container[i].getSHOT_PUT())));
            p_c.push_back((round_to_2(player_container[i].getHIGH_JUMP())));
            p_c.push_back((round_to_2(player_container[i].get400_METERS())));
            p_c.push_back((round_to_2(player_container[i].get110_METERS_HURDLES())));
            p_c.push_back((round_to_2(player_container[i].getDISCUS_THROW())));
            p_c.push_back((round_to_2(player_container[i].getPOLE_VAULT())));
            p_c.push_back((round_to_2(player_container[i].getJAVELIN_THROW())));

            /*for (unsigned int i = 0; i < p_c.size(); i++)
            {
                if (p_c[i] == 0.00)
                {
                    p_c[i] =
                }
            }*/

            //write scores to file
            out_str << std::setw(14) << std::left << player_container[i].getFirstName() << std::setw(14) << std::left << player_container[i].getLastName();
            out_str << std::setw(5) << player_container[i].getCountry();
            out_str << std::setw(8) << p_c[0] << std::setw(6);
            if (p_c[1] == 0)
            {
                out_str << "    " << std::setw(8);
            }
            else
            {
                out_str << p_c[1] << std::setw(8);
            }

            //out_str << p_c[1] << std::setw(8);
            if (p_c[2] == 0)
            {
                out_str << "    ";
            }
            else
            {
                out_str << p_c[2];
            }
            
            if (p_c[3] == 0)
            {
                out_str << std::setw(6) << "    " << std::setw(7) << setiosflags(ios::fixed) << setprecision(2);
            }
            else
            {
                out_str << std::setw(6) << p_c[3] << std::setw(7) << setiosflags(ios::fixed) << setprecision(2);
            }
            
            if (p_c[4] == 0)
            {
                out_str << "    ";
            }
            else
            {
                out_str << p_c[4];
            }
            if (p_c[5] == 0)
            {
                out_str << std::setw(7) << "    ";
            }
            else
            {
                out_str << std::setw(7) << p_c[5];
            }
            if (p_c[6] == 0)
            {
                out_str << std::setw(8) << "    " << std::setw(6);
            }
            else
            {
                out_str << std::setw(8) << p_c[6] << std::setw(6);
            }

            if (p_c[7] == 0)
            {
                out_str << "    " << std::setw(7);
            }
            else
            {
                out_str << p_c[7] << std::setw(7);
            }

            if (p_c[8] ==0)
            {
                out_str << "    ";
            }
            else
            {
                out_str << p_c[8];
            }
            
            out_str << (player_container[i].get1500_METERS()) << std::endl;
        }
    }

    if (command == "points")
    {
        sort(player_container.begin(), player_container.end(), sort_by_points);
        out_str << "DECATHLETE POINTS" << std::setw(24) << "100" << std::setw(7) << "LJ"
                << std::setw(7) << "SP" << std::setw(7) << "HJ" << std::setw(7) << "400";
        out_str << std::setw(7) << "110H" << std::setw(7) << "DT" << std::setw(7)
                << "PV" << std::setw(7) << "JT" << std::setw(9) << "1500"
                << std::setw(10) << "TOTAL" << std::endl;
        for (unsigned int i = 0; i < player_container.size(); ++i)
        {

            out_str << std::setw(13) << std::left << player_container[i].getFirstName() << std::setw(16) << std::left << player_container[i].getLastName();
            out_str << std::setw(7) << player_container[i].getCountry();
            out_str << std::right << std::setw(5) << player_container[i].get100_METERS_points() << std::setw(7) << player_container[i].getLONG_JUMP_points() << std::setw(7) << player_container[i].getSHOT_PUT_points() << std::setw(7) << player_container[i].getHIGH_JUMP_points();
            out_str << std::setw(7) << player_container[i].get400_METERS_points() << std::setw(7) << player_container[i].get110_METERS_HURDLES_points() << std::setw(7) << player_container[i].getDISCUS_THROW_points() << std::setw(7) << player_container[i].getPOLE_VAULT_points() << std::setw(7) << player_container[i].getJAVELIN_THROW_points();
            out_str << std::setw(9) << player_container[i].get1500_METERS_points() << std::setw(10) << player_container[i].getTotal_points() << std::endl;
        }
    }

    if (command == "custom")
    {
        sort(player_container.begin(), player_container.end(), sort_by_100m);
        out_str << "BEST 100M RUNNER" << std::setw(24) << "100" << std::setw(7) << "LJ"
                << std::setw(7) << "SP" << std::setw(7) << "HJ" << std::setw(7) << "400";
        out_str << std::setw(7) << "110H" << std::setw(7) << "DT" << std::setw(7)
                << "PV" << std::setw(7) << "JT" << std::setw(9) << "1500"
                << std::setw(10) << "TOTAL" << std::endl;
        for (unsigned int i = 0; i < player_container.size(); ++i)
        {

            out_str << std::setw(13) << std::left << player_container[i].getFirstName() << std::setw(16) << std::left << player_container[i].getLastName();
            out_str << std::setw(7) << player_container[i].getCountry();
            out_str << std::right << std::setw(5) << player_container[i].get100_METERS_points() << std::setw(7) << player_container[i].getLONG_JUMP_points() << std::setw(7) << player_container[i].getSHOT_PUT_points() << std::setw(7) << player_container[i].getHIGH_JUMP_points();
            out_str << std::setw(7) << player_container[i].get400_METERS_points() << std::setw(7) << player_container[i].get110_METERS_HURDLES_points() << std::setw(7) << player_container[i].getDISCUS_THROW_points() << std::setw(7) << player_container[i].getPOLE_VAULT_points() << std::setw(7) << player_container[i].getJAVELIN_THROW_points();
            out_str << std::setw(9) << player_container[i].get1500_METERS_points() << std::setw(10) << player_container[i].getTotal_points() << std::endl;
        }
    }
    
}