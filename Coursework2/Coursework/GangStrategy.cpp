#include "GangStrategy.h"
#include "GangMember.h"


GangStrategy::GangStrategy()
{
	tokens = { "IF","BETRAY","SILENCE","RANDOM","+","-",">","<","=","GOTO","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","ALLOUTCOMES_A","ALLOUTCOMES_B","ALLOUTCOMES_C"
		,"W","X","Y","Z","A","B","C","LASTOUTCOME","ITERATIONS","MYSCORE"," ","0","1","2","3","4","5","6","7","8","9" };
}


GangStrategy::~GangStrategy()
{
}

vars GangStrategy::getvar(string var, GangMember A)
{	// Takes the variable read in and interprets it to the actual value needed. Recursively splits and runs the variable if it represents multiple variables separated by a + or -
	vars v;
	if (var == "LASTOUTCOME") { v.stringvar = A.get_last_outcome(); }
	else if (var == "W" || var == "X" || var == "Y" || var == "Z" || var == "A" || var == "B" || var == "C") { v.stringvar = var; }
	else if (var == "ALLOUTCOMES_W") { v.intvar = A.get_allw(); }
	else if (var == "ALLOUTCOMES_X") { v.intvar = A.get_allx(); }
	else if (var == "ALLOUTCOMES_Y") { v.intvar = A.get_ally(); }
	else if (var == "ALLOUTCOMES_Z") { v.intvar = A.get_allz(); }
	else if (var == "ALLOUTCOMES_A") { v.intvar = A.get_allA(); }
	else if (var == "ALLOUTCOMES_B") { v.intvar = A.get_allB(); }
	else if (var == "ALLOUTCOMES_C") { v.intvar = A.get_allC(); }
	else if (var == "ITERATIONS") { v.intvar = A.get_iteration(); }
	else if (var == "MYSCORE") { v.intvar = A.get_score(); }
	else if (var.find_first_of("+") != string::npos) { v.intvar = getvar(var.substr(0, var.find_first_of("+")), A).intvar + getvar(var.substr(var.find_first_of("+") + 1), A).intvar; }
	else if (var.find_first_of("-") != string::npos) { v.intvar = getvar(var.substr(0, var.find_first_of("-")), A).intvar - getvar(var.substr(var.find_first_of("-") + 1), A).intvar; }
	else if (var.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) { v.intvar = stoi(var); }
	return v;

}

