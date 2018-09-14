//
//  main.cpp
//  ass1
//
//  Created by Alexandre Soares da Silva on 2/25/17.
//  Copyright © 2017 Alexandre Soares da Silva. All rights reserved.
//

#include <iostream>
#include <vector>
//#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include "tokenizer.h"

using namespace std;

//struct AtomicStmt
//{
//    string relation;
//    vector<string> args;
//    bool notEmpty; //if 1, it's NOT empty
//    void printAtomStmt()
//    {
//        if (notEmpty == 1)
//        {
//            cout << "\natomSt = " << relation <<endl;
//            for (int i = 0; i < args.size(); i++)
//                cout << "args = " << args[i] << endl;
//        }
//    }
//    AtomicStmt(){notEmpty=0;}
//};

//typedef vector<AtomicStmt> state;

struct Literal //member struct AmtomStmt holds the atomic_statement & polarity =
{
    //string relation;
    //vector<string> args;
    bool polarity; //if 1, positive (atom statement); 0, negative (s[0] == "not", s[1:] == literal)
    bool notEmpty; //1 if NOT empty
    AtomicStmt AtomStmt;
    void printLiteral()
    {
        if (notEmpty == 1)
        {
            if (polarity == 1)
            {
                cout << ">POSITIVE literal(check above)\n";
                //AtomStmt.printAtomStmt();
            }
            else if (polarity == 0)
            {
                cout << ">NEGATIVE literal(check above)\n";
                //AtomStmt.printAtomStmt();
            }
        }
    }
};

typedef vector<Literal> literalList;
literalList literal_listP(vector<string> s);
literalList NEliteral_listP(vector<string> s);
Literal literalP(vector<string> s);

//state initial_state_declarationP(vector<string> s);
//state atom_listP(vector<string> s);
//state NEatom_listP(vector<string> s);

struct Condition //member functions' definitions within the strcut
{
    vector<AtomicStmt> negative; //NEliteral_list with s[0] == "not"
    vector<AtomicStmt> positive; // NEatom_list without not
    bool notEmpty; //1 if NOT empty
    void getLiterals(literalList a)
    {
        notEmpty = 1;
        for (int i = 0; i < a.size(); i++ )
        {
            if( a[i].Literal::polarity == 1)
                positive.push_back(a[i].Literal::AtomStmt);
            else if ( a[i].Literal::polarity == 0)
                negative.push_back(a[i].Literal::AtomStmt);
        }
    }
    Condition(){notEmpty = 0;}//default constructor
    Condition(vector<string> s){ getLiterals( literal_listP(s));}//alternate constrcutor
};

struct Action
{
    AtomicStmt label;
    Condition preconditions;
    Condition effects;
    void printAction()
    {
        cout<<"\n>>>> Action <<<<\n";
        label.printAtomStmt();
        cout << "\n>> Preconditions:\n";
        for (int j = 0; j< preconditions.positive.size() ;j++)
        {
            //cout << "\npositive";
            preconditions.positive[j].AtomicStmt::printAtomStmt();
        }
        for (int j = 0; j< preconditions.negative.size() ;j++)
        {
            cout << "\nNOT";
            preconditions.negative[j].AtomicStmt::printAtomStmt();
        }
        cout <<"\n>> Effects:\n";
        for (int j = 0; j< effects.positive.size() ;j++)
        {
            //cout << "positive:\n";
            effects.positive[j].AtomicStmt::printAtomStmt();
        }
        for (int j = 0; j< effects.negative.size() ;j++)
        {
            cout << "\nNOT";
            effects.negative[j].AtomicStmt::printAtomStmt();
        }
    }
    bool notEmpty;
    Action(){notEmpty=0;}//default constructor
};


struct STRIPSInstance
{
    state initialState;
    Condition goal;
    vector<Action> actions;
    bool notEmpty;
    void printSTRIPS_programP()
    {
        if (notEmpty==1)
        {
            cout<<"     INITIAL STATE:   \n";
            for (int i = 0; i < static_cast<int>(initialState.size());i++)//prints AtomicStmt
                initialState[i].AtomicStmt::printAtomStmt();
            
            cout<<"\n   GOAL:   \n";
            for (int i = 0; i < static_cast<int>(goal.positive.size());i++)//prints AtomicStmt
            {
                //cout << "POSITIVE condition:\n";
                goal.positive[i].AtomicStmt::printAtomStmt();
            }
            cout << endl;
            for (int i = 0; i < static_cast<int>(goal.negative.size());i++)//prints AtomicStmt
            {
                cout << "\nNOT";
                goal.negative[i].AtomicStmt::printAtomStmt();
            }
            
            cout << "\n     ACTIONS:    \n";
            for (int i = 0; i < actions.size(); i++)
            {
                cout << i << ".\n";
                actions[i].printAction();
            }
        }
        cout << endl;
    }//END of print function
    STRIPSInstance(){notEmpty=0;}//default constructor
};

STRIPSInstance STRIPS_programP(vector<string> s);

struct ConcreteAction
{
    string actionType;
    vector<string> arguments;
    void printConcreteAction()
    {
        cout << "\nactionType = " << actionType <<endl;
        for (int i = 0; i < arguments.size(); i++)
            cout << "arguments = " << arguments[i] << endl;
    }
};

struct node
{
    state destination;
    vector<ConcreteAction> path;
};

void printState(state atVec);
AtomicStmt atomic_statementP(vector<string> s);
Condition goal_declarationP(vector<string> s);
vector<Action> action_setP(vector<string> s);
vector<Action> NEaction_listP(vector<string> s);
Action action_declarationP(vector<string> s);


