/*
2019253025 ������
����1 : Hangman ����
stringŬ���� ���
�̹� ���� �Ǿ����� �� ���ĺ��� ����ϰ� �ƴϸ� ��_������ ���
������ ����Ǹ� �������� �Ǵ� �����С��� ����Ѵ�.
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
	int i = rand() % 5 + 1;			// i���� 1~5���� �������� ����
	switch (i) {					// �������� ���õ� i���� Ȯ��
	case 1: problem = "teacher";	// 1�� ��� ������ teacher�� �� 
		break;
	case 2: problem = "student";	// 2�� ��� ������ student�� �� 
		break;
	case 3: problem = "hangman";	// 3�� ��� ������ hangman�� �� 
		break;
	case 4: problem = "tuesday";	// 4�� ��� ������ tuesday�� �� 
		break;
	case 5: problem = "rainbow";	// 5�� ��� ������ rainbow�� �� 
		break;
	}
}

int StringClass::CheckAnswer() {

	int line = 0;				// ���� ��������� �Է��ϴ� ����(ù��° ���� = 0)
	int errorcount = 0;			// �õ��� �� �ִ� ��ȸ�� 7��(Ʋ�� Ƚ��)
	int answercount = 0;		// ������ ������ 1�� ��
	int checknum = -1;			// �ܾ� �� �� do while�� �ȿ��� ������ ���� Ȯ�ο� ����

	answer = "_______";	// ���� �ڽ��� ���� ��Ȳ�� ǥ���ϴ� answer
	string answerword;	// �ڽ��� �ܾ ���ٰ� �����ϴ� ���ڸ� �Է��ϴ� answerword

	do {
		ifstream in("HangmanProgress.txt");
		char buf[100];

		if (!in.is_open()) {
			cout << "������ ã�� �� �����ϴ�!" << std::endl;
			return 0;
		}

		if (checknum <= -1) {				// checknum�� 0�̻��� ��� ã������ �ܾ �������� �����ϹǷ� �Ʒ� if���� ����ؼ� �����ϰ� -1�� ��� ã������ �ܾ ���ų� ù �õ� �̹Ƿ� if���� ���� ���ڸ� �Է¹��� checknum�� -2�� ��� ���ڸ� �ϳ��� �Է��Ѱ� �ƴ϶� �ٽ� �Է��ϰ� ��
			while (in) {
				in.getline(buf, 100);		// �� �پ� �޾Ƽ�
				if (line > (errorcount + 1) * 8 - 8 && line <= (errorcount + 1) * 8) {	// ���� ��ȸ�� ���� �׿� �´� ȭ�� ���(ex) ���� ��ȸ�� 7���� ��� errorcount�� 0�̹Ƿ� line = 1(�ι�° ����)���� line = 8(��ȩ��° ����)���� ���)
					cout << buf << endl;
					line++;
				}
				else
					line++;
			}
			line = 0;	// ���� �ʱ�ȭ
			
			cout << "����:" << answer << endl;
			cout << "���ڸ� �Է��� �ּ���:";
			cin >> answerword;						// answerword�� �Է¹��� ���� ����
			checknum = problem.find(answerword);	// ������ �Է¹��� ���ڰ� �ִ��� Ȯ��(���ٸ� checknum�� -1�� ���� �ִٸ� ���°�� �����ϴ��� checknum�� ����)
			system("cls");
			if (answerword.length() != 1) {			// ���� ���ڸ� �ϳ��� �Է��Ѱ� �ƴ϶�� checknum�� -2�� ����� �ٽ� �Է��ϵ��� ����
				cout << "�߸��� �Է��Դϴ�. �� ���ڸ� �ۼ����ּ���." << endl;
				checknum = -2;
			}
			if (checknum == -1) {			// checknum�� -1�̶�� ã������ �ܾ �� ���ڰ� ���� �� 
				cout << "ã���÷��� �ܾ �� ���ڴ� �����ϴ�:" << answerword << endl;
				errorcount++;				// Ʋ�� Ƚ���� 1ȸ ������
			}
		}

		if (checknum >= 0) {					// checknum�� ����� ���
			switch (checknum) {					// checknum�� ���ڷ� �� �ܾ��� ��ġ�� �� �� ����
			case 0: answer.replace(0, 1, answerword);	// 0�ΰ�� ������ ù��° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� ù��° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 1);	// �� �ڿ��� ������ �ܾ ���� �� �����Ƿ� �� �ڿ� ������ �Է¹��� ���ڰ� �ִ��� Ȯ��
				break;
			case 1: answer.replace(1, 1, answerword);	// 1�ΰ�� ������ �ι�° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� �ι�° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 2);
				break;
			case 2: answer.replace(2, 1, answerword);	// 2�ΰ�� ������ ����° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� ����° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 3);
				break;
			case 3: answer.replace(3, 1, answerword);	// 3�ΰ�� ������ �׹�° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� �׹�° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 4);
				break;
			case 4: answer.replace(4, 1, answerword);	// 4�ΰ�� ������ �ټ���° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� �ټ���° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 5);
				break;
			case 5: answer.replace(5, 1, answerword);	// 5�ΰ�� ������ ������° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� ������° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 6);
				break;
			case 6: answer.replace(6, 1, answerword);	// 6�ΰ�� ������ �ϰ���° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(answer)�� �ϰ���° �ܾ �Է��� �ܾ�� �����
				checknum = problem.find(answerword, 7);
			}
			cout << "ã���÷��� ���ڿ� �� �ܾ �ֽ��ϴ�!" << endl;	// ������ �ش� ���ڰ� �ִٴ� ���� ǥ��
			if (answer.compare(problem) == 0) {		// ���ݱ��� �������� ���� �ܾ��(answer)�� ������ �ش��ϴ� �ܾ���� ������ ��ġ�� ���
				answercount = 1;					// answercount�� 1�� �ٲٰ� do while���� ��������
			}
		}
	} while (errorcount < 7 && answercount == 0);	// ������ ���缭 answercount�� 1�̵ǰų� ���� ��ȸ�� 0(Ʋ�� Ƚ���� 7��)�� �� ������ �ݺ�

	if (errorcount == 7) {	// ���� ��ȸ�� 0(Ʋ�� Ƚ���� 7��)�� �� ��� ������
		system("cls");
		ifstream in("HangmanProgress.txt");
		char buf[100];

		while (in) {
			in.getline(buf, 100);		// �� �پ� �޾Ƽ�
			if (line > (errorcount + 1) * 8 - 8 && line <= (errorcount + 1) * 8) {	// ���� ��ȸ�� ���� �׿� �´� ȭ�� ���(ex) ���� ��ȸ�� 7���� ��� errorcount�� 0�̹Ƿ� line = 1(�ι�° ����)���� line = 8(��ȩ��° ����)���� ���)
				cout << buf << endl;
				line++;
			}
			else
				line++;
		}

		cout << "�����Դϴ�. ������ �ٽ� �����ϼ���." << endl;
		cout << "����: " << problem << endl;
	}
	if (answercount == 1) {	// answercount�� 1�� ��� ������
		system("cls");
		cout << "�����Դϴ�. ���ϵ帳�ϴ�!" << endl;
		cout << "����: " << answer << endl;
	}

	return 0;
}

int main() {

	StringClass problem1;
	problem1.CheckAnswer();

	return 0;
}