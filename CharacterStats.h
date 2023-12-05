#include <string>
#pragma once

using namespace std;

class CharacterStats { // This class constructs each CharacterStats object aka each Valorant Agent with data
public:
    int acs;
    int kills;
    int deaths;
    int assists;
    int numGamesPicked;
    int numTimesPicked;
    int numGamesWon;
    string agentName;

    CharacterStats() { // Constructor that initializes everything to empty
        acs = 0;
        kills = 0;
        deaths = 0;
        assists = 0;
        numGamesPicked = 0;
        numTimesPicked = 0;
        numGamesWon = 0;
        agentName = "";
    }

    float KDACalculator() { // Calculates the Agent's KDA ratio
        float kda = ((float) (kills + assists)) / ((float) deaths);
        return kda;
    }
};