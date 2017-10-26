#pragma once
#include "StrategyGenerator.h"

// GangStrategyGenerator extending StrategyGenerator Class.
// It allows for generating strategy files with the 6 additional tokens (which are given in the constructor)
class GangStrategyGenerator :
	public StrategyGenerator
{
public:
	GangStrategyGenerator();
	~GangStrategyGenerator();
protected:
};

