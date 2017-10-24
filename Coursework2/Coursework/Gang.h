#pragma once
#include <string>
#include <iostream>

using namespace std;

class GangMember;
class GangStrategy;
enum class Decision;

class Gang
{
public:
	Gang(string fileA, string fileB, string fileC, string fileD, string fileE);
	~Gang();
	void get_strat(GangStrategy ** strat, string file);
	void pick_specials();
	Decision * get_gang_decisions(int iteration);
	void get_gang_outcome();
protected:
	GangMember* gang_members[5];
};