bool STRIPS_program(vector<string> s);
bool initial_state_declaration(vector<string> s);
bool action_set(vector<string> s);
bool NEaction_list(vector<string> s);
bool action_declaration(vector<string> s);
bool effects_declaration(vector<string> s);
bool preconditions_declaration(vector<string> s);
bool action_prototype(vector<string> s);
bool goal_declaration(vector<string> s);
bool literal_list(vector<string> s);
bool NEliteral_list(vector<string> s);
bool literal(vector<string> s);
bool atom_list(vector<string> s);
bool NEatom_list(vector<string> s);
bool atomic_statement(vector<string> s);

//char symbol_list(std::vector<std::string> &s);
//char symbol(const std::vector<std::string> &s);
//char NEsymbol_list(const std::vector<std::string> &s);
//char STRIPS_keyword(const std::vector<std::string> &s);

vector<string> slice(const vector<string> &s, int loBound, int upBound);
vector<std::string> tokenize(string s);
vector<ConcreteAction> allActions();
bool satisfies(state S, Condition C);
Action substitute(vector<string> args, Action A);
bool possible(ConcreteAction c, state S);
state result(ConcreteAction c,state S);
vector<state> Successors(state S);
vector<ConcreteAction> solve(string S);
node search(node N);
vector<node> children(node N);
vector<ConcreteAction> statePossibleActions(state d);
bool Green(node N);

string saveTextIntoString(string fileName); //gets text form file
void test (vector<string> vectStr); //vector input
string vectorToString(vector<string> s);

//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
STRIPSInstance I;

//PROGRAM STARTS
int main()
{
    string text;
     // text = saveTextIntoString("test_planner.txt");
    text = saveTextIntoString("planner.txt");
    
    //vector<string> fullText = tokenize(text);
    
    //randomTokens = slice(fullText,26,39);
    
    //this is the planner's full string
    //const vector<string> randomTokens = tokenize("Initial state: At(A), Level(low), BoxAt(C), BananasAt(B)\nGoal:    Have(bananas)\nActions:\n// move from X to Y\n_Move(X, Y)_\nPreconditions:  At(X), Level(low)\nEffects: not At(X), At(Y)\n// climb up on the box\nClimbUp(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions:  At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n// take the bananas\n_TakeBananas(Location)_\nPreconditions:  At(Location), BananasAt(Location), Level(high)\nEffects: Have(bananas)");
    
    //this is the full planner, tokenized
    //const vector<string> fullText= {"Initial","state",":","At","(","A",")",",","Level","(","low",")",",","BoxAt","(","C",")",",","BananasAt","(","B",")","Goal",":","Have","(","bananas",")","Actions",":","_","Move","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","Level","(","low",")","Effects",":","not","At","(","X",")",",","At","(","Y",")","_","ClimbUp","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","low",")","Effects",":","Level","(","high",")",",","not","Level","(","low",")","_","ClimbDown","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","high",")","Effects",":","Level","(","low",")",",","not","Level","(","high",")","_","MoveBox","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","BoxAt","(","X",")",",","Level","(","low",")","Effects",":","BoxAt","(","Y",")",",","not","BoxAt","(","X",")",",","At","(","Y",")",",","not","At","(","X",")","_","TakeBananas","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BananasAt","(","Location",")",",","Level","(","high",")","Effects",":","Have","(","bananas",")"};
    
    //for testing smaller functions that create the structures
    //vector<string> randomTokens = {"_","Move","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","Level","(","low",")","Effects",":","not","At","(","X",")",",","At","(","Y",")"};
    
   
    //prints the tokens
	//test(randomTokens);
    //test(fullText);
    
    
    //I = STRIPS_programP(tokenize(text));
    
    //PRINTS the strip STRUCT
    //I.printSTRIPS_programP();
    //vector<ConcreteAction> allConcreteActions = allActions();
    //Condition initStateCond;
    
    //should satisfy
//    for(int i=0; i < I.initialState.size();i++)
//    {
//        initStateCond.positive.push_back(I.initialState[i]);
//    }
    
    //should not satisfy (psh back to negative parts of the condition
    //initStateCond.negative.push_back(I.initialState[1]);
    
    //cout << endl;
    
    //cout << satisfies(I.initialState, initStateCond) << endl;
    
    //vector<string> arguments = {"A","C"};
    
    //I.actions[0].printAction();
    
    //Action subsNew = substitute(arguments, I.actions[0]);
    
    //subsNew.printAction();
    
//    for(int i=0; i <allConcreteActions.size(); i++)
//        cout << possible(allConcreteActions[i],I.initialState) << endl;
//    state newState = result(allConcreteActions[4],I.initialState);
//    for(int i = 0; i < newState.size(); i++)
//        newState[i].printAtomStmt();
    
//    vector<state> succInitState;
//    succInitState = Successors(I.initialState);
//    
//    for(int i=0;i<succInitState.size(); i++)
//        for(int j = 0; j < succInitState[i].size(); j++)
//            succInitState[i][j].printAtomStmt();
    
    //node root;
//    vector<ConcreteAction> v; //v is an empty vect
//    root.dest = I.initialState;
//    root.path = v;
//    vector<ConcreteAction> solutionPath = search(root).path;
    
    //allActions();
    
//    for(int i = 0; i < Successors(I.initialState).size(); i++)
//    {
//        cout << "State " << i << endl;
//        for(int j = 0; j < Successors(I.initialState)[i].size(); j++ )
//            Successors(I.initialState)[i][j].printAtomStmt();
//    }
    
    
    
//    for(int i = 0; i < possConAct.size(); i++)
//        possConAct[i].printConcreteAction();
    
    vector<ConcreteAction> solved = solve(text);
    
    for(int i = 0; i <solved.size();i++)
        solved[i].printConcreteAction();
    
    return 0;
}
// PROGRAM ENDS

//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


