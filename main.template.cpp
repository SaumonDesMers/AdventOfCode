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

int main()
{
	return 0;
}