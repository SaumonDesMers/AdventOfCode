#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> readFile(string path);
vector<string> split(string s, string sep);
vector<uint64_t> vsToVll(const vector<string>& v_in);


struct Hand
{
	string cards;
	uint64_t bid;
	int type;

	Hand(string s, uint64_t b): cards(s), bid(b), type(-1) {}

	string str()
	{
		return "H{" + cards + ", " + to_string(bid) + ", " + to_string(type) + "}";
	}
};

const vector<char> cardType = {
	'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'
};

int handType(string cards)
{
	multiset<int> counts;
	for (auto& type: cardType)
	{
		counts.insert(count(cards.begin(), cards.end(), type));
	}

	if (counts.count(5) == 1)
		return 7;
	if (counts.count(4) == 1)
		return 6;
	if (counts.count(3) == 1 && counts.count(2) == 1)
		return 5;
	if (counts.count(3) == 1)
		return 4;
	if (counts.count(2) == 2)
		return 3;
	if (counts.count(2) == 1)
		return 2;
	return 1;
}

int bestHandType(string cards)
{
	// cout << "best type of: " << cards << endl;
	int bestType = 0;
	for (auto& ct: cardType)
	{
		string newCards = cards;
		replace(newCards.begin(), newCards.end(), 'J', ct);
		// cout << "  " << newCards << " = " << handType(newCards) << endl;
		bestType = max(bestType, handType(newCards));
	}
	return bestType;
}

bool sortHands(const Hand & h1, const Hand & h2)
{
	if (h1.type == h2.type)
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (h1.cards[i] != h2.cards[i])
				return find(cardType.begin(), cardType.end(), h1.cards[i]) < find(cardType.begin(), cardType.end(), h2.cards[i]);
		}
	}
	
	return h1.type < h2.type;
}

int main()
{
	vector<string> lines = readFile("input.txt");

	vector<Hand> hands;

	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<string> tmp = split(lines[i], " ");
		hands.push_back(Hand(tmp[0], stoll(tmp[1])));
		hands.back().type = bestHandType(hands.back().cards);
	}

	sort(hands.begin(), hands.end(), sortHands);

	int p1_sum = 0;
	for (size_t i = 0; i < hands.size(); i++)
	{
		p1_sum += hands[i].bid * (i + 1);
		cout << hands[i].str() << endl;
		// cout << hands[i].bid << endl;
	}
	
	cout << "Part1: " << p1_sum << endl;

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

vector<uint64_t> vsToVll(const vector<string>& v_in)
{
	vector<uint64_t> v_out;

	for (auto& str: v_in)
	{
		v_out.push_back(stoll(str));
	}
	
	return v_out;
}