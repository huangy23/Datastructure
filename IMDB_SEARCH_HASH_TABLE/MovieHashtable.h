#include <vector>
#include <list>
#include <string>
#include <map>
#include <memory>
#include "Movie.h"

using namespace std;

class MovieHashtable
{
private:
    static const unsigned int DEFAULT_TABLE_SIZE = 100;
    static constexpr float DEFAULT_OCCUPANCY = 0.5f;
    unsigned int m_size;
    unsigned int m_count;
    float m_occupancy;
    vector<pair<string, list<shared_ptr<Movie>>>> m_table;
    std::map<string, string> m_actors;

    void add(string q, shared_ptr<Movie> m);
    void insert_entry(unsigned int i, string q, shared_ptr<Movie> m);
    bool entry_available(unsigned int i);
    void resize();
    int allocate_entry(const string &key);
    int find(string q);

public:
    MovieHashtable();
    void set_table_size(unsigned int size);
    void set_occupancy(float occupancy);
    void read_movies_file(std::string filename);
    void read_actors_file(std::string filename);
    list<shared_ptr<Movie>> search(string query);
    string actor_name(string nconst);
};