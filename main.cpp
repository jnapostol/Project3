#include <string>
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>		// Access to of-, if-, fstream
#include <vector>
#include <tuple>
#include <chrono>       // Timer
#include <bits/stdc++.h>        // Set precision for output

#include "CharacterStats.h"
#include "MaxHeap.h"
#include "CustomMap.h"
#include "Iterator.h"

using namespace std::chrono;
static CharacterStats arr[17][7]; //2D array where rows represents character/agent name and columns represents map name
static map<string, int> CharNameToIndex; // Turns our character name into an index to be used for arr
static map<string, int> MapNameToIndex; // Does the same for map name
static int GamesOnEachMap[7];

vector<string> AvailableMaps_CustomMap; // Flags what user has already chosen
map<int, pair<string, bool>> GamesInfo;
vector<CustomMap<float, tuple<string, float, float, float>>> CalculatedCustomMapData(7);
vector<MaxHeap> HeapOfHeaps; // Create a vector of heaps

void InitializeCharToIndex() { // Initialize all agents with an index
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
void InitializeMapToIndex() { // Initialize valorant map names with an index
    MapNameToIndex["Ascent"] = 0;
    MapNameToIndex["Bind"] = 1;
    MapNameToIndex["Breeze"] = 2;
    MapNameToIndex["Fracture"] = 3;
    MapNameToIndex["Haven"] = 4;
    MapNameToIndex["Icebox"] = 5;
    MapNameToIndex["Split"] = 6;
}
string IndexToChar(int index) { // veronica help lmao
    string charName = "";
    switch(index){
        case 0:
            charName = "astra";
            break;
        case 1:
            charName = "breach";
            break;
        case 2:
            charName = "brimstrone";
            break;
        case 3:
            charName = "chamber";
            break;
        case 4:
            charName = "cypher";
            break;
        case 5:
            charName = "jett";
            break;
        case 6:
            charName = "kayo";
            break;
        case 7:
            charName = "killjoy";
            break;
        case 8:
            charName = "omen";
            break;
        case 9:
            charName = "phoenix";
            break;
        case 10:
            charName = "raze";
            break;
        case 11:
            charName = "reyna";
            break;
        case 12:
            charName = "sage";
            break;
        case 13:
            charName = "skye";
            break;
        case 14:
            charName = "sova";
            break;
        case 15:
            charName = "viper";
            break;
        case 16:
            charName = "yoru";
            break;
        default:
            cout << "Invalid index!" << endl;
    }
    return charName;
}
string IndexToMap(int index) {
    string mapName = "";
    switch(index){
        case 0:
            mapName = "Ascent";
            break;
        case 1:
            mapName = "Bind";
            break;
        case 2:
            mapName = "Breeze";
            break;
        case 3:
            mapName = "Fracture";
            break;
        case 4:
            mapName = "Haven";
            break;
        case 5:
            mapName = "Icebox";
            break;
        case 6:
            mapName = "Split";
            break;
    }
    return mapName;
}

void GetScoreboardData(string& filepath) { // Interpreting the data from Scoreboard_Data.csv file
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
    int counter = 0; // Used to count 10 players at a time

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

    string agentName, _gameID, _kills, _deaths, _assists, _acs;
    bool isPicked[17]; // Boolean that returns if an agent has already been picked in the Valorant map

    for (int i = 0; i < 7; i++) // In every Valorant map
    {
        for (int j = 0; j < 17; j++) // For every Valorant agent
        {
            arr[j][i].agentName = IndexToChar(j); // Get their index associated to their agent name
        }
    }

    for (int i = 0; i < rows.size(); i++) { // Loop through the rows in Scoreboard_Data
        if (counter == 10 || counter == 0) { // When we've reached the last player in a game
            for(int j = 0; j < 17; j++) { // Update the status of the agents to not be picked
                isPicked[j] = false;
            }
            counter = 0; // Reset the counter
            _gameID = rows[i][0]; // Get the Game ID, once every game
            currentMapName = GamesInfo[stoi(_gameID)].first; // Get the current map name, once every game
            team1Won = GamesInfo[stoi(_gameID)].second; // Get if Team 1 has won, once every game
        }
        counter++;

        // Get the ACS, Kills, Deaths, Assists, and Number of Times picked for every agent and total up the sum in a map
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].acs += stoi(rows[i][5]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].kills += stoi(rows[i][6]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].deaths += stoi(rows[i][7]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].assists += stoi(rows[i][8]);
        arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numTimesPicked++;

        if (!(isPicked[CharNameToIndex[rows[i][4]]])) {
            arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesPicked++;
            isPicked[CharNameToIndex[rows[i][4]]] = true;
        }
        if(team1Won && counter < 6) { // When Team 1 has won, update the Number of Games Won for the first 5 agents
            arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesWon++;
        } else {
            if(counter >= 6) { // Otherwise, update the Number of Games Won for the last 5 agents
                arr[CharNameToIndex[rows[i][4]]][MapNameToIndex[currentMapName]].numGamesWon++;
            }
        }
    }
    inFile.close();
}
void GetData(string& filepath) { // Interpret the data from the Games.csv file
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

        string game_ID, random, map_name, team1_name, winner;

        getline(stream, game_ID, ',');
        getline(stream, random, ','); //read into random simply to extract data we don't need
        getline(stream, map_name, ',');
        getline(stream, random, ',');
        getline(stream, random, ',');
        getline(stream, team1_name, ',');
        getline(stream, random, ',');
        getline(stream, winner, ',');

        GamesOnEachMap[MapNameToIndex[map_name]]++; // Increment the number of games on each map using the map_name

        bool Team1Win = false;
        if (winner == team1_name) { // If the winner of the game is Team 1, return true
            Team1Win = true;
        }
        // Store a pair of values: map name and bool if team 1 won, with key: Game ID
        GamesInfo[stoi(game_ID)] = make_pair(map_name, Team1Win);
    }
    inFile.close();
}

