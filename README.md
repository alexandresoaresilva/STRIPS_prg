# STRIPS_prg
This personal project is based on assignment for the 2017 spring data structures class at Texas Tech University, taught by Dr. Rushton (CS dept).
 Written by: Alexandre Soares
 Date: 28 December 2017
 
 Description:
 This code tokenizes a STRIPS planner such as
 string STRIPS_plannerFullText = "Initial state: At(A), Level(low), BoxAt(C), BananasAt(B)\nGoal:    Have(bananas)\nActions:\n// move from X to Y\n_Move(X, Y)_\nPreconditions:  At(X), Level(low)\nEffects: not At(X), At(Y)\n// climb up on the box\nClimbUp(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions:  At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n// take the bananas\n_TakeBananas(Location)_\nPreconditions:  At(Location), BananasAt(Location), Level(high)\nEffects: Have(bananas)";
 
 turning the previous string into:
 const vector<string> fullText= {"Initial","state",":","At","(","A",")",",","Level","(","low",")",",","BoxAt","(","C",")",",","BananasAt","(","B",")","Goal",":","Have","(","bananas",")","Actions",":","_","Move","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","Level","(","low",")","Effects",":","not","At","(","X",")",",","At","(","Y",")","_","ClimbUp","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","low",")","Effects",":","Level","(","high",")",",","not","Level","(","low",")","_","ClimbDown","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","high",")","Effects",":","Level","(","low",")",",","not","Level","(","high",")","_","MoveBox","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","BoxAt","(","X",")",",","Level","(","low",")","Effects",":","BoxAt","(","Y",")",",","not","BoxAt","(","X",")",",","At","(","Y",")",",","not","At","(","X",")","_","TakeBananas","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BananasAt","(","Location",")",",","Level","(","high",")","Effects",":","Have","(","bananas",")"};
 
 
 To test it, copy into a txt file the slightly modified STRIPS planner text below. It was copied from the Wikipedia article about STRIPS planner, with the modification "Goal:" instead of "Goal state:".
 
 /////////////////////////////////////////////////////////////////////////////////////////////////////////

Initial state: Place(A), Level(low), BoxAt(C), BananasAt(B)

Goal:    Have(bananas)

Actions:

// move from X to Y
_Move(X, Y)_
Preconditions:  Place(X), Level(low)
Effects: not Place(X), Place(Y)

// climb up on the box
_ClimbUp(Location)_
Preconditions:  Place(Location), BoxAt(Location), Level(low)
Effects: Level(high), not Level(low)

// climb down from the box
_ClimbDown(Location)_
Preconditions:  Place(Location), BoxAt(Location), Level(high)
Effects: Level(low), not Level(high)

// move monkey and box from X to Y
_MoveBox(X, Y)_
Preconditions:  Place(X), BoxAt(X), Level(low)
Effects: BoxAt(Y), not BoxAt(X), Place(Y), not Place(X)

// take the bananas
_TakeBananas(Location)_
Preconditions:  Place(Location), BananasAt(Location), Level(high)
Effects: Have(bananas)

 /////////////////////////////////////////////////////////////////////////////////////////////////////////
