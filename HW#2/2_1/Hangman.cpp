/*
2019253025 윤광현
문제1 : Hangman 게임
string클래스 사용
이미 예측 되었으면 그 알파벳을 출력하고 아니면 ‘_’문자 출력
게임이 종료되면 “성공” 또는 “실패”를 출력한다.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <Windows.h>
using namespace std;

int main() {
	string str1 = "teacher";	// 랜덤으로 나올 문제 1
	string str2 = "student";	// 랜덤으로 나올 문제 2
	string str3 = "hangman";	// 랜덤으로 나올 문제 3
	string str4 = "tuesday";	// 랜덤으로 나올 문제 4
	string str5 = "rainbow";	// 랜덤으로 나올 문제 5
	string strp = "problem";	// 문제(랜덤으로 위 다섯 문제들중 하나와 swap하여 문제가 됨)
	string stra1 = "_______";	// 현재 자신이 맞춘 상황을 표현하는 answer1
	string stra2;				// 자신이 단어에 들어간다고 생각하는 문자를 입력하는 answer2

	srand(time(NULL));
	int i = rand() % 5 + 1;		// i값을 1~5까지 랜덤으로 선택
	int lifecount = 5;			// 시도할 수 있는 기회는 5번
	int answercount = 0;		// 정답을 맞출경우 1이 됨
	int checknum = -1;			// 단어 비교 및 do while문 안에서 실행을 위한 확인용 숫자

	switch (i) {				// 랜덤으로 선택된 i값을 확인
	case 1: swap(str1, strp);	// 1일 경우 문제는 str1이 됨 (strp와 str1을 스왑함)
		break;
	case 2: swap(str2, strp);	// 2일 경우 문제는 str2가 됨 (strp와 str2를 스왑함)
		break;
	case 3: swap(str3, strp);	// 3일 경우 문제는 str3가 됨 (strp와 str3를 스왑함)
		break;
	case 4: swap(str4, strp);	// 4일 경우 문제는 str4가 됨 (strp와 str4를 스왑함)
		break;
	case 5: swap(str5, strp);	// 5일 경우 문제는 str5가 됨 (strp와 str5를 스왑함)
		break;
	}

	do {
		if (checknum <= -1) {				// checknum이 0이상인 경우 찾으려는 단어가 아직까지 존재하므로 아래 if문을 계속해서 수행하고 -1인 경우 찾으려는 단어가 없거나 첫 시도 이므로 if문을 통해 문자를 입력받음 checknum이 -2인 경우 문자를 하나만 입력한게 아니라 다시 입력하게 됨
			cout << "남은 기회 " << lifecount << "번" << endl;
			cout << "문제:" << stra1 << endl;
			cout << "문자를 입력해 주세요:";
			cin >> stra2;					// stra2에 입력받은 문자 저장
			checknum = strp.find(stra2);	// 문제(strp)에 입력받은 문자(stra2)가 있는지 확인(없다면 checknum에 -1을 저장 있다면 몇번째에 존재하는지 checknum에 저장)
			system("cls");
			if (stra2.length() != 1) {		// 만약 문자를 하나만 입력한게 아니라면 checknum을 -2로 만들어 다시 입력하도록 만듦
				cout << "잘못된 입력입니다. 한 문자만 작성해주세요." << endl;
				checknum = -2;
			}
			if (checknum == -1) {			// checknum이 -1이라면 찾으려는 단어에 그 문자가 없는 것 
				cout << "찾으시려는 단어에 그 문자는 없습니다:" << stra2 << endl;
				lifecount--;				// 남은 기회가 1회 감소됨
			}
		}
		if (checknum >= 0) {					// checknum이 양수인 경우
			switch (checknum) {					// checknum의 숫자로 그 단어의 위치를 알 수 있음
			case 0: stra1.replace(0, 1, stra2);	// 0인경우 문제의 첫번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 첫번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 1);	// 이 뒤에도 동일한 단어가 있을 수 있으므로 이 뒤에 문제에 입력받은 문자가 있는지 확인
				break;
			case 1: stra1.replace(1, 1, stra2);	// 1인경우 문제의 두번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 두번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 2);
				break;
			case 2: stra1.replace(2, 1, stra2);	// 2인경우 문제의 세번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 세번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 3);
				break;
			case 3: stra1.replace(3, 1, stra2);	// 3인경우 문제의 네번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 네번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 4);
				break;
			case 4: stra1.replace(4, 1, stra2);	// 4인경우 문제의 다섯번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 다섯번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 5);
				break;
			case 5: stra1.replace(5, 1, stra2);	// 5인경우 문제의 여섯번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 여섯번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 6);
				break;
			case 6: stra1.replace(6, 1, stra2);	// 6인경우 문제의 일곱번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(stra1)의 일곱번째 단어가 입력한 단어로 변경됨
				checknum = strp.find(stra2, 7);
			}
			cout << "찾으시려는 문자에 그 단어가 있습니다!" << endl;	// 문제에 해당 문자가 있다는 것을 표시
			if (stra1.compare(strp) == 0) {		// 지금까지 정답으로 맞춘 단어들(stra1)과 문제에 해당하는 단어들이 완전히 일치할 경우
				answercount = 1;				// answercount를 1로 바꾸고 do while문을 빠져나옴
			}
		}
	} while (lifecount > 0 && answercount == 0);	// 정답을 맞춰서 answercount가 1이되거나 남은 기회가 0이 될 때까지 반복

	if (lifecount == 0) {	// 남은 기회가 0이 된 경우 실패함
		system("cls");
		cout << "실패입니다. 다음에 다시 도전하세요." << endl;
		cout << "정답: " << strp << endl;
	}
	if (answercount == 1) {	// answercount가 1인 경우 성공함
		system("cls");
		cout << "성공입니다. 축하드립니다!" << endl;
		cout << "정답: " << stra1 << endl;
	}
	return 0;
}