/* Based on assignment for the 2017 spring data structures class at Texas Tech University,
 * taught by Dr. Rushton (CS dept).
 * Written by: Alexandre Soares
 * Date: 28 December 2017
 * Description:
 * This code tokenizes a STRIPS planner such as
 * string STRIPS_plannerFullText = "Initial state: At(A), Level(low), BoxAt(C), BananasAt(B)\nGoal:    Have(bananas)\nActions:\n// move from X to Y\n_Move(X, Y)_\nPreconditions:  At(X), Level(low)\nEffects: not At(X), At(Y)\n// climb up on the box\nClimbUp(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions:  At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n// take the bananas\n_TakeBananas(Location)_\nPreconditions:  At(Location), BananasAt(Location), Level(high)\nEffects: Have(bananas)";
 * turning the previous string into
 * const vector<string> fullText= {"Initial","state",":","At","(","A",")",",","Level","(","low",")",",","BoxAt","(","C",")",",","BananasAt","(","B",")","Goal",":","Have","(","bananas",")","Actions",":","_","Move","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","Level","(","low",")","Effects",":","not","At","(","X",")",",","At","(","Y",")","_","ClimbUp","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","low",")","Effects",":","Level","(","high",")",",","not","Level","(","low",")","_","ClimbDown","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BoxAt","(","Location",")",",","Level","(","high",")","Effects",":","Level","(","low",")",",","not","Level","(","high",")","_","MoveBox","(","X",",","Y",")","_","Preconditions",":","At","(","X",")",",","BoxAt","(","X",")",",","Level","(","low",")","Effects",":","BoxAt","(","Y",")",",","not","BoxAt","(","X",")",",","At","(","Y",")",",","not","At","(","X",")","_","TakeBananas","(","Location",")","_","Preconditions",":","At","(","Location",")",",","BananasAt","(","Location",")",",","Level","(","high",")","Effects",":","Have","(","bananas",")"};
 *
 *
 *
//example of STRIPS planner mildly modified ("Goal:" instead of "Goal state:")
 * from Wikipedia (copy it to a text file)
 * /////////////////////////////////////////////////////////////////////////////////

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

 ///////////////////////////////////////////////////////////////////////////////*/

#ifndef _STRIPS_tokenizer_h
#define _STRIPS_tokenizer_h
//only adds libraries if they haven't been added yet
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

using std::vector;
using std::string;
using std::endl;
using std::cin;
using std::cout;

class STRIPS_tokenizer {
public:
	STRIPS_tokenizer();
	STRIPS_tokenizer(const string &fileNameAndPath);
	~STRIPS_tokenizer();

	string get_cppstring_fullText();
	void set_cppstring_fullText(const string& full_STRIPS_planner_ext);
	void load_preset_STRIPS_planner_fullText();

	vector<string> getVectStrg_Tokenized_STRIPS();

	void print_cppstring_fullText();//prints from vector saved within the object
	void print_Vector_of_strg();//prints from the object's vector
	void print_Vector_of_strg(const vector<string> &vectStr); //prints strings from argument vector

	//char * getCstring_fullText_();
private:
	string cppstring_fullText; //STRIPS text from file saved here (no changes yet)
	vector<string> tokenized_STRIPS; //where tokens are saved for parsing

	void askForFileNameAndExtractTextFromFile(); //asks for path and retrieves string from file
	void saveFileToString(const string& fileName);
	void tokenize();
	void tokenize(const string &s);
	void saveNewTokenIntoTokensVec(string &token, vector<string> &tokens); //helper for the tokenize function


	void skipComment(const string &s, uint32_t &position);
	void skipWhiteSpace(const string &s, uint32_t &position);
	bool isSpecialToken(const char &special); //boolean test
	bool isWhiteSpace(const char  &whiteSp); //boolean test
	bool hasCommentBegun(const char &commentBeginning);

	//char * cstring_fullText; //c-string holding the new text

								 //string * tokenized_STRIPS_ptr;

};

#endif /* tokenizer_h */
