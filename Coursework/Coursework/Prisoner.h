#pragma once
#include <string>


enum Outcome { W, X, Y, Z };														// W: both silence , X: silence + other betrayed , Y: betrayed + other silent , Z: both betrayed

using namespace std;

class Strategy;
enum class Decision;

class Prisoner
{
public:
	Prisoner();
	~Prisoner();
	int get_score();
	//Strategy get_strategy();
	void set_strategy(Strategy * strategy);
	void sentence(Outcome outcome);											// Add years to myscore, set last_outcome and add to counters
	Decision get_decision(int iteration);									// Use the strategy logic to choose betray or silence
	int get_allw();
	int get_allx();
	int get_ally();
	int get_allz();
	int get_iteration();
	string get_last_outcome();
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

