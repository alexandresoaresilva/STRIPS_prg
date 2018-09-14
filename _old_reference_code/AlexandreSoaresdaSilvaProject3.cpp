///////////////////////////////////////////////////////////////////////////////////////////////////
//      /* STRIPS_programP */
// does: builds the struct corresponding to a STRIPSInstance
// from a vector<string> tokens; tokens being strings form a STRIPS program
//
//   ********** STRIPSInstance STRIPS_programP(vector<string> s) **************
//  The function STRIPS_programP(vector<string> s) appears last on this document
//
// Written by: Alexandre Soares da Silva
// Date: April 6, 2017
// Submitted as assignment 3's solution for Dr. Rushton's  CS 2413 - Data Structures class
// (Texas Tech University)
//
////////////////////////////////////////////////////////////////////////////////////////////////////
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
/////// tokenizer ///////////////////////////////////////////////////////////////////////
/////// slicer function ///////////////////////////////////////////////////////////////
vector<string> slice(const vector<string> &s,uint32_t loBound, uint32_t upBound) {
    vector<string> sliced;

    for (uint32_t i = loBound; i < upBound; i++)
        sliced.push_back(s[i]);

    return sliced;
}

///////// foundational boolean functions
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
bool STRIPS_keyword(vector<string> s) { //s needs to be sliced to be used in here
        return (
            !s.empty()
            && (s.size() == 1)
                && ( s[0] == "Initial"
                    || s[0] == "state"
                    || s[0] == "Goal"
                    || s[0] == "Actions"
                    || s[0] == "Preconditions"
                    || s[0] == "Effects"
                    || s[0] == "not"
                    || s[0] == "NOT"
                )
            ) //end of return
}

bool symbol(vector<string> &s) {
    return( !s.empty()
            && ( s.size() == 1)
            && !STRIPS_keyword(s)
        ); //end of return
}

bool NEsymbol_list(vector<string> &s) {
    if (s.size() == 1 && symbol(slice(s, 0, 1)))
        return true;
    else if (s.size() >= 3 && symbol(slice(s, 0, 1)) && s[1] == ",")
        if ( NEsymbol_list(slice(s, 2, s.size())) )
            return true;
    return false;
}

bool symbol_list(vector<string> s) {
    return ( s.empty() || NEsymbol_list(s));
}

bool atomic_statement(vector<string> s) {
    if (s.size() >= 4)
        if ( symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")")
            if (symbol_list(slice(s, 2, static_cast<int>(s.size() - 1))) )return true;
    return false;
}


bool NEatom_list(vector<string> s) {
    if (atomic_statement(s)) return true;
    else {
        for (uint32_t i = 3; i < (s.size() - 1); i++)
        {
            if (s[i] == ",")
                if (atomic_statement(slice(s, 0, i)) && NEatom_list(slice(s, i + 1, static_cast<int>(s.size()))) )return true;
        }
    }
    return false;
}

bool atom_list(vector<string> s) { // I don't know if this will actually work
    if (s.empty() || NEatom_list(s))
        return true;
    return false;
}

/**********************************************************************************************
 *
 * AtomicStmt - ESSENCIAL
 *
 **********************************************************************************************/
struct AtomicStmt {
    AtomicStmt(){notEmpty=0;}
    string relation;
    vector<string> args;
    bool notEmpty; //if 1, it's NOT empty
    void printAtomStmt() {
        if (notEmpty == 1) {
            cout << endl << "atomSt = " << relation << endl;
            for (uint16_t i = 0; i < args.size(); i++)
                cout << "args = " << args[i] << endl;
        }
    }
};

AtomicStmt atomic_statementP(vector<string> s) {
    AtomicStmt NewAtomicStmt;

    if(s.size() >= 4) {
        if (symbol(slice(s, 0, 1)) && s[1] == "(" && s[s.size() - 1] == ")") {
            NewAtomicStmt.relation = s[0];
            NewAtomicStmt.notEmpty = 1;

            if ( symbol_list(slice(s, 2, (s.size() - 1))) ) //slices@s[2] & s.size()-2,noparens
                for (uint32_t i = 2; i < (s.size() - 1); i++) {
                    if (s[i] == ",")
                        i++;
                    NewAtomicStmt.args.push_back(s[i]);
                }
        }
    }
    else
        NewAtomicStmt.notEmpty = 0;

    //NewAtomicStmt.printAtomStmt();
    return NewAtomicStmt;
}

typedef vector<AtomicStmt> state;

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
        for (uint32_t i = 1; i < ( s.size() - 1); i++)
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
    for(uint32_t i = 0; i < atVec.size(); i++)//for
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
        for (uint32_t i = 3; i < (s.size() - 1); i++) //literal > 3 tokens
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
        for (uint32_t i = 3; i < (s.size() - 1); i++)
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

