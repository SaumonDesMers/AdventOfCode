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

	for (auto& line: lines)
	{
		cout << line << endl;
	}

	return 0;
}