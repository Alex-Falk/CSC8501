#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Strategy.h"
#include "Prisoner.h"

using namespace std;


Strategy::Strategy() {

}


Strategy::~Strategy() {
	terminate_tree(&root);
}


Strategy::Strategy(const Strategy &strat) 
{
	root = nullptr;
	*root = *strat.root;
}


void Strategy::terminate_tree(node ** tree)
{
	if (*tree) {
		if ((*tree)->left)
			terminate_tree(&((*tree)->left));
		if ((*tree)->right)
			terminate_tree(&((*tree)->right));

		delete *tree;
		*tree = nullptr;
		tree = nullptr;
	}
}


void Strategy::terminate()
{	// Public function that can be called to terminate the tree
	terminate_tree(&root);
}


void Strategy::read(std::string filename) 
{ // Reads in a file and stores each line in a vector of strings
	file = filename;
	ifstream inFile;
	inFile.open(filename);
	
	while (!inFile.eof()) {
		string line;
		getline(inFile, line);
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		if (line != "") { lines.push_back(line); }
	}

	inFile.close();
}


void Strategy::interpret() 
{	// Takes the vector of strings read in by the read(filename) function and attempts interpretation
	for (int i = 0; i < lines.size(); ++i) 
	{
		int first_letter_idx = lines[i].find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");									
		int thisline = stoi(lines[i].substr(0, first_letter_idx));

		linenos.push_back(thisline);

		if (lines[i].substr(first_letter_idx, 2) == "IF") 
		{
			string lhs, op, rhs, gotoline;

			int size = lines[i].size();
			int op_pos = lines[i].find_first_of("<=>");
			int goto_pos = lines[i].find("GOTO");

			
			if (goto_pos == string::npos) 
			{	// Error if the if statement is not followed by a "GOTO"
				throw runtime_error("Invalid If statement on line " + to_string(thisline) + " " + lines[i]);
			}


			lhs = lines[i].substr(first_letter_idx + 2, op_pos - (first_letter_idx + 2));
			op = lines[i][op_pos];
			rhs = lines[i].substr(op_pos + 1, goto_pos - (op_pos + 1));
			gotoline = lines[i].substr(goto_pos + 4);

			if (!(checkvar(lhs) && checkvar(rhs))) 
			{	// Check that both lhs and rhs are valid variables
				throw runtime_error("Invalid Variable on line " + to_string(thisline) + " " + lines[i]);
			}
		}
		else if (!((lines[i].substr(first_letter_idx, 6) == "BETRAY") || (lines[i].substr(first_letter_idx, 7) == "SILENCE") || (lines[i].substr(first_letter_idx, 6) == "RANDOM"))) 
		{	// If there is no IF, BETRAY, SILENCE, RANDOM throw an error
			throw runtime_error("Invalid Command");
		}
	}

	// Interpret the first line ( and recursively the others)
	interpret_line(linenos[0], &root);

}


