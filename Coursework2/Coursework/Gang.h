#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GangMember.h"

using namespace std;

//class GangMember;
class GangStrategy;
enum class Decision;
enum method { CUSTOM, SWAP, STAY, RANDOM };										// Method of spy dection

class Gang
{
public:
	Gang(string fileA, string fileB, string fileC, string fileD, string fileE);	// Initialise a strategy with 5 given filenames
	~Gang();
	void get_strat(GangStrategy ** strat, string file);							//
	vector<Decision> get_gang_decisions(int iteration);							// Finds out what each member of the gang decides and returns all the decisions
	void sentence_gang(GangMember::Outcome outcome);							// Given an outcome, sentences the members by the required number of years
	int get_scores();															// Return sentence in years per prisoner
	void add_scores(int x);														// Add x amount of years to the sentence
	vector<string> return_strats();												// Returns a list of the strategies used by the gang members
	void giveSpy();																// Pick a Member of the gang to be a spy
	int findSpy(method method);													// Runs logic to choose a spy to see if he is found/detected
	friend ostream& operator<<(ostream& ostr, Gang gang);						// Overload operator << so gang can be printed out
	int get_allw();
	int get_allx();
	int get_ally();
	int get_allz();
	int get_alla();
	int get_allb();
	int get_allc();
protected:
	GangMember* gang_members[5];
	vector<string> strats;
	bool withSpy = false;
	int spy_idx;
	int ldr_idx;
};

