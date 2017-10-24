#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GangMember.h"

using namespace std;

//class GangMember;
class GangStrategy;
enum class Decision;

class Gang
{
public:
	Gang(string fileA, string fileB, string fileC, string fileD, string fileE);
	~Gang();
	void get_strat(GangStrategy ** strat, string file);
	vector<Decision> get_gang_decisions(int iteration);
	void sentence_gang(GangMember::Outcome outcome);
	int get_scores();
	vector<string> return_strats();
protected:
	GangMember* gang_members[5];
	vector<string> strats;
};

