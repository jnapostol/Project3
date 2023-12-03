#include <string>
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>		// Access to of-, if-, fstream
#include <vector>
#include <tuple>
#include <bits/stdc++.h>
#include "CharacterStats.h"
#include "MaxHeap.h"


using namespace std;
static CharacterStats arr[17][7]; //2D array where rows represents character/agent name and columns represents map name
static map<string, int> CharNameToIndex; //turns our character name into an index to be used for arr
static map<string, int> MapNameToIndex; //does the same for map name
static int GamesOnEachMap[7];
map<int, pair<string, bool>> GamesInfo;
vector<map<float, tuple<string, float, float, float>>> CalculatedMapData(7);

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
    //lowercase
    CharNameToIndex["astra"] = 0;
    CharNameToIndex["breach"] = 1;
    CharNameToIndex["brimstone"] = 2;
    CharNameToIndex["chamber"] = 3;
    CharNameToIndex["cypher"] = 4;
    CharNameToIndex["jett"] = 5;
    CharNameToIndex["kayo"] = 6;
    CharNameToIndex["killjoy"] = 7;
    CharNameToIndex["omen"] = 8;
    CharNameToIndex["phoenix"] = 9;
    CharNameToIndex["raze"] = 10;
    CharNameToIndex["reyna"] = 11;
    CharNameToIndex["sage"] = 12;
    CharNameToIndex["skye"] = 13;
    CharNameToIndex["sova"] = 14;
    CharNameToIndex["viper"] = 15;
    CharNameToIndex["yoru"] = 16;
}
void InitializeMapToIndex() {
    MapNameToIndex["Ascent"] = 0;
    MapNameToIndex["Bind"] = 1;
    MapNameToIndex["Breeze"] = 2;
    MapNameToIndex["Fracture"] = 3;
    MapNameToIndex["Haven"] = 4;
    MapNameToIndex["Icebox"] = 5;
    MapNameToIndex["Split"] = 6;
    //lowercase
    MapNameToIndex["ascent"] = 0;
    MapNameToIndex["bind"] = 1;
    MapNameToIndex["breeze"] = 2;
    MapNameToIndex["fracture"] = 3;
    MapNameToIndex["haven"] = 4;
    MapNameToIndex["icebox"] = 5;
    MapNameToIndex["split"] = 6;
}
void GetScoreboardData(string& filepath)
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
            row.push_back(word);
        }

        rows.push_back(row);
    }

    string agentName;
    string _gameID, _kills, _deaths, _assists, _acs;
    bool isPicked[17];
    for (int i = 0; i < rows.size(); i++) { // loop through the size of the row

        if (counter == 10 || counter == 0) { // we've reached the last player in the first game
            for(int j = 0; j < 17; j++) {
                isPicked[j] = false;
            }
            counter = 0; // reset the counter
            _gameID = rows[i][0]; // get the game ID
            //cout << "GAME ID: " << _gameID << endl;
            currentMapName = GamesInfo[stoi(_gameID)].first;
            //cout << "CURRENT MAP: " << currentMapName << endl;
            team1Won = GamesInfo[stoi(_gameID)].second;
        }
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].agentName = rows[i][4];

        counter++;
        //cout << "GameID: " << rows[i][0] << endl;
        //cout << "Team Name: " << rows[i][3] << endl;
        //cout << "Agent Name: " << rows[counter][4] << endl;*/
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].acs += stoi(rows[i][5]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].kills += stoi(rows[i][6]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].deaths += stoi(rows[i][7]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].assists += stoi(rows[i][8]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numTimesPicked++;
        if (!(isPicked[CharNameToIndex[rows[i][4]]])) {
            arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesPicked++;
            isPicked[CharNameToIndex[rows[i][4]]] = true;
        }
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
void GetData(string& filepath)
{
    map<int, pair<string, bool>> MapStorage;
    vector<int> gameIDs;

    ifstream inFile(filepath);

    if(!inFile.is_open())
    {
        cout << filepath << " was NOT opened!" << endl;
    }
    else
    {
        cout << "Loading..." << endl;
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

    /*for (int i = 0; i < 7; i++) {
        cout << GamesOnEachMap[i] <<endl;
    }*/

    /*for(auto it = GamesInfo.begin(); it != GamesInfo.end(); it++) {
        cout<<it->first <<" " <<it->second.first <<" " <<it->second.second <<endl;
    }*/

    inFile.close();
}
void CreateCalculatedMap() {
    //map<float, tuple<string, float, float, float>> CalculateMap;
    float acs = 1;
    float kda = 1;
    float win_rate = 1;
    float pick_rate = 1;


    for (int i = 0; i < 7; i++) {
        cout<<"\nNow Calculating Map: " <<i <<endl;
        for (int j = 0; j < 17; j++) {
            cout<<"row " <<j <<" column " <<i <<endl;
            //cout<<arr[11][2].kills <<" " <<CharNameToIndex["reyna"] <<endl;
            //cout<<"Win Rate = " <<arr[CharNameToIndex["Reyna"]][MapNameToIndex["Breeze"]].numGamesWon <<" NumTimesPicked " <<arr[CharNameToIndex["Reyna"]][MapNameToIndex["Breeze"]].numTimesPicked;
            cout<<"Times Picked: " <<arr[j][i].numTimesPicked <<endl;
            if(arr[j][i].numTimesPicked == 0) {
                win_rate = 0;
                pick_rate = 0;
                acs = 0;
                kda = 0;
            } else {
                win_rate = ((float) arr[j][i].numGamesWon) / ((float) arr[j][i].numTimesPicked);
                pick_rate = ((float) arr[j][i].numGamesPicked) / ((float)GamesOnEachMap[i]);
                acs = ((float) arr[j][i].acs) / ((float) arr[j][i].numTimesPicked);
                kda = arr[j][i].KDACalculator();
            }
            cout<<"Win: " <<win_rate <<" " <<"Pick: " <<pick_rate <<" " <<"ACS: " <<acs <<" " <<"KDA: " <<kda <<endl;
            CalculatedMapData[i][win_rate] = make_tuple(arr[j][i].agentName, pick_rate, acs, kda);
            cout<<"inserted at " <<i <<endl;
        }
    }
    for(int i = 0; i < 7; i++) {
        cout<<"\n\n\nMap: " <<i <<endl;
        for(const auto it : CalculatedMapData[i]) { //auto it = CalculatedMapData[i].begin(); it != CalculatedMapData[i].end; it++ //const auto it : CalculatedMapData[i]
            cout<<"Character: " <<get<0>(it.second) <<" Win Rate: "<<" " <<it.first <<" Pick Rate: " <<get<1>(it.second) <<" ACS: " <<get<2>(it.second) <<" KDA: " <<get<3>(it.second) <<endl;
        }
    }
}
void CreateCalculatedHeap() {
    cout << "ENTER Heap Calculator"<< endl;

    vector<MaxHeap> heapOfHeaps; // create a vector of heaps
    // each heap contains 17 agents. each agent has a tuple with: WinRate, AgentName, PickRate,ACS, KDA

    string currentAgentOnMap;
    float calc_KDA, calc_ACS, win_Rate,pick_Rate;

    // tuple<float, string, float, float, float> agentData;

    for (int i = 0; i < 7; i++) { // loop through map
        MaxHeap heapObject(17);
        for (int j = 0; j < 17; j++) { //loop through array

            currentAgentOnMap = arr[j][i].agentName; // get the current agent name
            win_Rate = ((float) arr[j][i].numGamesWon) / ((float) arr[j][i].numTimesPicked);
            calc_ACS = ((float) arr[j][i].acs) / ((float) arr[j][i].numTimesPicked);
            calc_KDA = arr[j][i].KDACalculator();
            pick_Rate = ((float) arr[j][i].numGamesPicked) / ((float)GamesOnEachMap[i]);

            cout << "Agent: " << currentAgentOnMap << " WinRate:  " << win_Rate << " ACS: " << calc_ACS << " KDA: " << calc_KDA << " PickRate: " << pick_Rate << endl;

            // tuple<float, string, float, float, float> _tuple = make_tuple(win_Rate,currentAgentOnMap,pick_Rate, calc_ACS,calc_KDA); // make tuple with agent data
            // agentData = _tuple;
            cout << "INSERTING DATA INTO HEAP" << endl;

            heapObject.Insert(make_tuple(win_Rate,currentAgentOnMap,pick_Rate, calc_ACS,calc_KDA));

        }
        cout << "PUSHING HEAP INTO VECTOR" << endl;
        heapOfHeaps.push_back(heapObject); // 7 maps each with 17 agents
    }

    // MaxHeap obj;
    cout << "EXTRACTING THE MAX" << endl;
    for (int k = 0; k < heapOfHeaps.size(); k++) { // looping through 7 heaps
        cout << "Max of map " << k << " " <<  endl;
        heapOfHeaps[k].extractMax();

    }

}

void PrintTable()
{
    using std::setw;
    std::cout << std::left;
    std::cout <<
              setw(7) << "[Agent Name]" << setw(6) << "[ACS]" << setw(9) << "[Kills]" << "[Deaths]" << "[Assists]" << endl;
}

int main() {
    InitializeCharToIndex();
    InitializeMapToIndex();
    string gameScoreboard = "Game_Scoreboard.csv";
    string games = "Games.csv";
    GetData(games);
    GetScoreboardData(gameScoreboard);

    // Opening Menu
    int dataStructure, option;
    string mapName;
    cout << "\n~~~~~~~~~~Welcome to our Professional Valorant Match Agent Statistics program!~~~~~~~~~" << endl;
    cout << "Do you want to get better at Valorant? See what the pros are doing!" << endl;
    cout << "Pick a data structure to load the stats into." << endl;
    cout << "1) Map" << endl << "2) Max Heap" << endl;
    cin >> dataStructure;

    switch(dataStructure){
        case 1:
            CreateCalculatedMap();
            break;
        case 2:
            CreateCalculatedHeap();
            break;
        default:
            cout << "default" << endl;
    }

    cout << "\nChoose a map and see which agents are performing the best on it { Breeze, Bind, Haven, Icebox, Ascent, Split, Fracture }: " << endl;
    cin >> mapName;

    // Display the table of character stats and the elapsed time just below it

    cout << "\n----------Options Menu----------" << endl << "1) Choose a new map" << endl << "2) Exit the program" << endl;\
    cin >> option;


    // input parsing
    return 0;
}

// two diff classes to store data/process it?

// storing via map (hash?) & max heap



