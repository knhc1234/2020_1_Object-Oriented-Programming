/*
	Monster의 각종 정보 (현재의 x좌표, y좌표, 먹은 아이템의 수, 움직인 횟수, 몬스터의 모습(symbol))를 다루는 클래스를 작성하고
	클래스 이름과 동일한 멤버 함수인 생성자를 생성하고
	멤버함수 moving을 이용하여 Monster를 이동시키며 바뀐 정보들을 저장한다
	이 때 바뀐 정보등을 화면상에 나타낼 때 멤버함수를 이용해 보고자 하였으나
	하나일 때는 문제가 되지 않지만 여러 Monster의 정보를 멤버함수를 이용해 담기가 어려워
	showing함수와 statement함수를 이용해 따로 나타내었다. 
	showing함수는 맵의 출력부에 해당하며 statement는 상태 출력부에 해당한다.
*/
#include <iostream>	
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

int map[10][20]{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};  // 맵은 아이템(1)이 가득 차 있으며 Monster(2)들이 먹은 자리는 빈자리(0)이 된다.

class Monster {
public:
	int y;					// 몬스터의 현재 y좌표
	int x;					// 몬스터의 현재 x좌표
	int foodcount = 0;		// 몬스터가 먹은 아이템의 개수
	int movingcount = 0;	// 몬스터가 움직인 횟수
	string name;			// 몬스터의 이름
	string symbol;			// 몬스터의 상징(화면상에 출력되는 모양)
	Monster();
	Monster(int a);
	Monster(int a, int b);

	void moving(int* a, int* b);
};

Monster::Monster() {		// Monster()과 같은 형태인 경우 몬스터의 현재 x좌표는 1, y좌표는 1이다.
	x = 1;
	y = 1;
}

Monster::Monster(int a) {	// Monster(int a)와 같은 형태인 경우 몬스터의 현재 x좌표는 a, y좌표는 1이다.
	x = a;
	y = 1;
}

Monster::Monster(int a, int b) {	// Monster(int a, int b)와 같은 형태인 경우 몬스터의 현재 x좌표는 a, y좌표는 b이다.
	x = a;
	y = b;
}

