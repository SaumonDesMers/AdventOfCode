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

vector<string> getCols(vector<string> rows)
{
	vector<string> cols;

	cols.insert(cols.end(), rows[0].size(), string(rows.size(), ' '));

	for (size_t i = 0; i < rows.size(); i++)
	{
		for (size_t j = 0; j < rows[0].size(); j++)
		{
			cols[j][i] = rows[i][j];
		}
	}
	return cols;
}

int mismatchCount(string s1, string s2)
{
	int count = 0;
	for (size_t i = 0; i < s1.size(); i++)
	{
		if (s1[i] != s2[i])
			count++;
	}
	return count;
}

int findSymetry(vector<string>& lines)
{
	int maxMismatchCount = 1;
	for (int i = 0; i+1 < int(lines.size()); i++)
	{
		int negOffset = 0;
		int posOffset = 1;
		int mismatch = 0;

		// cout << "\ntesting: " << lines[i - negOffset] << endl;
		// cout << "         " << lines[i + posOffset] << endl;
		while (mismatch <= maxMismatchCount)
		{
			mismatch += mismatchCount(lines[i - negOffset], lines[i + posOffset]);
			// cout << "mismatch count = " << mismatch << endl;
			negOffset++;
			posOffset++;

			if (i - negOffset < 0 || i + posOffset >= int(lines.size()))
			{
				if (mismatch == maxMismatchCount)
					return i + 1;
				else
					break;
			}
		}
	}
	return 0;
}


int main()
{
	vector<string> fileLines = readFile("input.txt");
	fileLines.push_back("");

	uint64_t p1_sum = 0;

	vector<string> rows;
	vector<string> cols;
	for (size_t i = 0; i < fileLines.size(); i++)
	{
		if (!fileLines[i].empty())
		{
			rows.push_back(fileLines[i]);
		}
		else
		{
			cols = getCols(rows);

			// cout << "\nrow (" << rows.size() << "x" << rows[0].size() << ")" << endl;
			// print(rows, "\n");
			// cout << findSymetry(rows) << endl;
			p1_sum += 100 * findSymetry(rows);

			// cout << "\ncol (" << cols.size() << "x" << cols[0].size() << ")" << endl;
			// print(cols, "\n");
			// cout << findSymetry(cols) << endl;
			p1_sum += findSymetry(cols);


			cols.clear();
			rows.clear();
		}
	}

	cout << "Part1: " << p1_sum << endl;

	return 0;
}



/*

#.##..##.
..#.##.#.
##......#
##......#
..#.##.#.
..##..##.
#.#.##.#.

*/


















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