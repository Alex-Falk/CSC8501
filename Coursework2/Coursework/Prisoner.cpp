#include "Prisoner.h"
#include "Strategy.h"


Prisoner::Prisoner() {
	myscore = 0;
}


Prisoner::~Prisoner() {
}

int Prisoner::get_score()
{
	return myscore;
}
void Prisoner::add_score(int x)
{
	myscore += x;
}
//
//Strategy Prisoner::get_strategy()
//{
//	return *strat;
//}

void Prisoner::set_strategy(Strategy * strategy) {
	strat = strategy;
}

void Prisoner::sentence(Outcome outcome) {
	
	last_outcome = outcome;
	switch (outcome) {
	case W:
		alloutcomes_w++;
		myscore += 2;
		break;
	case X:
		alloutcomes_x++;
		myscore += 5;
		break;
	case Y:
		alloutcomes_y++;
		myscore += 0;
		break;
	case Z:
		alloutcomes_z++;
		myscore += 4;
		break;

	}
}

Decision Prisoner::get_decision(int iteration)
{
	this->iteration = iteration;
	return strat->decide_result(*this);
}

int Prisoner::get_allw()
{
	return alloutcomes_w;
}

int Prisoner::get_allx()
{
	return alloutcomes_x;
}

int Prisoner::get_ally()
{
	return alloutcomes_y;
}

int Prisoner::get_allz()
{
	return alloutcomes_z;
}

int Prisoner::get_iteration()
{
	return iteration;
}

string Prisoner::get_last_outcome()
{
	switch (last_outcome) {
	case W:
		return "W";
		break;
	case X:
		return "X";
		break;
	case Y:
		return "Y";
		break;
	case Z:
		return "Z";
		break;
	}
}
