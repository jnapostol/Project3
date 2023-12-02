#include <iostream>
#include <iomanip>
#include <fstream>		// Access to of-, if-, fstream
#include <string>
#include <vector>
#include <map>
#include "CharacterStats.h"
using namespace std;

void GetData(string& filepath)
{
    vector<int> gameIDs;
    map<int, pair<string, bool>> MapStorage;

    ifstream inFile;
    inFile.open(filepath);

    if(!inFile.is_open())
        cout << filepath << " was NOT opened!" << endl;

    // Read the heading data from the file
    string lineFromFile, word;
    getline(inFile, lineFromFile);
    vector<string> row;
    vector<vector<string>> rows;

    while (getline(inFile, lineFromFile))       // Get all entries from the file, one line at a time
    {
        row.clear();

        getline(inFile, lineFromFile);

        istringstream stream(lineFromFile);     // Create a stream from the line of data from the file

        while (getline(stream, word, ','))
            row.push_back(word);

        /*CharacterStats s;		// Create object s, which is an individual character's set of stats
        string temp_gameID;     // GameID is the first column in both files
        int gameID = stoi(temp_gameID);*/

        rows.push_back(row);

        /*getline(stream, temp_gameID, ',');		// Separate the single line of data into its constituent parts
        int gameID = stoi(temp_gameID);

        gameIDs.push_back(gameID);       // how to store the gameIDs? Used for connecting map to a character

        if (filepath == "Games.csv")
        {

        }*/
        /*if (filepath == "Game_Scoreboard.csv")
        {
            string agentName;
            string temp_ACS, temp_kills, temp_deaths, temp_assists;		// Tokens to be converted from string into original datatypes

            getline(stream, agentName, ',');		// Separate the single line of data into its constituent parts
            s.agentName = agentName;                            // Set each of these values as an attribute of the character stats

            getline(stream, temp_ACS, ',');
            s.acs = stoi(temp_ACS);
        }*/
        // Add gameID and mapName and ifWon bool in mapStorage
    }

    for (int i = 0; i < rows.size(); i++)
    {
        //for (int j = 0; j < row.size(); j++)
        cout << "GameID " << rows[i][0] << ", " << rows[i][2] << endl;
    }

    inFile.close();
}

int main() {
    static map<string, int> CharNameToIndex;
    CharNameToIndex["Astra"] = 0;
    CharNameToIndex["Breach"] = 1;
    CharNameToIndex["Brimstone"] = 2;
    CharNameToIndex["Chamber"] = 3;
    CharNameToIndex["Cypher"] = 4;
    CharNameToIndex["Jett"] = 5;
    CharNameToIndex["Kayo"] = 6;
    CharNameToIndex["Killjoy"] = 7;
    CharNameToIndex["Omen"] = 8;
    CharNameToIndex["Phoenix"] = 9;
    CharNameToIndex["Raze"] = 10;
    CharNameToIndex["Reyna"] = 11;
    CharNameToIndex["Sage"] = 12;
    CharNameToIndex["Skye"] = 13;
    CharNameToIndex["Sova"] = 14;
    CharNameToIndex["Viper"] = 15;
    CharNameToIndex["Yoru"] = 16;

    static map<string, int> MapNameToIndex;
    MapNameToIndex["Ascent"] = 0;
    MapNameToIndex["Bind"] = 1;
    MapNameToIndex["Breeze"] = 2;
    MapNameToIndex["Fracture"] = 3;
    MapNameToIndex["Haven"] = 4;
    MapNameToIndex["Icebox"] = 5;
    MapNameToIndex["Split"] = 6;

    static CharacterStats arr[17][7]; //initialize the 2-D array
    string gameScoreboard = "Game_Scoreboard.csv";
    string games = "Games.csv";
    GetData(games);
    //GetData(gameScoreboard);

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