void CreateCalculatedMap() { // Creates a custom map data structure for each map name
    auto beg = high_resolution_clock::now(); // Timing the storage of the custom map data structure

    // Initialize agent ACS, KDA, win-rate, and pick-rate to 1
    float acs = 1;
    float kda = 1;
    float win_rate = 1;
    float pick_rate = 1;

    for (int i = 0; i < 7; i++) { // Loop through the number Valorant maps
        for (int j = 0; j < 17; j++) { // Loop through the number of Valorant agents

            if(arr[j][i].numTimesPicked == 0) { // If the agent was picked 0 times
                // Set the agent's data to 0
                win_rate = 0;
                pick_rate = 0;
                acs = 0;
                kda = 0;
            }
            else { // Otherwise, calculate the agent's data
                win_rate = ((float) arr[j][i].numGamesWon) / ((float) arr[j][i].numTimesPicked);
                pick_rate = ((float) arr[j][i].numGamesPicked) / ((float)GamesOnEachMap[i]);
                acs = ((float) arr[j][i].acs) / ((float) arr[j][i].numTimesPicked);
                kda = arr[j][i].KDACalculator();
                CalculatedCustomMapData[i].Insert(win_rate, make_tuple(arr[j][i].agentName, pick_rate, acs, kda));
            }
        }
    }
    // Calculating and printing the elapsed time below
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);
    cout << "Elapsed Time to create CUSTOM MAP in microseconds: " << duration.count() << endl;
}
void PrintCustomMap(string nameOfMap)
{
    auto beg = high_resolution_clock::now();
    int index = MapNameToIndex[nameOfMap]; // Turn the nameOfMap from input into an index;

    bool firstIteration = true;
    for (Iterator<float, tuple<string, float, float, float>> it(CalculatedCustomMapData[index]); it != CalculatedCustomMapData[index].End(); it++) {
        if (firstIteration == true)
        {
            cout << "------ MAP DISPLAY ------" << endl;
            cout << "\nHighest performing agent on " << IndexToMap(index) <<endl;
            cout << "Agent Name: " << get<0>(it.second) << endl;
            cout << "Win Rate: " << fixed << setprecision(2) << it.first << endl;
            cout << "Pick Rate: " << fixed << setprecision(2)  << get<1>(it.second) << endl;
            cout << "ACS (Average Combat Score): " << fixed << setprecision(2) << get<2>(it.second) << endl;
            cout << "KDA (Kills-Deaths-Assists Calculation): " << fixed << setprecision(2) << get<3>(it.second) << endl;
            firstIteration = false;
            cout << "\n" << setw(9) << "[Agent Name]" << setw(11) << "[Win Rate]" << setw(12) << "[Pick Rate]" << setw(6) << "[ACS]" << setw(12) << "[KDA]" << endl;
        }
        cout << setw(9) << get<0>(it.second)
             << setw(11) << fixed << setprecision(2) << it.first
             << setw(11) << fixed << setprecision(2)  << get<1>(it.second)
             << setw(11) << fixed << setprecision(2)  << get<2>(it.second)
             << setw(11) << fixed << setprecision(2)  << get<3>(it.second) << endl;
    }
    cout << endl;
    // Calculating and printing the elapsed time below
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);
    cout << "Elapsed Time to print from CUSTOM MAP in microseconds: " << duration.count() << endl;
    cout << endl;
}

