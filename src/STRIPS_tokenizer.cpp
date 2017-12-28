#include "STRIPS_tokenizer.h"

/* Default Constructor
 * 1. asks for file name where STRIPS planner's text is saved
 * 2. saves the full text into member variable string cppstring_fullText
 * 3. tokenizes the STRIPS planner
 * 4. Shrinks vector to size()
 * 5. prints the strings in the member variable vector<string> tokenized_STRIPS
 */
STRIPS_tokenizer::STRIPS_tokenizer() : cppstring_fullText(""){
//    cstring_fullText = nullptr;
    askForFileNameAndExtractTextFromFile();
    tokenize(); //overloaded version which loads string saved in
    // the member variable cppstring_fullText
    print_Vector_of_strg();
    tokenized_STRIPS.shrink_to_fit(); //shrinks to size
};

/* Constructor 2
 * 1. argument fileName for saving the STRIPS planner text into
 * member variable cppstring_fullText
 * 2. tokenizes the STRIPS planner
 * 3. Shrinks vector to size()
 * 4. prints the strings in the member variable vector<string> tokenized_STRIPS
 */
STRIPS_tokenizer::STRIPS_tokenizer(const string &fileName)  : cppstring_fullText(""){
//    cstring_fullText = nullptr;
    saveFileToString(fileName);

    tokenize(); //overloaded version which loads string saved in
    // the member variable cppstring_fullText
    tokenized_STRIPS.shrink_to_fit(); //shrinks to size
    print_Vector_of_strg();
}

/* Destructor
 * when there's a point in the object, this will delete it
 */
STRIPS_tokenizer::~STRIPS_tokenizer(){
//    if ( this-> cstring_fullText != NULL )
//        delete this->cstring_fullText;
}

/* ::askForFileNameAndExtractTextFromFile()
 * gets from user input the STRIPS planner text's file name
 * saves it into this object's member variable cppstring_fullText
 * prints retrieved texts
 */
void STRIPS_tokenizer::askForFileNameAndExtractTextFromFile(){
	cout << endl;
    cout << "STRIPS tokenizer\n";
    cout << "Enter STRIPS planner text's file name:\n";
    string fileName = "";
    getline(cin,fileName);
    saveFileToString(fileName);
}


/* ::saveFileToString
 * 1. attempts to open a text file with full text of the
 * STRIPS planner and saves it into the object's string
 * member variable cppstring_fullText
 * 2. prints the saved text
 */
void STRIPS_tokenizer::saveFileToString(const string& fileName) {
	std::ifstream openFile(fileName, std::ios::in);
    if ( openFile.fail()) {
        string message = "could not open " + fileName;
        cout << message  << endl;
    }
    else{
        string wholeText((std::istreambuf_iterator<char>(openFile)), std::istreambuf_iterator<char>());
    	openFile.close();
    	set_cppstring_fullText(wholeText);
    	print_cppstring_fullText();
    }
}//gets text form file

/* ::get_cppstring_fullText()
 * returns this object's string member variable that
 * tholds the STRIPS planner's full text
 */
string STRIPS_tokenizer::get_cppstring_fullText() {
	return cppstring_fullText;
}

/* ::tokenize(const string &s)
 * gets tokens (c++ strings) from argument
 * and tokenizes it
 */
void STRIPS_tokenizer::tokenize(const string &s) {
    string token;
    vector<string> tokens;
    char dummy; //for saving individual chars from string
    uint32_t string_size = s.size();
    for (uint32_t i = 0; i < string_size; ++i) {

    	dummy = s[i]; // when push_back is used later on in this function,
    	//only this char is pushed and not the whole remaining text

    	//patterns recognized here are right before a new token or right after a previous token
        if ( hasCommentBegun(s[i]) || isSpecialToken(s[i]) || isWhiteSpace(s[i]) ) {

        	//pushes back string token into vector (after pattern is over)
        	//token must != empty for the push back to work
        	saveNewTokenIntoTokensVec(token,tokens);

			if ( hasCommentBegun(s[i]) ) { //skips comments
				if ( i < (string_size-1) ) //safe index for function skip comment
					skipComment(s,i);
			}
			else if (isWhiteSpace(s[i])) { //skips white spaces
				if ( i < (string_size-1) ) //safe index for function skip white space
					skipWhiteSpace(s,i);
			}
			else if (isSpecialToken(s[i])) { //saves special chars
				token = token + dummy; //conversion to string from char
		     	saveNewTokenIntoTokensVec(token,tokens);
			}
        }
        else //if dummy != any of the above, appends char to token
        	token = token + dummy;
    }
    tokenized_STRIPS = tokens;
}

/* ::tokenize()
 * overloaded version of the previous function
 * calls the previous function with this object's
 * string member cppstring_fullText as argument
 */
