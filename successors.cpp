//assignment 4
//include the set library
//include the algorithm library
//written by Alexandre Soares da Silva, CompE student at Texas Tech University
//Date: 8 May 2017
//Data Structes CS 2413
#include <set>
#include <algorithm>

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
    
    //getting action types and illegal action arguments (some illegal arguments will be put into actlegalArgs  set of strings
    for(int i = 0; i < static_cast<int>(I.actions.size());i++)
    {
        concActionType newConcActionType;
        
        newConcActionType.label = I.actions[i].label.relation;
        newConcActionType.arity = static_cast<int>(I.actions[i].label.args.size());
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
        for(int j=0; j < C.positive.size(); j++)
            if( S[i].relation == C.positive[j].relation)
                for(int a = 0; a < S[i].args.size(); a++)
                    for( int k = 0; k < C.positive[j].args.size(); k++)
                    {
                        posMatchesExpectedArgs++;
                        if ( S[i].args[a] == C.positive[j].args[k])
                            posMatchesFoundArgs++;
                    }
    
    for(int i = 0; i < S.size(); i++ )
        for(int j=0; j < C.negative.size(); j++) //looking for negative matches
            if ( S[i].relation == C.negative[j].relation )
                return false;
    
    return ( posMatchesExpectedArgs == posMatchesFoundArgs );
}



Action substitute(vector<string> args, Action A)
{
    int actionArity( static_cast<int>(A.label.args.size()) );//saves the no. of arguments in the Action
    vector<string> varActionArgs = A.label.args; //saves the variable arguments
    
    if ( args.size() == actionArity)
        for(int i=0; i < varActionArgs.size();i++)//looks for variables matching the label ones within other parts of the action and replaces them
        {
            //vector<string>::iterator it;
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
    //c.printConcreteAction();
    for(int i=0; i < I.actions.size(); i++)//compares concrete action label to labels in the STRIPS instance
        if ( I.actions[i].label.relation == c.actionType ) // retrieves preconditions and matches them to those present in the state
        {
            
            return ( satisfies(S, substitute(c.arguments, I.actions[i]).preconditions) ); //matches positive condition relations within state relations (real arguments included)
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
