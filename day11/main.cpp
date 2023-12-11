#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

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


int main()
{
	vector<string> space = readFile("input.txt");

	vector<size_t> rowToExpand(space.size());
	vector<size_t> colToExpand(space[0].size());
	for (size_t i = 0; i < space.size(); i++)
		rowToExpand[i] = i;
	for (size_t i = 0; i < space[0].size(); i++)
		colToExpand[i] = i;
	
	for (size_t i = 0; i < space.size(); i++) // row
	{
		for (size_t j = 0; j < space[i].size(); j++) // col
		{
			if (space[i][j] == '#')
			{
				if (auto it = find(rowToExpand.begin(), rowToExpand.end(), i); it != rowToExpand.end())
					rowToExpand.erase(it);
				if (auto it = find(colToExpand.begin(), colToExpand.end(), j); it != colToExpand.end())
					colToExpand.erase(it);
			}
		}
	}

	const int expansionFactor = 1000000;

	vector<Pos> galaxies;

	for (size_t i = 0; i < space.size(); i++) // row
	{
		for (size_t j = 0; j < space[i].size(); j++) // col
		{
			if (space[i][j] == '#')
			{
				galaxies.push_back(Pos(j, i));
			}
		}
	}

	uint64_t p1_sum = 0;
	for (size_t i = 0; i < galaxies.size()-1; i++)
	{
		for (size_t j = i + 1; j < galaxies.size(); j++)
		{
			int minRow = min(galaxies[i].y, galaxies[j].y);
			int maxRow = max(galaxies[i].y, galaxies[j].y);
			int expansedRowCount = count_if(rowToExpand.begin(), rowToExpand.end(),
				[minRow, maxRow](int row) { return row > minRow && row < maxRow; }
			);

			int minCol = min(galaxies[i].x, galaxies[j].x);
			int maxCol = max(galaxies[i].x, galaxies[j].x);
			int expansedColCount = count_if(colToExpand.begin(), colToExpand.end(),
				[minCol, maxCol](int row) { return row > minCol && row < maxCol; }
			);

			p1_sum += abs(galaxies[i].x - galaxies[j].x) + abs(galaxies[i].y - galaxies[j].y)
					+ (expansedRowCount + expansedColCount) * (expansionFactor - 1);
		}
	}

	cout << "Part1: " << p1_sum << endl;

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