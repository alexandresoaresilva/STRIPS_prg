/* RESISTANCE CACULATOR: for 4, 5 and 6-color band resistors
 The program gets the number of bands & the bands' color. The user types in the desired color for the asked band, and the program calculates the resistor's resistance, tolerance, and possible min and max resistances from the tolerance. In the 6-band resistor, the temperature coefficient is used to calulate the min and max resistances at 21º C (celsius).
 
 OBS: 
 1. No temperature coefficient is shown for 4 and 5 bands;
 2. tolerance does not have a white possible band (corrected, in disagreement with the assignment sheet, but in accordance with updated/correct color table for resistors referenced in EN 60062:2005). I did this because I programmed a very similar assignment for Dr. Sarraf's Matlab class, and he recommended us to use the table from wikipedia, which seemed more complete than the one on the assignent sheet;
 3. Tolerance, in the 4-band resistor, can have other colors beyond standard in the build by design. I couldn't find an agreement between internet sources about tolerance, colors, so I used the one with the most colors available;
 3. Beyond the assignment sheet, temperature has also black, green, and gray possible bands (corrected, same as previous);
 4. Black cannot be an input for band 1.
 
 */

//Date: November 26, 2016
//Written by: Alexandre Soares da Silva


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//void calculateValue(double bands[], int band);

struct Resistor
{
    string bands;
    int values;
    double tolerance;
    int temperature;
};

class ResistorCalc
{
public:
    /*-----------------------Gets user's choice of resistor's number of bands-------------------------------------*/
    void getBandNum(int &bandNum);//mutuator - 4, 5, or 6
    /*-----------------------Save colors/values from structure into private member variables-------------------------------*/
    void getBandsFromStruct(Resistor Values[]);
    /*-----------------------Get bands from user input and calculates corresponding resistance---------------------------*/
    int getAndCalcBands(int bandNum);//gets colors from user and calculates everything needed (tolerance etc)

private:
    /*-----------------------Checks Band and returns true or false-------------------------------------*/
    bool checkBand(string bandChoices, int bandNum, int &index, int &tolIndex, int &tempIndex, int chosenBandNum);
    /*-----------------------calculates resistance's digits-------------------------------------*/
    double writeResistance(int value, int bandNum, int chosenBandNum);//calculates base resistance
    /*-----------------------calculates tolerance and temperature from resistance-------------------------------------*/
    void toleranceTempDisp(double resistance, double tolerance, int temperature, int chosenBandNum);
    /*-----------------------gets Max and min temperatures of operation-------------------------------------*/
    void getMaxMinTemp(double &max, double &min);
    /*-----------------------writes nice resistances-------------------------------------*/
    void writeDecimals(double resistance);
    //VARIABLES
    int index, tolIndex, tempIndex;//for saving the colors' positions
    double maxTemp, minTemp;
    double baseResistance = 0;
    
    //arrays
    string userBandChoices[6];//for saving user choices of collors in bands
    string bands[12];//colors to be saved here
    int values[12];//reference value for first/second/third/multiplier bands,
    double tolerance[12];//fith band
    int temperature[12];//sixth band
};

int main() //PROGRAM STARTS-------------------------------------------------------------|
{
    int chosenBandNum(0);
    ResistorCalc NewResistorCalc;
    Resistor NewResistor[12] =
    {
        //organization {color, reference value for first/second/third/multiplier bands, tolerance, temperature coefficient}
        {"black",0,0,250},{"brown",1,0.01,100},{"red",2,0.02,50},{"orange",3,0.03,15}, {"yellow",4,0.04,25}, {"green",5,0.005,20}, {"blue",6,0.0025,10},{"violet",7,0.001,5},{"gray",8,0.0005,1},{"white",9,0.01,0}, {"gold",-1,0.05,0},{"silver",-2,0.1,0}
    };
    
    NewResistorCalc.getBandNum(chosenBandNum);//gets number of bands
    NewResistorCalc.getBandsFromStruct(NewResistor);//saves band values to be used within private member function
    NewResistorCalc.getAndCalcBands(chosenBandNum);//gets bands'colors
    
    return 0;
}//PROGRAM ENDS-------------------------------------------------------------------------|


