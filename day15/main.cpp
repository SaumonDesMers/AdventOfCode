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

int HASH(const string &s)
{
	int hash = 0;
	for (auto& c: s)
	{
		hash += c;
		hash *= 17;
		hash %= 256;
	}
	return hash;
}

string getLabel(const string &instruction)
{
	return instruction.substr(0, instruction.find_first_of("-="));
}

struct Lense
{
	string label;
	int lenght;

	Lense(string label, int lenght): label(label), lenght(lenght) {}
};

void printHashmap(vector<Lense> hashmap[256])
{
	for (size_t i = 0; i < 256; i++)
	{
		if (!hashmap[i].empty())
		{
			cout << "Box " << i << ": ";
			for (auto& l: hashmap[i])
			{
				cout << " [" << l.label << " " << l.lenght << "]";
			}
			cout << endl;
		}
	}
}

int main()
{
	vector<string> lines = readFile("input.txt");

	vector<Lense> hashmap[256];

	uint64_t p1_sum = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<string> instructions = split(lines[i], ",");
		for (size_t j = 0; j < instructions.size(); j++)
		{
			p1_sum += HASH(instructions[j]);

			string label = getLabel(instructions[j]);
			int hashmapIndex = HASH(label);

			auto it = find_if(hashmap[hashmapIndex].begin(), hashmap[hashmapIndex].end(), [&label](const Lense &l) { return l.label == label; });

			if (instructions[j].find('=') != string::npos)
			{
				int lenght = atoi(instructions[j].substr(instructions[j].find('=') + 1).c_str());

				
				if (it != hashmap[hashmapIndex].end())
				{
					it->label = label;
					it->lenght = lenght;
				}
				else
				{
					hashmap[hashmapIndex].push_back(Lense(label, lenght));
				}
			}
			else
			{
				if (it != hashmap[hashmapIndex].end())
				{
					hashmap[hashmapIndex].erase(it);
				}
			}

			// printHashmap(hashmap);
			// cout << endl;
		}
	}

	uint64_t p2_sum = 0;
	for (size_t i = 0; i < 256; i++)
	{
		for (size_t j = 0; j < hashmap[i].size(); j++)
		{
			p2_sum += (i + 1) * (j + 1) * hashmap[i][j].lenght;
		}
	}

	cout << "Part1: " << p1_sum << endl;
	cout << "Part2: " << p2_sum << endl;

	return 0;
}



























vector<string> readFile(string path)
{
	ifstream file(path);
	vector<string> lines;

	char line[100000] = {0};
	while (file.getline(line, 100000))
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