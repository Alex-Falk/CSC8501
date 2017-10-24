#pragma once
#include <string>


using namespace std;

class Strategy;
enum class Decision;

class Prisoner
{
public:
	virtual enum Outcome { W, X, Y, Z };											// W: both silence , X: silence + other betrayed , Y: betrayed + other silent , Z: both betrayed

	Prisoner();
	virtual ~Prisoner();
	virtual int get_score();
	//Strategy get_strategy();
	virtual void set_strategy(Strategy * strategy);
	virtual void sentence(Outcome outcome);											// Add years to myscore, set last_outcome and add to counters
	virtual Decision get_decision(int iteration);									// Use the strategy logic to choose betray or silence
	virtual int get_allw();
	virtual int get_allx();
	virtual int get_ally();
	virtual int get_allz();
	virtual int get_iteration();
	virtual string get_last_outcome();


protected:
	Strategy * strat;
	int myscore;
	int iteration;
	int alloutcomes_w;
	int alloutcomes_x;
	int alloutcomes_y;
	int alloutcomes_z;
	Outcome last_outcome;
};

