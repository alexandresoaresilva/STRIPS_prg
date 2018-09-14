

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      /* STRIPS_program checker*/
//
// does: returns true if input (vector of strings) is a tokenized STRIPS instance
// Written by: Alexandre Soares da Silva
// Date: April 2, 2017
// Submitted as assignment 2 solution for dr. Rushton's  CS 2413 - Data Structures class
// (Texas Tech University)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#include <vector>
#include <string>

using namespace std;

vector<string> slice(const vector<string> &s, int loBound, int upBound);
bool STRIPS_program(vector<string> s);
bool initial_state_declaration(vector<string> s);
bool goal_declaration(vector<string> s);
bool action_set(vector<string> s);
bool NEaction_list(vector<string> s);
bool action_declaration(vector<string> s);
bool action_prototype(vector<string> s);
bool preconditions_declaration(vector<string> s);
bool effects_declaration(vector<string> s);
bool NEliteral_list(vector<string> s);
bool literal_list(vector<string> s);
bool literal(vector<string> s);
bool atom_list(vector<string> s);
bool NEatom_list(vector<string> s);
bool atomic_statement(vector<string> s);
bool symbol_list(vector<string> s);
bool NEsymbol_list(vector<string> s);
bool symbol(vector<string> s);
bool STRIPS_keyword(vector<string> s);