struct Condition //member functions' definitions within the strcut
{
    vector<AtomicStmt> negative; //NEliteral_list with s[0] == "not"
    vector<AtomicStmt> positive; // NEatom_list without not
    bool notEmpty; //1 if NOT empty
    void getLiterals(literalList a)
    {
        notEmpty = 1;
        for (uint32_t i = 0; i < a.size(); i++ )
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
        for (uint32_t i = 4; i < s.size(); i++)
        {
            if (action_prototype(slice(s, 0, i)))
                for (uint32_t j = i+2; j < s.size(); j++) //they have to grow separatelly
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
            for (uint32_t i = 8; i < s.size(); i++)//action declaration has at least 8 tokens
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

struct Action
{
    AtomicStmt label;
    Condition preconditions;
    Condition effects;
    bool notEmpty;
    Action(){notEmpty=0;}//default constructor
};

Action action_declarationP(vector<string> s)
{
    Action NewAction;

    if (s.size() >= 3)
    {
        for (uint32_t i = 5; i < s.size(); i++)//prototype has at least 5 tokens
            if (action_prototype(slice(s, 0, i)))
            {
                //cout << "\nAction: ";
                NewAction.notEmpty = 1;
                NewAction.label = atomic_statementP(slice(s, 1, i-1));
                for (uint32_t j = i; j < s.size(); j++)
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
            for (uint32_t i = 8; i < s.size(); i++) //action decl > 8 tokens
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
            for (uint32_t i = 0; i < initialState.size();i++)//prints AtomicStmt
                initialState[i].AtomicStmt::printAtomStmt();

            cout<<"\n   GOAL:   \n";
            for (uint32_t i = 0; i < goal.positive.size();i++)//prints AtomicStmt
            {
                //cout << "POSITIVE condition:\n";
                goal.positive[i].AtomicStmt::printAtomStmt();
            }
            cout << endl;
            for (uint32_t i = 0; i < goal.negative.size();i++)//prints AtomicStmt
            {
                cout << "\nNOT";
                goal.negative[i].AtomicStmt::printAtomStmt();
            }

            cout << "\n     ACTIONS:    \n";
            for (uint32_t i = 0; i < actions.size(); i++)
            {
                cout<<"\n>>>> Action "<<i<<" <<<<\n";
                actions[i].label.printAtomStmt();
                cout << "\n>> Preconditions:\n";
                for (uint32_t j = 0; j< actions[i].preconditions.positive.size() ;j++)
                {
                    //cout << "\npositive";
                    actions[i].preconditions.positive[j].AtomicStmt::printAtomStmt();
                }
                for (uint32_t j = 0; j< actions[i].preconditions.negative.size() ;j++)
                {
                    cout << "\nNOT";
                    actions[i].preconditions.negative[j].AtomicStmt::printAtomStmt();
                }
                cout <<"\n>> Effects:\n";
                for (uint32_t j = 0; j< actions[i].effects.positive.size() ;j++)
                {
                    //cout << "positive:\n";
                    actions[i].effects.positive[j].AtomicStmt::printAtomStmt();
                }
                for (uint32_t j = 0; j< actions[i].effects.negative.size() ;j++)
                {
                    cout << "\nNOT";
                    actions[i].effects.negative[j].AtomicStmt::printAtomStmt();
                }
            }
        }

    }//END of print function
    STRIPSInstance(){notEmpty=0;}//default constructor
};
bool STRIPS_program(vector<string> s)
{
    if (s.size() > 7) // minimum list: (0. "Initial", 1. "state", 2. ":", 3. "Goal",4. ":",5. "Actions",6. ":",7. NEaction_list)
    {
        int initStateEndIndex(0), goalDeclEndIndex(0);
        bool initStateTrue(0), goalDeclTrue(0);

        for (uint32_t i = 3; i < (s.size() - 4); i++) //so avoids the minimum list for Goal & Actions
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

        for (uint32_t i = 3; i < (s.size() - 4); i++) //avoids minimum list for Goal & Actions, skips > initial
            if (initial_state_declaration(slice(s, 0, i)) && s[i] == "Goal") //i and NOT i+1 because slicing happens at i-1
            {
                newSTRIPSInstance.initialState = initial_state_declarationP(slice(s, 0, i));
                initStateEndIndex = i;//it will evaluate to true before reaching
                initStateTrue = 1;
                break;
            }

        if (initStateTrue)
        {
            for (uint32_t j = initStateEndIndex; j < (s.size() - 2); j++) //s.size()-2 because "Actions",":",NEaction_list
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
            for (uint32_t z = goalDeclEndIndex; z < static_cast<int>(s.size()); z++)
                if (action_set(slice(s, z, static_cast<int16_t>(s.size()))))
                    newSTRIPSInstance.actions = action_setP(slice(s, z, static_cast<int16_t>(s.size())));


        }
        newSTRIPSInstance.notEmpty = 1;
    }
    else
        cout<< "The input is not a STRIPS program.\n";
    return newSTRIPSInstance;
}
