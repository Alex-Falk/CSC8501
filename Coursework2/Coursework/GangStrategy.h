#pragma once
#include "Strategy.h"

// Forward declaration
class GangMember;

// GangStrategy extending Strategy Class.
// It allows for interpretation of strategies with Gang Logic
// TODO: Store Gang strategies in different folder?
class GangStrategy :
	public Strategy
{
public:
	GangStrategy();
	~GangStrategy();
protected:
	// Overwrite the getvar function to allow to check for variables that include gang Logic
	virtual vars getvar(string var, GangMember A);
};

