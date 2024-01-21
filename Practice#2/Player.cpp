#include <iostream>
using namespace std;

#include "Player.h"
#include "UpDownGame.h"

bool Player::go() {
	int number;
	cout << name+">>";
	cin >> number;
	return UpDownGame::check(number);
}