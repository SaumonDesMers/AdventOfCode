#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> vsToVll(const vector<string>& v_in);

template<typename T>
void print(const vector<T> & v, string sep)
{
	for (size_t i = 0; i+1 < v.size(); i++)
		cout << v[i] << sep;
	if (!v.empty())
		cout << v.back() << endl;
}

void buildWall(vector<string> &platform)
{
	for (size_t i = 0; i < platform.size(); i++)
	{
		platform[i].insert(platform[i].begin(), '#');
		platform[i].insert(platform[i].end(), '#');
	}
	platform.insert(platform.begin(), string(platform[0].size(), '#'));
	platform.insert(platform.end(), string(platform[0].size(), '#'));
}

void tiltNorth(vector<string> &platform)
{
	int callCount = 0;

	// for (int i = 1; i < (int)platform.size(); i++)
	// {
	// 	for (int j = 0; j < (int)platform[i].size(); j++)
	// 	{
	// 		if (platform[i][j] == 'O')
	// 		{
	// 			int offset = 0;
	// 			while (i >= offset + 1 && platform[i - offset - 1][j] == '.')
	// 			{
	// 				callCount++;
	// 				offset++;
	// 			}
				
	// 			if (offset > 0)
	// 			{
	// 				platform[i][j] = '.';
	// 				platform[i - offset][j] = 'O';
	// 			}
	// 		}
	// 	}
	// }

	for (int i = 0; i < (int)platform.size()-1; i++)
	{
		for (int j = 0; j < (int)platform[i].size(); j++)
		{
			if (platform[i][j] == '#')
			{
				int offset = 0;
				int Ocount = 0;

				while (platform[i + offset + 1][j] != '#')
				{
					if (platform[i + offset + 1][j] == 'O')
					{
						Ocount++;
						platform[i + offset + 1][j] = '.';
					}
					offset++;
					callCount++;
				}

				for (int k = 0; k < Ocount; k++)
				{
					platform[i + k + 1][j] = 'O';
					callCount++;
				}
			}
		}
	}

	cout << "call count = " << callCount << endl;
}

void tiltSouth(vector<string> &platform)
{
	for (int i = (int)platform.size()-1; i >= 0; i--)
	{
		for (int j = 0; j < (int)platform[i].size(); j++)
		{
			if (platform[i][j] == 'O')
			{
				int offset = 0;
				while (i + offset + 1 < (int)platform.size() && platform[i + offset + 1][j] == '.')
				{
					offset++;
				}
				
				if (offset > 0)
				{
					platform[i][j] = '.';
					platform[i + offset][j] = 'O';
				}
			}
		}
	}
}

void tiltWest(vector<string> &platform)
{
	for (int i = 0; i < (int)platform.size(); i++)
	{
		for (int j = 1; j < (int)platform[i].size(); j++)
		{
			if (platform[i][j] == 'O')
			{
				int offset = 0;
				while (j >= offset + 1 && platform[i][j - offset - 1] == '.')
				{
					offset++;
				}
				
				if (offset > 0)
				{
					platform[i][j] = '.';
					platform[i][j - offset] = 'O';
				}
			}
		}
	}
}

void tiltEast(vector<string> &platform)
{
	for (int i = 0; i < (int)platform.size(); i++)
	{
		for (int j = (int)platform[i].size()-1; j >= 0; j--)
		{
			if (platform[i][j] == 'O')
			{
				int offset = 0;
				while (j + offset + 1 < (int)platform[i].size() && platform[i][j + offset + 1] == '.')
				{
					offset++;
				}
				
				if (offset > 0)
				{
					platform[i][j] = '.';
					platform[i][j + offset] = 'O';
				}
			}
		}
	}
}

void cycle(vector<string> &platform)
{
	tiltNorth(platform);
	tiltWest(platform);
	tiltSouth(platform);
	tiltEast(platform);
}


int main()
{
	vector<string> platform = readFile("input.txt");

	buildWall(platform);

	// print(platform, "\n");
	// cout << endl;

	tiltNorth(platform);
	// size_t maxCycle = 10;
	// for (size_t i = 0; i < maxCycle; i++)
	// {
	// 	cycle(platform);
	// 	// cout << (i * 100 / maxCycle) << endl;
	// }

	// print(platform, "\n");
	// cout << endl;

	uint64_t p1_sum = 0;
	for (size_t i = 0; i < platform.size(); i++)
	{
		for (size_t j = 0; j < platform[0].size(); j++)
		{
			if (platform[i][j] == 'O')
			{
				p1_sum += platform.size() - 1 - i;
			}
		}
	}

	cout << "Part1: " << p1_sum << endl;

	// for (size_t i = 0; i < platform.size(); i++)
	// {
	// 	for (size_t j = 0; j < platform[i].size(); j++)
	// 	{
	// 		if (platform[i][j] == 'O')
	// 			cout << "\033[31mO\033[0m";
	// 		else if (platform[i][j] == '#')
	// 			cout << "\033[32m#\033[0m";
	// 		else
	// 			cout << platform[i][j];
	// 	}
	// 	cout << endl;
	// }

	return 0;
}



























vector<string> readFile(string path)
{
	ifstream file(path);
	vector<string> lines;

	char line[1000] = {0};
	while (file.getline(line, 1000))
	{
		lines.push_back(line);
	}

	return lines;
}

vector<string> split(string s, string sep) {
	vector<string> tab;
	size_t i = 0;
	while ((i = s.find_first_of(sep, i)) != string::npos) {
		string subs = s.substr(0, i);
		if (!subs.empty())
			tab.push_back(subs);
		i = s.find_first_not_of(sep, i);
		s.erase(0, i);
		i = 0;
	}
	if (!s.empty())
		tab.push_back(s);
	return tab;
}

vector<uint64_t> vsToVll(const vector<string>& v_in)
{
	vector<uint64_t> v_out;

	for (auto& str: v_in)
	{
		v_out.push_back(stoll(str));
	}
	
	return v_out;
}