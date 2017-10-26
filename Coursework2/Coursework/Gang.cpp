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

	// This sets up the strats to be the list of strategies excluding the "Strategies\" from the name
	strats = { fileA.substr(11), fileB.substr(11), fileC.substr(11), fileD.substr(11), fileE.substr(11) };

	// Set up 5 strategy pointers
	GangStrategy * stratA = new GangStrategy(); 
	GangStrategy * stratB = new GangStrategy();
	GangStrategy * stratC = new GangStrategy();
	GangStrategy * stratD = new GangStrategy();
	GangStrategy * stratE = new GangStrategy();

	// Read in the strategy and interpret it, then save it the the pointed to strategies
	get_strat(&stratA, fileA);
	get_strat(&stratB, fileB);
	get_strat(&stratC, fileC);
	get_strat(&stratD, fileD);
	get_strat(&stratE, fileE);

	// If all the strategies exist set the up the Gang Members wirh each strategy
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
	// Reads in strategy file
	(*strat)->read(file);

	// Tries to interpret the strategy, if it fails throw a runtime error
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

vector<Decision> Gang::get_gang_decisions(int iteration)
{
	vector<Decision> decisions(5);
	int betrays = 0;

	// loop through all gang members and return the decisions for all apart from the spy
	for (int i = 0; i < 5; ++i) 
	{
		if (i != spy_idx)
		{
			Decision decision = gang_members[i]->get_decision(iteration);
			decisions[i] = decision;
			if (decision == Decision::BETRAY) { betrays++; }
		}
	}

	// Make the spy choice - go for minority decision
	if (betrays > 2) {
		decisions[spy_idx] = Decision::SILENCE;
	}
	else if (betrays < 2) {
		decisions[spy_idx] = Decision::BETRAY;
	}
	else {
		//TODO figure out what the spy does if there is no minority option, maybe not have him go last?
		decisions[spy_idx] = Decision::BETRAY;
	}



	return decisions;
}

void Gang::sentence_gang(GangMember::Outcome outcome)
{
	// Loop through each gang member and sentence them according to the given outcome
	for (int i = 0; i < 5; ++i)
	{
		gang_members[i]->sentence(outcome);
	}
}

int Gang::get_scores()
{
	int score = gang_members[0]->get_score();
	return score;
}

void Gang::add_scores(int x)
{
	for (int i = 0; i < 5; ++i)
	{
		gang_members[i]->add_score(x);
	}
}

vector<string> Gang::return_strats()
{
	return strats;
}

void Gang::giveSpy()
{
	// Set the first member of the gang to be the leader and the spy to be selected randomly from the remaining members
	withSpy = true;
	spy_idx = rand() % 4 + 1;
	gang_members[spy_idx]->makeSpy();
	gang_members[0]->makeLeader();
}

int Gang::findSpy(method mthd)
{	// 
	int found_spy = 0;
	
	if (withSpy) {

		int guess_spy_idx, not_spy_idx;


		switch (mthd)
		{
		case CUSTOM:
			cout << "You Are the gang leader, guess which other gang member is a spy (1,2,3 or 4): \t";
			cin >> guess_spy_idx;
			cout << "\n";
			break;
		case SWAP:
		case STAY:
		case RANDOM:
			guess_spy_idx = (rand() % 4) + 1;
			break;
		}

		int other_members[3];

		switch (guess_spy_idx) {
		case 1:
			other_members[0] = 2;
			other_members[1] = 3;
			other_members[2] = 4;
			break;
		case 2:
			other_members[0] = 1;
			other_members[1] = 3;
			other_members[2] = 4;
			break;
		case 3:
			other_members[0] = 1;
			other_members[1] = 2;
			other_members[2] = 4;
			break;
		case 4:
			other_members[0] = 1;
			other_members[1] = 2;
			other_members[2] = 3;
			break;
		default:
			cout << "You did not choose a valid gang member, choosing gang member 1 \n";
			other_members[0] = 2;
			other_members[1] = 3;
			other_members[2] = 4;
			break;
		}
		
		not_spy_idx = other_members[rand() % 3];

		int new_other_members[2];
		for (int i = 0; i < 3; ++i)
		{
			int j = 0;
			if (not_spy_idx != other_members[i]) 
			{
				new_other_members[j] = other_members[i];
				j++;
			}
		}

		char switch_choice;

		switch (mthd)
		{
		case CUSTOM:
			cout << "Gang member " << not_spy_idx << " has been revealed not to be spy. Do you wish to switch your choice? (Y/N) \t";
			cin >> switch_choice;
			cout << "\n";
			break;
		case SWAP:
			switch_choice = 'Y';
			break;
		case STAY:
			switch_choice = 'N';
			break;
		case RANDOM:
			int rand_switch_choice = rand() % 2;
			if (rand_switch_choice == 0) { switch_choice = 'Y'; }
			else { switch_choice = 'N'; }
		}

		switch (switch_choice) {
		case 'Y':
		case 'y':
			switch (mthd)
			{
			case CUSTOM:
				cout << "Choose another gang member that is not " << guess_spy_idx << " or " << not_spy_idx << "\t";
				cin >> guess_spy_idx;
				cout << "\n";
				break;

			case SWAP:
				guess_spy_idx = new_other_members[rand() % 2];
			}
			if (guess_spy_idx - 1 == spy_idx) { found_spy = 2; }
			break;
		default:
			if (guess_spy_idx - 1 == spy_idx) {	found_spy = 1; }
			break;
		}
	}

	return found_spy;

}

int Gang::get_allw()
{
	return gang_members[0]->get_allw();
}

int Gang::get_allx()
{
	return gang_members[0]->get_allx();
}

int Gang::get_ally()
{
	return gang_members[0]->get_ally();
}

int Gang::get_allz()
{
	return gang_members[0]->get_allz();
}

int Gang::get_alla()
{
	return gang_members[0]->get_allA();
}
int Gang::get_allb()
{
	return gang_members[0]->get_allB();
}
int Gang::get_allc()
{
	return gang_members[0]->get_allC();
}

ostream& operator<<(ostream& ostr, Gang gang)
{
	ostr << "Strategies: ";
	for (int i = 0; i < 5; ++i)
	{
		int first_nr_idx = gang.strats[i].find_first_of("0123456789");
		ostr << gang.strats[i].substr(first_nr_idx, gang.strats[i].size() - first_nr_idx - 4) << " ";
	}
	return ostr;
}