std::string saveTextIntoString(std::string fileName)
{
	ifstream openFile(fileName, std::ios::in);

	//saves text from file to std::string found on Stackoverflow http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstd::string
	std::string wholeText((istreambuf_iterator<char>(openFile)), istreambuf_iterator<char>());
	openFile.close();
	return wholeText;

}//gets text form file

//NOT USED
std::string vectorToString(vector<std::string> s)
{
	std::string sliced;
	//code found on Stafkoverflow http://stackoverflow.com/questions/15347123/how-to-construct-a-stdstd::string-from-a-stdvectorstd::string
	for (const auto &piece : s) sliced += piece;
	return sliced;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////	STRIPSInstance

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//******************* functions available
/*
 STRIPSInstance STRIPS_programP(vector<string> s);
 STRIPSInstance::printSTRIPS_programP();
 
 state initial_state_declarationP(vector<string> s);
 state atom_listP(vector<string> s);
 state NEatom_listP(vector<string> s);
 void printState(state atVec);
 AtomicStmt atomic_statementP(vector<string> s);
 AtomicStmt::printAtomStmt();
 Condition goal_declarationP(vector<string> s);
 Condition::getLiterals(literalList a);
 vector<Action> action_setP(vector<string> s);
 vector<Action> NEaction_listP(vector<string> s);
 Action action_declarationP(vector<string> s);
 literalList literal_listP(vector<string> s);
 literalList NEliteral_listP(vector<string> s);
 Literal literalP(vector<string> s);
 Literal::printLiteral();
 
 
 bool STRIPS_program(vector<string> s);
 bool initial_state_declaration(vector<string> s)
 bool action_set(vector<string> s)
 bool NEaction_list(vector<string> s)
 bool action_declaration(vector<string> s);
 bool effects_declaration(vector<string> s);
 bool preconditions_declaration(vector<string> s);
 bool action_prototype(vector<string> s);
 bool goal_declaration(vector<string> s);
 bool literal_list(vector<string> s);
 bool NEliteral_list(vector<string> s);
 bool literal(vector<string> s);
 bool atom_list(vector<string> s);
 bool NEatom_list(vector<string> s);
 bool atomic_statement(vector<string> s);
 bool symbol_list(vector<string> s);
 bool NEsymbol_list(vector<string> s);
 bool symbol(vector<string> s);
 bool STRIPS_keyword(vector<string> s);
 
 vector<string> slice(const vector<string> &s, int loBound, int upBound);
 vector<std::string> tokenize(string s);
 
*/ 
 
/////// slicer function ///////////////////////////////////////////////////////////////
//vector<string> slice(const vector<string> &s, int loBound, int upBound)
//{
//    vector<string> sliced;
//    for (int i = static_cast<int>(loBound); i < static_cast<int>(upBound); i++)
//    {
//        sliced.push_back(s[i]);
//    }
//    return sliced;
//}

///////// foundational boolean functions
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//char STRIPS_keyword(const std::vector<std::string> &s)//s needs slicing before here
//{
//    if ( s.size() == 1 )
//        if (s[0] == "Initial" || s[0] == "state"
//            || s[0] == "Goal" || s[0] == "Actions"
//            || s[0] == "Preconditions" || s[0] == "Effects"
//            || s[0] == "not" || s[0] == "NOT" )
//            return 1;
//    return 0;
//}

//char NEsymbol_list(const std::vector<std::string> &s)
//{
//    if (s.size() == 1 && symbol(slice(s, 0, 1))) return 1;
//    else if (s.size() >= 3 && symbol(slice(s, 0, 1)) && s[1] == ",")
//        if ( NEsymbol_list(slice(s, 2, static_cast<int>(s.size()))) )return 1;
//    return 0;
//}

//char symbol_list(std::vector<std::string> &s)
//{
//    return (s.empty() || NEsymbol_list(s));
//}
//
//bool atomic_statement(vector<string> s)
//{
//    if (s.size() >= 4)
//        if ( symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")")
//            if (symbol_list(slice(s, 2, static_cast<int>(s.size() - 1))) )return true;
//    return false;
//}


bool NEatom_list(vector<string> s)
{
    if (atomic_statement(s)) return true;
    else
    {
        for (int i = 3; i < static_cast<int>(s.size() - 1); i++)
        {
            if (s[i] == ",")
                if (atomic_statement(slice(s, 0, i)) && NEatom_list(slice(s, i + 1, static_cast<int>(s.size()))) )return true;
        }
    }
    return false;
}

bool atom_list(vector<string> s)// I don't know if this will actually work
{
    if (s.empty() || NEatom_list(s))
        return true;
    return false;
}

/**********************************************************************************************
 *
 * AtomicStmt - functions
 *
 **********************************************************************************************/

AtomicStmt atomic_statementP(vector<string> s)
{
    AtomicStmt NewAtomicStmt;
    
    if(s.size() >= 4)
    {
        if (symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")")
        {
            NewAtomicStmt.relation = s[0];
            NewAtomicStmt.notEmpty = 1;
            
            if ( symbol_list(slice(s, 2, static_cast<int>(s.size() - 1))) ) //slices@s[2] & s.size()-2,noparens
                for (int i = 2; i < static_cast<int>(s.size() - 1); i++)
                {
                    if (s[i] == ",")
                        i++;
                    NewAtomicStmt.args.push_back(s[i]);
                }
        }
    }
   // else
       // NewAtomicStmt.notEmpty = 0;
    
    //NewAtomicStmt.printAtomStmt();
    return NewAtomicStmt;
}

state NEatom_listP(vector<string> s)
{
    state newAtomStmtVec;
    
    if (atomic_statement(s))
    {
        AtomicStmt NewAtomicStmt = atomic_statementP(s);
        newAtomStmtVec.push_back(NewAtomicStmt);
    }
    else
    {
        for (int i = 1; i < static_cast<int>(s.size() - 1); i++)
            if (s[i] == ",")
                if (atomic_statement(slice(s, 0, i)) && NEatom_list(slice(s, i + 1, static_cast<int>(s.size()))) )
                {
                    //cout << "recursion"<<endl;
                    AtomicStmt NewAtomicStmt = atomic_statementP(slice(s, 0, i));
                    newAtomStmtVec.push_back(NewAtomicStmt);
                    state NewAtomicStmtVec1 = NEatom_listP(slice(s, i + 1, static_cast<int>(s.size())));
                    newAtomStmtVec.insert(end(newAtomStmtVec), begin(NewAtomicStmtVec1), end(NewAtomicStmtVec1));//found on stackoverflow http://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
                }
    }
    return newAtomStmtVec;
}

state atom_listP(vector<string> s)
{
    vector<AtomicStmt> newAtomStmtVec;
    if (s.empty())
        return newAtomStmtVec;
    else
        return NEatom_listP(s);
}

void printState(state atVec)//helper
{
    for(int i = 0; i < static_cast<int>(atVec.size()); i++)//for
    {
        cout << atVec[i].AtomicStmt::relation <<endl;
        for(int j = 0; j < static_cast<int>(atVec[i].AtomicStmt::args.size()); j++)//args in vector<AtomicStmt>
            cout << atVec[i].AtomicStmt::args[j];
    }
    cout << endl;//this new line char is needed for printing all arguments
}

///////////////// Literal/Condition - intermediary boolean funct's //////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

bool literal(vector<string> s)// I don't know if this will actually work
{
    if (atomic_statement(s))return true;
    else if ( s.size() > 0 && (s[0] == "not" || s[0] == "NOT") && atomic_statement(slice(s, 1, static_cast<int>(s.size()))) )
        return true;
    return false;
}

bool NEliteral_list(vector<string> s) //might need adjustment in loop condition i <=
{
    if (literal(s))return true;
    else
        for (int i = 3; i < (s.size() - 1); i++) //literal > 3 tokens
            if (s[i] == ",")
                if (literal(slice(s, 0, i)) && NEliteral_list(slice(s, i + 1, static_cast<int>(s.size()))))return true;
    return false;
}

bool literal_list(vector<string> s)// I don't know if this will actually work
{
    if (s.empty() || NEliteral_list(s))
        return true;
    return false;
}

/**************************************************************************************************
 *
 * Literal
 *
 **************************************************************************************************/


Literal literalP(vector<string> s)
{
    Literal NewLiteral;
    
    if (atomic_statement(s))
    {
        NewLiteral.polarity = 1;
        NewLiteral.AtomStmt = atomic_statementP(s);
        NewLiteral.notEmpty = 1;
        
    }
    else if ( s.size() > 0 && (s[0] == "not" || s[0] == "NOT") && atomic_statement(slice(s, 1, static_cast<int>(s.size()))) )
    {
        NewLiteral.polarity = 0;
        NewLiteral.AtomStmt = atomic_statementP(slice(s, 1, static_cast<int>(s.size())));
        NewLiteral.notEmpty = 1;
    }
    else
        NewLiteral.notEmpty = 0;
    
    //NewLiteral.printLiteral();
    return NewLiteral;
}

literalList NEliteral_listP(vector<string> s) //might need adjustment in loop condition i <=
{
    literalList newLiteralList;
    
    if (literal(s))
        newLiteralList.push_back(literalP(s));
    else
        for (int i = 3; i < (s.size() - 1); i++)
            if (s[i] == ",")
                if (literal(slice(s, 0, i)) && NEliteral_list(slice(s, i + 1, static_cast<int>(s.size()))))
                {
                    newLiteralList.push_back(literalP(slice(s, 0, i)));//slices and pushes back
                    literalList newLiteralList1 = NEliteral_listP(slice(s, i + 1, static_cast<int>(s.size())));
                    newLiteralList.insert(end(newLiteralList), begin(newLiteralList1), end(newLiteralList1));//found on stackoverflow http://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
                }
    return newLiteralList;
}

literalList literal_listP(vector<string> s)
{
    literalList newLiteralList;
    if (s.empty())
        return newLiteralList;
    else
        return NEliteral_listP(s);
}

///////////////// intermediary boolean functions for Condition/goal declaration/
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
bool goal_declaration(vector<string> s) //NOTE: declaration on the Wikipedia's example is followed by "state"; here, it's not.
{
    if (s.size() >= 2)
        if ( s[0] == "Goal" && s[1] == ":" && literal_list(slice(s, 2, static_cast<int>(s.size()))) )return true;
    return false;
}
//////////////////////////////////////////////

/**************************************************************************************************
 *
 * Condition - ESSENCIAL
 *
 **************************************************************************************************/

Condition goal_declarationP(vector<string> s)
{
    Condition NewCondition;
    
    if (s.size() >= 2)
    {
        if ( s[0] == "Goal" && s[1] == ":" && literal_list(slice(s, 2, static_cast<int>(s.size()))) )
        {
            //cout << "\nGoal decl:\n";
            NewCondition.getLiterals( literal_listP( slice( s, 2, static_cast<int>(s.size()) ) ) );
        }
    }
    else
    {
        Condition NewCondition;//initalizes notEmpty to 0
    }
    return NewCondition;
}
///////////////// intermediary boolean functions for Action set//////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

bool action_prototype(vector<string> s)
{
    //for (int i = 1; i < s.size(); i++) //might need adjustment in loop condition i <=
    if (s[0] == "_" && s[s.size() - 1] == "_")
        if ( atomic_statement(slice(s, 1, static_cast<int>(s.size() - 1))) )return true;
    return false;
}
bool preconditions_declaration(vector<string> s)
{
    if (s.size()>1 && (s[0] == "Preconditions" && s[1] == ":"))
        if ( literal_list(slice(s, 2, static_cast<int>(s.size()))) )return true;
    return false;
}

bool effects_declaration(vector<string> s)
{
    if (s.size()>1 && (s[0] == "Effects" && s[1] == ":"))
        if ( literal_list(slice(s, 2, static_cast<int>(s.size()))) )return true;
    return false;
}

bool action_declaration(vector<string> s)
{
    if (s.size() >= 3)
    {
        for (int i = 4; i < static_cast<int>(s.size()); i++)
        {
            if (action_prototype(slice(s, 0, i)))
                for (int j = i+2; j < static_cast<int>(s.size()); j++) //they have to grow separatelly
                    if ( preconditions_declaration(slice(s, i, j)) && effects_declaration(slice(s, j, static_cast<int>(s.size()))) )return true;
        }
    }
    return false;
}

bool NEaction_list(vector<string> s) //might need adjustment in loop condition i <=
{
    if (s.size()> 0)
    {
        if (action_declaration(s))return true;
        else
        {
            for (int i = 8; i < static_cast<int>(s.size()); i++)//action declaration has at least 8 tokens
            {
                if ( action_declaration(slice(s, 0, i)) && NEaction_list(slice(s, i, static_cast<int>(s.size()))) )return true;
            }
        }
    }
    return false;
}

bool action_set(vector<string> s) //might need adjustment in loop condition i <=
{
    
    if (s.size() >= 3 && (s[0] == "Actions" && s[1] == ":"))
        if (NEaction_list(slice(s, 2, static_cast<int>(s.size()))))return true;
    return false;
}

/**************************************************************************************************
 *
 * Action - ESSENCIAL
 *
 **************************************************************************************************/

Action action_declarationP(vector<string> s)
{
    Action NewAction;
    
    if (s.size() >= 3)
    {
        for (int i = 5; i < static_cast<int>(s.size()); i++)//prototype has at least 5 tokens
            if (action_prototype(slice(s, 0, i)))
            {
                //cout << "\nAction: ";
                NewAction.notEmpty = 1;
                NewAction.label = atomic_statementP(slice(s, 1, i-1));
                for (int j = i; j < static_cast<int>(s.size()); j++)
                {
                    if ( preconditions_declaration(slice(s, i, j)) && effects_declaration(slice(s, j, static_cast<int>(s.size()))) )
                    {
                        //cout << "\nPreconditions:\n";
                        NewAction.preconditions.getLiterals( literal_listP(slice(s, i+2, j)));//i+2 so it skips "Prec..."
                        //cout << "\nEffects:\n";
                        NewAction.effects.getLiterals( literal_listP(slice(s, j+2, static_cast<int>(s.size()))));//j+2 so it skips "Eff..."
                    }
                }
            }
    }
    return NewAction;
}

vector<Action> NEaction_listP(vector<string> s)
{
    vector<Action> newActVec;
    
    if (s.size()> 0)
    {
        if (action_declaration(s))
        {
            newActVec.push_back(action_declarationP(slice(s,0,static_cast<int>(s.size()))));//saves action into vector
            //slice starts at 2 to skip "Actions:"
        }
        else
        {
            for (int i = 8; i < static_cast<int>(s.size()); i++) //action decl > 8 tokens
            {
                if ( action_declaration(slice(s, 0, i)) && NEaction_list(slice(s, i, static_cast<int>(s.size()))) )
                {
                    newActVec.push_back(action_declarationP(slice(s, 0, i)));//saves action into vector
                    vector<Action> newActVec1 = NEaction_listP(slice(s, i, static_cast<int>(s.size())));
                    newActVec.insert(end(newActVec), begin(newActVec1), end(newActVec1));//found on stackoverflow http://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
                }
            }
        }
    }
    return newActVec;
}

vector<Action> action_setP(vector<string> s)
{
    vector<Action> newActVec;
    if (s.size() >= 3 && (s[0] == "Actions" && s[1] == ":"))
        if (NEaction_list(slice(s, 2, static_cast<int>(s.size()))))
            newActVec = NEaction_listP(slice(s, 2, static_cast<int>(s.size())));
    return newActVec;
}

state initial_state_declarationP(vector<string> s)
{
    state newState;
    if (s.size() >= 3) // size >= 3 to avoid crashing when testing smaller parts
    {
        if (s[0] == "Initial" && s[1] == "state" && s[2] == ":" && atom_list(slice(s, 3, static_cast<int>(s.size()))))
        {
            newState = atom_listP(slice(s, 3, static_cast<int>(s.size())));
        }
    }
    return newState;
}
///////////////// intermediary boolean functions for STRIPS program //////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
bool initial_state_declaration(vector<string> s)
{
    if (s.size() >= 3) // size >= 3 to avoid crashing when testing smaller parts of the strips vector
        if (s[0] == "Initial" && s[1] == "state" && s[2] == ":" && atom_list(slice(s, 3, static_cast<int>(s.size()))))return true;
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************************************
 *
 * STRIPSInstance - ESSENCIAL
 *
 **************************************************************************************************/

bool STRIPS_program(vector<string> s)
{
    if (s.size() > 7) // minimum list: (0. "Initial", 1. "state", 2. ":", 3. "Goal",4. ":",5. "Actions",6. ":",7. NEaction_list)
    {
        int initStateEndIndex(0), goalDeclEndIndex(0);
        bool initStateTrue(0), goalDeclTrue(0);
        
        for (int i = 3; i < static_cast<int>(s.size() - 4); i++) //so avoids the minimum list for Goal & Actions
            if (initial_state_declaration(slice(s, 0, i)) && s[i] == "Goal") //i and NOT i+1 because slicing happens at i-1
            {
                initStateEndIndex = i;//it will evaluate to true before reaching
                initStateTrue = 1;
                break;
            }
        
        if (initStateTrue)
            for (int j = initStateEndIndex; j < static_cast<int>(s.size() - 2); j++) //s.size()-2 because "Actions",":",NEaction_list
                if (goal_declaration(slice(s, initStateEndIndex, j)))
                    if (s[j] == "Actions")
                    {
                        goalDeclEndIndex = j;
                        goalDeclTrue = 1;
                        break;
                    }
        
        if (initStateTrue  && goalDeclTrue)
            for (int z = goalDeclEndIndex; z < static_cast<int>(s.size()); z++)
                if (action_set(slice(s, z, static_cast<int16_t>(s.size()))))return true;
    }
    return false;
}

STRIPSInstance STRIPS_programP(vector<string> s)
{
    STRIPSInstance newSTRIPSInstance;
    
    if ( s.size() > 7 && STRIPS_program(s) )
    {
        // minimum list: (0. "Initial", 1. "state", 2. ":", 3. "Goal",4. ":",5. "Actions",6. ":",7. NEaction_list)
        int initStateEndIndex(0), goalDeclEndIndex(0);
        bool initStateTrue(0), goalDeclTrue(0);
        
        for (int i = 3; i < static_cast<int>(s.size() - 4); i++) //avoids minimum list for Goal & Actions, skips > initial
            if (initial_state_declaration(slice(s, 0, i)) && s[i] == "Goal") //i and NOT i+1 because slicing happens at i-1
            {
                newSTRIPSInstance.initialState = initial_state_declarationP(slice(s, 0, i));
                initStateEndIndex = i;//it will evaluate to true before reaching
                initStateTrue = 1;
                break;
            }
        
        if (initStateTrue)
        {
            for (int j = initStateEndIndex; j < static_cast<int>(s.size() - 2); j++) //s.size()-2 because "Actions",":",NEaction_list
                if (goal_declaration(slice(s, initStateEndIndex, j)))
                    if (s[j] == "Actions")
                    {
                        newSTRIPSInstance.goal = goal_declarationP(slice(s, initStateEndIndex, j));
                        goalDeclEndIndex = j;
                        goalDeclTrue = 1;
                        break;
                    }
        }
        
        if (initStateTrue  && goalDeclTrue)
        {
            for (int z = goalDeclEndIndex; z < static_cast<int>(s.size()); z++)
                if (action_set(slice(s, z, static_cast<int16_t>(s.size()))))
                    newSTRIPSInstance.actions = action_setP(slice(s, z, static_cast<int16_t>(s.size())));
            
            
        }
        newSTRIPSInstance.notEmpty = 1;
    }
    else
        cout<< "The input is not a STRIPS program.\n";
    return newSTRIPSInstance;
}

//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


//assignment 4
//include the set library
//include the algorithm library


vector<ConcreteAction> allActions()
{
    //used just here for building the concrete actions
    struct concActionType
    {
        string label;
        unsigned int arity;
        void printconcActionType()
        {
            cout << "concActionType: " << label << endl;
            cout << "arity: " << arity << endl;
        }
    };
    
    vector<concActionType> allConcActTypes;
    
    
    set<string> actIllegalArgs;
    //vector<string> concActTypes;
    
    set<string> actlegalArgs;
    
    set<string> actlegalArgUni;
    
    //getting action types and illegal action arguments (some illegal arguments will be put into actlegalArgs  set of strings
    for(int i = 0; i < static_cast<int>(I.actions.size());i++)
    {
        concActionType newConcActionType;
        
        newConcActionType.label = I.actions[i].label.relation;
        newConcActionType.arity = static_cast<int>(I.actions[i].label.args.size());
        
        if ( newConcActionType.arity > 1 )
        {
            for(int j = 0; j < static_cast<int>(I.actions[i].label.args.size()) ; j++)
                actIllegalArgs.insert(I.actions[i].label.args[j]);
            
            
            //getting arguments from preconditions - positive followed by negative
            for(int j = 0; j < static_cast<int>(I.actions[i].preconditions.positive.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].preconditions.positive[j].args.size()) ; k++)
                    actlegalArgs.insert(I.actions[i].preconditions.positive[j].args[k]);
            
            for(int j = 0; j < static_cast<int>(I.actions[i].preconditions.negative.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].preconditions.negative[j].args.size()) ; k++)
                    actlegalArgs.insert(I.actions[i].preconditions.negative[j].args[k]);
            
            //getting arguments from effects - positive followed by negative
            for(int j = 0; j < static_cast<int>(I.actions[i].effects.positive.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].effects.positive[j].args.size()) ; k++)
                    actlegalArgs.insert(I.actions[i].effects.positive[j].args[k]);
            
            for(int j = 0; j < static_cast<int>(I.actions[i].effects.negative.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].effects.negative[j].args.size()) ; k++)
                    actlegalArgs.insert(I.actions[i].effects.negative[j].args[k]);
            
            allConcActTypes.push_back(newConcActionType);
        }
        else
        {
            for(int j = 0; j < static_cast<int>(I.actions[i].label.args.size()) ; j++)
                actIllegalArgs.insert(I.actions[i].label.args[j]);
            
            
            //getting arguments from preconditions - positive followed by negative
            for(int j = 0; j < static_cast<int>(I.actions[i].preconditions.positive.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].preconditions.positive[j].args.size()) ; k++)
                    actlegalArgUni.insert(I.actions[i].preconditions.positive[j].args[k]);
            
            for(int j = 0; j < static_cast<int>(I.actions[i].preconditions.negative.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].preconditions.negative[j].args.size()) ; k++)
                    actlegalArgUni.insert(I.actions[i].preconditions.negative[j].args[k]);
            
            //getting arguments from effects - positive followed by negative
            for(int j = 0; j < static_cast<int>(I.actions[i].effects.positive.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].effects.positive[j].args.size()) ; k++)
                    actlegalArgUni.insert(I.actions[i].effects.positive[j].args[k]);
            
            for(int j = 0; j < static_cast<int>(I.actions[i].effects.negative.size()) ; j++)
                for(int k = 0; k < static_cast<int>(I.actions[i].effects.negative[j].args.size()) ; k++)
                    actlegalArgUni.insert(I.actions[i].effects.negative[j].args[k]);
            allConcActTypes.push_back(newConcActionType);
        }
        
    }
    
