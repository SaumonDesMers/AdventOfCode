#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<int> vsToVi(const vector<string>& v_in);


int next(vector<int> v)
{
	if (all_of(v.begin(), v.end(), [](int n) { return n == 0; }))
	{
		return 0;
	}

	vector<int> diffs;
	for (size_t i = 0; i+1 < v.size(); i++)
	{
		diffs.push_back(v[i+1] - v[i]);
	}
	return next(diffs) + v.back(); // part 1
	return v.front() - next(diffs); // part 2
}


int main()
{
	vector<string> lines = readFile("input.txt");

	int sum = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		int predict = next(vsToVi(split(lines[i], " ")));
		sum += predict;
	}

	cout << sum << endl;

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

vector<int> vsToVi(const vector<string>& v_in)
{
	vector<int> v_out;

	for (auto& str: v_in)
	{
		v_out.push_back(stoll(str));
	}
	
	return v_out;
}