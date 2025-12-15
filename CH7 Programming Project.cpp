#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// Reads team names or winners from a file into a vector
void getTeams(const string& filename, vector<string>& teams) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        exit(1);
    }

    string name;
    while (getline(file, name)) {
        teams.push_back(name);
    }

    file.close();
}

// Counts how many times a team appears in the winners list
int findWinner(const string& teamName, const vector<string>& winners) {
    int count = 0;
    for (const string& winner : winners) {
        if (winner == teamName) {
            count++;
        }
    }
    return count;
}

int main() {
    vector<string> teams;
    vector<string> winners;

    // Load team names and winners
    getTeams("Teams.txt", teams);
    getTeams("WorldSeriesWinners.txt", winners);

    // Display all team names
    cout << "Team Names:\n";
    for (const string& team : teams) {
        cout << team << endl;
    }

    // Prompt user for team name
    string input;
    cout << "\nEnter the name of a team (enter quit to end):\n";
    getline(cin, input);

    while (input != "quit") {
        int wins = findWinner(input, winners);
        cout << input << " won the World Series " << wins << " times.\n";

        cout << "\nEnter the name of a team (enter quit to end):\n";
        getline(cin, input);
    }

    return 0;
}