///////
    //getting the legal action arguments from Initial state
    for(int i = 0; i < static_cast<int>(I.initialState.size());i++)
        for(int j=0;j < static_cast<int>(I.initialState[i].args.size());j++)
            actlegalArgs.insert(I.initialState[i].args[j]);
////////
    // gets legal arguments from goal (positive
    for(int i = 0; i < static_cast<int>(I.goal.positive.size());i++)
        for(int j=0;j < static_cast<int>(I.goal.positive[i].args.size());j++) //for positive args
            if (!I.goal.positive[i].args[j].empty())
                actlegalArgs.insert(I.goal.positive[i].args[j]);
    
    //goal - legal negative args
    for(int i = 0; i < static_cast<int>(I.goal.negative.size());i++)
        for(int j=0;j < static_cast<int>(I.goal.negative[i].args.size());j++)
            if (!I.goal.negative[i].args[j].empty())
                actlegalArgs.insert(I.goal.negative[i].args[j]);
    
    

//prints possible actions
//    cout << "||||||||||||||||||||||||||||||||||||||||||||||||"<<endl << endl;
//    cout << "ConcreteActions Types: "<<endl;
//    for(int i = 0; i < static_cast<int>(allConcActTypes.size()); i++) {
//        cout << endl;
//        cout << i << ".";
//        allConcActTypes[i].printconcActionType();
//    }
    
    
    //find ilegal arguments in the set of legal arugments and delete them
    set<string>::iterator iter;
    for(iter = actIllegalArgs.begin(); iter != actIllegalArgs.end(); iter++)
    {
        auto search = actlegalArgs.find(*iter);
        if ( search != actlegalArgs.end() )
            actlegalArgs.erase(*search);
    }

    vector<string> legalActArgsVec; //saves set members to vector for easier permutation
    for(iter = actlegalArgs.begin(); iter != actlegalArgs.end(); iter++)
        legalActArgsVec.push_back(*iter);

    
    vector<ConcreteAction> newConcActVec;
    
    for(int i = 0; i < allConcActTypes.size();i++)
    {
        vector<vector<string>> allPossibleLegalArgsComb; //stores vectos of string with valid combinations of arguments
        
        do  //code adapted from http://stackoverflow.com/questions/17006808/find-all-permutations-of-a-string-in-c
        {
            vector<string> newLegalArgs;
            //vector<string>::iterator iter;
            
            for (int j=0; j < allConcActTypes[i].arity;j++) //keeps the right amount of arguments
                newLegalArgs.push_back(legalActArgsVec[j]);
            
            allPossibleLegalArgsComb.push_back(newLegalArgs); //saves back a vector of strings with appropriate arity for action[i]
        }
        while ( std::next_permutation(legalActArgsVec.begin(), legalActArgsVec.end()) );
        
        vector<vector<string>>::iterator it;
        
        //iterator for getting rid of duplicates
        it = unique(allPossibleLegalArgsComb.begin(),allPossibleLegalArgsComb.end());
            
        allPossibleLegalArgsComb.resize(std::distance(allPossibleLegalArgsComb.begin(),it)); //erasing remaining spaces related to duplicates
        

        for(int j = 0; j < allPossibleLegalArgsComb.size();j++) //saves args into concrete action struct
        {
            ConcreteAction newConcAction;
            
            newConcAction.actionType = allConcActTypes[i].label; //i runs through action labels
            
            for(int k = 0; k < allPossibleLegalArgsComb[j].size();k++)
            {
                newConcAction.arguments.push_back(allPossibleLegalArgsComb[j][k]);

            }
            newConcActVec.push_back(newConcAction);
        }
    }
    
    
