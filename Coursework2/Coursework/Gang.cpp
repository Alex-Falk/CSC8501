#include "Gang.h"
#include "GangMember.h"
#include "GangStrategy.h"

// TODO: Assign each gang member a strategy
// TODO: Spy mechanic


Gang::Gang(string fileA, string fileB, string fileC, string fileD, string fileE)
{
	for (int i = 0; i < 5; i++)
	{
		gang_members[i] = new GangMember();
	}


	GangStrategy * stratA = new GangStrategy(); 
	GangStrategy * stratB = new GangStrategy();
	GangStrategy * stratC = new GangStrategy();
	GangStrategy * stratD = new GangStrategy();
	GangStrategy * stratE = new GangStrategy();

	get_strat(&stratA, fileA);
	get_strat(&stratB, fileB);
	get_strat(&stratC, fileC);
	get_strat(&stratD, fileD);
	get_strat(&stratE, fileE);

	if (stratA && stratB && stratC && stratD && stratE) {
		gang_members[0]->set_strategy(stratA);
		gang_members[1]->set_strategy(stratB);
		gang_members[2]->set_strategy(stratC);
		gang_members[3]->set_strategy(stratD);
		gang_members[4]->set_strategy(stratE);
	}
}

Gang::~Gang()
{
}

// TODO: Check about this, might not work
void Gang::get_strat(GangStrategy ** strat, string file)
{
	(*strat)->read(file);

	try {
		(*strat)->interpret();
	}
	catch (const runtime_error& rte) {
		cout << "Error interpreting file " << (*strat)->getFile() << " " << rte.what();
		(*strat)->terminate();

		delete (*strat);
		(*strat) = nullptr;
	}

}

Decision * Gang::get_gang_decisions(int iteration)
{
	for (int i = 0; i < 5; ++i) 
	{
		gang_members[i]->get_decision(iteration);
	}
}
