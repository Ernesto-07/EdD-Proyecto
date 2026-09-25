/*
 * player.h
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

using namespace std;

class Player {
private:
    string name;
    int score;

public:
    Player() {
        name = "";
        score = 0;
    }

    Player(string n, int s) {
        name = n;
        score = s;
    }

    string getName() {
        return name;
    }

    int getScore() {
        return score;
    }
    bool operator>=(Player p2) {
        return score >= p2.score;
    }
};

#endif