//    cout << "--- ----- FINAL concrete actions  ---------  ---" << endl;
//    
//    for(int a = 0; a < newConcActVec.size(); a++)
//    {
//        cout << newConcActVec[a].actionType << endl;
//        for(int k = 0; k < static_cast<int>(newConcActVec[a].arguments.size()); k++)
//        {
//            cout << newConcActVec[a].arguments[k] << endl;
//        }
//        cout << endl;
//    }

    return newConcActVec;
}

//requires #include<set>
bool satisfies(state S, Condition C) //matches positive condition relations within state relations
//returns false if it finds a negative C relation within state S
{
    int posMatchesExpectedArgs(0);
    int posMatchesFoundArgs(0);
    
    
    for(int i = 0; i < S.size(); i++ )
        for(int j=0; j < C.negative.size(); j++) //looking for negative matches
            if ( S[i].relation == C.negative[j].relation )
                return false;
    
    for(int i = 0; i < S.size(); i++ )
        for(int j=0; j < C.positive.size(); j++)
            if( S[i].relation == C.positive[j].relation)
                for(int a = 0; a < S[i].args.size(); a++)
                    for( int k = 0; k < C.positive[j].args.size(); k++)
                    {   posMatchesExpectedArgs++;
                        
                        if ( S[i].args[a] == C.positive[j].args[k]) posMatchesFoundArgs++;
                    }
    return ( posMatchesExpectedArgs == posMatchesFoundArgs );
}

