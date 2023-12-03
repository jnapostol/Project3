#include <string>

using namespace std;
//for each row of scoreboard we add ACS, deaths, kills, games played and assists to the map specific values for each character
//"picked" vector add each name
//every 10 columns of scoreboard, numGames++ and clear picked

class CharacterStats {
public:
    int acs;
    int kills;
    int deaths;
    int assists;
    int numGamesPicked;
    int numTimesPicked;
    int numGamesWon;
    string agentName;

    CharacterStats() {
        acs = 0;
        kills = 0;
        deaths = 0;
        assists = 0;
        numGamesPicked = 0;
        numTimesPicked = 0;
        numGamesWon = 0;
        agentName = "";
    }
    float KDACalculator() {
        float kda = ((float) (kills + assists)) / ((float) deaths);
        return kda;
    }

    /*float PickRateCalculator() { // note that numGames played on each map is a per map variable
        float pickRate = numGamesPicked/numGames;
        return pickRate;
    }*/
};