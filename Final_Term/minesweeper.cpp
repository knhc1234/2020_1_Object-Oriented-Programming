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

#define SPACE 32		// Ű������ ASC��
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

#define Music "Rhythm_Canon.wav"										// ���� ���ϸ�

#define col GetStdHandle(STD_OUTPUT_HANDLE)								// �ܼ�â�� �ڵ������� �޾ƿ�
#define RED SetConsoleTextAttribute(col,0x000c);						// ������
#define BLUE SetConsoleTextAttribute(col,0x0001 | 0x0008);				// �Ķ���
#define YELGREEN SetConsoleTextAttribute(col, 0x00a);					// ���λ�
#define YELLOW SetConsoleTextAttribute(col,0x000e);						// �����
#define GREEN SetConsoleTextAttribute(col,0x0002);						// �ʷϻ�
#define SKY SetConsoleTextAttribute(col, 0x000b);						// �ϴû�

void gotoxy(int x, int y);

class GameMap {				// ������ ��� ����(���� ��ġ)
	int minemap[22][22];	// ���� ȭ��(0�̻�: ��ó�� ���� ��(���� ����), -1: ���� ����, -2: ��)
public:
	int return_minemap(int i, int j);	// minemap�� Ȯ���� �� �̿��ϴ� �Լ�
	void made_minemap();				// minemap�� ��(-2), ����(-1), ��ĭ(0)���� ä��
	int made2_minemap();				// minemap���� ��ĭ�� �κ��� �ֺ��� ���ڼ��ڷ� ä��� �� ���ڼ��� ����
};

class RecordMap {	// ������ ��� �� �Ϻ� ���� ����(���� ���̴� ȭ���� �ٷ�)	
	int checkmap[22][22];			// ���� �� ��Ȳ(0: Ȯ�� ����, 1: Ȯ�� ��, 2: flag)
public:
	int return_checkmap(int i, int j);	// checkmap�� Ȯ���� �� �̿��ϴ� �Լ�
	void reset_checkmap();				// checkmap�� 0���� �ʱ�ȭ��
	virtual void print_map() = 0;		// ���� �� ��Ȳ ���(checkmap���� Ȯ���� ��Ȳ)
	void get_checkmap(int i, int j);	// checkmap�� ������(ENTERŰ�� Ȯ���� ��)
	void flag_checkmap(int i, int j);	// checkmap�� flag�� ������(SPACE�� flag ��ġ �� ����)
};

int GameMap::return_minemap(int i, int j) {	// �ش� minemap ���� ����
	return this->minemap[i][j];
}

void GameMap::made_minemap() {	// minemap�� ���ڸ� ����
	int x;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			if (i == 0 || i == 21 || j == 0 || j == 21) {	// ���� ���� �κе��� ��(-2)
				minemap[i][j] = WALL;
			}
			else {
				x = rand() % 5 - 1;	// 0�̻�: ���� �ƴ�, -1: ����	���� ���� �뷫 80�� ������ ����
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

int GameMap::made2_minemap() {		// ���ڰ� ���� ĭ�� ��ó�� ���ڼ��� ����Ͽ� minemap�� ���� ����
	int count;
	int totalcount = 0;
	for (int i = 1; i < 21; i++) {
		for (int j = 1; j < 21; j++) {
			count = 0;					// �ֺ��� ���� ĭ�� 0���� �ʱ�ȭ�Ͽ� �ٽ� ���
			if (minemap[i][j] != -1) {	// �ش� ĭ�� ���ڰ� �ƴ϶�� �ֺ��� 8������ �����Ͽ� ������ ����ŭ count�����Ͽ� 
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
				minemap[i][j] = count;		// minemap�� �ֺ��� ���� �� ����
			}
			else
				totalcount++;
		}
	}
	return totalcount;
}

int RecordMap::return_checkmap(int i, int j) {	// �ش� checkmap���� ����
	return checkmap[i][j];
}

void RecordMap::reset_checkmap() {	// checkmap�� 0���� �ʱ�ȭ(1�� �Ǹ� ENTERŰ�� Ȯ���� ��, 2�� �Ǹ� Flag�� ���� ��)
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			checkmap[i][j] = 0;
		}
	}
}