//helper function to slice the vector
vector<string> slice(const vector<string> &s, int loBound, int upBound)
{
	vector<string> sliced;
	for (int i = static_cast<uint16_t>(loBound); i < static_cast<uint16_t>(upBound); i++)
	{
		sliced.push_back(s[i]);
	}
	return sliced;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	MAIN function- starts the recursive descent calls
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool STRIPS_program(vector<string> s)
{
	if (s.size() > 7) // minimum list: (0. "Initial", 1. "state", 2. ":", 3. "Goal",4. ":",5. "Actions",6. ":",7. NEaction_list)
	{
		int initStateEndIndex(0), goalDeclEndIndex(0);
		bool initStateTrue(0), goalDeclTrue(0);

		for (int i = 1; i < static_cast<uint16_t>(s.size() - 4); i++) //so avoids the minimum list for Goal & Actions
			if (initial_state_declaration(slice(s, 0, i)) && s[i] == "Goal") //i and NOT i+1 because slicing happens at i-1
			{
				initStateEndIndex = i;//it will evaluate to true before reaching
				initStateTrue = 1;
				break;
			}

		if (initStateTrue)
			for (int j = initStateEndIndex; j < static_cast<uint16_t>(s.size() - 2); j++) //s.size()-2 because "Actions",":",NEaction_list
				if (goal_declaration(slice(s, initStateEndIndex, j)))
					if (s[j] == "Actions")
					{
						goalDeclEndIndex = j;
						goalDeclTrue = 1;
						break;
					}

		if (initStateTrue  && goalDeclTrue)
			for (int z = goalDeclEndIndex; z < static_cast<uint16_t>(s.size()); z++)
				if (action_set(slice(s, z, s.size())))return true;
	}
	return false;
}

bool initial_state_declaration(vector<string> s)
{
	if (s.size() >= 3) // size >= 3 to avoid crashing when testing smaller parts of the strips vector 
		if (s[0] == "Initial" && s[1] == "state" && s[2] == ":" && atom_list(slice(s, 3, s.size())))return true;
	return false;
}

bool action_set(vector<string> s) //might need adjustment in loop condition i <=
{

	if (s.size() >= 3 && (s[0] == "Actions" && s[1] == ":"))
		if (NEaction_list(slice(s, 2, s.size())))return true;
	return false;
}

bool action_declaration(vector<string> s)
{
	if (s.size() >= 3)
	{
		for (int i = 1; i < static_cast<uint16_t>(s.size()); i++)
			if (action_prototype(slice(s, 0, i)))
				for (int j = 2; j < static_cast<uint16_t>(s.size()); j++) //they have to grow separatelly
					if (preconditions_declaration(slice(s, i, j)) && effects_declaration(slice(s, j, s.size())))return true;
	}
	return false;
}

bool action_prototype(vector<string> s)
{
	//for (int i = 1; i < s.size(); i++) //might need adjustment in loop condition i <=
	if (s[0] == "_" && s[s.size() - 1] == "_")
		if (atomic_statement(slice(s, 1, s.size() - 1)))return true;
	return false;
}

bool preconditions_declaration(vector<string> s)
{
	if (s.size()>1 && (s[0] == "Preconditions" && s[1] == ":"))
		if (literal_list(slice(s, 2, s.size())))return true;
	return false;
}

bool effects_declaration(vector<string> s)
{
	if (s.size()>1 && (s[0] == "Effects" && s[1] == ":"))
		if (literal_list(slice(s, 2, s.size())))return true;
	return false;
}
bool goal_declaration(vector<string> s) //NOTE: declaration on the Wikipedia's example is followed by "state"; here, it's not.
{
	if (s.size() >= 2)
		if (s[0] == "Goal" && s[1] == ":" && literal_list(slice(s, 2, s.size())))return true;
	//if ( s[0] == "Goal" && s[1] == "state" && s[2] == ":" && literal_list(slice(s,3,s.size())) )return true; // WITH "state"
	return false;
}

bool NEaction_list(vector<string> s) //might need adjustment in loop condition i <=
{
	if (s.size()> 0)
	{
		if (action_declaration(s))return true;
		else
		{
			for (int i = 1; i < static_cast<uint16_t>(s.size()); i++)
			{
				if (action_declaration(slice(s, 0, i)) && NEaction_list(slice(s, i, s.size())))return true;
			}
		}
	}
	return false;
}

bool NEliteral_list(vector<string> s) //might need adjustment in loop condition i <=
{
	if (literal(s))return true;
	else
		for (int i = 1; i < static_cast<uint16_t>(s.size() - 1); i++)
			if (s[i] == ",")
				if (literal(slice(s, 0, i)) && NEliteral_list(slice(s, i + 1, s.size())))return true;
	return false;
}

bool literal_list(vector<string> s)// I don't know if this will actually work
{
	for (int i = 1; i < static_cast<uint16_t>(s.size()); i++)
	{
		if (s.empty() || NEliteral_list(s))
			return true;
	}
	return false;
}

bool literal(vector<string> s)// I don't know if this will actually work
{
	if (atomic_statement(s))return true;
	else if ( s.size() > 0 && (s[0] == "not" || s[0] == "NOT") && atomic_statement(slice(s, 1, s.size())))
		return true;
	return false;
}

bool NEatom_list(vector<string> s)
{
	if (atomic_statement(s)) return true;
	else
	{
		for (int i = 1; i < static_cast<uint16_t>(s.size() - 1); i++)
		{
			if (s[i] == ",")
				if (atomic_statement(slice(s, 0, i)) && NEatom_list(slice(s, i + 1, s.size())))return true;
		}
	}
	return false;
}

bool atom_list(vector<string> s)// I don't know if this will actually work
{
	for (int i = 1; i < static_cast<uint16_t>(s.size()); i++)
	{
		if (s.empty() || NEatom_list(s))
			return true;
	}

	//    if ( slice(s,0,1).empty() || NEliteral_list(slice(s,0,1)))
	//        return true;
	return false;
}

bool atomic_statement(vector<string> s)
{
	if (s.size() >= 4)
		if (symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")")
			if (symbol_list(slice(s, 2, s.size() - 1)))return true;
	return false;
}

bool NEsymbol_list(vector<string> s)
{
	if (s.size() == 1 && symbol(slice(s, 0, 1))) return true;
	else if (s.size() >= 3 && symbol(slice(s, 0, 1)) && s[1] == ",")
		if (NEsymbol_list(slice(s, 2, s.size())))return true;
	return false;
}

bool symbol_list(vector<string> s)// I don't know if this will actually work
{
	return (s.empty() || NEsymbol_list(s));
}

bool symbol(vector<string> s)
{
	return(!s.empty() && s.size() == 1 && !STRIPS_keyword(s));
}

bool STRIPS_keyword(vector<string> s)//s needs to be sliced to be used in here
{
	if ((!s.empty() && s.size() == 1) && (s[0] == "Initial" || s[0] == "state" || s[0] == "Goal" || s[0] == "Actions" || s[0] == "Preconditions" || s[0] == "Effects" || s[0] == "not" || s[0] == "NOT"))
		return true;
	return false;
}
