#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

#define None 0b0
#define North 0b01000
#define South 0b00100
#define East 0b00010
#define West 0b00001

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> vsToVll(const vector<string>& v_in);

struct Pos
{
	int x, y;
	Pos(int a=0, int b=0): x(a), y(b) {}
	bool operator ==(const Pos &other) const { return x == other.x && y == other.y; }
	bool operator !=(const Pos &other) const { return !(*this == other); }
};

map<char, int> pipeDir = {
	make_pair('|', North | South),
	make_pair('-', East | West),
	make_pair('L', North | East),
	make_pair('J', North | West),
	make_pair('7', South | West),
	make_pair('F', South | East),
	make_pair('S', North | South | West | East),
	make_pair('+', North | South | West | East)
};

char at(const vector<string> & lines, int x, int y)
{
	if (x < 0 || x >= int(lines[0].size()) || y < 0 || y >= int(lines.size()))
		return -1;
	return lines[y][x];
}

void floodFillIGuess(vector<string> &path, int x, int y)
{
	path[y][x] = '*';
	if (at(path, x+1, y) == ' ')
		floodFillIGuess(path, x+1, y);
	if (at(path, x-1, y) == ' ')
		floodFillIGuess(path, x-1, y);
	if (at(path, x, y+1) == ' ')
		floodFillIGuess(path, x, y+1);
	if (at(path, x, y-1) == ' ')
		floodFillIGuess(path, x, y-1);
}

int main()
{
	vector<string> lines = readFile("input.txt");


	vector<string> extendedPipes;
	for (size_t i = 0; i < lines.size(); i++)
	{
		extendedPipes.push_back("");
		for (size_t j = 0; j < lines[0].size(); j++)
		{
			extendedPipes[i*2].push_back(lines[i][j]);
			extendedPipes[i*2].push_back('+');
		}
		extendedPipes[i*2].pop_back();

		extendedPipes.push_back("");
		for (size_t j = 0; j < lines[0].size(); j++)
		{
			extendedPipes[i*2+1] += "+ ";
		}
	}
	extendedPipes.pop_back();

	Pos start;
	for (size_t i = 0; i < extendedPipes.size(); i++)
	{
		for (size_t j = 0; j < extendedPipes[0].size(); j++)
		{
			if (extendedPipes[i][j] == 'S')
			{
				start.x = j;
				start.y = i;
			}
		}
	}


	vector<string> path(extendedPipes.size());
	for (size_t i = 0; i < path.size(); i++)
		path[i] = string(extendedPipes[0].size(), ' ');

	Pos current = start;
	int comeFrom = None;
	int stepCount = 0;
	do
	{
		char currPipe = extendedPipes[current.y][current.x];

		stepCount++;

		path[current.y][current.x] = '.';

		Pos lastPos = current;

		if (comeFrom != East && pipeDir[currPipe] & East) // East
		{
			char nextPipe = at(extendedPipes, current.x + 1, current.y);
			if (pipeDir[nextPipe] & West)
			{
				current.x += 1;
				comeFrom = West;
				continue;
			}
		}
		if (comeFrom != West && pipeDir[currPipe] & West) // West
		{
			char nextPipe = at(extendedPipes, current.x - 1, current.y);
			if (pipeDir[nextPipe] & East)
			{
				current.x -= 1;
				comeFrom = East;
				continue;
			}
		}
		if (comeFrom != North && pipeDir[currPipe] & North) // North
		{
			char nextPipe = at(extendedPipes, current.x, current.y - 1);
			if (pipeDir[nextPipe] & South)
			{
				current.y -= 1;
				comeFrom = South;
				continue;
			}
		}
		if (comeFrom != South && pipeDir[currPipe] & South) // South
		{
			char nextPipe = at(extendedPipes, current.x, current.y + 1);
			if (pipeDir[nextPipe] & North)
			{
				current.y += 1;
				comeFrom = North;
				continue;
			}
		}

		if (lastPos == current)
		{
			cout << "Error: did not move at " << current.x << " " << current.y << endl;
			break;
		}

	} while (current != start);

	floodFillIGuess(path, 0, 0);
	floodFillIGuess(path, 140, 0);

	int part2 = 0;
	for (size_t i = 0; i < extendedPipes.size(); i++)
	{
		for (size_t j = 0; j < extendedPipes[0].size(); j++)
		{
			if (path[i][j] == '.')
				cout << "\033[31m" << extendedPipes[i][j] << "\033[0m";
			else if (path[i][j] == '*')
				cout << "\033[32m" << extendedPipes[i][j] << "\033[0m";
			else if (extendedPipes[i][j] != '+' && extendedPipes[i][j] != ' ')
			{
				cout << "\033[34m" << extendedPipes[i][j] << "\033[0m";
				part2++;
			}
			else
				cout << extendedPipes[i][j];
		}
		cout << endl;
	}

	// replace 'extendedPipes' by 'lines' in the code to have the right part1
	// cout << "Part1: " << (stepCount / 2) << endl;
	cout << "Part2: " << part2 << endl;

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
		tab.push_back(s.substr(0, i));
		i = s.find_first_not_of(sep, i);
		s.erase(0, i);
		i = 0;
	}
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