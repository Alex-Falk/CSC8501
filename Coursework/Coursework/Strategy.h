#pragma once
#include <string>
#include <vector>

using namespace std;

enum class Decision {BETRAY,SILENCE};
class Prisoner;
struct vars {
	int intvar = NULL;
	string stringvar = "";
};

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

class Strategy {
protected:
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
	void terminate_tree(node ** tree);
	Decision decide(node ** tree, Prisoner A);
	bool checkvar(string var);
	vector<string> tokens = { "IF","BETRAY","SILENCE","RANDOM","+","-",">","<","=","GOTO","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","W","X","Y","Z","LASTOUTCOME","ITERATIONS","MYSCORE"," ","0","1","2","3","4","5","6","7","8","9" };
public:
	Strategy();
	~Strategy();
	Strategy(const Strategy &strat);
	void read(string filename);
	void interpret();
	void interpret_line(int i, node ** tree);
	bool ifstatement(string var1, char op, string var2, Prisoner prisoner);
	void terminate();
	Decision decide_result(Prisoner A);
	vars getvar(string var, Prisoner A);

	string getFile();
};