void RecordMap::get_checkmap(int i, int j) {	// Ȯ�ι�ư�� ���� checkmap�� Ȯ���ߴٰ�(1) ����
	if (checkmap[i][j] == 0 || checkmap[i][j] == FLAG) {
		checkmap[i][j] = CHECK;
	}
}

void RecordMap::flag_checkmap(int i, int j) {	// Flag ��ġ �� ����
	if (checkmap[i][j] == 0) {
		checkmap[i][j] = FLAG;
	}
	else if (checkmap[i][j] == FLAG) {
		checkmap[i][j] = 0;
	}
}   

class Game :public RecordMap ,public GameMap {	// ������ ���� ����(������ �������� ��� �͵��� �ٷ�)
	string name;			// �÷��̾��� �̸�
	int score = 0;			// ���
	int totalcount;			// ���� ���ڼ�
public:
	void Opening();			// Ÿ��Ʋȭ��(������)
	string return_name();	// �÷��̾��� �̸� ��ȯ(return����)
	friend int Modeselect(Game &a);	// ��� ����(1:���� ����, 2: ����, 3: ��ŷ����, 4: �����ϱ�)
	void resetinfo();		// ���� ���۽� minemap�迭�� �ʱ�ȭ�Ͽ� ���ο� map�� ����� �� ���� ������ �������� checkmap�� ����� ���� ȭ���� ���
	virtual void print_map();	// ���� �� ��Ȳ ���(checkmap���� Ȯ���� ��Ȳ) �߻�Ŭ���� �̿�
	void PlayGame();		// ���� ����
	void seeRanking();		// ���� ��ŷ Top 10�� �� �� ����(������ ��������)
	void Ranking();			// ���ο� ���� ���� �ڿ� ������ ��ŷ(������ �ִٸ� �ݿ��Ͽ� ȭ�鿡 ����ϰ� ������ ������ ���Ͽ� ������)
	void Win_Game();		// ���� �¸��� ������ ���� �޼���
};

void Game::resetinfo() {	// ������ �����ϱ� ���� ���� �ʱ�ȭ��
	made_minemap();			// minemap�� ����
	this->totalcount = made2_minemap();	// minemap���� ��ĭ�� �κ��� �ֺ��� ���ڼ��ڷ� ä��� �� ���ڼ��� totalcount�� ��ȯ 
	reset_checkmap();		// checkmap�� 0���� �ʱ�ȭ(���� �ƹ��͵� Ȯ�� ���� ����)
	print_map();			// ��� ������ �ʱ�ȭ(���ο� ���� ������ ����)�Ͽ����Ƿ� ȭ�� ���(���� ����)
}

void Game::print_map() {	// ���� ȭ���� ���
	system("cls");			// ��ü ȭ�� ���� �� �ٽ� ���
	int x = 13;				// gotoxy�� x��ǥ
	int y = 8;				// gotoxy�� y��ǥ
	for (int i = 1; i < 21; i++) {	// 1���� 20����(0�� 21�� ��)
		gotoxy(x, y);		// �ش� ��� ��ġ�� �̵�
		for (int j = 1; j < 21; j++) {	// 1���� 20���� (0�� 21�� ��)
			if (return_checkmap(i, j) == 0)		// checkmap�� 0�̶�� ���� Ȯ������ ���� ���̹Ƿ� �Ʒ��� ���� ���
				cout << "��";
			else if (return_checkmap(i, j) == CHECK) {	//  checkmap�� 1�̶�� Ȯ���� ���̹Ƿ� minemap�� ���� ���(�ֺ��� ���� ��)
				cout << return_minemap(i, j) << " ";
			}
			else
				cout << "��";			// checkmap�� 2��� flag ǥ��
		}
		y = y + 1;	// ������ ��� �Է��ߴٸ� gotoxy�� y��ǥ���� 1�����Ͽ� ��� �ݺ�
	}
	cout << endl;

	SKY;
	gotoxy(10, 6);
	cout << "Player: " << name << "\tScore: " << score << "\t���� ��: " << totalcount;				// ���� ȭ�鿡 �÷��̾�� ����, ���� ���ڼ�, Ű ������� ���
	gotoxy(14, 32);
	cout << "                ��Ű �����";
	gotoxy(10, 34);
	cout << "��: ��     �Ʒ�: ��     ����: ��     ������ : ��";
	gotoxy(10, 36);
	cout << "Ȯ���ϱ�: ENTER    FLAG(��): SPACE    ����(��)";
	gotoxy(10, 38);
	cout << "�����ϱ� : ESC";

	gotoxy(0, 0);
}

