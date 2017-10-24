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
	virtual vars getvar(string var, GangMember A);
};

