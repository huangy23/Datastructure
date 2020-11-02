#include <iostream>
#include <fstream>
#include "MovieHashtable.h"

#define PERMUTE_COUNT 64
#define BIT_MASK_1 0x1
#define BIT_MASK_2 0x2
#define BIT_MASK_3 0x4
#define BIT_MASK_4 0x8
#define BIT_MASK_5 0x10
#define BIT_MASK_6 0x20


unsigned int my_hash(string const &k, unsigned int N)
{
    unsigned int value = 0;
    for (unsigned int i = 0; i < k.size(); ++i)
        value = value * 8 + k[i]; // conversion to int is automatic
    return value % N;
}


void permute_queries(shared_ptr<Movie> m, vector<string> &queries)
{
    for (int i = 0; i < PERMUTE_COUNT; i++)
    {
        string q = "";
        if (i & BIT_MASK_1)
            q += m->title;
        else
            q += "?";
        if (i & BIT_MASK_2)
            q += m->year;
        else
            q += "?";
        if (i & BIT_MASK_3)
            q += m->runtime;
        else
            q += "?";
        if (i & BIT_MASK_4)
            q += m->genres;
        else
            q += "0";
        if (i & BIT_MASK_5)
            q += m->actors;
        else
            q += "0";
        if (i & BIT_MASK_6)
            q += m->roles;
        else
            q += "0";
        queries.push_back(q);
    }
}

MovieHashtable::MovieHashtable()
{
    m_size = DEFAULT_TABLE_SIZE;
    m_count = 0;
    m_occupancy = DEFAULT_OCCUPANCY;
    m_table.resize(m_size);
}


void MovieHashtable::set_table_size(unsigned int size)
{
    m_size = size;
    m_table.resize(m_size);
}


void MovieHashtable::set_occupancy(float occ)
{
    m_occupancy = occ;
}


void MovieHashtable::read_movies_file(string filename)
{
    ifstream in(filename);
    if (!in.good())
        return;
    while (!in.eof())
    {
        string title;
        getline(in, title);
        if (title.length() == 0)
            break;
        shared_ptr<Movie> m(new Movie());
        m->title = title;
        getline(in, m->year);
        getline(in, m->runtime);
        getline(in, m->genres);
        getline(in, m->actors);
        getline(in, m->roles);

        vector<string> queries;
        permute_queries(m, queries);
        for (unsigned int i = 0; i < queries.size(); i++)
            add(queries.at(i), m);
    }
}


void MovieHashtable::read_actors_file(string filename)
{
    ifstream in(filename);
    if (!in.good())
        return;
    while (!in.eof())
    {
        string line;
        getline(in, line);
        if (line.length() == 0)
            break;
        int pos = line.find(' ');
        string nconst = line.substr(0, pos);
        string name = line.substr(pos + 1, line.length() - nconst.length() - 1);
        m_actors[nconst] = name;
    }
}


list<shared_ptr<Movie>> MovieHashtable::search(string query)
{
    list<shared_ptr<Movie>> l;
    int i = find(query);
    if (i != -1)
        return m_table.at(i).second;
    return l;
}


void MovieHashtable::add(string query, shared_ptr<Movie> m)
{
    int i = find(query);
    if (i != -1)
    {
        /* If the query has been inserted before, append m to the list */
        m_table.at(i).second.push_back(m);
    }
    else
    {
        /* Otherwise allocate a new entry in the hastable */
        i = allocate_entry(query);
        if (i != -1)
            insert_entry(i, query, m);
    }
}


string MovieHashtable::actor_name(string nconst)
{
    return m_actors[nconst];
}


void MovieHashtable::insert_entry(unsigned int i, string q, shared_ptr<Movie> m)
{
    m_table.at(i).first = q;
    m_table.at(i).second.push_back(m);
    m_count++;
    resize();
}


bool MovieHashtable::entry_available(unsigned int i)
{
    return m_table.at(i).second.size() == 0;
}


void MovieHashtable::resize()
{
    if ((float)m_count / m_size <= m_occupancy)
        return;
    
    vector<pair<string, list<shared_ptr<Movie>>>> table(m_table);
    m_size *= 2;
    m_table.clear();
    m_table.resize(m_size);
    for (unsigned int i = 0; i < table.size(); i++)
    {
        string key = table.at(i).first;
        unsigned int entry_index = allocate_entry(key);
        m_table.at(entry_index).first = table.at(i).first;
        m_table.at(entry_index).second = table.at(i).second;
    }
}


int MovieHashtable::allocate_entry(const string &key)
{
    unsigned int i = my_hash(key, m_size);
    unsigned int begin_index = i;
    while (!entry_available(i))
    {
        
        i = (i + 1) % m_size;
        if (i == begin_index)
            return -1;
    }
    return i;
}


int MovieHashtable::find(string q)
{
    unsigned int i = my_hash(q, m_size);
    if (entry_available(i))
        return -1;
    unsigned int begin_index = i;
    while (!entry_available(i))
    {
        if (q == m_table.at(i).first)
            return i;
        i = (i + 1) % m_size;
        if (i == begin_index)
            break;
    }
    return -1;
}
