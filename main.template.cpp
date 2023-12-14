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


int main()
{
	vector<string> lines = readFile("input.txt");

	for (size_t i = 0; i < lines.size(); i++)
	{
		string &line = lines[i];
		cout << line << endl;
	}

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