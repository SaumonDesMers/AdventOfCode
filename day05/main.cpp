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
		// cout << "str: [" << str << "]" << endl;
		v_out.push_back(stoll(str));
	}
	
	return v_out;
}

void applyRange(vector<string>& lines, size_t &i, vector<uint64_t>& input)
{
	vector<vector<uint64_t> > ranges;
	for (; i < lines.size(); i++)
	{
		if (lines[i].empty()) break;

		// cout << "line: [" << lines[i] << "]" << endl;
		ranges.push_back(vsToVll(split(lines[i], " ")));
	}
	i++;

	vector<uint64_t> output;
	for (auto& range: ranges)
	{
		uint64_t destRange = range[0];
		uint64_t srcRange = range[1];
		uint64_t size = range[2];

		vector<size_t> to_erase;
		for (auto& in: input)
		{
			if (in >= srcRange && in <= srcRange + size)
			{
				// cout << "in " << in << " found in range " << destRange << " " << srcRange << " " << size;
				// cout << " and became " << (in + destRange - srcRange) << endl;
				output.push_back(in + destRange - srcRange);
				to_erase.push_back(in);
			}
		}
		for (auto& n: to_erase)
			input.erase(find(input.begin(), input.end(), n));
	}
	input.insert(input.end(), output.begin(), output.end());

	// cout << "input is now: ";
	// for (auto& in: input)
		// cout << in << " ";
	// cout << endl;
	// cout << endl;

}

void part_one()
{
	vector<string> lines = readFile("input.txt");

	vector<uint64_t> input = vsToVll(split(lines[0], " "));

	size_t i = 2;

	// cout << "input is now: ";
	// for (auto& in: input)
		// cout << in << " ";
	// cout << endl;
	// cout << endl;

	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);
	applyRange(lines, i, input);

	sort(input.begin(), input.end());

	// cout << "input is now: ";
	// for (auto& in: input)
		// cout << in << " ";
	// cout << endl;
}

struct Range
{
	uint64_t begin;
	uint64_t end;

	Range(uint64_t b, uint64_t e): begin(b), end(e) {}

	Range(string b, string s): begin(stoll(b)), end(begin + stoll(s) - 1) {}

	string str()
	{
		string str = "R{" + to_string(begin) + ", " + to_string(end) + "}";
		return str;
	}
};

struct RangeCopy
{
	Range src;
	Range dst;

	RangeCopy(Range s, Range d): src(s), dst(d) {}

	RangeCopy(string str): src(0, 0), dst(0, 0)
	{
		vector<uint64_t> s = vsToVll(split(str, " "));
		src.begin = s[1];
		src.end = s[1] + s[2] - 1;
		dst.begin = s[0];
		dst.end = s[0] + s[2] - 1;
	}

	string str()
	{
		string str = "RC{" + src.str() + ", " + dst.str() + "}";
		return str;
	}
};

vector<RangeCopy> getRangeCopy(vector<string>& lines, size_t &i)
{
	vector<RangeCopy> rcs;
	for (; i < lines.size(); i++)
	{
		if (lines[i].empty()) break;

		// cout << "line: [" << lines[i] << "]" << endl;
		rcs.push_back(RangeCopy(lines[i]));
	}
	i++;

	return rcs;
}

vector<Range> findOverlaps(RangeCopy &rc, vector<Range>& input)
{
	// cout << "search overlap with: " << rc.str() << endl;
	// find overlaping range
	vector<Range> overlaps;
	for (auto& r: input)
	{
		// cout << "  for " << r.str() << endl;
		bool beginIn = (r.begin >= rc.src.begin && r.begin <= rc.src.end);
		bool endIn = (r.end >= rc.src.begin && r.end <= rc.src.end);

		// cout << boolalpha << "    beginIn = " << beginIn << endl;
		// cout << boolalpha << "    endIn = " << endIn << endl;

		if (beginIn && !endIn)
		{
			Range overlap(r.begin, rc.src.end);
			overlaps.push_back(overlap);
			r.begin = rc.src.end + 1;
		}
		else if (!beginIn && endIn)
		{
			Range overlap(rc.src.begin, r.end);
			overlaps.push_back(overlap);
			r.end = rc.src.begin - 1;
		}
		else if (beginIn && endIn)
		{
			Range overlap = r;
			overlaps.push_back(overlap);
			r.begin = 0;
			r.end = 0;
		}
		else if (r.begin <= rc.src.begin && r.end >= rc.src.end)
		{
			Range overlap = rc.src;
			overlaps.push_back(overlap);

			Range splitedRange(rc.src.end + 1, r.end);
			r.end = rc.src.begin - 1;

			input.push_back(splitedRange);
		}
	}
	// cout << "  find overlaps:" << endl;
	// for (auto& o: overlaps)
		// cout << "    " << o.str() << endl;
	
	return overlaps;
}

vector<Range> transformRanges(vector<Range> overlaps, RangeCopy rc)
{
	// cout << "  new range are:" << endl;
	for (auto& r: overlaps)
	{
		r.begin += rc.dst.begin - rc.src.begin;
		r.end += rc.dst.begin - rc.src.begin;
		// cout << "    " << r.str() << endl;
	}
	return overlaps;
}

void applyRangeCopy(vector<Range>& input, vector<RangeCopy> rangesCopy)
{
	// cout << "input are:" << endl;
	// for (auto& in: input)
		// cout << "  " << in.str() << endl;
	
	vector<Range> output;

	for (auto& rc: rangesCopy)
	{
		vector<Range> overlaps = findOverlaps(rc, input);

		vector<Range> transformedOverlaps = transformRanges(overlaps, rc);

		output.insert(output.end(), transformedOverlaps.begin(), transformedOverlaps.end());
	}

	// cout << "add non overlaping range:" << endl;
	for (auto& r: input)
	{
		if (r.begin == 0 && r.end == 0) continue;

		// cout << "  " << r.str() << endl;
		output.push_back(r);
	}

	sort(output.begin(), output.end(), [](const Range &r1, const Range &r2) { return r1.begin < r2.begin; });

	// cout << "full output is:" << endl;
	// for (auto& r: output)
		// cout << "  " << r.str() << endl;
	
	for (size_t i = 0; i+1 < output.size(); i++)
	{
		if (output[i].end+1 >= output[i+1].begin)
		{
			output[i+1].begin = output[i].begin;
			
			if (output[i].end > output[i+1].end)
			{
				output[i+1].end = output[i].end;
			}

			output[i].begin = 0;
			output[i].end = 0;
		}
	}

	auto newEnd = remove_if(output.begin(), output.end(), [](const Range& r) { return r.begin == 0 && r.end == 0; });
	output.erase(newEnd, output.end());

	// cout << "merged output is:" << endl;
	// for (auto& r: output)
		// cout << "  " << r.str() << endl;
	// cout << endl;

	input = output;
}

void part_two()
{
	vector<string> lines = readFile("input.txt");

	vector<string> inputLine = split(lines[0], " ");

	vector<Range> input;
	while (!inputLine.empty())
	{
		input.push_back(Range(inputLine[inputLine.size() - 2], inputLine[inputLine.size() - 1]));
		inputLine.pop_back();
		inputLine.pop_back();
	}

	// cout << "input:" << endl;
	// for (auto& r: input)
		// cout << r.str() << endl;

	size_t i = 2;
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));
	applyRangeCopy(input, getRangeCopy(lines, i));

	cout << input[0].begin << endl;

}

int main()
{

	// part_one();
	part_two();

	return 0;
}