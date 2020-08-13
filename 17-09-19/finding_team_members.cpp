#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//each team consists of two participants and their strength
typedef struct team_struct {
    int strength;
    int first;
    int second;
} team_t;

bool compare(const team_t* t1, const team_t* t2) {
    return t1->strength > t2->strength;
}

int main() {
    int n; //number of teams to be formed
    cin >> n;
    int couples = (n*(n-1))/2; //number of possible couples
    vector<team_t*> teams;
    int mates[2*n]; //contains each contestant's mate
    teams.reserve(couples); //vector of possible couples
    for(int i=0; i<2*n; i++)
        mates[i] = 0; //means not assigned

    for(int i=1; i<2*n; ++i)
        for(int j=0; j<i; ++j) { //form all the possible teams
            team_t* t = (team_t*) malloc(sizeof(team_t));
            cin >> t->strength;
            t->first = i;
            t->second = j;
            teams.push_back(t);
    }

    //sort teams by strength
    sort(teams.begin(), teams.end(), compare);

    for(int i=0; i<teams.size(); ++i) {
        //assign mates greedly
        if(mates[teams[i]->first] == 0 && mates[teams[i]->second] == 0) {
            mates[teams[i]->first] = teams[i]->second+1;
            mates[teams[i]->second] = teams[i]->first+1;
        }
    }

    for(int i=0; i<2*n; i++)
        cout << mates[i] << " ";
    cout << endl;

    return 0;
}
