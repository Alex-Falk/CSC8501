#pragma once
#include <string>
#include <iostream>

using namespace std;

class GangMember;
class GangStrategy;
enum class Decision;
enum GangMember::Outcome;

class Gang
{
public:
	Gang(string fileA, string fileB, string fileC, string fileD, string fileE);
	~Gang();
	void get_strat(GangStrategy ** strat, string file);
	Decision * get_gang_decisions(int iteration);
	void sentence_gang(GangMember::Outcome outcome);
protected:
	GangMember* gang_members[5];
};

