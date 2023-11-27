#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>		// Access to of-, if-, fstream
#include <string>
#include "CharStats.h"
#include "MaxHeap.h"
using namespace std;

void GetDataFromCSVFile(const char* filepath)
{
    ifstream inFile(filepath);
    inFile.open(filepath);

    if (inFile.is_open())
    {
        // Read the heading data from the file
        string lineFromFile;
        getline(inFile, lineFromFile);

        // Get all entries from the file, one line at a time
        while (getline(inFile, lineFromFile))
        {
            // Create a stream from the line of data from the file
            istringstream stream(lineFromFile);

            string setName = "";
            string setTheme = "";
            int setNumber = 0;
            int numberMinifigures = 0;
            int pieceCount = 0;
            float setPrice = 0;

            string temp_setNumber, temp_numberMinifigures, temp_pieceCount;		// Tokens to be converted from string into original datatypes
            string temp_setPrice;

            CharStats s;		// Create object s, which is an individual legoset

            getline(stream, temp_setNumber, ',');		// Separate the single line of data into its constituent parts
            s.setNumber = stoi(temp_setNumber);			// Set each of these values as an attribute of the legoset

            legosets.push_back(s);		// Add that legoset to the vector of legosets

        }
    }
    else
    {
        cout << filepath << " was not opened!" << endl;
    }

}

int main() {

    const char* filepath1 = "data/Game_Scoreboard.xlsx";
    const char* filepath2 = "data/Games.xlsx";

    

    // menu options
    cout << "Welcome to our Professional Valorant Match Agent Statistics program!" << endl;
    cout << "Do you want to get better at Valorant? See what the pros are doing!" << endl;
    cout << "Pick a data structure to load the stats into." << endl;
    cout << "1) Map" << endl << "2) Max Heap" << endl;

    // input parsing

    return 0;
}

// two diff classes to store data/process it?

// storing via map (hash?) & max heap



