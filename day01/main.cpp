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
	vector<string> lines = readFile("input.txt");

	int sum = 0;

	vector<string> nbs = {
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
	};


	for (auto& line: lines)
	{
		size_t first = line.size();
		int first_nb = 0;
		for (size_t i = 0; i < nbs.size(); i++)
		{
			size_t tmp = line.find(nbs[i]);
			if (tmp != string::npos && tmp <= first)
			{
				first = tmp;

				if (i < 9)
					first_nb = i+1;
				else
					first_nb = line[first] - '0';
			}
		}
		
		size_t last = 0;
		int last_nb = 0;
		for (size_t i = 0; i < nbs.size(); i++)
		{
			size_t tmp = line.rfind(nbs[i]);
			cout << line << "\t" << nbs[i] << "\t" << tmp << endl;
			if (tmp != string::npos && tmp >= last)
			{
				last = tmp;
				
				cout << (i < 9) << endl;
				if (i < 9)
					last_nb = i+1;
				else
					last_nb = line[last] - '0';
			}
		}
		
		int n = 10 * first_nb + last_nb;
		cout << line[first] << " " << first_nb << " | " << line[last] << " " << last_nb << " = " << n << endl;
		cout << line << " = " << n << endl;

		sum += n;
	}

	cout << sum << endl;

	return 0;
}