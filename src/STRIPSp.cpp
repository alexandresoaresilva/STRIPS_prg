/*
 * STRIPSp.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: alexa
 */

#include "STRIPSp.h"

STRIPSp::STRIPSp() : STRIPS_tokenizer(), it_is_a_STRIPS_planner(0) {
	cout << endl;
	    cout << "STRIPSp (recognizer) class\n";
	    cout << ">>>>>>>>>>>>>>>>>>>>>>\n";
	STRIPS_tokenizer::print_Vector_of_strg();
	it_is_a_STRIPS_planner = STRIPS_program(STRIPS_tokenizer::getVectStrg_Tokenized_STRIPS());
	printIsItASTRIPS_planner();
	// TODO Auto-generated constructor stub
}

STRIPSp::~STRIPSp() {
	// TODO Auto-generated destructor stub
}

void STRIPSp::printIsItASTRIPS_planner(){
	if (it_is_a_STRIPS_planner)
		cout << "STRIPS planner\n";
	else
		cout << "NOT a STRIPS planner\n";
}

vector<string> STRIPSp::slice(const vector<string> &s, uint32_t loBound, uint32_t upBound) {
	    vector<string> sliced;

	    for (auto i = loBound; i < upBound; i++)
	        sliced.push_back(s[i]);

	    return sliced;
}

bool STRIPSp::STRIPS_keyword(const vector<string> &s) {//s needs to be sliced to be used in here
	if ( !s.empty()
		&& ( s.size() == 1 )
			&& ( s[0] == "Initial"
				|| s[0] == "state"
				|| s[0] == "Goal"
				|| s[0] == "Actions"
				|| s[0] == "Preconditions"
				|| s[0] == "Effects"
				|| s[0] == "not"
				|| s[0] == "NOT" ) ) //end of if
		return true;
	return false;
}

bool STRIPSp::symbol(const vector<string> &s) {
    return( !s.empty()
            && ( s.size() == 1)
            && !STRIPS_keyword(s) ); //end of return
}

bool STRIPSp::NEsymbol_list(const vector<string> &s) {
    if (s.size() == 1 && symbol(slice(s, 0, 1)))
        return true;
    else if (s.size() >= 3 && symbol(slice(s, 0, 1)) && s[1] == ",")
        if ( NEsymbol_list(slice(s, 2, s.size())) )
            return true;
    return false;
}

bool STRIPSp::symbol_list(const vector<string> &s) {// I don't know if this will actually work
	return (s.empty() || NEsymbol_list(s));
}

bool STRIPSp::atomic_statement(const vector<string> &s) {
	if (s.size() >= 4)
		if (symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")")
			if (symbol_list(slice(s, 2, s.size() - 1)))return true;
	return false;
}

bool STRIPSp::NEatom_list(const vector<string> &s) {
	if (atomic_statement(s)) return true;
	else {
		for (uint32_t i = 1; i < (s.size() - 1); i++) {
			if (s[i] == ",")
				if (atomic_statement(slice(s, 0, i)) && NEatom_list(slice(s, i + 1, s.size())))return true;
		}
	}
	return false;
}

bool STRIPSp::atom_list(const vector<string> &s) {// I don't know if this will actually work
	for (uint32_t i = 1; i < s.size(); i++) {
		if (s.empty() || NEatom_list(s))
			return true;
	}
	return false;
}

bool STRIPSp::literal(const vector<string> &s) {// I don't know if this will actually work
	if (atomic_statement(s))return true;
	else if (s.size()>0 && (s[0] == "not" || s[0] == "NOT") && atomic_statement(slice(s, 1, s.size())))
		return true;
	return false;
}

bool STRIPSp::NEliteral_list(const vector<string> &s) {//might need adjustment in loop condition i <=
	if (literal(s))return true;
	else
		for (uint32_t i = 1; i < (s.size() - 1); i++)
			if (s[i] == ",")
				if (literal(slice(s, 0, i)) && NEliteral_list(slice(s, i + 1, s.size())))return true;
	return false;
}

bool STRIPSp::literal_list(const vector<string> &s) {// I don't know if this will actually work
	for (uint32_t i = 1; i < s.size(); i++) {
		if (s.empty() || NEliteral_list(s))
			return true;
	}
	return false;
}