Action substitute(vector<string> args, Action A)
{
    int actionArity( static_cast<int>(A.label.args.size()) );//saves the no. of arguments in the Action
    vector<string> varActionArgs = A.label.args; //saves the variable arguments
    
    if ( args.size() == actionArity)
        for(int i=0; i < varActionArgs.size();i++)//looks for variables matching the label ones within other parts of the action and replaces them
        {
            replace(A.label.args.begin(),A.label.args.end(),varActionArgs[i],args[i]);
            
            for(int j=0; j < A.preconditions.positive.size(); j++)//replaces positive precon with the appropriate args
                replace(A.preconditions.positive[j].args.begin(),A.preconditions.positive[j].args.end(),varActionArgs[i],args[i]);
            
            for(int j=0; j < A.preconditions.negative.size(); j++)//replaces negative precon with the appropriate args
                replace(A.preconditions.negative[j].args.begin(),A.preconditions.negative[j].args.end(),varActionArgs[i],args[i]);
            
            for(int j=0; j < A.effects.positive.size(); j++)//replaces positive eff args with the input args
                replace(A.effects.positive[j].args.begin(),A.effects.positive[j].args.end(),varActionArgs[i],args[i]);
            
            for(int j=0; j < A.effects.negative.size(); j++)//replaces negative eff args with the input args
                replace(A.effects.negative[j].args.begin(),A.effects.negative[j].args.end(),varActionArgs[i],args[i]);
        }
    return A;
}

