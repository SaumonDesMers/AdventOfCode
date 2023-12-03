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

	int p1_sum = 0;

	multimap<size_t, int> possibleGear;

	for (size_t i = 0; i < lines.size(); i++)
	{
		string line = lines[i];

		size_t startSearchFrom = 0;
		while (true)
		{
			size_t nbStartIndex = line.find_first_of("0123456789", startSearchFrom);
			if (nbStartIndex == string::npos)
				break;
			size_t nbEndIndex = line.find_first_not_of("0123456789", nbStartIndex);

			size_t upLeftRow = max(i, (size_t)1) - 1;
			size_t upLeftCol = max(nbStartIndex, (size_t)1) - 1;

			size_t downRightRow = min(lines.size() - 1, i + 1);
			size_t downRightCol = min(line.size() - 1, nbEndIndex);

			int nb = atoi(line.substr(nbStartIndex, nbEndIndex - nbStartIndex).c_str());
			// printf("%d: (%zu, %zu)(%zu, %zu)\n", nb, upLeftRow, upLeftCol, downRightRow, downRightCol);

			bool breakOut = false;
			for (size_t row = upLeftRow; row <= downRightRow; row++)
			{
				for (size_t col = upLeftCol; col <= downRightCol; col++)
				{
					char c = lines[row][col];
					if (string("0123456789.").find(c) == string::npos && breakOut == false)
					{
						p1_sum += nb;
						breakOut = true;
					}

					if (c == '*')
					{
						possibleGear.insert(make_pair(row * line.size() + col, nb));
						cout << "insert: " << row << "," << col << " as " << (row * line.size() + col) << endl;
					}
				}
			}

			startSearchFrom = nbEndIndex;
		}
	}

	int p2_sum = 0;

	for (size_t i = 0; i < lines.size() * lines[0].size(); i++)
	{
		if (possibleGear.count(i) == 2)
		{
			auto p = possibleGear.equal_range(i);

			size_t n1 = p.first->second;
			size_t n2 = (--p.second)->second;

			cout << "gear " << i << " = " << n1 << "*" << n2 << " = " << (n1*n2) << endl;
			// cout << n1 << " " << n2 << endl;

			p2_sum += n1 * n2;
		}
	}


	cout << "Part 1: " << p1_sum << endl;
	cout << "Part 2: " << p2_sum << endl;

	return 0;
}