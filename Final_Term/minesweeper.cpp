#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"winmm.lib")
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#define SPACE 32		// 키보드의 ASC값
#define ENTER 13		
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

#define BOMB -1
#define WALL -2
#define CHECK 1
#define FLAG 2

#define Music "Rhythm_Canon.wav"										// 음악 파일명

#define col GetStdHandle(STD_OUTPUT_HANDLE)								// 콘솔창의 핸들정보를 받아옴
#define RED SetConsoleTextAttribute(col,0x000c);						// 빨간색
#define BLUE SetConsoleTextAttribute(col,0x0001 | 0x0008);				// 파란색
#define YELGREEN SetConsoleTextAttribute(col, 0x00a);					// 연두색
#define YELLOW SetConsoleTextAttribute(col,0x000e);						// 노란색
#define GREEN SetConsoleTextAttribute(col,0x0002);						// 초록색
#define SKY SetConsoleTextAttribute(col, 0x000b);						// 하늘색

void gotoxy(int x, int y);

class GameMap {				// 게임의 기록 영역(지뢰 배치)
	int minemap[22][22];	// 게임 화면(0이상: 근처의 지뢰 수(지뢰 없음), -1: 지뢰 있음, -2: 벽)
public:
	int return_minemap(int i, int j);	// minemap을 확인할 때 이용하는 함수
	void made_minemap();				// minemap을 벽(-2), 지뢰(-1), 빈칸(0)으로 채움
	int made2_minemap();				// minemap에서 빈칸인 부분을 주변의 지뢰숫자로 채우고 총 지뢰수를 리턴
};

class RecordMap {	// 게임의 기록 및 일부 실행 영역(현재 보이는 화면을 다룸)	
	int checkmap[22][22];			// 현재 맵 상황(0: 확인 안함, 1: 확인 함, 2: flag)
public:
	int return_checkmap(int i, int j);	// checkmap을 확인할 때 이용하는 함수
	void reset_checkmap();				// checkmap을 0으로 초기화함
	virtual void print_map() = 0;		// 현재 맵 상황 출력(checkmap으로 확인한 상황)
	void get_checkmap(int i, int j);	// checkmap을 변경함(ENTER키로 확인할 때)
	void flag_checkmap(int i, int j);	// checkmap에 flag를 설정함(SPACE로 flag 설치 및 해제)
};

int GameMap::return_minemap(int i, int j) {	// 해당 minemap 값을 리턴
	return this->minemap[i][j];
}

void GameMap::made_minemap() {	// minemap에 지뢰를 넣음
	int x;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			if (i == 0 || i == 21 || j == 0 || j == 21) {	// 가장 끝쪽 부분들은 벽(-2)
				minemap[i][j] = WALL;
			}
			else {
				x = rand() % 5 - 1;	// 0이상: 지뢰 아님, -1: 지뢰	지뢰 수를 대략 80개 정도로 생성
				if (x == BOMB) {
					minemap[i][j] = BOMB;
				}
				else {
					minemap[i][j] = 0;
				}
			}
		}
	}
}

int GameMap::made2_minemap() {		// 지뢰가 없는 칸에 근처의 지뢰수를 계산하여 minemap에 정보 삽입
	int count;
	int totalcount = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 21; j++) {
			count = 0;					// 주변의 지뢰 칸수 0으로 초기화하여 다시 계산
			if (minemap[i][j] != -1) {	// 해당 칸이 지뢰가 아니라면 주변의 8방향을 조사하여 지뢰의 수만큼 count증가하여 
				if (minemap[i - 1][j - 1] == BOMB) {
					count++;
				}
				if (minemap[i - 1][j] == BOMB) {
					count++;
				}
				if (minemap[i - 1][j + 1] == BOMB) {
					count++;
				}
				if (minemap[i][j - 1] == BOMB) {
					count++;
				}
				if (minemap[i][j + 1] == BOMB) {
					count++;
				}
				if (minemap[i + 1][j - 1] == BOMB) {
					count++;
				}
				if (minemap[i + 1][j] == BOMB) {
					count++;
				}
				if (minemap[i + 1][j + 1] == BOMB) {
					count++;
				}
				minemap[i][j] = count;		// minemap에 주변의 지뢰 수 저장
			}
			else
				totalcount++;
		}
	}
	return totalcount;
}