bool possible(ConcreteAction c,state S) //matches preconditions with state - still spills the wrong combinations of vectors from allAction
{
    for(int i=0; i < I.actions.size(); i++)//compares concrete action label to labels in the STRIPS instance
        if ( I.actions[i].label.relation == c.actionType ) // retrieves preconditions and matches them to those present in the state
        {
//            I.actions[i].printAction();
//            c.printConcreteAction();
            return ( satisfies(S, substitute(c.arguments, I.actions[i]).preconditions) ); //matches positive condition's relations
            // within state relations (real arguments included)
        }
    return false;
}

state result(ConcreteAction c,state S)
{
    Action newAction;
    //substitute(c.arguments,newAction);
    if (possible(c,S))
    {
        for(int i=0; i < I.actions.size(); i++)//compares concrete action label to labels in the STRIPS instance
            if ( I.actions[i].label.relation == c.actionType ) // retrieves preconditions and matches them to those present in the state
            {
                newAction = substitute(c.arguments, I.actions[i]);
                break;
            }
        for(int j=0; j < S.size(); j++)//replaces positive eff args with the input args
            for(int k=0; k < newAction.effects.positive.size(); k++)//replaces positive eff args with the input args
                if ( S[j].relation == newAction.effects.positive[k].relation)
                    S[j].args = newAction.effects.positive[k].args;
    }
    return S;
}

