//assignment 5
//include the set library
//include the algorithm library
//written by Alexandre Soares da Silva, CompE student at Texas Tech University
//Date: 9 May 2017
//Data Structes CS 2413
//doesn't work properly

#include <set>
#include <algorithm>



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

