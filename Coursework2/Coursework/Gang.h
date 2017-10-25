#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GangMember.h"

using namespace std;

//class GangMember;
class GangStrategy;
enum class Decision;
enum method { CUSTOM, SWAP, STAY, RANDOM };

class Gang
{
public:
	Gang(string fileA, string fileB, string fileC, string fileD, string fileE);
	~Gang();
	void get_strat(GangStrategy ** strat, string file);
	vector<Decision> get_gang_decisions(int iteration);
	void sentence_gang(GangMember::Outcome outcome);
	int get_scores();
	void add_scores(int x);
	vector<string> return_strats();
	void giveSpy();
	int findSpy(method method);
	friend ostream& operator<<(ostream& ostr, Gang gang);
protected:
	GangMember* gang_members[5];
	vector<string> strats;
	bool withSpy = false;
	int spy_idx;
	int ldr_idx;
};