int RecordMap::return_checkmap(int i, int j) {	// 해당 checkmap값을 리턴
	return checkmap[i][j];
}

void RecordMap::reset_checkmap() {	// checkmap을 0으로 초기화(1이 되면 ENTER키로 확인한 것, 2가 되면 Flag를 놓은 것)
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			checkmap[i][j] = 0;
		}
	}
}

void RecordMap::get_checkmap(int i, int j) {	// 확인버튼을 눌러 checkmap에 확인했다고(1) 저장
	if (checkmap[i][j] == 0 || checkmap[i][j] == FLAG) {
		checkmap[i][j] = CHECK;
	}
}

void RecordMap::flag_checkmap(int i, int j) {	// Flag 설치 및 해제
	if (checkmap[i][j] == 0) {
		checkmap[i][j] = FLAG;
	}
	else if (checkmap[i][j] == FLAG) {
		checkmap[i][j] = 0;
	}
}   

class Game :public RecordMap ,public GameMap {	// 게임의 실행 영역(게임의 전반적인 모든 것들을 다룸)
	string name;			// 플레이어의 이름
	int score = 0;			// 기록
	int totalcount;			// 남은 지뢰수
public:
	void Opening();			// 타이틀화면(오프닝)
	string return_name();	// 플레이어의 이름 반환(return해줌)
	friend int Modeselect(Game &a);	// 모드 선택(1:게임 시작, 2: 도움말, 3: 랭킹보기, 4: 종료하기)
	void resetinfo();		// 게임 시작시 minemap배열을 초기화하여 새로운 map을 만들고 그 안의 정보를 바탕으로 checkmap을 만들고 만든 화면을 출력
	virtual void print_map();	// 현재 맵 상황 출력(checkmap으로 확인한 상황) 추상클래스 이용
	void PlayGame();		// 게임 진행
	void seeRanking();		// 현재 랭킹 Top 10을 볼 수 있음(파일을 바탕으로)
	void Ranking();			// 새로운 판이 끝난 뒤에 나오는 랭킹(변동이 있다면 반영하여 화면에 출력하고 변동된 내용을 파일에 저장함)
	void Win_Game();		// 게임 승리시 나오는 축하 메세지
};

void Game::resetinfo() {	// 게임을 시작하기 위해 정보 초기화함
	made_minemap();			// minemap을 생성
	this->totalcount = made2_minemap();	// minemap에서 빈칸인 부분을 주변의 지뢰숫자로 채우고 총 지뢰수를 totalcount에 반환 
	reset_checkmap();		// checkmap을 0으로 초기화(아직 아무것도 확인 안한 상태)
	print_map();			// 모든 값들을 초기화(새로운 게임 생성과 같음)하였으므로 화면 출력(게임 진행)
}

void Game::print_map() {	// 게임 화면을 출력
	system("cls");			// 전체 화면 삭제 후 다시 출력
	int x = 13;				// gotoxy의 x좌표
	int y = 8;				// gotoxy의 y좌표
	for (int i = 1; i < 21; i++) {	// 1부터 20까지(0과 21은 벽)
		gotoxy(x, y);		// 해당 출력 위치로 이동
		for (int j = 1; j < 21; j++) {	// 1부터 20까지 (0과 21은 벽)
			if (return_checkmap(i, j) == 0)		// checkmap이 0이라면 아직 확인하지 않은 것이므로 아래와 같이 출력
				cout << "□";
			else if (return_checkmap(i, j) == CHECK) {	//  checkmap이 1이라면 확인한 것이므로 minemap의 값을 출력(주변의 지뢰 수)
				cout << return_minemap(i, j) << " ";
			}
			else
				cout << "♪";			// checkmap이 2라면 flag 표시
		}
		y = y + 1;	// 한줄을 모두 입력했다면 gotoxy의 y좌표값을 1증가하여 출력 반복
	}
	cout << endl;

	SKY;
	gotoxy(10, 6);
	cout << "Player: " << name << "\tScore: " << score << "\t지뢰 수: " << totalcount;				// 게임 화면에 플레이어와 점수, 남은 지뢰수, 키 설명등을 출력
	gotoxy(14, 32);
	cout << "                ※키 설명※";
	gotoxy(10, 34);
	cout << "위: ↑     아래: ↓     왼쪽: ←     오른쪽 : →";
	gotoxy(10, 36);
	cout << "확인하기: ENTER    FLAG(♪): SPACE    지뢰(※)";
	gotoxy(10, 38);
	cout << "종료하기 : ESC";

	gotoxy(0, 0);
}