void CreateCalculatedHeap() { // Creates a heap per Valorant map - consisting of 17 agents per heap
    // Each agent has a tuple with: WinRate, AgentName, PickRate,ACS, KDA
    auto beg = high_resolution_clock::now(); // Timing the storage of data
    string currentAgentOnMap;
    float calc_KDA, calc_ACS, win_Rate,pick_Rate;

    for (int i = 0; i < 7; i++) { // Loop through the number of Valorant maps
        MaxHeap heapObject(17);
        for (int j = 0; j < 17; j++) { // Loop through the number of Valorant agents
            currentAgentOnMap = arr[j][i].agentName; // Get agent name
            win_Rate = ((float) arr[j][i].numGamesWon) / ((float) arr[j][i].numTimesPicked); // Get win-rate
            calc_ACS = ((float) arr[j][i].acs) / ((float) arr[j][i].numTimesPicked); // Get ACS
            calc_KDA = arr[j][i].KDACalculator(); // Get KDA ratio
            pick_Rate = ((float) arr[j][i].numGamesPicked) / ((float)GamesOnEachMap[i]); // Get pick-rate

            // Create a tuple with the data above and insert it into the heap
            heapObject.Insert(make_tuple(win_Rate,currentAgentOnMap,pick_Rate, calc_ACS,calc_KDA));
        }
        HeapOfHeaps.push_back(heapObject); // Insert the heap into the vector
    }

    // Timing the storage of the algorithm below
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);
    cout << "Elapsed time to create MAX HEAP in microseconds: " << duration.count() << endl;
}
void PrintHeap(string nameOfMap)
{
    auto beg = high_resolution_clock::now();
    int index = MapNameToIndex[nameOfMap]; // Turn the nameOfMap from input into an index
    tuple<float, string, float, float, float> max = HeapOfHeaps[index].extractMax();

    cout << "---------- MAX HEAP DISPLAY ----------" << endl;
    cout << "\nHighest performing agent on " << IndexToMap(index) <<endl;
    cout << "Agent Name: " << get<1>(max) << endl;
    cout << "Win Rate: " << fixed << setprecision(2) << get<0>(max) << endl;
    cout << "Pick Rate: " << fixed << setprecision(2)  << get<2>(max) << endl;
    cout << "ACS (Average Combat Score): " << fixed << setprecision(2) << get<3>(max) << endl;
    cout << "KDA (Kills-Deaths-Assists Calculation): " << fixed << setprecision(2) << get<4>(max) << endl;

    cout << "\n" << setw(9) << "[Agent Name]" << setw(11) << "[Win Rate]" << setw(12) << "[Pick Rate]" << setw(6) << "[ACS]" << setw(12) << "[KDA]" << endl;
    for (int i = 0; i < 16; i++)
    {
        max = HeapOfHeaps[index].extractMax();
        cout << setw(9) << get<1>(max)
                << setw(11) << fixed << setprecision(2) << get<0>(max)
                << setw(11) << fixed << setprecision(2)  << get<2>(max)
                << setw(11) << fixed << setprecision(2)  << get<3>(max)
                << setw(11) << fixed << setprecision(2)  << get<4>(max) << endl;
    }
    cout << endl;
    // Timing the storage of the algorithm below
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - beg);
    cout << "Elapsed time to print from MAX HEAP in microseconds: " << duration.count() << endl;
    cout << endl;
}

int main() {
    InitializeCharToIndex();
    InitializeMapToIndex();

    string gameScoreboard = "Game_Scoreboard.csv";
    string games = "Games.csv";

    GetData(games); // Interpret the Games.csv file and get necessary data
    GetScoreboardData(gameScoreboard); // Interpret the Game_Scoreboard.csv file and get necessary data

    // Initialize chosen maps
    AvailableMaps_CustomMap.push_back("Ascent");
    AvailableMaps_CustomMap.push_back("Bind");
    AvailableMaps_CustomMap.push_back("Breeze");
    AvailableMaps_CustomMap.push_back("Fracture");
    AvailableMaps_CustomMap.push_back("Haven");
    AvailableMaps_CustomMap.push_back("Icebox");
    AvailableMaps_CustomMap.push_back("Split");

    int option;
    string mapName;
    bool quit = false;
    bool firstIteration = true;
    while (!AvailableMaps_CustomMap.empty() && !quit)
    {
        if (firstIteration == true)
        {
            // Opening Menu
            cout << "\n~~~~~~~~~~ Welcome to our Professional Valorant Match Agent Statistics program! ~~~~~~~~~" << endl;
            cout << "Do you want to get better at Valorant? See what the pros are doing!" << endl;
            cout << "These are the following data structures we'll be loading the stats into:" << endl;
            cout << "1) Map" << endl << "2) Max Heap" << endl;
            cout << "The data and their elapsed build and print times will be displayed together!\n" << endl;

            CreateCalculatedMap();
            CreateCalculatedHeap();
            firstIteration = false;
        }

        // Provide the option to choose more maps from what was not already chosen
        cout << "\n---------- Options Menu ----------" << endl
        << "1) Choose a map and see which agents are performing the best on it." << endl
        << "2) Quit program" << endl;
        cin >> option;

        switch(option)
        {
            case 1:
                cout << "\nChoose a map!" << endl << "Available maps: ";
                // List the available maps
                for (int i = 0; i < AvailableMaps_CustomMap.size(); i++)
                    cout << AvailableMaps_CustomMap[i] << "  |  ";
                cin >> mapName;
                // Adjust the available maps list according to what was chosen
                for (int i = 0; i < AvailableMaps_CustomMap.size(); i++)
                {
                    if (mapName == AvailableMaps_CustomMap[i])
                    {
                        AvailableMaps_CustomMap[i] = "[X] " + AvailableMaps_CustomMap[i];
                    }
                }
                cout << endl;
                PrintCustomMap(mapName);
                PrintHeap(mapName);
                break;
            case 2:
                cout << "Program ended." << endl;
                quit = true;
                break;
        }
    }
    return 0;
}
