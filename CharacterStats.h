#pragma once
#include <string>

class CharacterStats {
public:
    std::string agentName;
    int acs;
    int kills;
    int deaths;
    int assists;
    int numGamesPicked;
    int numTimesPicked;
    int numGamesWon;

    CharacterStats() {
        acs = 0;
        kills = 0;
        deaths = 0;
        assists = 0;
        numGamesPicked = 0;
        numTimesPicked = 0;
        numGamesWon = 0;
    }
};