void Game::Win_Game() {
	system("cls");
	YELLOW;
	int y = 8;
	gotoxy(10, y);
	cout << "���ϵ帳�ϴ�! ��� ���ڸ� �߰��Ͽ����ϴ�!";
	for (y = 9; y < 15; y++) {
		gotoxy(10, y);
		cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�";
	}
	gotoxy(10, y);
	cout << "�ڡڡڡڡ�Player: " << name << "\tScore: " << score << "�ڡڡڡڡ�";
	for (y = 16; y < 22; y++) {
		gotoxy(10, y);
		cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�";
	}
	gotoxy(10, y);
	cout << "Ranking ����: Press Any Key";
	_getch();
}

void Game::PlayGame() {
	int x = 13;		// gotoxy�� ���� �⺻ x��ǥ��
	int y = 8;		// gotoxy�� ���� �⺻ y��ǥ��
	int i;			// checkmap�� Ȯ���ϱ� ���� row��
	int j;			// checkmap�� Ȯ���ϱ� ���� column��
	gotoxy(x, y);	// ȭ�鿡 ǥ�õ� ���� ù��° ĭ (13,8)�� �̵�
	while (1) {		// ���� ���� ������ ���� ����
		if (score + totalcount == 400) {	// ��� ���ڸ� ã�Ƴ� ���(���ڸ� ������ ��� ĭ�� �߰�) ���ϸ޼��� ���
			Win_Game();
			break;
		}
		i = (y - 8) + 1;		// checkmap�� Ȯ���ϱ� ���� row�� ���
		j = (x - 13) / 2 + 1;	// checkmap�� Ȯ���ϱ� ���� column�� ���
		try {	// ������ �ʴ� �Է�Ű�� �Է��� ��� ����ó��
			int ch = _getch();
			if (ch != ESC && ch != ENTER && ch != SPACE && ch != 224)	// ESC, ENTER, SPACE, ����Ű�� ������ ������ �ʴ� �Է�Ű�� ����� ��� ����ó��
				throw ch;
			if (ch == ESC) {	// ESC�� ������ ��� ������ ������
				gotoxy(10, 30);
				cout << "������ ����˴ϴ�.(ESC) ";
				Sleep(5000);
				break;
			}
			try {
				if (ch == ENTER) {
					if (return_minemap(i, j) == BOMB) {	// ���ڸ� ���� ��� ���� ����
						cout << "��";	// �ش�ĭ�� ������ ��� ���ڸ� ǥ��
						RED;
						gotoxy(10, 30);
						cout << "���ڸ� ��ҽ��ϴ�. ���� ����(5�� �� ����) ";	// ���� ���� �޼��� ���
						Sleep(5000);	// 5�� �� ����
						break;
					}
					else {								// ���ڸ� ���� ���� ���
						if (return_checkmap(i, j) == CHECK)		// �̹� ���� ENTERŰ�� Ȯ���� �κ��̶�� throw�� ����ó����
							throw 0;
						else {							// Ȯ���� �κ��� �ƴ϶�� ENTER�� �Է¹޾�
							get_checkmap(i, j);			// Ȯ���ߴٰ� checkmap�� ����
							score++;					// ���� 1�� ���� (���ڸ� ���� �ʾ����Ƿ�)
							print_map();				// ���� ������ �ٽ� ������
						}
					}
				}
				if (ch == SPACE) {					// SPACEŰ�� ������ ���(flag ����)
					if (return_checkmap(i, j) == CHECK)		// �̹� ���� ENTERŰ�� Ȯ���� �κ��̶�� throw�� ����ó����
						throw 0;
					else {								// Ȯ���� �κ��� �ƴ϶��
						flag_checkmap(i, j);			// ������ flag�� ������ ��� flag ����, �ƴ� ��� flag�� ����
						print_map();					// ���� ������ �ٽ� ������
					}
				}
			}
			catch (int inner) {							// �̹� Ȯ�ε� �κп� ENTER �Ǵ� SPACE�� �ϴ� ���
				RED;									// ���������� ���
				gotoxy(10, 30);							// �̹� Ȯ���� �����̶�� ���
				cout << "�̹� Ȯ���� �����Դϴ�.";
				SKY;									// �ϴû����� ���
			}
			if (ch == 224) {	// ����Ű�� �Է��� ���
				ch = _getch();
				try {	// �̵��� �� ���� ĭ���� �̵��Ϸ��� ��� ���� ó���� ��
					switch (ch) {
					case UP:
						if (return_minemap(i - 1, j) == WALL)		// ���� ��ĭ���� ���� �̵��Ϸ��� ��� ����ó��
							throw ch;
						else {
							y = y - 1;
							gotoxy(10, 30);		// �������� 1ĭ �̵�
							cout << "                                          ";	// �����޼����� ���� �� ����
						}
						break;
					case DOWN:
						if (return_minemap(i + 1, j) == WALL)		// ���� �Ʒ�ĭ���� �Ʒ��� �̵��Ϸ��� ��� ����ó��
							throw ch;
						else {
							y = y + 1;
							gotoxy(10, 30);		// �Ʒ������� 1ĭ �̵�
							cout << "                                          ";	// �����޼����� ���� �� ����
						}
						break;
					case LEFT:
						if (return_minemap(i, j - 1) == WALL)		// ���� ����ĭ���� �������� �̵��Ϸ��� ��� ����ó��
							throw ch;
						else {
							x = x - 2;
							gotoxy(10, 30);		// �������� 1ĭ �̵�
							cout << "                                           ";	// �����޼����� ���� �� ����
						}
						break;
					case RIGHT:
						if (return_minemap(i, j + 1) == WALL)		// ���� ������ĭ���� ���������� �̵��Ϸ��� ��� ����ó��
							throw ch;
						else {
							x = x + 2;
							gotoxy(10, 30);		// ���������� 1ĭ �̵�
							cout << "                                           ";	// �����޼����� ���� �� ����
						}
						break;
					}
				}
				catch (int inner) {		// ����Ű�� �Է��� �� �� �ʸӷ� ������ �� ��� 
					RED;				// ����������
					gotoxy(10, 30);
					cout << "�� �ʸӷ� �̵��� �� �����ϴ�.";	// �� �ʸӷ� �̵��� �� ���ٰ� ���
					SKY;	// �ϴû����� �ǵ���
				}
			}
			gotoxy(x, y);
		}
		catch (int outer) {		// �߸��� �Է��� �޾Ƶ鿴�� ��
			RED;				// ���������� 
			gotoxy(10, 30);
			cout << "ESC ENTER SPACE �� �� �� �� �� �Է����ּ���.";	// �̿� ���� ��ɾ �Է� �������� ���
			SKY;	// �ϴû����� �ǵ���
		}
	}
}