bool STRIPSp::action_prototype(const vector<string> &s) {

	if (s[0] == "_" && s[s.size() - 1] == "_")
		if (atomic_statement(slice(s, 1, s.size() - 1)))return true;
	return false;
}

bool STRIPSp::effects_declaration(const vector<string> &s) {
	if (s.size()>1 && (s[0] == "Effects" && s[1] == ":")) //instead of postconditions
		if (literal_list(slice(s, 2, s.size())))return true;
	return false;
}

bool STRIPSp::preconditions_declaration(const vector<string> &s) {
	if (s.size()>1 && (s[0] == "Preconditions" && s[1] == ":"))
		if (literal_list(slice(s, 2, s.size())))return true;
	return false;
}

bool STRIPSp::action_declaration(const vector<string> &s) {
	if (s.size() >= 3) {
		for (uint32_t i = 1; i < s.size(); i++)
			if (action_prototype(slice(s, 0, i)))
				for (uint32_t j = 2; j < s.size(); j++) //they have to grow separatelly
					if (preconditions_declaration(slice(s, i, j)) && effects_declaration(slice(s, j, s.size())))return true;
	}
	return false;
}

bool STRIPSp::NEaction_list(const vector<string> &s) {//might need adjustment in loop condition i <=

	if (s.size()> 0)
	{
		if (action_declaration(s))return true;
		else
		{
			for (uint32_t i = 1; i < s.size(); i++)
			{
				if (action_declaration(slice(s, 0, i)) && NEaction_list(slice(s, i, s.size())))return true;
			}
		}
	}
	return false;
}

bool STRIPSp::action_set(const vector<string> &s) {//might need adjustment in loop condition i <=
	if (s.size() >= 3 && (s[0] == "Actions" && s[1] == ":"))
		if (NEaction_list(slice(s, 2, s.size())))return true;
	return false;
}

bool STRIPSp::initial_state_declaration(const vector<string> &s) {
	if (s.size() >= 3) // size >= 3 to avoid crashing when testing smaller parts of the strips vector
		if (s[0] == "Initial" && s[1] == "state" && s[2] == ":" && atom_list(slice(s, 3, s.size())))return true;
	return false;
}

bool STRIPSp::goal_declaration(const vector<string> &s) {//NOTE: declaration on the Wikipedia's example is followed by "state"; here, it's not.
	if (s.size() >= 2)
		if (s[0] == "Goal" && s[1] == ":" && literal_list(slice(s, 2, s.size())))return true;
	//if ( s[0] == "Goal" && s[1] == "state" && s[2] == ":" && literal_list(slice(s,3,s.size())) )return true; // WITH "state"
	return false;
}

//MAIN function- starts the recursive descent calls
bool STRIPSp::STRIPS_program(const vector<string> &s) {
	if (s.size() > 7) // minimum list: (0. "Initial", 1. "state", 2. ":", 3. "Goal",4. ":",5. "Actions",6. ":",7. NEaction_list)
	{
		int initStateEndIndex(0), goalDeclEndIndex(0);
		bool initStateTrue(0), goalDeclTrue(0);

		for (uint32_t i = 1; i < (s.size() - 4); i++) //so avoids the minimum list for Goal & Actions
			if (initial_state_declaration(slice(s, 0, i)) && s[i] == "Goal") //i and NOT i+1 because slicing happens at i-1
			{
				initStateEndIndex = i;//it will evaluate to true before reaching
				initStateTrue = 1;
				break;
			}

		if (initStateTrue)
			for (uint32_t j = initStateEndIndex; j < (s.size() - 2); j++) //s.size()-2 because "Actions",":",NEaction_list
				if (goal_declaration(slice(s, initStateEndIndex, j)))
					if (s[j] == "Actions")
					{
						goalDeclEndIndex = j;
						goalDeclTrue = 1;
						break;
					}

		if (initStateTrue  && goalDeclTrue)
			for (uint32_t z = goalDeclEndIndex; z < s.size(); z++)
				if (action_set(slice(s, z, s.size())))return true;
	}
	return false;
}
