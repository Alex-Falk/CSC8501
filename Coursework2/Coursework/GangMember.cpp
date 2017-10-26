#include "GangMember.h"



GangMember::GangMember()
{
}


GangMember::~GangMember()
{
}

int GangMember::get_allA()
{
	return alloutcomes_a;
}

int GangMember::get_allB()
{
	return alloutcomes_b;
}

int GangMember::get_allC()
{
	return alloutcomes_c;
}

bool GangMember::isLeader()
{
	return is_leader;
}

bool GangMember::isSpy()
{
	return is_spy;
}

void GangMember::makeLeader()
{
	is_leader = true;
}

void GangMember::makeSpy()
{
	is_spy = true;
}

void GangMember::sentence(Outcome outcome)
{	// Adds the sentence in years to this Gang Member, sets the last_outcome and updates alloutcome variables
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
	case A:
		alloutcomes_a++;
		myscore += 2.5;
	case B:
		alloutcomes_b++;
		myscore += 3;
	case C:
		alloutcomes_c++;
		myscore += 2;
	}


}

string GangMember::get_last_outcome()
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
	case A:
		return "A";
		break;
	case B:
		return "B";
		break;
	case C:
		return "C";
		break;
	}
}
