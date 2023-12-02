#include <iostream>
#include <iomanip>
#include <fstream>		// Access to of-, if-, fstream
#include <string>
#include <vector>
#include <map>
#include "CharacterStats.h"
using namespace std;

static CharacterStats arr[17][7]; //2D array where rows represents character/agent name and columns represents map name
static map<string, int> CharNameToIndex; //turns our character name into an index to be used for arr
static map<string, int> MapNameToIndex; //does the same for map name
static int GamesOnEachMap[7];
map<int, pair<string, bool>> GamesInfo;

void InitializeCharToIndex() {
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
}
void InitializeMapToIndex() {
    MapNameToIndex["Ascent"] = 0;
    MapNameToIndex["Bind"] = 1;
    MapNameToIndex["Breeze"] = 2;
    MapNameToIndex["Fracture"] = 3;
    MapNameToIndex["Haven"] = 4;
    MapNameToIndex["Icebox"] = 5;
    MapNameToIndex["Split"] = 6;
}
void GetScoreboardData(const char* filepath)
{
    ifstream inFile(filepath);

    if(!inFile.is_open())
    {
        cout << filepath << " was NOT opened!" << endl;
    }

    // Read the heading data from the file
    string lineFromFile, word;
    getline(inFile, lineFromFile);
    vector<string> row;
    vector<vector<string>> rows;

    string currentMapName = "";
    bool team1Won = false;
    int counter = 0;
    // Get all entries from the file, one line at a time
    while (getline(inFile, lineFromFile))
    {
        row.clear();

        // Create a stream from the line of data from the file
        istringstream stream(lineFromFile);

        while (getline(stream, word, ',')) {
            //cout<<"Word: " <<word <<endl;
            row.push_back(word);
        }

        rows.push_back(row);
    }

    string agentName;
    string _gameID, _kills, _deaths, _assists, _acs;
    for (int i = 0; i < rows.size(); i++) { // loop through the size of the row

        if (counter == 10 || counter == 0) { // we've reached the last player in the first game
            counter = 0; // reset the counter
            _gameID = rows[i][0]; // get the game ID
            cout << "GAME ID: " << _gameID << endl;
            currentMapName = GamesInfo[stoi(_gameID)].first;
            cout << "CURRENT MAP: " << currentMapName << endl;
            team1Won = GamesInfo[stoi(_gameID)].second;
        }

        cout << rows[i][4] << endl; // Agent Name
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].agentName = agentName;

        counter++;
        //cout << "GameID: " << rows[i][0] << endl;
        //cout << "Team Name: " << rows[i][3] << endl;
        //cout << "Agent Name: " << rows[counter][4] << endl;*/
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].acs += stoi(rows[i][5]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].kills += stoi(rows[i][6]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].deaths += stoi(rows[i][7]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].assists += stoi(rows[i][8]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numTimesPicked++;
        if(team1Won && counter < 6) {
            arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesWon++;
        } else {
            if(counter >= 6) {
                arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesWon++;
            }
        }
        //cout << "ACS: " << rows[i][5] << endl;
        //cout << "Kills: " << rows[i][6] << endl;
        //cout << "Deaths: " << rows[i][7] << endl;
        //cout << "Assists: " << rows[i][8] << endl;



        /*

        getline(stream, _gameID, ',');
        getline(stream, agentName, ',');
        getline(stream, _gameID, ',');
        getline(stream, _kills, ',');
        getline(stream, _deaths, ',');
        getline(stream, _assists, ',');
        getline(stream, _acs, ',');

        if (counter == 10) { // we've reached the last player in the first game
            counter = 0; // reset the counter

            GamesInfo[stoi(_gameID)].first = currentMapName; // store current map name from ziad's data
            GamesInfo[stoi(_gameID)].second = teamWon;// store bool if team won from ziad's data

        }
        cout << "ARW" << endl;
        counter++;
        //BUG STOI issue
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].agentName = agentName;
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].numTimesPicked++;
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].kills += stoi(_kills);
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].deaths += stoi(_deaths);
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].assists += stoi(_assists);
        arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].acs += stoi(_acs);


        cout << "pp" << endl;

        if(teamWon && counter < 6) {
                    cout << "poopoo" << endl;

            arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].numGamesWon++;
        }
        else {
            if (counter >= 6) {
                arr[CharNameToIndex[agentName]][MapNameToIndex[currentMapName]].numGamesWon++;
            }
        }*/

    }
    inFile.close();
}
void GetData(const char* filepath)
{
    map<int, pair<string, bool>> MapStorage;
    vector<int> gameIDs;

    ifstream inFile(filepath);

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

        //CharacterStats s;
        string game_ID;
        string random;
        string map_name;
        string team1_name;
        string winner;
        getline(stream, game_ID, ',');
        getline(stream, random, ',');
        getline(stream, map_name, ',');
        getline(stream, random, ',');
        getline(stream, random, ',');
        getline(stream, team1_name, ',');
        getline(stream, random, ',');
        getline(stream, winner, ',');


        //cout << game_ID <<" " <<map_name <<" " <<team1_name <<" " <<winner << endl;
        GamesOnEachMap[MapNameToIndex[map_name]]++;
        bool Team1Win = false;
        if (winner == team1_name) {
            Team1Win = true;
        }
        GamesInfo[stoi(game_ID)] = make_pair(map_name, Team1Win);
    }

    for (int i = 0; i < 7; i++) {
        cout << GamesOnEachMap[i] <<endl;
    }
    /*for(auto it = GamesInfo.begin(); it != GamesInfo.end(); it++) {
        cout<<it->first <<" " <<it->second.first <<" " <<it->second.second <<endl;
    }*/

    inFile.close();
}

int main() {
    InitializeCharToIndex();
    InitializeMapToIndex();
    const char* gameScoreboard = "Scoreboard";
    const char* games = "Games";
    GetData(games);
    GetScoreboardData(gameScoreboard);


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