void Monster::moving(int* a, int* b) {	// 몬스터를 움직이게 하고 그 정보를 저장하는 함수
	srand(time(NULL));
	int checkcount = 0;		// 제대로 이동이 이루어졌는지 확인하기 위한 변수(이동할 경우 1이됨, 이동을 안한 경우 0이 유지됨)
	map[*b][*a] = 0;		// 이동전 위치한 곳을 빈 공간(0)으로 만듦(이동을 위한 준비(이동 전 위치를 지우고 이동 후 위치를 표시하기 위함))
	do {
		int i = rand() % 8;	// rand으로 0~7의 값을 받아 0일 경우 좌상측, 1일경우 상측, 2일경우 우상측, 3일경우 좌측, 4일경우 우측, 5일경우 좌하측, 6일경우 하측, 7일경우 우하측으로 이동한다.
		switch (i) {
		case 0:												// 0인 경우 좌상측으로 이동
			if (*a != 0 && *b != 0) {						// 좌상측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b - 1][*a - 1] != 2) {				// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b - 1][*a - 1] == 1) {			// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b - 1][*a - 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;
						*b = *b - 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						foodcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
						movingcount++;
					}
					else if (map[*b - 1][*a - 1] == 0) {	// 아이템이 없는 경우
						map[*b - 1][*a - 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;						
						*b = *b - 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 이동 횟수도 증가한다.
					}
				}
			}
			break;
		case 1:												// 1인 경우 상측으로 이동
			if (*b != 0) {									// 상측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b - 1][*a] != 2) {					// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b - 1][*a] == 1) {				// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b - 1][*a] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*b = *b - 1;
						checkcount = 1;
						foodcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
					}
					else if (map[*b - 1][*a] == 0) {		// 아이템이 없는 경우
						map[*b - 1][*a] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*b = *b - 1;
						checkcount = 1;
						movingcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
					}										// 이동 횟수도 증가한다.
				}
			}
			break;
		case 2:												// 2인 경우 우상측으로 이동
			if (*a != 19 && *b != 0) {						// 우상측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b - 1][*a + 1] != 2) {				// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b - 1][*a + 1] == 1) {			// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b - 1][*a + 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						*b = *b - 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						foodcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
						movingcount++;
					}
					else if (map[*b - 1][*a + 1] == 0) {	// 아이템이 없는 경우
						map[*b - 1][*a + 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						*b = *b - 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 이동 횟수도 증가한다.
					}
				}
			}
			break;
		case 3:												// 3인 경우 좌측으로 이동
			if (*a != 0) {									// 좌측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b][*a - 1] != 2) {					// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b][*a - 1] == 1) {				// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b][*a - 1] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;
						checkcount = 1;
						foodcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
					}
					else if (map[*b][*a - 1] == 0) {		// 아이템이 없는 경우
						map[*b][*a - 1] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;
						checkcount = 1;
						movingcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
					}										// 이동 횟수도 증가한다.
				}
			}
			break;
		case 4:												// 4인 경우 우측으로 이동
			if (*a != 19) {									// 우측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b][*a + 1] != 2) {					// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b][*a + 1] == 1) {				// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b][*a + 1] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						checkcount = 1;
						foodcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
					}
					else if (map[*b][*a + 1] == 0) {		// 아이템이 없는 경우
						map[*b][*a + 1] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						checkcount = 1;
						movingcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
					}										// 이동 횟수도 증가한다.
				}
			}
			break;
		case 5:												// 5인 경우 좌하측으로 이동
			if (*a != 0 && *b != 9) {						// 좌하측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b + 1][*a - 1] != 2) {				// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b + 1][*a - 1] == 1) {			// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b + 1][*a - 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;
						*b = *b + 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						foodcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
						movingcount++;
					}
					else if (map[*b + 1][*a - 1] == 0) {	// 아이템이 없는 경우
						map[*b + 1][*a - 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a - 1;
						*b = *b + 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 이동 횟수도 증가한다.
					}
				}
			}
			break;
		case 6:												// 6인 경우 하측으로 이동
			if (*b != 9) {									// 하측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b + 1][*a] != 2) {					// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b + 1][*a] == 1) {				// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b + 1][*a] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*b = *b + 1;
						checkcount = 1;
						foodcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
					}
					else if (map[*b + 1][*a] == 0) {		// 아이템이 없는 경우
						map[*b + 1][*a] = 2;				// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*b = *b + 1;
						checkcount = 1;
						movingcount++;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
					}										// 이동 횟수도 증가한다.
				}
			}
			break;
		case 7:												// 7인 경우 우하측으로 이동
			if (*a != 19 && *b != 9) {						// 우하측으로 이동할 수 없는 경우 do while문으로 다른 곳으로 이동
				if (map[*b + 1][*a + 1] != 2) {				// 해당 좌표가 Monster가 위치한 곳인 경우 do while문으로 다른 곳으로 이동
					if (map[*b + 1][*a + 1] == 1) {			// 위 두 경우가 아니라면 이동할 수 있는 좌표이며 아이템이 있는 경우 
						map[*b + 1][*a + 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						*b = *b + 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						foodcount++;						// 아이템을 얻었으므로 해당 몬스터의 foodcount가 증가되고 이동 횟수도 증가한다.
						movingcount++;
					}
					else if (map[*b + 1][*a + 1] == 0) {	// 아이템이 없는 경우
						map[*b + 1][*a + 1] = 2;			// 해당 좌표로 이동(2를 map에 저장)하고 이동한 그 좌표를 Monster의 x, y에 저장하며
						*a = *a + 1;
						*b = *b + 1;
						checkcount = 1;						// 이동을 하였으므로 checkcount가 1이 되어 do while문을 빠져나간다.
						movingcount++;						// 이동 횟수도 증가한다.
					}
				}
			}
		}
	} while (checkcount == 0);	// checkcount가 1이 될 때까지(이동을 할 때까지) do while문 반복
}

void statement(Monster m1, Monster m2, Monster m3, Monster m4, Monster m5) {	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다
	cout << "전체 이동 횟수 = " << m1.movingcount + m2.movingcount + m3.movingcount + m4.movingcount + m5.movingcount << endl;		
	cout << "남은 아이템 수 = " << 195 - (m1.foodcount + m2.foodcount + m3.foodcount + m4.movingcount + m5.movingcount) << endl;
	cout << "       " << m1.name << m1.symbol << m1.foodcount << endl;
	cout << "       " << m2.name << m2.symbol << m2.foodcount << endl;
	cout << "       " << m3.name << m3.symbol << m3.foodcount << endl;
	cout << "       " << m4.name << m4.symbol << m4.foodcount << endl;
	cout << "       " << m5.name << m5.symbol << m5.foodcount << endl;
}

void showing(Monster m1, Monster m2, Monster m3, Monster m4, Monster m5) {		// map과 Monster들의 정보를 토대로 각 Monster의 현재 위치와 아이템이 있는 지역과 없는 지역을 화면상에 출력한다
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == m1.y && j == m1.x) {
				cout << m1.symbol;
			}
			else if (i == m2.y && j == m2.x) {
				cout << m2.symbol;
			}
			else if (i == m3.y && j == m3.x) {
				cout << m3.symbol;
			}
			else if (i == m4.y && j == m4.x) {
				cout << m4.symbol;
			}
			else if (i == m5.y && j == m5.x) {
				cout << m5.symbol;
			}
			else if (map[i][j] == 0) {
				cout << "□";
			}
			else if (map[i][j] == 1) {
				cout << "■";
			}
		}
		cout << endl;
	}
	cout << endl;
};