void Strategy::interpret_line(int thisline, node ** tree) 
{	// Interpret the line with a given number and put it onto the tree

	currentline = thisline;

	int i = find(linenos.begin(), linenos.end(), thisline) - linenos.begin();
	int first_letter_idx = lines[i].find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	if (!(*tree)) 
	{
		*tree = new node;
		(*tree)->lineno = thisline;

	}

	if (lines[i].substr(first_letter_idx, 2) == "IF") 
	{	// Interpret The IF statement by splitting it up into components
		string lhs, op, rhs, gotoline;

		int size = lines[i].size();
		int op_pos = lines[i].find_first_of("<=>");
		int goto_pos = lines[i].find("GOTO");
		int nextline = linenos[i + 1];

		lhs = lines[i].substr(first_letter_idx + 2, op_pos - (first_letter_idx + 2));
		op = lines[i][op_pos];
		rhs = lines[i].substr(op_pos + 1, goto_pos - (op_pos + 1));
		gotoline = lines[i].substr(goto_pos + 4);
		
		vector<string> command = { "IF",lhs,op,rhs, };

		// Set Populate the node and set up the left and right children
		// left: next line ie. IF returns false, right: "goto" line ie. IF returns true
		(*tree)->command = command;
		(*tree)->left = new node;
		(*tree)->right = new node;
		(*tree)->left->lineno = nextline;
		(*tree)->right->lineno = stoi(gotoline);

		// Recursively populate the tree with the line numbers of the children
		interpret_line(nextline, &((*tree)->left));
		interpret_line(stoi(gotoline), &((*tree)->right));

	}

	else if (lines[i].substr(first_letter_idx,6) == "BETRAY") 
	{	// Populate node and have no children
		(*tree)->command = { "BETRAY" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else if (lines[i].substr(first_letter_idx, 7) == "SILENCE") 
	{	// Populate node and have no children
		(*tree)->command = { "SILENCE" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else if (lines[i].substr(first_letter_idx, 6) == "RANDOM") 
	{	// Populate node and have no children
		(*tree)->command = { "RANDOM" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else 
	{	// TODO: Throw and error instead. Right now 
		cerr << "Invalid Command in the file on line " << thisline << ": " << lines[i];
		terminate_tree(tree);
		exit(0);
	}
}


bool Strategy::ifstatement(string lhs, char op, string rhs, Prisoner A)
{	// Returns the outcome of an IF statement with given parameters
	int v1 = 0, v2 = 0;
	bool result = false;

	vars var_left = getvar(lhs, A);
	vars var_right = getvar(rhs, A);

	switch (op) {
	case '=':
		if ((var_left.intvar == var_right.intvar && var_left.intvar != 0) || (var_left.stringvar == var_right.stringvar && var_left.stringvar != "")) { result = true; }
		break;
	case '>':
		if (var_left.intvar > var_right.intvar) { result = true; }
		break;
	case '<':
		if (var_left.intvar < var_right.intvar) { result = true; }
	}

	return result;
}


bool Strategy::checkvar(string var) 
{	// Checks whether the given variable is a valid variable in the strategy language
	bool result = false;
	if (std::find(tokens.begin(), tokens.end(), var) != tokens.end()) { result = true; }
	else if (var.find_first_of("+-") != string::npos) { result = (checkvar(var.substr(0, var.find_first_of("+-"))) && checkvar(var.substr(var.find_first_of("+-") + 1))); }
	else if (var.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) { result = true; }
	else { result = false; }

	return result;
}


vars Strategy::getvar(string var, Prisoner A) 
{	// Takes the variable read in and interprets it to the actual value needed. Recursively splits and runs the variable if it represents multiple variables separated by a + or -
	vars v;
	if (var == "LASTOUTCOME") { v.stringvar = A.get_last_outcome(); }
	else if (var == "W" || var == "X" || var == "Y" || var == "Z") { v.stringvar = var; }
	else if (var == "ALLOUTCOMES_W") { v.intvar = A.get_allw(); }
	else if (var == "ALLOUTCOMES_X") { v.intvar = A.get_allx(); }
	else if (var == "ALLOUTCOMES_Y") { v.intvar = A.get_ally(); }
	else if (var == "ALLOUTCOMES_Z") { v.intvar = A.get_allz(); }
	else if (var == "ITERATIONS") { v.intvar = A.get_iteration(); }
	else if (var == "MYSCORE") { v.intvar = A.get_score(); }
	else if (var.find_first_of("+") != string::npos) { v.intvar = getvar(var.substr(0, var.find_first_of("+")), A).intvar + getvar(var.substr(var.find_first_of("+") + 1), A).intvar; }		
	else if (var.find_first_of("-") != string::npos) { v.intvar = getvar(var.substr(0, var.find_first_of("-")), A).intvar - getvar(var.substr(var.find_first_of("-") + 1), A).intvar; }
	else if (var.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) { v.intvar = stoi(var); }
	return v;
	
}


Decision Strategy::decide_result(Prisoner A) 
{	// public function that can be called to make a decision given the prisoner (and his strategy)
	return decide(&root, A);
}


Decision Strategy::decide(node ** tree,Prisoner A)
{	// Follows through the tree until it hits a BETRAY, SILENCE or RANDOM node, which will be the decision it returns.
	if (*tree) 
	{
		if ((*tree)->command[0] == "IF") 
		{
			bool result = ifstatement((*tree)->command[1], (*tree)->command[2][0], (*tree)->command[3], A);
			if (result)
				return decide(&((*tree)->right), A);
			else
				return decide(&((*tree)->left), A);
		}
		else if ((*tree)->command[0] == "BETRAY")
			return Decision::BETRAY;
		else if ((*tree)->command[0] == "SILENCE")
			return Decision::SILENCE;
		else if ((*tree)->command[0] == "RANDOM")
			return static_cast<Decision>(rand() % 2);

	}
	else 
	{	// This does not happen unless prisoner is created without a strategy
		cout << "This strategy does not exist!! Returning Random outcome";
		return static_cast<Decision>(rand() % 2);
	}

}


string Strategy::getFile()
{
	return file;
}


