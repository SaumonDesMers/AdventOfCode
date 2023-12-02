#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string path)
{
	ifstream file(path);
	vector<string> lines;

	char line[256] = {0};
	while (file.getline(line, 256))
	{
		lines.push_back(line);
	}

	return lines;
}

vector<string> split(string s, string sep) {
	vector<string> tab;
	size_t i = 0;
	while ((i = s.find_first_of(sep, i+1)) != string::npos) {
		tab.push_back(s.substr(0, i));
		s.erase(0, i+1);
		i = 0;
	}
	tab.push_back(s);
	return tab;
}

int main()
{
	vector<string> lines = readFile("input.txt");

	int idSum = 0;
	int powerSum = 0;

	map<string, int> maxColor = {
		{"red", 12},
		{"green", 13},
		{"blue", 14}
	};
	
	for (auto& line: lines)
	{
		map<string, int> minColor = {
			{"red", 0},
			{"green", 0},
			{"blue", 0}
		};

		vector<string> tmp = split(line, ":");

		int id = atoi(tmp[0].c_str());
		bool isPossible = true;

		vector<string> sets = split(tmp[1], ";");

		for (auto& set: sets)
		{
			vector<string> colors = split(set, ",");

			for (auto& color: colors)
			{
				vector<string> pair = split(color, " ");
				int nb = atoi(pair[0].c_str());

				if (nb > maxColor[pair[1]]) // part 1
				{
					isPossible = false;
				}

				if (nb > minColor[pair[1]]) // part 2
				{
					minColor[pair[1]] = nb;
				}
			}
		}

		if (isPossible) // part 1
		{
			idSum += id;
		}

		powerSum += minColor["red"] * minColor["green"] * minColor["blue"]; // part 2
	}

	cout << "part 1: " << idSum << endl;
	cout << "part 2: " << powerSum << endl;

	return 0;
}