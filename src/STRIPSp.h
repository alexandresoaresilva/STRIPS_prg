/*
 * STRIPSp.h
 *
 *  Created on: Jan 10, 2018
 *      Author: alexa
 */

#ifndef STRIPSP_H_
#define STRIPSP_H_

#ifndef STRIPS_tokenizer_h
#include "STRIPS_tokenizer.h"
#endif

#ifndef _VECTOR_
#include<vector>
#endif

#ifndef _STRING_
#include<string>
#endif

#ifndef _FSTREAM_
#include<fstream>
#endif

#ifndef _IOSTREAM_
#include<iostream>
#endif

#ifndef _ITERATOR_
#include<iterator>
#endif

//using std::vector;
//using std::string;
//using std::endl;
//using std::cin;
//using std::cout;

class STRIPSp : public STRIPS_tokenizer {
public:
	STRIPSp();
	virtual ~STRIPSp();
	void printIsItASTRIPS_planner();
private:
	bool it_is_a_STRIPS_planner;
	vector<string> slice(const vector<string> &s,uint32_t loBound, uint32_t upBound);
	//related to Atomic Statement/list
	bool STRIPS_keyword(const vector<string> &s);//s needs to be sliced to be used in here
	bool symbol(const vector<string> &s);
	bool NEsymbol_list(const vector<string> &s);
	bool symbol_list(const vector<string> &s);// I don't know if this will actually work
	bool atomic_statement(const vector<string> &s);
	bool NEatom_list(const vector<string> &s);
	bool atom_list(const vector<string> &s);// I don't know if this will actually work

	//literals
	bool literal(const vector<string> &s);// I don't know if this will actually work
	bool NEliteral_list(const vector<string> &s); //might need adjustment in loop condition i <=
	bool literal_list(const vector<string> &s);// I don't know if this will actually work

	//actions
	bool action_prototype(const vector<string> &s);
	bool preconditions_declaration(const vector<string> &s);
	bool effects_declaration(const vector<string> &s);
	bool action_declaration(const vector<string> &s);
	bool NEaction_list(const vector<string> &s); //might need adjustment in loop condition i <=
	bool action_set(const vector<string> &s); //might need adjustment in loop condition i <=

	bool initial_state_declaration(const vector<string> &s);
	bool goal_declaration(const vector<string> &s); //NOTE: declaration on the Wikipedia's example is followed by "state"; here, it's not.
	bool STRIPS_program(const vector<string> &s);



};

#endif /* STRIPSP_H_ */
