#ifndef _SEARCHER_H
#define _SEARCHER_H
#include <vector>
#include <fstream>
#include <string>
#include <functional>
#include <chrono>
#include <random>

class Searcher
{
private:
	std::vector<std::string> mainwordlist;
	std::vector<std::string> wordlist;
	std::mt19937 rng;
	int sz;

public:
	Searcher();
	struct performanceStat {
		int result;
		int comparisons;
		long long timeInUs;
	};

	std::string getRandomWord();
	std::string makeUpRandomWord();

	void loadData(const char* filename);
	void setDataSize(int words);


	performanceStat testPerformance(const std::string& w);
	int binarySearch(const std::string& w);

	int binarySearch(const std::string& w, std::function<int(const std::string&, const std::string&)> cmp);
};

#endif // !_SEARCHER_H