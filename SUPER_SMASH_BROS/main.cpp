#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

//function to process frame for one or all move(s)
void get_move_frame_q(const string &charactor, const string &move, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile);
void get_fighters_d(const string &move, const int &frame, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile);
void get_fast_fighters_f(const string &move, const int &num, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile);
void get_slow_fighters_s(const string &move, const int &num, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile);
bool comp(const pair<int, string> &a,
		  const pair<int, string> &b);

int main(int argc, char **argv)
{
	// Argument parsing
	if (argc != 4)
	{
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	//input file: frame database file
	std::ifstream dbfile(argv[1]);
	if (!dbfile)
	{
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	//input file: input queries
	std::ifstream infile(argv[2]);
	if (!infile)
	{
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	//output file
	std::ofstream outfile(argv[3]);
	if (!outfile)
	{
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	//get txt to database map
	string input; //input word by word
	vector<string> content;
	while (dbfile >> input)
	{
		content.push_back(input);
	}

	//map to store frame data
	map<string, vector<int>> fram_database;

	for (unsigned int i = 8; i < content.size(); i += 8)
	{
		string temp_charactor = content[i];
		vector<int> temp_moves = {stoi(content[i + 1]), stoi(content[i + 2]), stoi(content[i + 3]), stoi(content[i + 4]), stoi(content[i + 5]), stoi(content[i + 6]), stoi(content[i + 7])};
		fram_database.insert(pair<string, vector<int>>(temp_charactor, temp_moves));
	}

	string query_input;
	vector<string> query_content;
	while (infile >> query_input)
	{
		query_content.push_back(query_input);
	}

	for (unsigned int i = 0; i < query_content.size(); i += 3)
	{
		if (query_content[i] == "-q")
		{
			string temp_charactor = query_content[i + 1];
			string temp_move = query_content[i + 2];
			get_move_frame_q(temp_charactor, temp_move, fram_database, move_names, outfile);
			outfile << endl;
		}

		if (query_content[i] == "-d")
		{
			string temp_move = query_content[i + 1];
			int target_frame = stoi(query_content[i + 2]);
			outfile << "-d " << temp_move << " " << target_frame << endl;
			get_fighters_d(temp_move, target_frame, fram_database, move_names, outfile);
			outfile << endl;
		}
		if (query_content[i] == "-f")
		{
			string temp_move = query_content[i + 1];
			int num_fighters = stoi(query_content[i + 2]);
			outfile << "-f " << temp_move << " " << num_fighters << endl;
			get_fast_fighters_f(temp_move, num_fighters, fram_database, move_names, outfile);
			outfile << endl;
		}
		if (query_content[i] == "-s")
		{
			string temp_move = query_content[i + 1];
			int num_fighters = stoi(query_content[i + 2]);
			outfile << "-s " << temp_move << " " << num_fighters << endl;
			get_slow_fighters_s(temp_move, num_fighters, fram_database, move_names, outfile);
			outfile << endl;
		}
	}

	//void get_move_frame_q(const string &charactor, const string &move, const map<string, vector<int>> &database, const string m_n[7])
	return 0;
}

void get_move_frame_q(const string &charactor, const string &move, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile)
{
	bool found_charactor = false;
	bool found_move = false;

	int move_code; //0:jab 6:down-smash 7:all

	//situation when move is all
	if (move == "all")
	{
		move_code = 7;
		found_move = true;
	}

	for (signed int i = 0; i < 7; i++)
	{
		if (m_n[i] == move)
		{
			move_code = i;
			found_move = true;
		}
	}

	map<string, vector<int>>::const_iterator map_itr = database.begin();
	for (; map_itr != database.end(); map_itr++)
	{
		if (map_itr->first == charactor)
		{
			found_charactor = true;
		}

		//bool process
		if (found_charactor == true && found_move == true)
		{
			if (move_code != 7)
			{
				outfile << map_itr->first << " " << m_n[move_code] << ": " << map_itr->second[move_code] << endl;
				break;
			}
			else if (move_code == 7)
			{
				map<string, int> temp_all_moves; //(move, num)
				for (unsigned int i = 0; i < map_itr->second.size(); i++)
				{
					//outfile << map_itr->first << " " << m_n[i] << ": " << map_itr->second[i] << endl;
					temp_all_moves.insert(pair<string, int>(m_n[i], map_itr->second[i]));
				}

				for (map<string, int>::iterator temp_map_i = temp_all_moves.begin(); temp_map_i != temp_all_moves.end(); temp_map_i++)
				{
					outfile << charactor << " " << temp_map_i->first << ": " << temp_map_i->second << endl;
				}
				break;
			}
		}
	}

	if (found_charactor == false)
	{
		outfile << "Invalid character name: " << charactor << endl;
	}

	if (found_charactor == true && found_move == false)
	{
		outfile << "Invalid move name: " << move << endl;
	}
}

void get_fighters_d(const string &move, const int &frame, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile)
{
	vector<string> fighters_out;

	int move_code; //0:jab 6:down-smash
	for (signed int i = 0; i < 7; i++)
	{
		if (m_n[i] == move)
		{
			move_code = i;
		}
	}

	map<string, vector<int>>::const_iterator map_itr = database.begin();
	for (; map_itr != database.end(); map_itr++)
	{
		if (map_itr->second[move_code] == frame)
		{
			fighters_out.push_back(map_itr->first);
		}
	}

	for (unsigned int i = 0; i < fighters_out.size(); i++)
	{
		outfile << fighters_out[i] << endl;
	}
}

void get_fast_fighters_f(const string &move, const int &num, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile)
{
	int move_code; //0:jab 6:down-smash
	for (signed int i = 0; i < 7; i++)
	{
		if (m_n[i] == move)
		{
			move_code = i;
		}
	}

	map<string, int> fighter_move;
	vector<pair<int, string>> items;

	map<string, vector<int>>::const_iterator map_itr = database.begin();
	for (; map_itr != database.end(); map_itr++)
	{
		items.push_back(pair<int, string>(map_itr->second[move_code], map_itr->first));
	}

	sort(items.begin(), items.end());

	for (signed int i = 0; i < num; i++)
	{
		outfile << items[i].second << " " << items[i].first << endl;
	}
}

void get_slow_fighters_s(const string &move, const int &num, const map<string, vector<int>> &database, const string m_n[7], std::ofstream &outfile)
{
	int move_code; //0:jab 6:down-smash
	for (signed int i = 0; i < 7; i++)
	{
		if (m_n[i] == move)
		{
			move_code = i;
		}
	}

	map<string, int> fighter_move;
	vector<pair<int, string>> items;

	map<string, vector<int>>::const_iterator map_itr = database.begin();
	for (; map_itr != database.end(); map_itr++)
	{
		items.push_back(pair<int, string>(map_itr->second[move_code], map_itr->first));
	}

	int current_max = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i].first > current_max)
		{
			current_max = items[i].first;
		}
	}

	sort(items.begin(), items.end());
	//items.begin()->first = current_max;
	/*
	for (signed int i = 0; i < num; i++)
	{
		outfile << items[i].second << " " << items[i].first << endl;
	}*/

	int count = 0; //eg 11

	//vector<pair<int, string>>::reverse_iterator item_it = items.rbegin();
	vector<pair<int, string>>::reverse_iterator it_2 = items.rbegin();
	vector<pair<int, string>>::reverse_iterator it_1 = items.rbegin();
	bool start_reverse = false;
	bool plusone = false;
	bool notplus = true;
	//bool print_first = false;
	it_2++;
	//it_1++;
	//it_2++;
	int maxi = num;
	while (count < maxi)
	{
		if (plusone == true && notplus == true)
		{
			maxi++;
			notplus = false;
		}
		
		
		if (start_reverse == true)
		{
			vector<pair<int, string>>::reverse_iterator it_temp = it_1;
			it_temp--;
			if (it_1->first != it_temp->first)
			{
				start_reverse = false;
				it_1 = it_2;
				it_2++; 
			}
			else
			{
				it_1--;
				outfile << it_1->second << " " << it_1->first << endl;
			}
		}
		else
		{
			if (it_2->first == it_1->first)
			{
				while (it_2->first == it_1->first)
				{
					it_2++;
					it_1++;
					start_reverse = true;
				}
				outfile << it_1->second << " " << it_1->first << endl;
			}
			else
			{
				string tttmp = (it_1)->second;
				int tttmp_int = (it_1)->first;
				outfile << tttmp << " " << tttmp_int << endl;
				it_2++;
				it_1++;
				plusone = true;

			}
		}

		count++;
	}
}

bool comp(const pair<int, string> &a,
		  const pair<int, string> &b)
{
	//return (a.first < b.first);
	if (a.first > b.first)
	{
		if (a.second > b.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