void gotoxy(int x, int y) {	// ��ǥ ���� �Լ�
	COORD Position;
	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

void Game::Opening() {						// ���� �� ȭ�� �ϴû����� ��� ������ ȭ�� ���
	SKY;
	gotoxy(36, 10);
	cout << "�ڡ�����ã��ڡ�";
	gotoxy(32, 17);
	cout << "������: 2019253025 ������";
	gotoxy(32, 24);
	cout << "�̸��� �Է����ּ���: ";		// �̸��� �Է¹���(�÷��̾��� ��� ���� �� �̿�)
	cin >> this->name;
	gotoxy(32, 27);
	cout << "ȯ���մϴ�! " << this->name << "��!" << endl;
	Sleep(3000);
}

int Modeselect(Game &a) {			
	gotoxy(31, 7);
	cout << "Player: " << a.return_name();	// Game a�� �÷��̾� �̸��� �޾Ƽ� ���
	gotoxy(31, 10);
	cout << "��带 �����Ͻÿ�";
	RED;							// ���������� ���� ����: ���
	gotoxy(31, 13);
	cout << "���� ����";
	gotoxy(50, 13);
	cout << ":";
	BLUE;							// �Ķ������� ����: ���
	gotoxy(31, 16);
	cout << "����";
	gotoxy(50, 16);
	cout << ":";
	YELLOW;							// ��������� ��ŷ: ���
	gotoxy(31, 19);
	cout << "��ŷ";
	gotoxy(50, 19);
	cout << ":";
	GREEN;							// �ʷϻ����� �����ϱ�: ���
	gotoxy(31, 22);
	cout << "�����ϱ�";
	gotoxy(50, 22);
	cout << ":";
	SKY;							// �ϴû����� "�� ��: Enter or Space"����� ȭ��ǥ ���
	gotoxy(31, 24);
	cout << "�� ��: Enter or Space";
	gotoxy(55, 13);
	cout << "��";

	int x = 55, y = 13, key = 72;	// ȭ��ǥ�� ó�� ��ġ�� x��ǥ�� y��ǥ�� ����

	while (key != ENTER && key != SPACE) {		// ENTER�� SPACE�� �Է��� �� ���� �ݺ�(���� ������ ȭ��ǥ �̵� ����)
		if (_kbhit() != 0) {
			key = _getch();						// Ű���� �Է��� ����
			gotoxy(31, 30);
			cout << "                                   ";	// ��µ� ���� �޼��� ������
			try {
				if (key != 224 && key != ENTER && key != SPACE)	// ����Ű, ENTER, SPACE�� ������ Ű�� �Է��� ��� ����ó��
					throw key;
				if (key == 224) {					// ����Ű�� ������ ��� 224�� ��ȯ�ް� �ٽ� �ѹ� ��ȯ���� �����Ƿ�
					key = _getch();					// �ش� ����Ű�� ���� ������ ����
					if (key != UP && key != DOWN)	// ����Ű�� �����µ� ����, �Ʒ��� ����Ű�� �ƴ� ��� ����ó��
						throw key;
				}
				try {
					switch (key) {
					case UP:							// ���� ����Ű�� ���
						if (y == 13) {					// ���� ��ĭ�� ��� ���� �̵� �Ұ��̹Ƿ� ���� ó��
							throw y;
						}
						else {							// �� ���� ���
							gotoxy(x, y);
							cout << "  ";				// ���� ��ġ�� ȭ��ǥ�� �����(�ܻ� ����)
							y = y - 3;
							gotoxy(x, y);
							cout << "��";				// �� ĭ ��ĭ���� �̵�
						}
						break;
					case DOWN:							// �Ʒ��� ����Ű�� ��� 
						if (y == 22) {					// ���� �Ʒ�ĭ�� ��� �Ʒ��� �̵� �Ұ��̹Ƿ� ����ó��
							throw y;
						}
						else {							// �� ���� ���
							gotoxy(x, y);
							cout << "  ";				// ���� ��ġ�� ȭ��ǥ�� �����(�ܻ� ����)
							y = y + 3;
							gotoxy(x, y);
							cout << "��";				// �� ĭ �Ʒ�ĭ���� �̵�
						}
						break;
					case ENTER:							// ENTER�� SPACE �Է� ��(����)
					case SPACE:
						if (y == 13)
							return 1;				// '���� ����'�� mode�� 1 ��ȯ
						else if (y == 16)
							return 2;				// '����'�� mode�� 2 ��ȯ
						else if (y == 19)
							return 3;				// '�̾��ϱ�'�� mode�� 3 ��ȯ
						else if (y == 22)
							return 4;				// '�����ϱ�'�� mode�� 4 ��ȯ
						break;
					}
				}
				catch (int inner) {		// ���� ���ʿ��� ��������, ���� �Ʒ��ʿ��� �Ʒ������� �̵��� �̵� �Ұ����ϴٰ� ���
					gotoxy(31, 30);
					cout << "�ش� �������δ� �̵��� �Ұ����մϴ�.";
				}
			}
			catch (int outer) {		// ����Ű, ENTER, SPACE�� ������ Ű�� �Է��� ��� �ش� Ű�θ� �Է��ش޶�� ���
				gotoxy(31, 30);
				cout << "ENTER SPACE �� ��� �Է����ּ���.";
			}
		}
	}
}

string Game::return_name() {	// Ŭ���� Game�� name�� ����
	return this->name;
}

void Game::seeRanking() {	// ���� top 10 ��ŷ�� ���� �Լ�
	vector<int> v(10);		// int �� ���� ����(10ĭ¥��)
	vector<string> s = { "-", "-" , "-" , "-", "-", "-", "-", "-", "-", "-" };	// string�� ���� ����(10��¥��)
	int getscore;			// �Է¹��� ����
	string getname = "";	// �Է¹��� �̸�
	int i = 0;				// �� 10���� �б� ���� ����
	ifstream in("Ranking.txt");	// Ranking.txt�� ����
	if (in.is_open()) {		// ������ �дµ� �����ߴٸ�
		while (i != 10) {	// �ش� ������ ����(top 10)
			getname = "";	// getname �ʱ�ȭ
			char c;	
			do {
				in.get(c);	// ' '������ �ܾ �Է¹���
				if (c != ' ' && c != '\n')
					getname = getname + c;	// ' ', '\n'�� �ƴ϶�� �Է¹��� �ܾ getname�� �̾� ����
			} while (c != ' ');	// ' '�� �Է¹��� ��� while�� Ż��(�̸� ���� ������ txt���Ͽ� �����ֱ� ����)
			in >> getscore;		// ������ �Է¹���
			v[i] = getscore;	// v[i]�� ������
			s[i] = getname;		// s[i]�� �̸��� �Է���
			i++;				// i 1����
		}
	}
	in.close();		// ������ ����
	system("cls");	// ȭ�� �ʱ�ȭ
	YELLOW;			// ��������� ���
	gotoxy(38, 8);
	cout << "�ڡ�Ranking Top 10�ڡ�" << endl;	// �о���� Top 10�� �����
	for (int i = 0; i < 10; i++) {
		gotoxy(32, 10 + 2 * i);
		cout << i + 1 << "��\t" << "Player: " << s.at(i) << "\tScore: " << v.at(i) << endl;
	}
	gotoxy(32, 30);
	cout << "Press Any Key to exit";
	_getch();	// �ƹ� ��ư�� �Է��ϸ� �޴�ȭ������ ���ư�
	SKY;			// �ϴû����� ���
}

template <class T>
void myswap(T& a, T& b) {	// swap�Լ�(Ranking�����ÿ� ���)
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void Game::Ranking() {	// ������ ������ �÷��̾��� ��ϰ� ������ ��ŷ�� ����ϰ� �̸� ���Ͽ� ����
	vector<int> v(10);	// int �� ���� ����(10ĭ¥��)
	int getscore;		// ��ŷ ������ ���� ������ ó���� �̿�Ǵ� ����	
	int i = 0;			// �� 10���� �б� ���� ����
	vector<string> s = { "-", "-" , "-" , "-", "-", "-", "-", "-", "-", "-" };	// string�� ���� ����(10��¥��)
	string getname = "";		// ��ŷ ������ ���� ������ ó���� �̿�Ǵ� ����
	ifstream in("Ranking.txt");		// Ranking.txt�� ����
	if (in.is_open()) {			// ������ �дµ� �����ߴٸ�
		while (i != 10) {		// �ش� ������ ����(top 10)
			getname = "";		// getname �ʱ�ȭ
			char c;
			do {
				in.get(c);		// ' '������ �ܾ �Է¹���
				if (c != ' ' && c != '\n')
					getname = getname + c;	// ' ', '\n'�� �ƴ϶�� �Է¹��� �ܾ getname�� �̾� ����
			} while (c != ' ');	// ' '�� �Է¹��� ��� while�� Ż��(�̸� ���� ������ txt���Ͽ� �����ֱ� ����)
			in >> getscore;		// ������ �Է¹���
			v[i] = getscore;	// v[i]�� ������
			s[i] = getname;		// s[i]�� �̸��� �Է���
			i++;				// i 1����
		}
	}
	in.close();			// ������ ����
	getscore = score;	// �̹� ������ ����� getscore�� ����
	getname = name;		// ������ �÷��� �� �÷��̾��� �̸��� getname�� ����
	for (int i = 0; i < 10; i++) {	
		if (getscore >= v.at(i)) {	// v[i]�� ����� ��Ϻ��� �̹� ������ ����� ũ�ų� ���� ���
			myswap(getscore, v[i]);	// ���� ����
			myswap(getname, s[i]);	// �̸��� �׿� ���� ����
		}
	}
	system("cls");		// ȭ�� �ʱ�ȭ
	YELLOW;				// ��������� ���
	gotoxy(38, 8);
	cout << "�ڡ�Ranking Top 10�ڡ�" << endl;	// ���� �� Top 10�� �����
	for (int i = 0; i < 10; i++) {
		gotoxy(32, 10 + 2 * i);
		cout << i + 1 << "��\t" << "Player: " << s.at(i) << "\tScore: " << v.at(i) << endl;
	}

	gotoxy(32, 30);	// �̹� ������ ��ϰ� �÷��̾� �̸��� �����
	cout << "�̹� ���\t" << "Player: " << name << "\tScore: " << score << endl;
	gotoxy(24, 32);	// ����޽���
	cout << "������ �÷����� �ּż� �����մϴ�. -������: ������-" << endl;
	ofstream out("Ranking.txt");	// Ranking.txt������ ����
	if (out.is_open()) {			// ���� �� ���� ���� ����
		for (int i = 0; i < 10; i++) {
			out << s.at(i) << " ";
			out << v.at(i) << endl;
		}
	}
}

void Help() {		// ���� ���� ���
	system("cls");
	YELGREEN;
	gotoxy(26, 10);
	cout << "����";
	gotoxy(26, 12);
	cout << "�� ������ ����ã�� �Դϴ�.";
	gotoxy(26, 14);
	cout << "����Ű�� �̵��� �Ͻ� �� ������";
	gotoxy(26, 16);
	cout << "ENTERŰ�� ������ �Ͻ� �� �ֽ��ϴ�.";
	gotoxy(26, 18);
	cout << "���� �����Ͻ� ĭ�� ���ڶ�� ������ �����ϴ�.";
	gotoxy(26, 20);
	cout << "���� �����Ͻ� ĭ�� ���ڰ� �ƴ϶�� ��ó�� ���ڼ��� �����ݴϴ�.";
	gotoxy(26, 22);
	SKY;
	cout << "�̸� ���� ������ �� ���� ĭ�� �����Ͽ�";
	gotoxy(26, 24);
	cout << "SPACEŰ�� �����ø� FLAG(��)�� ��ġ �� �� �ֽ��ϴ�.";
	gotoxy(26, 26);
	cout << "�� �ڸ��� FLAG(��)�� ���� �� SPACE�� �����ٸ� FLAG(��)�� �����մϴ�.";
	gotoxy(26, 28);
	cout << "�� FLAG(��)�� ��Ʈ���� �����Ͽ� ����(��)�� �ǵ帮�� ����";
	gotoxy(26, 30);
	cout << "������ ��� �����ø� �¸��Դϴ�.";
	gotoxy(26, 32);
	cout << "������: Press Any Key";
	_getch();	// �ƹ� Ű�� �Է��ϸ� �޴�â���� ���ư�
}

int main(void) {
	int mode = 2;	// ������ ���(1: ���� ����, 2: ����, 3: ��ŷ, 4: �����ϱ�) 
	Game a;			// Game�� ���� ��� ������ �ٷ�� a����
	system("mode con: cols=100 lines=40");	// �ܼ�â ũ�� ���� �Լ�
	a.Opening();	// ���� ù ȭ��(������), �÷��̾��� �̸� �Է�
	PlaySound(Music, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);		// bgm���� 
	while (mode == 2 || mode == 3) {	// ����, ��ŷ�� ��� ������ �ٽ� ��� ����â���� ���ư�
		system("cls");					// ȭ�� �ʱ�ȭ
		mode = Modeselect(a);			// ���� ��带 �����ϱ� ���� â mode���� ������
		if (mode == 2)					// mode�� 2�� ���
			Help();						// ���� ���
		if (mode == 3)					// mode�� 3�� ���
			a.seeRanking();				// ��ŷ ���
	}
	switch (mode) {		
	case 1:				// ��尡 1�� ���
		a.resetinfo();	// ���ο� ���� ����(minemap�� checkmap�� �ʱ�ȭ��)
		a.PlayGame();	// ������ ����
		a.Ranking();	// ������ ������(���1) �̹� ������ ��ϰ� ��������� top 10�� ����ϰ� top 10�� ���� ����� ���Ͽ� ������	
		break;			
	case 4:
		system("cls");	// ��尡 4�� ��� ���α׷� ����
		gotoxy(31, 15);
		cout << "���α׷��� �����մϴ�. ������ �� �÷��� ���ּ���!" << endl;
		return 0;
	}
	return 0;		// ���α׷� ����
}
