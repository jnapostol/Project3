#include <iostream>
#include <iomanip>
#include <fstream>		// Access to of-, if-, fstream
#include <string>
#include <vector>
#include "CharacterStats.h"
using namespace std;

void GetData(string& filepath)
{
    vector<int> gameIDs;

    ifstream inFile;
    inFile.open(filepath);

    if(!inFile.is_open())
    {
        cout << filepath << " was NOT opened!" << endl;
    }

    // Read the heading data from the file
    string lineFromFile;
    getline(inFile, lineFromFile);

    // Get all entries from the file, one line at a time
    while (getline(inFile, lineFromFile))
    {
        // Create a stream from the line of data from the file
        istringstream stream(lineFromFile);

        CharacterStats s;		// Create object s, which is an individual character's set of stats
        string temp_gameID;     // GameID is the first column in both files

        //inFile >> temp_gameID;
        getline(stream, temp_gameID, ',');		// Separate the single line of data into its constituent parts
        int gameID = stoi(temp_gameID);
        //cout << temp_gameID << endl;
        gameIDs.push_back(gameID);       // how to store the gameIDs? Used for connecting map to a character

        /*if (filepath == "data/Game_Scoreboard.csv")
        {
            string agentName;
            string temp_ACS, temp_kills, temp_deaths, temp_assists;		// Tokens to be converted from string into original datatypes

            getline(stream, agentName, ',');		// Separate the single line of data into its constituent parts
            s.agentName = agentName;                            // Set each of these values as an attribute of the character stats

            getline(stream, temp_ACS, ',');
            s.acs = stoi(temp_ACS);
        }*/
        // Add that CharacterStats object to the 2D array
    }

    for (int i = 0; i < gameIDs.size(); i++)
        cout << gameIDs[i] << endl;

    inFile.close();
}

int main() {

    string gameScoreboard = "Game_Scoreboard.csv";
    string games = "Games.csv";
    GetData(gameScoreboard);
    //GetData(games);
    //GetData(filepath2);

    // menu options
    cout << "\nWelcome to our Professional Valorant Match Agent Statistics program!" << endl;
    cout << "Do you want to get better at Valorant? See what the pros are doing!" << endl;
    cout << "Pick a data structure to load the stats into." << endl;
    cout << "1) Map" << endl << "2) Max Heap" << endl;

    // input parsing
    return 0;
}

// two diff classes to store data/process it?

// storing via map (hash?) & max heap



