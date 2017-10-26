#pragma once
#include "Prisoner.h"

// Extend Prisoner to allow gang logic
class GangMember :
	public Prisoner
{
public:
	enum Outcome {A,B,C,W,X,Y,Z};
	GangMember();
	~GangMember();
	int get_allA();
	int get_allB();
	int get_allC();
	bool isLeader();							// True if this is the GangLeader
	bool isSpy();								// True if this is the Spy
	void makeLeader();							// Set this to be the Leader
	void makeSpy();								// Set this to be the Spy
	virtual void sentence(Outcome outcome);		// Overwritten sentence method to include new outcomes
	virtual string get_last_outcome();			// Overwritten function that returns the last outcome
protected:
	int alloutcomes_a;
	int alloutcomes_b;
	int alloutcomes_c;
	bool is_leader = false;
	bool is_spy = false;

	Outcome last_outcome;
};

