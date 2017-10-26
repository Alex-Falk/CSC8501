#include "GangStrategyGenerator.h"



GangStrategyGenerator::GangStrategyGenerator() : StrategyGenerator()
{
	nrvars = { "ALLOUTCOMES_A","ALLOUTCOMES_B","ALLOUTCOMES_C","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","ITERATIONS","MYSCORE","NUMBER" };
	outcomevars = { "A","B","C","W","X", "Y", "Z" };
}


GangStrategyGenerator::~GangStrategyGenerator()
{
}
