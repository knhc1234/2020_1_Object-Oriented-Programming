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
#include <fstream>
using namespace std;

class StringClass {
public:
	string problem;
	string answer;
	StringClass();
	int CheckAnswer();
};

StringClass::StringClass() {
	srand(time(NULL));
	int i = rand() % 5 + 1;			// i값을 1~5까지 랜덤으로 선택
	switch (i) {					// 랜덤으로 선택된 i값을 확인
	case 1: problem = "teacher";	// 1일 경우 문제는 teacher가 됨 
		break;
	case 2: problem = "student";	// 2일 경우 문제는 student가 됨 
		break;
	case 3: problem = "hangman";	// 3일 경우 문제는 hangman이 됨 
		break;
	case 4: problem = "tuesday";	// 4일 경우 문제는 tuesday가 됨 
		break;
	case 5: problem = "rainbow";	// 5일 경우 문제는 rainbow가 됨 
		break;
	}
}

int StringClass::CheckAnswer() {

	int line = 0;				// 파일 입출력으로 입력하는 라인(첫번째 라인 = 0)
	int errorcount = 0;			// 시도할 수 있는 기회는 7번(틀린 횟수)
	int answercount = 0;		// 정답을 맞출경우 1이 됨
	int checknum = -1;			// 단어 비교 및 do while문 안에서 실행을 위한 확인용 숫자

	answer = "_______";	// 현재 자신이 맞춘 상황을 표현하는 answer
	string answerword;	// 자신이 단어에 들어간다고 생각하는 문자를 입력하는 answerword

	do {
		ifstream in("HangmanProgress.txt");
		char buf[100];

		if (!in.is_open()) {
			cout << "파일을 찾을 수 없습니다!" << std::endl;
			return 0;
		}

		if (checknum <= -1) {				// checknum이 0이상인 경우 찾으려는 단어가 아직까지 존재하므로 아래 if문을 계속해서 수행하고 -1인 경우 찾으려는 단어가 없거나 첫 시도 이므로 if문을 통해 문자를 입력받음 checknum이 -2인 경우 문자를 하나만 입력한게 아니라 다시 입력하게 됨
			while (in) {
				in.getline(buf, 100);		// 한 줄씩 받아서
				if (line > (errorcount + 1) * 8 - 8 && line <= (errorcount + 1) * 8) {	// 남은 기회에 따라 그에 맞는 화면 출력(ex) 남은 기회가 7번인 경우 errorcount는 0이므로 line = 1(두번째 라인)부터 line = 8(아홉번째 라인)까지 출력)
					cout << buf << endl;
					line++;
				}
				else
					line++;
			}
			line = 0;	// 라인 초기화
			
			cout << "문제:" << answer << endl;
			cout << "문자를 입력해 주세요:";
			cin >> answerword;						// answerword에 입력받은 문자 저장
			checknum = problem.find(answerword);	// 문제에 입력받은 문자가 있는지 확인(없다면 checknum에 -1을 저장 있다면 몇번째에 존재하는지 checknum에 저장)
			system("cls");
			if (answerword.length() != 1) {			// 만약 문자를 하나만 입력한게 아니라면 checknum을 -2로 만들어 다시 입력하도록 만듦
				cout << "잘못된 입력입니다. 한 문자만 작성해주세요." << endl;
				checknum = -2;
			}
			if (checknum == -1) {			// checknum이 -1이라면 찾으려는 단어에 그 문자가 없는 것 
				cout << "찾으시려는 단어에 그 문자는 없습니다:" << answerword << endl;
				errorcount++;				// 틀린 횟수가 1회 증가됨
			}
		}

		if (checknum >= 0) {					// checknum이 양수인 경우
			switch (checknum) {					// checknum의 숫자로 그 단어의 위치를 알 수 있음
			case 0: answer.replace(0, 1, answerword);	// 0인경우 문제의 첫번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 첫번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 1);	// 이 뒤에도 동일한 단어가 있을 수 있으므로 이 뒤에 문제에 입력받은 문자가 있는지 확인
				break;
			case 1: answer.replace(1, 1, answerword);	// 1인경우 문제의 두번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 두번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 2);
				break;
			case 2: answer.replace(2, 1, answerword);	// 2인경우 문제의 세번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 세번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 3);
				break;
			case 3: answer.replace(3, 1, answerword);	// 3인경우 문제의 네번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 네번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 4);
				break;
			case 4: answer.replace(4, 1, answerword);	// 4인경우 문제의 다섯번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 다섯번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 5);
				break;
			case 5: answer.replace(5, 1, answerword);	// 5인경우 문제의 여섯번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 여섯번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 6);
				break;
			case 6: answer.replace(6, 1, answerword);	// 6인경우 문제의 일곱번째 단어가 입력한 단어와 동일하므로 현재까지 맞춘 정답(answer)의 일곱번째 단어가 입력한 단어로 변경됨
				checknum = problem.find(answerword, 7);
			}
			cout << "찾으시려는 문자에 그 단어가 있습니다!" << endl;	// 문제에 해당 문자가 있다는 것을 표시
			if (answer.compare(problem) == 0) {		// 지금까지 정답으로 맞춘 단어들(answer)과 문제에 해당하는 단어들이 완전히 일치할 경우
				answercount = 1;					// answercount를 1로 바꾸고 do while문을 빠져나옴
			}
		}
	} while (errorcount < 7 && answercount == 0);	// 정답을 맞춰서 answercount가 1이되거나 남은 기회가 0(틀린 횟수가 7번)이 될 때까지 반복

	if (errorcount == 7) {	// 남은 기회가 0(틀린 횟수가 7번)이 된 경우 실패함
		system("cls");
		ifstream in("HangmanProgress.txt");
		char buf[100];

		while (in) {
			in.getline(buf, 100);		// 한 줄씩 받아서
			if (line > (errorcount + 1) * 8 - 8 && line <= (errorcount + 1) * 8) {	// 남은 기회에 따라 그에 맞는 화면 출력(ex) 남은 기회가 7번인 경우 errorcount는 0이므로 line = 1(두번째 라인)부터 line = 8(아홉번째 라인)까지 출력)
				cout << buf << endl;
				line++;
			}
			else
				line++;
		}

		cout << "실패입니다. 다음에 다시 도전하세요." << endl;
		cout << "정답: " << problem << endl;
	}
	if (answercount == 1) {	// answercount가 1인 경우 성공함
		system("cls");
		cout << "성공입니다. 축하드립니다!" << endl;
		cout << "정답: " << answer << endl;
	}

	return 0;
}

int main() {

	StringClass problem1;
	problem1.CheckAnswer();

	return 0;
}