#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

class Num {
public:
	int checknum;		// Num(a)를 통해 a가 1이면 홀수만 뽑도록 1이 되며 a가 2면 짝수만 뽑도록 2가 된다.
	Num(int a);
	void next();		// 0~Rand_MAX값 사이에서 checknum에 따라 홀수 또는 짝수만 10개 출력
	void next_range(int a, int b);	// a~b의 값들 사이에서 checknum에 따라 홀수 또는 짝수만 10개 출력
};

Num::Num(int a) {
	if (a % 2 == 1) {	// a가 1인 경우 홀수, a가 2인 경우 짝수만 선택하도록 설정
		checknum = 1;
	}
	else
		checknum = 2;
}

void Num::next() {	// 0~Rand_MAX값 사이에서 checknum에 따라 홀수 또는 짝수만 10개 출력
	srand(time(NULL));
	int checkcount = 0;			// 출력 횟수가 10이 되면 반복문을 종료하도록 하기 위한 변수(일종의 출력 횟수)
	while (checkcount < 10) {	// 10번 반복
		int answer = rand() % (RAND_MAX + 1);	// 랜덤 값을 얻음
		
		if (checknum == 1) {			// checknum이 1(홀수를 선택)인 경우
			if (answer % 2 == 1) {		// 랜덤으로 뽑은 숫자가 홀수인 경우(짝수인 경우 출력 x 다시 선택)
				cout << answer << " ";	// 출력
				checkcount++;			// 출력했으므로 출력 횟수 1 증가
			}
		}
		
		else if (checknum == 2) {		// checknum이 2(짝수를 선택)인 경우
			if (answer % 2 == 0) {		// 랜덤으로 뽑은 숫자가 짝수인 경우(홀수인 경우 출력 x 다시 선택)
				cout << answer << " ";	// 출력
				checkcount++;			// 출력했으므로 출력 횟수 1 증가
			}
		}
	}
	cout << endl;
}

void Num::next_range(int a, int b) {	// a~b의 값들 사이에서 checknum에 따라 홀수 또는 짝수만 10개 출력
	srand(time(NULL));
	int checkcount = 0;			// 출력 횟수가 10이 되면 반복문을 종료하도록 하기 위한 변수(일종의 출력 횟수)
	while (checkcount < 10) {	// 10번 반복
		int answer = rand() % (RAND_MAX + 1);	// 랜덤 값을 얻음

		if (answer<a || answer>b) {
			// 범위가 아니므로 다시 시도
		}

		else {	// 범위에 포함 되는 경우
			if (checknum == 1) {			// checknum이 1(홀수를 선택)인 경우
				if (answer % 2 == 1) {		// 랜덤으로 뽑은 숫자가 홀수인 경우(짝수인 경우 출력 x 다시 선택)
					cout << answer << " ";	// 출력
					checkcount++;			// 출력했으므로 출력 횟수 1 증가
				}
			}

			else if (checknum == 2) {		// checknum이 2(짝수를 선택)인 경우
				if (answer % 2 == 0) {		// 랜덤으로 뽑은 숫자가 짝수인 경우(홀수인 경우 출력 x 다시 선택)
					cout << answer << " ";	// 출력
					checkcount++;			// 출력했으므로 출력 횟수 1 증가
				}
			}
		}
	}
	cout << endl;
}

int main(void) {

	int a;	// 홀수 짝수를 결정하는 변수
	while (1) {
		cout << "홀수(1), 짝수(2)를 선택해주세요.: ";
		cin >> a;
		if (a == 1) {		// 1(홀수)을 고른 경우 반복문을 빠져나옴
			break;
		}
		else if (a == 2) {	// 2(짝수)를 고른 경우 반복문을 빠져나옴
			break;
		}
		else {				// 1,2를 고르지 않은 경우 잘못된 값을 고른 것이므로 다시 선택
			cout << "잘못된 입력입니다." << endl;
		}
	}
	
	Num answer1(a);			
	answer1.next();			// 0~RAND_MAX사이에서 10개의 홀수또는 짝수값 출력
	
	while (1) {
		cout << "홀수(1), 짝수(2)를 선택해주세요.: ";
		cin >> a;
		if (a == 1) {		// 1(홀수)을 고른 경우 반복문을 빠져나옴
			break;
		}
		else if (a == 2) {	// 2(짝수)를 고른 경우 반복문을 빠져나옴
			break;
		}
		else {				// 1,2를 고르지 않은 경우 잘못된 값을 고른 것이므로 다시 선택
			cout << "잘못된 입력입니다." << endl;
		}
	}
	
	Num answer2(a);				
	answer2.next_range(2, 50);	// 범위(이 경우 2부터 50)사이에서 10개의 홀수또는 짝수값 출력

	return 0;
}