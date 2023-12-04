#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include <cmath>

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
	vector<string> v_lines = readFile("input.txt");

	int p1_sum = 0;

	map<int, string> lines;

	multimap <int, int> matchingCount;

	for (auto& line: v_lines)
	{
		auto p = split(line.c_str(), ":");
		lines.insert(make_pair(atoi(p[0].c_str()), p[1]));
	}

	for (auto& p: lines)
	{
		int id = p.first;

		auto v2 = split(p.second, "|");
		auto winningNb_str = split(v2[0].c_str(), " ");
		auto nbs_str = split(v2[1].c_str(), " ");

		vector<int> winningNb;
		for (auto& n: winningNb_str)
		{
			int nb = atoi(n.c_str());
			if (nb != 0)
				winningNb.push_back(nb);
		}
		vector<int> nbs;
		for (auto& n: nbs_str)
		{
			int nb = atoi(n.c_str());
			if (nb != 0)
				nbs.push_back(nb);
		}

		int cardPoint = 0;

		vector<int> communNb;
		for (auto& n: winningNb)
		{
			if (find(nbs.begin(), nbs.end(), n) != nbs.end())
			{
				communNb.push_back(n);

				if (cardPoint == 0)
					cardPoint = 1;
				else
					cardPoint *= 2;
			}
		}

		matchingCount.insert(make_pair(id, communNb.size()));

		p1_sum += cardPoint;

		// std::cout << line << endl;

		std::cout << std::setw(1) << id << ":";
		for (auto& nb: winningNb)
			std::cout << std::setw(3) << nb;
		std::cout << " |";
		for (auto& nb: nbs)
			std::cout << std::setw(3) << nb;
		std::cout << endl;

		std::cout << id << ":";
		for (auto& nb: communNb)
		{
			std::cout << " " << nb;
		}
		std::cout << "\n" << endl;

	}

	for (size_t id = 0; id < matchingCount.size(); id++)
	{
		int nbOfCard = matchingCount.count(id);
		int nbOfMatch = matchingCount.find(id)->second;

		for (int idOffset = 1; idOffset < nbOfMatch + 1; idOffset++)
		{
			for (int n = 0; n < nbOfCard; n++)
			{
				auto it = matchingCount.find(id + idOffset);
				matchingCount.insert(
					make_pair(
						it->first,
						it->second
					)
				);
			}
		}

	}

	std::cout << "Part 1: " << p1_sum << endl;
	std::cout << "Part 2: " << matchingCount.size() << endl;

	return 0;
}