/*-----------------------Gets user's choice of resistor's band number-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
//
//
//
void ResistorCalc::getBandNum(int &bandNum)
{
    cout << "Please enter the number of bands of the resistor - 4,5, or 6 are the only valid choices: ";
    cin >> bandNum;
    cin.clear(); //
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//clears the stream (from StackOverflow)
    while ( bandNum != 4 && bandNum != 5 && bandNum != 6 )
    {
        cout << "Please enter a valid number  - 4,5, or 6: ";
        cin >> bandNum;
        cin.clear(); //this and next line are from the website StackOverflow
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//clears the input stream
    }
    cout << endl;
}

/*-----------------------Save bands from structure into private member variables in Class ResistorCalc-------------------------------------*/
// MEMBER FUNCTION of ResistorCalc class
//
//
//
void ResistorCalc::getBandsFromStruct(Resistor Values[])
{
    for (int i = 0; i < 12; i++)
    {
        bands[i] =Values[i].bands;
        values[i] = Values[i].values;
        tolerance[i] = Values[i].tolerance;
        temperature[i] = Values[i].temperature;
    }
}

/*-----------------------Get bands' colors from user input & calculates resistance-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
// RETURNS final resistance
// uses private member functions functions: checkBand ; writeResistance ; toleranceTempDisp
// converts string to lower case:
//      transform(userBandChoices[i].begin(), userBandChoices[i].end(), userBandChoices[i].begin(), ::tolower);
//      --> code line found on StackOverflow http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
//
int ResistorCalc::getAndCalcBands(int bandNum)
{
    int index(0), counter(0);
    
    
    for (int i = 0; i < bandNum; i++ ) //goes up to the chosen band number
    {
        
        do
        {
            if ( counter == 0 ) //for the first time asking the question
            {
                cout << "Please enter the color for band " << (i+1) << ": ";
                cin >> userBandChoices[i];
            }
            else
            {
                cout << "Please enter a valid color for band " << (i+1) << ": ";
                cin >> userBandChoices[i];
            }
            cin.clear(); //
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//clears the input stream (from StackOverflow)
            transform(userBandChoices[i].begin(), userBandChoices[i].end(), userBandChoices[i].begin(), ::tolower); //converts to lower case
        
            if ( userBandChoices[i] == "grey" )//makes sure same writing is used for grey
                userBandChoices[i] = "gray";
            counter++;//for avoinding asking repeatedly the same question
            
        } while  (checkBand(userBandChoices[i], i, index, tolIndex, tempIndex, bandNum) == false ); // checks if string input matches band colors
        
        counter = 0;
        
        //IF/ELSE's call the function to calculate the value of the first 4 bands
        // function writeResistance calculates the resistance's digits; this calculates its final value, puttin the digits together and multiplying where needed
        if ( i < 2 )
                baseResistance = baseResistance + writeResistance(values[index], i, bandNum);//base
        
        else if ( i == 2 )//third band
        {
            if ( bandNum == 4 ) //multiplier for 4 bands
                baseResistance = baseResistance * writeResistance(values[index], i, bandNum);
            else    //base for 5/6 bands
                baseResistance = baseResistance + writeResistance(values[index], i, bandNum);
        }
        
        else if ( ( i == 3 ) && ( bandNum > 4 ) )//multiplier for 5/6 bands
                baseResistance = baseResistance * writeResistance(values[index], i, bandNum);
        
    }
    toleranceTempDisp(baseResistance, tolerance[tolIndex],temperature[tempIndex], bandNum);
    return baseResistance;
}

/*-----------------------Checks Band and returns true or false-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
// RETURNS boolean value TRUE for found matching color
// used within function getAndCalcBands for checkin user input
//
bool ResistorCalc::checkBand(string bandChoices, int bandNum, int &index, int &tolIndex, int &tempIndex, int chosenBandNum)
{
    bool trueORFalse = false;
    
    if ( bandNum < 3 )//checks for correct values from user for bands 1,2,3
    {
        if ( bandNum == 0 )
        {
            for (int i = 1; i < 10; i++) //prevents "black" as first band input 
                if ( bandChoices == bands[i] )
                {
                    trueORFalse = true;
                    index = i;
                }
        }
        else
        {
        for (int i = 0; i < 10; i++)
            if ( bandChoices == bands[i] )
            {
                trueORFalse = true;
                index = i;
            }
        }
    }
    
    else if ( bandNum >= 3 && bandNum <= 4  )//for bands 4,5
    {
        if ( bandNum == 3 )
        {
            for (int i = 0; i < 12; i++)
                if (( bandChoices == bands[i] ) && ( chosenBandNum < 5))//tolerance comes earlier for four bands
                {
                    trueORFalse = true;
                    tolIndex = i;
                }
                else if (( bandChoices == bands[i] ) && ( chosenBandNum > 4))
                {
                    trueORFalse = true;
                    index = i;
                }
        }
        else
            for (int i = 1; i < 12; i++)
            {
                if ( i == 3 || i == 9 )//fifth band starts at brown, skipps orange & white
                    i++;
                if ( bandChoices == bands[i] )
                {
                    trueORFalse = true;
                    tolIndex = i;
                }
            }
    }
    else //for temperature coefficient
    {
        for (int i = 1; i < 9; i++)
        {
            if ( bandChoices == bands[i] )
            {
                trueORFalse = true;
                tempIndex = i;
            }
        }
    }
    return trueORFalse;
}

/*-----------------------calculates resistance's digits-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
// RETURNS each DIGIT of resistance (including multiplier) but DOES NOT calculate resistance
// RUNS within private member function getAndCalcBands' loop - within the loop, it actually helps calculate resistance
// VAR value =  number of the list from 0-9 and -1, -2
//
double ResistorCalc::writeResistance(int value, int bandNum, int chosenBandNum)
{
    
    double resistance(0);
    
    switch (bandNum)//bandNum = is the i in the for loop function ResistorCalc::getAndCalcBands for running through all first four bands
    {
        case 0:
            if ( chosenBandNum == 4 )
                resistance = value * 10;//2 significant digits (4 bands)
            else
                resistance = value * 100;//3 significant digits (5/6 bands) - MSB
            break;
        case 1:
            if ( chosenBandNum == 4 )
                resistance = value;//2 significant digits (4 bands)
            else
                resistance = value * 10;//3 significant digits (5/6 bands) - middle
            
            break;
        case 2:
            if ( chosenBandNum == 4 )
            {
                resistance = pow(10,value); //multiplier band for four-band resistor
                break;
            }
            else
            {
                resistance = value;////3 significant digits (5/6 bands) - LSB
                break;
            }
        case 3:
            if ( chosenBandNum > 4 ) //five and six band use the the fourth band for multiplier
            {
                resistance = pow(10,value);
                break;
            }
            else
            {
                break; //for four-band resistor --> tolerance can now be calculated by another function
            }
        default:
            break;
            
    }
    return resistance;
}
/*-----------------------gets Max and min temperatures of operation-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
//
//
//

void ResistorCalc::getMaxMinTemp(double &max, double &min)
{
    cout << "Please enter the maximum temperature your resistor will have to withstand in degress celsius: "<< endl;
    cin >> max;
    while (cin.fail())
    {
        cin.clear(); //
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data type. Please enter a number for the max temperature: " << endl;
        cin >> max;
    }
    
    cout << "Please enter the maximum temperature your resistor will have to withstand in degress celsius: "<< endl;
    cin >> min;
    while (cin.fail())
    {
        cin.clear(); //
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid data type. Please enter a number for the max temperature: " << endl;
        cin >> min;
    }
}

/*-----------------------calculates tolerance and temperature from resistance-------------------------------------*/
// MEMBER FUNCTION of ResistorValue class
// prints out results
//
//
void ResistorCalc::toleranceTempDisp(double resistance, double tolerance, int temperature, int chosenBandNum)
{
    if (chosenBandNum == 6)//for getting min and max
        getMaxMinTemp(maxTemp, minTemp);

    cout << "\nResults\n-------\n";
    cout.precision(1);
    cout << fixed;
    cout << "Resistance = ";
    writeDecimals(resistance);//prints the resistance nicely
    cout << endl << endl;
    cout << "Tolerance: " << tolerance*100 << " %\n";
    
    if (chosenBandNum < 6)//for 4 and 5 bands
    {
            cout << scientific;
            cout.precision(5);
            cout << "Rmin: " << resistance - resistance*tolerance << endl;
            cout << "Rmax: " << resistance + resistance*tolerance << endl;
    }
    else//for 6 bands
    {
        cout << "Temperature coefficient = " << temperature << " ppm"<< endl;
        //cout << scientific;
        cout.precision(6);//needs more precision than resistance
        //cout << "Rmin: " << resistance*(1+(minTemp-21.0)*(temperature/1000000.0)) << endl;
        
        cout << "Rmin: ";
        writeDecimals(resistance*(1+(minTemp-21.0)*(temperature/1000000.0)));
        cout << endl;
        cout << "Rmax: ";
        writeDecimals(resistance*(1+(maxTemp-21.0)*(temperature/1000000.0)));
        cout << endl;
    }
}

void ResistorCalc::writeDecimals(double resistance)
{
    if ( resistance >= 1000 && resistance < 1000000 )
    {
        resistance = resistance / 1000;
        cout << resistance << " Kiloohms";
    }
    else if ( resistance >= 1000000 && resistance < 1000000000 )
    {
        resistance = resistance / 1000000;
        cout << resistance << " Megaohms";
    }
    else if ( resistance >= 1000000000 )
    {
        resistance = resistance / 1000000000;
        cout << resistance << " Gigaohms";
    }
    else
        cout << resistance << " ohms";
}
