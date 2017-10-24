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

Strategy::Strategy(const Strategy &strat) {
	root = nullptr;
	*root = *strat.root;
}


void Strategy::read(std::string filename) {
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

void Strategy::interpret() {
	for (int i = 0; i < lines.size(); ++i) {

		int first_letter_idx = lines[i].find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		int thisline = stoi(lines[i].substr(0, first_letter_idx));

		linenos.push_back(thisline);

		if (lines[i].substr(first_letter_idx, 2) == "IF") {
			string var1, var2, gotoline;
			string op;

			int size = lines[i].size();
			int op_pos = lines[i].find_first_of("<=>");
			int goto_pos = lines[i].find("GOTO");

			
			if (goto_pos == string::npos) {
				throw runtime_error("Invalid If statement on line " + to_string(thisline) + " " + lines[i]);
			}


			var1 = lines[i].substr(first_letter_idx + 2, op_pos - (first_letter_idx + 2));
			op = lines[i][op_pos];
			var2 = lines[i].substr(op_pos + 1, goto_pos - (op_pos + 1));
			gotoline = lines[i].substr(goto_pos + 4);

			if (!(checkvar(var1) && checkvar(var2))) {
				throw runtime_error("Invalid Variable on line " + to_string(thisline) + " " + lines[i]);
			}
		}
		else if (!((lines[i].substr(first_letter_idx, 6) == "BETRAY") || (lines[i].substr(first_letter_idx, 7) == "SILENCE") || (lines[i].substr(first_letter_idx, 6) == "RANDOM"))) {
			throw runtime_error("Invalid Command");
		}
	}

	interpret_line(linenos[0], &root);

}

string Strategy::getFile() {
	return file;
}

void Strategy::interpret_line(int thisline, node ** tree) {
	currentline = thisline;
	int i = find(linenos.begin(), linenos.end(), thisline) - linenos.begin();

	int first_letter_idx = lines[i].find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");


	if (!(*tree)) {
		*tree = new node;
		(*tree)->lineno = thisline;

	}

	if (lines[i].substr(first_letter_idx, 2) == "IF") {
		// DO IF things
		string var1, var2, gotoline;
		string op;

		int size = lines[i].size();
		int op_pos = lines[i].find_first_of("<=>");
		int goto_pos = lines[i].find("GOTO");

		var1 = lines[i].substr(first_letter_idx + 2, op_pos - (first_letter_idx + 2));
		op = lines[i][op_pos];
		var2 = lines[i].substr(op_pos + 1, goto_pos - (op_pos + 1));
		gotoline = lines[i].substr(goto_pos + 4);
		
		int nextline = linenos[i + 1];

		vector<string> command = { "IF",var1,op,var2, };

		(*tree)->command = command;
		(*tree)->left = new node;
		(*tree)->right = new node;
		(*tree)->left->lineno = nextline;
		(*tree)->right->lineno = stoi(gotoline);

		interpret_line(nextline, &((*tree)->left));
		interpret_line(stoi(gotoline), &((*tree)->right));

	}

	else if (lines[i].substr(first_letter_idx,6) == "BETRAY") {
		// Do BETRAY things
		(*tree)->command = { "BETRAY" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else if (lines[i].substr(first_letter_idx, 7) == "SILENCE") {
		// Do SILENCE things
		(*tree)->command = { "SILENCE" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else if (lines[i].substr(first_letter_idx, 6) == "RANDOM") {
		// Do RANDOM things
		(*tree)->command = { "RANDOM" };
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else {
		cerr << "Invalid Command in the file on line " << thisline << ": " << lines[i];
		terminate_tree(tree);
		exit(0);
	}
}

void Strategy::terminate_tree(node ** tree) {
	if (*tree) {
		if ((*tree)->left)
			terminate_tree(&((*tree)->left));
		if ((*tree)->right)
			terminate_tree(&((*tree)->right));

		//(*tree)->left = nullptr;
		//(*tree)->right = nullptr;

		delete *tree;
		*tree = nullptr;
		tree = nullptr;
	}
}

void Strategy::terminate() {
	terminate_tree(&root);
	//root = nullptr;
}

bool Strategy::checkvar(string var) {
	bool result = false;
	if (std::find(tokens.begin(), tokens.end(), var) != tokens.end()) { result = true; }
	else if (var.find_first_of("+-") != string::npos) { result = (checkvar(var.substr(0, var.find_first_of("+-"))) && checkvar(var.substr(var.find_first_of("+-") + 1))); }
	else if (var.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) { result = true; }
	else { result = false; }

	return result;
}

vars Strategy::getvar(string var, Prisoner A) {
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
	else {
		//cerr << "Invalid Variable in input file " << file << " on line " << currentline << ": " << var; 
		// "Invalid Variable in input file " + file + " on line " + to_string(currentline) + ": " + var
	}
	return v;
	
}

bool Strategy::ifstatement(string var1, char op, string var2, Prisoner A) {
	//TODO: Check for +/- in the operands
	int v1 = 0, v2 = 0;
	bool result = false;

	vars v = getvar(var1, A);
	if (v.stringvar != "") { string v1 = v.stringvar; }
	else { v1 = v.intvar; }

	vars vb = getvar(var2, A);
	if (vb.stringvar != "") { string v2 = vb.stringvar; }
	else { v2 = vb.intvar; }


	switch (op) {
	case '=':
		if ((v.intvar == vb.intvar && v.intvar != 0) || (v.stringvar == vb.stringvar && v.stringvar != "")) { result = true; }
		break;
	case '>':
		if (v.intvar > vb.intvar) { result = true; }
		break;
	case '<':
		if (v.intvar < vb.intvar) { result = true; }
	}

	return result;
}

Decision Strategy::decide_result(Prisoner A) {
	return decide(&root, A);
}

Decision Strategy::decide(node ** tree,Prisoner A)
{
	if (*tree) {
		if ((*tree)->command[0] == "IF") {
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
	else {
		cout << "This strategy does not exist!! Returning Random outcome";
		return static_cast<Decision>(rand() % 2);
	}

	//Decision result;
	////TODO: Add logic that follows given set of instructions
	//result = static_cast<Decision>(rand() % 2);
	//return result;

}
