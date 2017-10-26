#pragma once
#include <string>
#include <vector>

using namespace std;

enum class Decision {BETRAY,SILENCE};

// Operator overloading for the Decision enum class that allows printing out a decision
inline ostream& operator<<(ostream& ostr, Decision& result) {
	switch (result) {
	case Decision::BETRAY:
		ostr << "Betray";
		break;
	case Decision::SILENCE:
		ostr << "Silence";
		break;
	}
	return ostr;
}

// Forward declaration of the prisoner class
class Prisoner;

// Struct to store a variable that might either be an int or a string
struct vars {
	int intvar = NULL;
	string stringvar = "";
};



class Strategy {
protected:
	// protected variables
	string file;
	int currentline;

	struct node {
		node * left;
		node * right;
		int lineno;
		vector<string> command;
	};
	node * root = nullptr;

	vector<int> linenos;
	vector<string> lines;

	// List of possible tokens that are allowed in the Strategy files
	vector<string> tokens = { "IF","BETRAY","SILENCE","RANDOM","+","-",">","<","=","GOTO","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z",
								"W","X","Y","Z","LASTOUTCOME","ITERATIONS","MYSCORE"," ","0","1","2","3","4","5","6","7","8","9" };

	// protected functions
	virtual void terminate_tree(node ** tree);											// Terminate the tree, clear memory
	virtual bool checkvar(string var);													// Checks whether the given variable is a valid variable in the strategy language
	virtual vars getvar(string var, Prisoner A);										// Takes the variable read in and interprets it to the actual value needed. Recursively splits and runs the variable if it represents multiple variables separated by a + or -
	virtual Decision decide(node ** tree, Prisoner A);									// Follows through the tree until it hits a BETRAY, SILENCE or RANDOM node, which will be the decision it returns.
	
public:
	Strategy();
	virtual ~Strategy();
	Strategy(const Strategy &strat);													// Copy constructor
	virtual void terminate();															// Terminate the tree, clear memory (by running protected terminate fuction with the root)
	virtual void read(string filename);													// Reads in a file and stores each line in a vector of strings
	virtual void interpret();															// Takes the vector of strings read in by the read(filename) function and attempts interpretation
	virtual void interpret_line(int i, node ** tree);									// Interpret the line with a given number and put it onto the tree
	virtual bool ifstatement(string var1, char op, string var2, Prisoner prisoner);		// Returns the outcome of an IF statement with given parameters
	virtual Decision decide_result(Prisoner A);											// public function that can be called to make a decision given the prisoner (and his strategy)
	virtual string getFile();
};