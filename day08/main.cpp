#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> vsToVll(const vector<string>& v_in);




int main()
{
	vector<string> lines = readFile("input.txt");

	unordered_map<string, pair<string, string> > network;

	string instructions = lines[0];

	for (size_t i = 2; i < lines.size(); i++)
	{
		auto tmp = split(lines[i], " ");
		network[tmp[0]] = make_pair(tmp[1], tmp[2]);
	}

	vector<string> currents;
	for (auto& n: network)
	{
		if (n.first[2] == 'A')
		{
			currents.push_back(n.first);
		}
	}

	// uint64_t i0 = 16697;
	// uint64_t i1 = 12169;
	// uint64_t i2 = 20093;
	// uint64_t i3 = 20659;
	// uint64_t i4 = 17263;
	// uint64_t i5 = 13301;

	uint64_t cycles[6] = {
		20659,
		12169,
		16697,
		20093,
		17263,
		13301
	};
	uint64_t cycleCount[6] = {1,1,1,1,1,1};
	uint64_t cycleTotal[6] = {0};

	while (true)
	{
		cycleTotal[0] = cycles[0] * cycleCount[0];
		cycleTotal[1] = cycles[1] * cycleCount[1];
		cycleTotal[2] = cycles[2] * cycleCount[2];
		cycleTotal[3] = cycles[3] * cycleCount[3];
		cycleTotal[4] = cycles[4] * cycleCount[4];
		cycleTotal[5] = cycles[5] * cycleCount[5];

		if (
			cycleTotal[0] == cycleTotal[1]
			&& cycleTotal[0] == cycleTotal[2]
			&& cycleTotal[0] == cycleTotal[3]
			&& cycleTotal[0] == cycleTotal[4]
			&& cycleTotal[0] == cycleTotal[5]
		)
		{
			cout << "Part2 = " << cycleTotal[0] << endl;
			break;
		}

		size_t minIndex = 0;
		for (size_t i = 0; i < 6; i++)
		{
			if (cycleTotal[i] < cycleTotal[minIndex])
			{
				minIndex = i;
			}
		}
		cycleCount[minIndex]++;

	}


	// size_t i = 0;
	// uint64_t total = 0;
	// uint64_t lastTotal[6] = {0};
	// uint64_t cycleCount[6] = {0};
	// while (true)
	// {
	// 	if (all_of(currents.begin(), currents.end() - 4, [](string& s) { return s[2] == 'Z'; }))
	// 		break;

	// 	for (size_t j = 0; j < 2; j++)
	// 	{
	// 		string& current = currents[j];

	// 		if (instructions[i] == 'R')
	// 		{
	// 			current = network[current].second;
	// 		}
	// 		else
	// 		{
	// 			current = network[current].first;
	// 		}

	// 		if (current[2] == 'Z')
	// 		{
	// 			uint64_t diff = max(total, lastTotal[j]) - min(total, lastTotal[j]);
	// 			lastTotal[j] = total;
	// 			cout << "diff " << j << " = " << diff << endl;
	// 			cout << "cycle count " << j << " = " << (++cycleCount[j]) << endl;
	// 		}
	// 	}

	// 	i = (i + 1) % instructions.size();
	// 	total++;
	// }

	// for (size_t j = 0; j < 6; j++)
	// {
	// 	cout << currents[j] << endl;
	// }

	// cout << "Part1: " << total << endl;

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