void Game::Win_Game() {
	system("cls");
	YELLOW;
	int y = 8;
	gotoxy(10, y);
	cout << "축하드립니다! 모든 지뢰를 발견하였습니다!";
	for (y = 9; y < 15; y++) {
		gotoxy(10, y);
		cout << "★★★★★★★★★★★★★★★★★★★★";
	}
	gotoxy(10, y);
	cout << "★★★★★Player: " << name << "\tScore: " << score << "★★★★★";
	for (y = 16; y < 22; y++) {
		gotoxy(10, y);
		cout << "★★★★★★★★★★★★★★★★★★★★";
	}
	gotoxy(10, y);
	cout << "Ranking 보기: Press Any Key";
	_getch();
}

void Game::PlayGame() {
	int x = 13;		// gotoxy를 위한 기본 x좌표값
	int y = 8;		// gotoxy를 위한 기본 y좌표값
	int i;			// checkmap을 확인하기 위한 row값
	int j;			// checkmap을 확인하기 위한 column값
	gotoxy(x, y);	// 화면에 표시된 제일 첫번째 칸 (13,8)로 이동
	while (1) {		// 게임 종료 전까지 게임 진행
		if (score + totalcount == 400) {	// 모든 지뢰를 찾아낸 경우(지뢰를 제외한 모든 칸을 발견) 축하메세지 출력
			Win_Game();
			break;
		}
		i = (y - 8) + 1;		// checkmap을 확인하기 위한 row값 계산
		j = (x - 13) / 2 + 1;	// checkmap을 확인하기 위한 column값 계산
		try {	// 사용되지 않는 입력키를 입력할 경우 예외처리
			int ch = _getch();
			if (ch != ESC && ch != ENTER && ch != SPACE && ch != 224)	// ESC, ENTER, SPACE, 방향키를 제외한 사용되지 않는 입력키를 사용할 경우 예외처리
				throw ch;
			if (ch == ESC) {	// ESC를 누르는 경우 게임을 종료함
				gotoxy(10, 30);
				cout << "게임이 종료됩니다.(ESC) ";
				Sleep(5000);
				break;
			}
			try {
				if (ch == ENTER) {
					if (return_minemap(i, j) == BOMB) {	// 지뢰를 밟은 경우 게임 종료
						cout << "※";	// 해당칸이 지뢰인 경우 지뢰를 표시
						RED;
						gotoxy(10, 30);
						cout << "지뢰를 밟았습니다. 게임 실패(5초 뒤 종료) ";	// 게임 종료 메세지 출력
						Sleep(5000);	// 5초 뒤 종료
						break;
					}
					else {								// 지뢰를 밟지 않은 경우
						if (return_checkmap(i, j) == CHECK)		// 이미 전에 ENTER키로 확인한 부분이라면 throw로 예외처리함
							throw 0;
						else {							// 확인한 부분이 아니라면 ENTER를 입력받아
							get_checkmap(i, j);			// 확인했다고 checkmap에 저장
							score++;					// 점수 1점 증가 (지뢰를 밟지 않았으므로)
							print_map();				// 변경 사항을 다시 보여줌
						}
					}
				}
				if (ch == SPACE) {					// SPACE키를 눌렀을 경우(flag 설정)
					if (return_checkmap(i, j) == CHECK)		// 이미 전에 ENTER키로 확인한 부분이라면 throw로 예외처리함
						throw 0;
					else {								// 확인한 부분이 아니라면
						flag_checkmap(i, j);			// 이전에 flag로 지정한 경우 flag 해제, 아닌 경우 flag로 지정
						print_map();					// 변경 사항을 다시 보여줌
					}
				}
			}
			catch (int inner) {							// 이미 확인된 부분에 ENTER 또는 SPACE를 하는 경우
				RED;									// 붉은색으로 출력
				gotoxy(10, 30);							// 이미 확인한 지점이라고 출력
				cout << "이미 확인한 지점입니다.";
				SKY;									// 하늘색으로 출력
			}
			if (ch == 224) {	// 방향키를 입력한 경우
				ch = _getch();
				try {	// 이동할 수 없는 칸으로 이동하려는 경우 예외 처리를 함
					switch (ch) {
					case UP:
						if (return_minemap(i - 1, j) == WALL)		// 제일 윗칸에서 위로 이동하려는 경우 예외처리
							throw ch;
						else {
							y = y - 1;
							gotoxy(10, 30);		// 위쪽으로 1칸 이동
							cout << "                                          ";	// 오류메세지가 있을 시 제거
						}
						break;
					case DOWN:
						if (return_minemap(i + 1, j) == WALL)		// 제일 아랫칸에서 아래로 이동하려는 경우 예외처리
							throw ch;
						else {
							y = y + 1;
							gotoxy(10, 30);		// 아래쪽으로 1칸 이동
							cout << "                                          ";	// 오류메세지가 있을 시 제거
						}
						break;
					case LEFT:
						if (return_minemap(i, j - 1) == WALL)		// 제일 왼쪽칸에서 왼쪽으로 이동하려는 경우 예외처리
							throw ch;
						else {
							x = x - 2;
							gotoxy(10, 30);		// 왼쪽으로 1칸 이동
							cout << "                                           ";	// 오류메세지가 있을 시 제거
						}
						break;
					case RIGHT:
						if (return_minemap(i, j + 1) == WALL)		// 제일 오른쪽칸에서 오른쪽으로 이동하려는 경우 예외처리
							throw ch;
						else {
							x = x + 2;
							gotoxy(10, 30);		// 오른쪽으로 1칸 이동
							cout << "                                           ";	// 오류메세지가 있을 시 제거
						}
						break;
					}
				}
				catch (int inner) {		// 방향키를 입력할 때 벽 너머로 가려고 할 경우 
					RED;				// 붉은색으로
					gotoxy(10, 30);
					cout << "벽 너머로 이동할 수 없습니다.";	// 벽 너머로 이동할 수 없다고 출력
					SKY;	// 하늘색으로 되돌림
				}
			}
			gotoxy(x, y);
		}
		catch (int outer) {		// 잘못된 입력을 받아들였을 때
			RED;				// 붉은색으로 
			gotoxy(10, 30);
			cout << "ESC ENTER SPACE ↑ ↓ ← → 로 입력해주세요.";	// 이와 같은 명령어만 입력 가능함을 출력
			SKY;	// 하늘색으로 되돌림
		}
	}
}

