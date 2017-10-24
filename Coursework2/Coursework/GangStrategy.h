#pragma once
#include "Strategy.h"

class GangMember;

class GangStrategy :
	public Strategy
{
public:
	GangStrategy();
	~GangStrategy();
protected:

	vector<string> tokens = { "IF","BETRAY","SILENCE","RANDOM","+","-",">","<","=","GOTO","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","ALLOUTCOMES_A","ALLOUTCOMES_B","ALLOUTCOMES_C"
								,"W","X","Y","Z","A","B","C","LASTOUTCOME","ITERATIONS","MYSCORE"," ","0","1","2","3","4","5","6","7","8","9" };

	virtual vars getvar(string var, GangMember A);
};

