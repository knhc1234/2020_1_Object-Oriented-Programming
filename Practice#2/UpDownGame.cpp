#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "UpDownGame.h"
#include "Player.h"

// static 멤버 변수의 메모리 할당을 위한 선언
int UpDownGame::answer = 9; // 디폴트
int UpDownGame::top = 99; // 디폴트
int UpDownGame::bottom = 0; // 디폴트

void UpDownGame::run() {	// 루프를 돌면서 게임을 진행하는 함수
	Player players[2] = { Player("안혜선"),Player("길라임") };

	cout << " 게임을 시작합니다." << endl;
	init(); // 램던 시드 설정과 문제로 사용할 랜덤 정답 생성

	int i=0;
	while(true) {
		msg();
		if(players[i].go()) {
			cout << players[i].getName() << "이 이겼습니다!!" << endl;
			break; // i 번째 선수가 이겼음
		}
		i++;
		i = i%2; // 0과 1을 번갈아 나오게 하기 위함
	}
}

void UpDownGame::init() { // answer 변수 랜덤 초기화
	srand((unsigned)time(0)); // 시작할 때마다, 다른 랜덤수를 발생시키기 위한 seed 설정
	int n = rand(); // 0에서 RAND_MAX(32767) 사이의 랜덤한 정수가 n에 발생
	answer = n % 100;
}

bool UpDownGame::check(int a) { // top과 bottom을 조절하고, 정답을 맞추었으면 true 리턴
	if(a < bottom || a > top) return false; // 범위를 벗어난 잘못된 입력
	if(answer == a)
		return true; // win!!

	if(a > answer) 
		top = a;
	else
		bottom = a;
	return false;
}

void UpDownGame::msg() {
	cout << "답은 " << bottom << "과 " << top << "사이에 있습니다." << endl;
}