void gotoxy(int x, int y) {	// 좌표 설정 함수
	COORD Position;
	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

void Game::Opening() {						// 시작 시 화면 하늘색으로 출력 오프닝 화면 출력
	SKY;
	gotoxy(36, 10);
	cout << "★★지뢰찾기★★";
	gotoxy(32, 17);
	cout << "제작자: 2019253025 윤광현";
	gotoxy(32, 24);
	cout << "이름을 입력해주세요: ";		// 이름을 입력받음(플레이어의 기록 저장 시 이용)
	cin >> this->name;
	gotoxy(32, 27);
	cout << "환영합니다! " << this->name << "님!" << endl;
	Sleep(3000);
}

int Modeselect(Game &a) {			
	gotoxy(31, 7);
	cout << "Player: " << a.return_name();	// Game a의 플레이어 이름을 받아서 출력
	gotoxy(31, 10);
	cout << "모드를 선택하시오";
	RED;							// 빨간색으로 게임 시작: 출력
	gotoxy(31, 13);
	cout << "게임 시작";
	gotoxy(50, 13);
	cout << ":";
	BLUE;							// 파란색으로 도움말: 출력
	gotoxy(31, 16);
	cout << "도움말";
	gotoxy(50, 16);
	cout << ":";
	YELLOW;							// 노란색으로 랭킹: 출력
	gotoxy(31, 19);
	cout << "랭킹";
	gotoxy(50, 19);
	cout << ":";
	GREEN;							// 초록색으로 종료하기: 출력
	gotoxy(31, 22);
	cout << "종료하기";
	gotoxy(50, 22);
	cout << ":";
	SKY;							// 하늘색으로 "선 택: Enter or Space"설명과 화살표 출력
	gotoxy(31, 24);
	cout << "선 택: Enter or Space";
	gotoxy(55, 13);
	cout << "←";

	int x = 55, y = 13, key = 72;	// 화살표가 처음 위치한 x좌표와 y좌표값 저장

	while (key != ENTER && key != SPACE) {		// ENTER나 SPACE를 입력할 때 까지 반복(선택 전까지 화살표 이동 가능)
		if (_kbhit() != 0) {
			key = _getch();						// 키보드 입력을 받음
			gotoxy(31, 30);
			cout << "                                   ";	// 출력된 에러 메세지 삭제용
			try {
				if (key != 224 && key != ENTER && key != SPACE)	// 방향키, ENTER, SPACE를 제외한 키를 입력한 경우 예외처리
					throw key;
				if (key == 224) {					// 방향키를 눌렀을 경우 224를 반환받고 다시 한번 반환값을 받으므로
					key = _getch();					// 해당 방향키에 대한 정보를 얻음
					if (key != UP && key != DOWN)	// 방향키를 눌렀는데 위쪽, 아래쪽 방향키가 아닌 경우 예외처리
						throw key;
				}
				try {
					switch (key) {
					case UP:							// 위쪽 방향키인 경우
						if (y == 13) {					// 제일 윗칸인 경우 위로 이동 불가이므로 예외 처리
							throw y;
						}
						else {							// 그 외의 경우
							gotoxy(x, y);
							cout << "  ";				// 현재 위치의 화살표를 지우고(잔상 제거)
							y = y - 3;
							gotoxy(x, y);
							cout << "←";				// 한 칸 윗칸으로 이동
						}
						break;
					case DOWN:							// 아랫쪽 방향키인 경우 
						if (y == 22) {					// 제일 아랫칸인 경우 아래로 이동 불가이므로 예외처리
							throw y;
						}
						else {							// 그 외의 경우
							gotoxy(x, y);
							cout << "  ";				// 현재 위치의 화살표를 지우고(잔상 제거)
							y = y + 3;
							gotoxy(x, y);
							cout << "←";				// 한 칸 아랫칸으로 이동
						}
						break;
					case ENTER:							// ENTER나 SPACE 입력 시(결정)
					case SPACE:
						if (y == 13)
							return 1;				// '게임 시작'은 mode에 1 반환
						else if (y == 16)
							return 2;				// '도움말'은 mode에 2 반환
						else if (y == 19)
							return 3;				// '이어하기'은 mode에 3 반환
						else if (y == 22)
							return 4;				// '종료하기'는 mode에 4 반환
						break;
					}
				}
				catch (int inner) {		// 제일 위쪽에서 위쪽으로, 제일 아래쪽에서 아래쪽으로 이동시 이동 불가능하다고 출력
					gotoxy(31, 30);
					cout << "해당 방향으로는 이동이 불가능합니다.";
				}
			}
			catch (int outer) {		// 방향키, ENTER, SPACE를 제외한 키를 입력한 경우 해당 키로만 입력해달라고 출력
				gotoxy(31, 30);
				cout << "ENTER SPACE ↑ ↓로 입력해주세요.";
			}
		}
	}
}

string Game::return_name() {	// 클래스 Game의 name을 리턴
	return this->name;
}

void Game::seeRanking() {	// 현재 top 10 랭킹을 보는 함수
	vector<int> v(10);		// int 형 벡터 생성(10칸짜리)
	vector<string> s = { "-", "-" , "-" , "-", "-", "-", "-", "-", "-", "-" };	// string형 벡터 생성(10개짜리)
	int getscore;			// 입력받은 점수
	string getname = "";	// 입력받은 이름
	int i = 0;				// 총 10개만 읽기 위한 변수
	ifstream in("Ranking.txt");	// Ranking.txt를 읽음
	if (in.is_open()) {		// 파일을 읽는데 성공했다면
		while (i != 10) {	// 해당 파일을 읽음(top 10)
			getname = "";	// getname 초기화
			char c;	
			do {
				in.get(c);	// ' '전까지 단어를 입력받음
				if (c != ' ' && c != '\n')
					getname = getname + c;	// ' ', '\n'이 아니라면 입력받은 단어를 getname에 이어 붙임
			} while (c != ' ');	// ' '을 입력받은 경우 while문 탈출(이름 점수 순으로 txt파일에 적혀있기 때문)
			in >> getscore;		// 점수를 입력받음
			v[i] = getscore;	// v[i]에 점수를
			s[i] = getname;		// s[i]에 이름을 입력함
			i++;				// i 1증가
		}
	}
	in.close();		// 파일을 닫음
	system("cls");	// 화면 초기화
	YELLOW;			// 노란색으로 출력
	gotoxy(38, 8);
	cout << "★★Ranking Top 10★★" << endl;	// 읽어들인 Top 10을 출력함
	for (int i = 0; i < 10; i++) {
		gotoxy(32, 10 + 2 * i);
		cout << i + 1 << "등\t" << "Player: " << s.at(i) << "\tScore: " << v.at(i) << endl;
	}
	gotoxy(32, 30);
	cout << "Press Any Key to exit";
	_getch();	// 아무 버튼을 입력하면 메뉴화면으로 돌아감
	SKY;			// 하늘색으로 출력
}

template <class T>
void myswap(T& a, T& b) {	// swap함수(Ranking변동시에 사용)
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void Game::Ranking() {	// 게임이 끝나고 플레이어의 기록과 변동된 랭킹을 출력하고 이를 파일에 저장
	vector<int> v(10);	// int 형 벡터 생성(10칸짜리)
	int getscore;		// 랭킹 변동및 파일 데이터 처리시 이용되는 변수	
	int i = 0;			// 총 10개만 읽기 위한 변수
	vector<string> s = { "-", "-" , "-" , "-", "-", "-", "-", "-", "-", "-" };	// string형 벡터 생성(10개짜리)
	string getname = "";		// 랭킹 변동및 파일 데이터 처리시 이용되는 변수
	ifstream in("Ranking.txt");		// Ranking.txt를 읽음
	if (in.is_open()) {			// 파일을 읽는데 성공했다면
		while (i != 10) {		// 해당 파일을 읽음(top 10)
			getname = "";		// getname 초기화
			char c;
			do {
				in.get(c);		// ' '전까지 단어를 입력받음
				if (c != ' ' && c != '\n')
					getname = getname + c;	// ' ', '\n'이 아니라면 입력받은 단어를 getname에 이어 붙임
			} while (c != ' ');	// ' '을 입력받은 경우 while문 탈출(이름 점수 순으로 txt파일에 적혀있기 때문)
			in >> getscore;		// 점수를 입력받음
			v[i] = getscore;	// v[i]에 점수를
			s[i] = getname;		// s[i]에 이름을 입력함
			i++;				// i 1증가
		}
	}
	in.close();			// 파일을 닫음
	getscore = score;	// 이번 게임의 기록을 getscore에 저장
	getname = name;		// 게임을 플레이 한 플레이어의 이름을 getname에 저장
	for (int i = 0; i < 10; i++) {	
		if (getscore >= v.at(i)) {	// v[i]에 저장된 기록보다 이번 게임의 기록이 크거나 같은 경우
			myswap(getscore, v[i]);	// 순위 변동
			myswap(getname, s[i]);	// 이름도 그에 따라 변경
		}
	}
	system("cls");		// 화면 초기화
	YELLOW;				// 노란색으로 출력
	gotoxy(38, 8);
	cout << "★★Ranking Top 10★★" << endl;	// 변동 된 Top 10을 출력함
	for (int i = 0; i < 10; i++) {
		gotoxy(32, 10 + 2 * i);
		cout << i + 1 << "등\t" << "Player: " << s.at(i) << "\tScore: " << v.at(i) << endl;
	}

	gotoxy(32, 30);	// 이번 게임의 기록과 플레이어 이름도 출력함
	cout << "이번 기록\t" << "Player: " << name << "\tScore: " << score << endl;
	gotoxy(24, 32);	// 감사메시지
	cout << "게임을 플레이해 주셔서 감사합니다. -제작자: 윤광현-" << endl;
	ofstream out("Ranking.txt");	// Ranking.txt파일을 열음
	if (out.is_open()) {			// 변동 된 순위 정보 저장
		for (int i = 0; i < 10; i++) {
			out << s.at(i) << " ";
			out << v.at(i) << endl;
		}
	}
}

void Help() {		// 도움말 내용 출력
	system("cls");
	YELGREEN;
	gotoxy(26, 10);
	cout << "도움말";
	gotoxy(26, 12);
	cout << "이 게임은 지뢰찾기 입니다.";
	gotoxy(26, 14);
	cout << "방향키로 이동을 하실 수 있으며";
	gotoxy(26, 16);
	cout << "ENTER키로 결정을 하실 수 있습니다.";
	gotoxy(26, 18);
	cout << "만약 선택하신 칸이 지뢰라면 게임이 끝납니다.";
	gotoxy(26, 20);
	cout << "만약 선택하신 칸이 지뢰가 아니라면 근처의 지뢰수를 보여줍니다.";
	gotoxy(26, 22);
	SKY;
	cout << "이를 보고 지뢰일 것 같은 칸을 예측하여";
	gotoxy(26, 24);
	cout << "SPACE키를 누르시면 FLAG(♪)를 설치 할 수 있습니다.";
	gotoxy(26, 26);
	cout << "그 자리에 FLAG(♪)가 있을 때 SPACE를 누른다면 FLAG(♪)를 해제합니다.";
	gotoxy(26, 28);
	cout << "이 FLAG(♪)와 힌트들을 조합하여 지뢰(※)를 건드리지 말고";
	gotoxy(26, 30);
	cout << "끝까지 살아 남으시면 승리입니다.";
	gotoxy(26, 32);
	cout << "나가기: Press Any Key";
	_getch();	// 아무 키나 입력하면 메뉴창으로 돌아감
}

int main(void) {
	int mode = 2;	// 게임의 모드(1: 게임 시작, 2: 도움말, 3: 랭킹, 4: 종료하기) 
	Game a;			// Game에 대한 모든 정보를 다루는 a생성
	system("mode con: cols=100 lines=40");	// 콘솔창 크기 조절 함수
	a.Opening();	// 게임 첫 화면(오프닝), 플레이어의 이름 입력
	PlaySound(Music, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);		// bgm설정 
	while (mode == 2 || mode == 3) {	// 도움말, 랭킹의 경우 끝나면 다시 모드 선택창으로 돌아감
		system("cls");					// 화면 초기화
		mode = Modeselect(a);			// 게임 모드를 선택하기 위한 창 mode값을 리턴함
		if (mode == 2)					// mode가 2인 경우
			Help();						// 도움말 기능
		if (mode == 3)					// mode가 3인 경우
			a.seeRanking();				// 랭킹 기능
	}
	switch (mode) {		
	case 1:				// 모드가 1인 경우
		a.resetinfo();	// 새로운 게임 생성(minemap과 checkmap을 초기화함)
		a.PlayGame();	// 게임을 진행
		a.Ranking();	// 게임이 끝나고(모드1) 이번 게임의 기록과 현재까지의 top 10을 출력하고 top 10에 대한 기록을 파일에 저장함	
		break;			
	case 4:
		system("cls");	// 모드가 4인 경우 프로그램 종료
		gotoxy(31, 15);
		cout << "프로그램을 종료합니다. 다음에 또 플레이 해주세요!" << endl;
		return 0;
	}
	return 0;		// 프로그램 종료
}
