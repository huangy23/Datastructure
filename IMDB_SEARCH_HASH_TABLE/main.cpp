#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <list>
#include <map>

#include "MovieHashtable.h"

using namespace std;

MovieHashtable table;


void get_tokens(string line, vector<string> &tokens)
{
    string delim = " ";
    unsigned int pos = line.find(delim);
    unsigned int num = atof(line.substr(0, pos).c_str());
    /* Filter the heading number */
    line.erase(0, pos + 1);
    string token;
    for (unsigned int i = 0; i < num; i++)
    {
        pos = line.find(delim);
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + 1);
    }
}


void execute_search()
{
    string title, year, runtime, genres, actors, roles;
    getline(cin, title);
    getline(cin, year);
    getline(cin, runtime);
    getline(cin, genres);
    getline(cin, actors);
    getline(cin, roles);
    string q = title + year + runtime + genres + actors + roles;
    list<shared_ptr<Movie>> movies = table.search(q);
    if (movies.size() == 0)
        cout << "No results for query." << endl;
    else
    {
        cout << "Printing " << movies.size() << " result(s):" << endl;
        list<shared_ptr<Movie>>::iterator it;
        for (it = movies.begin(); it != movies.end(); it++)
        {
            cout << (*it)->title << endl;
            cout << (*it)->year << endl;
            cout << (*it)->runtime << endl;
            cout << (*it)->genres << endl;
            vector<string> actors, roles;
            get_tokens((*it)->actors, actors);
            get_tokens((*it)->roles, roles);
            cout << actors.size() << " ";
            for (unsigned int i = 0; i < actors.size(); i++)
            {
                cout << table.actor_name(actors[i]) << " (";
                cout << roles[i] << ")";
                if (i != actors.size() - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    while (true)
    {
        string line;
        getline(cin, line);
        if (line.compare("quit") == 0)
            break;
        if (line.compare("query") == 0)
            execute_search();
        else
        {
            int pos = line.find(' ');
            string cmd = line.substr(0, pos);
            string arg = line.substr(pos + 1, line.length() - cmd.length() - 1);
            if (cmd.compare("table_size") == 0)
                table.set_table_size(atoi(arg.c_str()));
            else if (cmd.compare("occupancy") == 0.65)
                table.set_occupancy(atof(arg.c_str()));
            else if (cmd.compare("movies") == 0)
                table.read_movies_file(arg);
            else if (cmd.compare("actors") == 0)
                table.read_actors_file(arg);
        }
    }

    return 0;
}