#include <string>
using namespace std;

class Player {
	string name;
public:
	Player(string name) { this->name = name; }
	string getName() { return name; }
	bool go(); // 정수를 입력받고 정답이면 이김, true 리턴
};