void STRIPS_tokenizer::tokenize() {
	tokenize(cppstring_fullText);
}

bool STRIPS_tokenizer::isSpecialToken(const char &special) {
    switch (special){
        case ':':
        case ',':
        case '_':
        case '(':
        case ')':
            return 1;
        default:
            return 0;
    }
}

bool STRIPS_tokenizer::isWhiteSpace(const char &whiteSp) {
    //if ( ( whiteSp >= 9 && whiteSp <= 14 ) || whiteSp == 32 ||  whiteSp == '\0' )
    if ( ( whiteSp >= 9 && whiteSp <= 14 ) || whiteSp == 32 )
        return 1;
    return 0;
}

bool STRIPS_tokenizer::hasCommentBegun(const char &commentBeginning) { // @suppress("No return")
    return (commentBeginning == '/');
}

void STRIPS_tokenizer::skipComment(const string &s, uint32_t &position) {
    //tests the next char because the for loop will i increment again
        // while ((s[position + 1] != '\n') && (s[position + 1] != '\r') && (s[position + 1] != '\0'))
        while ((s[position + 1] != '\n') && (s[position + 1] != '\r') )
            position++;
}

void STRIPS_tokenizer::skipWhiteSpace(const string &s, uint32_t &position) {
    //tests the next char because the for loop will i increment again after this run and the char will be skipped
    while ( ( s[position + 1] >= 9 && s[position + 1] <= 14 ) || s[position + 1] == 32 )
        position++;
}

void STRIPS_tokenizer::saveNewTokenIntoTokensVec(string &token, vector<string> &tokens) {
	if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
    }
}

void STRIPS_tokenizer::set_cppstring_fullText(const string& full_STRIPS_planner_ext){
	cppstring_fullText = full_STRIPS_planner_ext;
}

/* ::load_preset_STRIPS_planner_fullText()
 * loads the saved STRIPS planner (slightly modified from https://en.wikipedia.org/wiki/STRIPS
 *  to have "Goal:" instead of "Goal state:"
 * the STRIPS planner's full text
 */
void STRIPS_tokenizer::load_preset_STRIPS_planner_fullText(){
	string full_STRIPS_planner_ext = "Initial state: At(A), Level(low), BoxAt(C), BananasAt(B)\nGoal:    Have(bananas)\nActions:\n// move from X to Y\n_Move(X, Y)_\nPreconditions:  At(X), Level(low)\nEffects: not At(X), At(Y)\n// climb up on the box\nClimbUp(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions:  At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n// take the bananas\n_TakeBananas(Location)_\nPreconditions:  At(Location), BananasAt(Location), Level(high)\nEffects: Have(bananas)";
	set_cppstring_fullText(full_STRIPS_planner_ext);
}

/*
 * to be added later
 */
// char * STRIPS_tokenizer::getCstring_fullText_(){
//     return this->cstring_fullText;
// }

/* ::getVectStrg_Tokenized_STRIPS()
 * returns vector of strings with STRIPS planner tokens
 */
vector<string> STRIPS_tokenizer::getVectStrg_Tokenized_STRIPS() {
	return tokenized_STRIPS;
}

/* ::print_cppstring_fullText()
 * Prints the string member variable that contains
 * the STRIPS planner's full text
 */
void STRIPS_tokenizer::print_cppstring_fullText() {
	if ( cppstring_fullText != "" ) {
		cout << "Full extracted STRIPS planner from file "<< endl;
		cout << this->cppstring_fullText << endl;
	}
}

/* ::print_Vector_of_strg()
 * Prints the strings contained in the class member vector of strings with the tokenized
 * STRIPS planner. The strings are printed with angular brackets around it:
 *				i.
 * 				>string<
 * the angular brackets serve the purpose of showing clearly the
 * beginning and end of the string (e.g. making undesired whitespace evident)
 */
void STRIPS_tokenizer::print_Vector_of_strg() //prints out all vector of strings
{
	for (uint32_t i = 0; i < tokenized_STRIPS.size(); i++)
	{
		cout << endl;
		cout << i << ".\n";
		cout << ">" << tokenized_STRIPS[i] << "<\n";
	}
}

/* ::print_Vector_of_strg(const vector<string> &vectStr)
 * Overloaded version of the previous function.
 * prints the vector of strings used as argument in the same way
 * as the previous one
 */
void STRIPS_tokenizer::print_Vector_of_strg(const vector<string> &vectStr) //prints out all vector of strings
{
    for (int i = 0; i < static_cast<uint16_t>(vectStr.size()); i++)
    {
        cout << std::endl;
        cout << i << ".\n";
        cout << ">" << vectStr[i] << "<\n";
    }
}
