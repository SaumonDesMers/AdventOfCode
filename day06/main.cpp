#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> toNb(const vector<string>& v_in);

int main()
{
	vector<string> lines = readFile("input.txt");

	vector<uint64_t> times = toNb(split(lines[0], " "));
	vector<uint64_t> distancesToBeat = toNb(split(lines[1], " "));
	uint64_t p1_product = 1;

	for (size_t i = 0; i < times.size(); i++)
	{
		uint64_t solutionNb = 0;
		for (size_t n = 0; n < times[i]; n++)
		{
			if (n * (times[i] - n) > distancesToBeat[i])
			{
				solutionNb++;
			}
		}
		p1_product *= solutionNb;
	}

	cout << p1_product << endl;

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

vector<uint64_t> toNb(const vector<string>& v_in)
{
	vector<uint64_t> v_out;

	for (auto& str: v_in)
	{
		v_out.push_back(stoll(str));
	}
	
	return v_out;
}