vector<state> Successors(state S)
{
    vector<state> successors;

    vector<ConcreteAction> allPossibleActions = allActions();
    for(int i = 0; i < allPossibleActions.size(); i++)
        successors.push_back( result(allPossibleActions[i],S) );
    return successors;
}

//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
//******************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

//assingment 5
//add

bool Green(node N)
{
    return(satisfies(N.destination, I.goal));
}


vector<node> children(node N)
{
    state d = N.destination;
    vector<ConcreteAction> p = N.path;
    
    vector<node> childList;
    vector<ConcreteAction> statePossActs = statePossibleActions(d);
    
    //    For each concrete action a that is possible in state d:
    
    for(int i=0; i < statePossActs.size(); i++)
    {
        ConcreteAction possAct = statePossActs[i];
        node n;
        n.path.assign(p.begin(), p.end());
        n.path.push_back(possAct);
        n.destination = result(possAct,d);
        
        childList.push_back(n);
    }
    
    return childList;
}

vector<ConcreteAction> statePossibleActions(state d)
{
    vector<ConcreteAction> allPossConcAct;
    vector<ConcreteAction> allConcAct = allActions();
    for(int i = 0; i < allConcAct.size(); i++ )
        if (possible(allConcAct[i], d))
            allPossConcAct.push_back(allConcAct[i]);
    return allPossConcAct;
}

node search(vector<node> N)
{
    vector<node> open;
    open.assign(N.begin(),N.end());
    
    while(!open.empty())
    {
        node X = open[0];
        if ( Green(X) ) return X;
        children(X);
        vector<node> tail;
        vector<node> kids = children(X);
        
        for(int i=1; i< open.size(); i++)
            tail.push_back(open[i]); //the tail; 0 is the head
        
        open.assign(tail.begin(),tail.end());
        
        for(int i=0; i < kids.size(); i++) //after the tail
            open.push_back(kids[i]);
        search(open);
    }
    return N[0];
}
node makeNode(state S, vector<ConcreteAction> X)
{
    node newNode;
    newNode.destination = S;
    newNode.path = X;
    return newNode;
}

vector<ConcreteAction> solve(string S)
{
    vector<ConcreteAction> solutionPath;
    
    vector<string> fullText = tokenize(S);
    I = STRIPS_programP(fullText);
    
    node root;
    
    state goalFound = I.initialState;
    
    
    vector<node> childrenTotal;
    vector<node> childrenInit = children(root);
    
    root.destination = I.initialState;
    
    while( !satisfies(goalFound,I.goal ) )
    {
        vector<state> newState = Successors(goalFound);
        for(int i=0; i < newState.size(); i++)
        {
            node newNode;
            newNode.destination=newState[i];
            childrenInit.push_back(newNode);
            goalFound = newState[i];
            if (satisfies(goalFound,I.goal ))
                break;
        }
        cout << "error"<<endl;
    }
    
    //for(int i = 0; i < childrenInit.size(); i++)
    solutionPath = search(childrenInit).path;
    
    return solutionPath;
}

