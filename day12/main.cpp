#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> vsToVll(const vector<string>& v_in);

struct SpringRow
{
	string springs;
	vector<uint64_t> groups;
	int validStateCount = 0;
	int damagedSpringsCount = 0;
	int potentialDamagedSpringsCount = 0;

	SpringRow(string _s, vector<uint64_t> _g): springs(_s), groups(_g)
	{
		for (auto& g: groups)
		{
			damagedSpringsCount += g;
		}
		potentialDamagedSpringsCount = count_if(springs.begin(), springs.end(), [](char c) { return c == '#' || c == '?'; });
	}

	string str() const
	{
		string str = "(" + springs;
		for (auto& g: groups)
			str += " " + to_string(g);
		return str + ")";
	}

	void unfold()
	{
		string newSprings = "";
		vector<uint64_t> newGroups;

		for (size_t i = 0; i < 5; i++)
		{
			newSprings += springs;
			newGroups.insert(newGroups.end(), groups.begin(), groups.end());
		}

		springs = newSprings;
		groups = newGroups;

		damagedSpringsCount *= 5;
		potentialDamagedSpringsCount *= 5;
	}

	bool isValid()
	{
		if (springs.find('?') != string::npos)
		{
			// cout << str() << " invalid: '?' found" << endl;
			return false;
		}

		vector<string> splittedSprings = split(springs, ".");

		if (groups.size() != splittedSprings.size())
		{
			// cout << str() << " invalid: wrong number of groups: " << splittedSprings.size() << " expected " << groups.size() << endl;
			return false;
		}

		for (size_t i = 0; i < groups.size(); i++)
		{
			if (groups[i] != splittedSprings[i].size())
			{
				// cout << str() << " invalid: wrong groups " << i << " size: " << splittedSprings[i].size() << " expected " << groups[i] << endl;
				return false;
			}
		}

		// cout << str() << " valid" << endl;
		return true;
	}

	bool isPartialyValid()
	{
		bool inGroup = false;
		int groupIndex = -1;
		int currentGroupSize = 0;

		if (potentialDamagedSpringsCount < damagedSpringsCount)
		{
			// cout << str() << " invalid" << endl;
			return false;
		}

		for (size_t i = 0; i < springs.size(); i++)
		{
			if (springs[i] == '.')
			{
				if (inGroup)
				{
					if (currentGroupSize != groups[groupIndex])
					{
						// cout << str() << " invalid" << endl;
						return false;
					}
					inGroup = false;
				}
			}
			else if (springs[i] == '#')
			{
				if (!inGroup)
				{
					inGroup = true;
					groupIndex++;
					currentGroupSize = 0;
				}
				currentGroupSize++;
			}
			else
			{
				// cout << str() << " partialy valid" << endl;
				return true;
			}

		}

		if (inGroup)
		{
			if (currentGroupSize != groups[groupIndex])
			{
				// cout << str() << " invalid" << endl;
				return false;
			}
			inGroup = false;
		}

		// cout << str() << " partialy valid" << endl;
		return true;
	}
};

ostream& operator<<(ostream& os, const SpringRow& sr)
{
	os << sr.str();
	return os;
}

uint64_t callCount = 0;
void searchAll(SpringRow& sr, size_t i = 0)
{
	callCount++;
	if (i >= sr.springs.size())
	{
		if (sr.isValid())
		{
			sr.validStateCount++;
		}
		return;
	}
	else if (!sr.isPartialyValid())
	{
		return;
	}

	if (sr.springs[i] != '?')
	{
		return searchAll(sr, i + 1);
	}

	sr.springs[i] = '.';
	sr.potentialDamagedSpringsCount--;
	searchAll(sr, i + 1);

	sr.springs[i] = '#';
	sr.potentialDamagedSpringsCount++;
	searchAll(sr, i + 1);

	sr.springs[i] = '?';
}


int main()
{
	vector<string> lines = readFile("input.txt");

	vector<SpringRow> springRows;
	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<string> tmp = split(lines[i], " ");
		SpringRow springRow(tmp[0], vsToVll(split(tmp[1], ",")));

		// cout << springRow << endl;
		springRow.unfold();
		// cout << springRow << endl;

		springRows.push_back(springRow);
	}

	// cout << springRows[4] << endl;
	// callCount = 0;
	// searchAll(springRows[4]);
	// cout << "call count = " << callCount << endl;
	// cout << springRows[4].validStateCount << endl;

	uint64_t p1_sum = 0;
	for (size_t i = 0; i < 2; i++)
	{
		searchAll(springRows[i]);
		// cout << springRows[i] << " -> " << springRows[i].validStateCount << endl;
		p1_sum += springRows[i].validStateCount;
		cout << i << endl;
	}

	cout << "Part1: " << p1_sum << endl;
	cout << "Call count: " << callCount << endl;

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