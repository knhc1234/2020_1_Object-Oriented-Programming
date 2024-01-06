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
using namespace std;

int main() {
	string str1 = "teacher";	// �������� ���� ���� 1
	string str2 = "student";	// �������� ���� ���� 2
	string str3 = "hangman";	// �������� ���� ���� 3
	string str4 = "tuesday";	// �������� ���� ���� 4
	string str5 = "rainbow";	// �������� ���� ���� 5
	string strp = "problem";	// ����(�������� �� �ټ� �������� �ϳ��� swap�Ͽ� ������ ��)
	string stra1 = "_______";	// ���� �ڽ��� ���� ��Ȳ�� ǥ���ϴ� answer1
	string stra2;				// �ڽ��� �ܾ ���ٰ� �����ϴ� ���ڸ� �Է��ϴ� answer2

	srand(time(NULL));
	int i = rand() % 5 + 1;		// i���� 1~5���� �������� ����
	int lifecount = 5;			// �õ��� �� �ִ� ��ȸ�� 5��
	int answercount = 0;		// ������ ������ 1�� ��
	int checknum = -1;			// �ܾ� �� �� do while�� �ȿ��� ������ ���� Ȯ�ο� ����

	switch (i) {				// �������� ���õ� i���� Ȯ��
	case 1: swap(str1, strp);	// 1�� ��� ������ str1�� �� (strp�� str1�� ������)
		break;
	case 2: swap(str2, strp);	// 2�� ��� ������ str2�� �� (strp�� str2�� ������)
		break;
	case 3: swap(str3, strp);	// 3�� ��� ������ str3�� �� (strp�� str3�� ������)
		break;
	case 4: swap(str4, strp);	// 4�� ��� ������ str4�� �� (strp�� str4�� ������)
		break;
	case 5: swap(str5, strp);	// 5�� ��� ������ str5�� �� (strp�� str5�� ������)
		break;
	}

	do {
		if (checknum <= -1) {				// checknum�� 0�̻��� ��� ã������ �ܾ �������� �����ϹǷ� �Ʒ� if���� ����ؼ� �����ϰ� -1�� ��� ã������ �ܾ ���ų� ù �õ� �̹Ƿ� if���� ���� ���ڸ� �Է¹��� checknum�� -2�� ��� ���ڸ� �ϳ��� �Է��Ѱ� �ƴ϶� �ٽ� �Է��ϰ� ��
			cout << "���� ��ȸ " << lifecount << "��" << endl;
			cout << "����:" << stra1 << endl;
			cout << "���ڸ� �Է��� �ּ���:";
			cin >> stra2;					// stra2�� �Է¹��� ���� ����
			checknum = strp.find(stra2);	// ����(strp)�� �Է¹��� ����(stra2)�� �ִ��� Ȯ��(���ٸ� checknum�� -1�� ���� �ִٸ� ���°�� �����ϴ��� checknum�� ����)
			system("cls");
			if (stra2.length() != 1) {		// ���� ���ڸ� �ϳ��� �Է��Ѱ� �ƴ϶�� checknum�� -2�� ����� �ٽ� �Է��ϵ��� ����
				cout << "�߸��� �Է��Դϴ�. �� ���ڸ� �ۼ����ּ���." << endl;
				checknum = -2;
			}
			if (checknum == -1) {			// checknum�� -1�̶�� ã������ �ܾ �� ���ڰ� ���� �� 
				cout << "ã���÷��� �ܾ �� ���ڴ� �����ϴ�:" << stra2 << endl;
				lifecount--;				// ���� ��ȸ�� 1ȸ ���ҵ�
			}
		}
		if (checknum >= 0) {					// checknum�� ����� ���
			switch (checknum) {					// checknum�� ���ڷ� �� �ܾ��� ��ġ�� �� �� ����
			case 0: stra1.replace(0, 1, stra2);	// 0�ΰ�� ������ ù��° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� ù��° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 1);	// �� �ڿ��� ������ �ܾ ���� �� �����Ƿ� �� �ڿ� ������ �Է¹��� ���ڰ� �ִ��� Ȯ��
				break;
			case 1: stra1.replace(1, 1, stra2);	// 1�ΰ�� ������ �ι�° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� �ι�° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 2);
				break;
			case 2: stra1.replace(2, 1, stra2);	// 2�ΰ�� ������ ����° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� ����° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 3);
				break;
			case 3: stra1.replace(3, 1, stra2);	// 3�ΰ�� ������ �׹�° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� �׹�° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 4);
				break;
			case 4: stra1.replace(4, 1, stra2);	// 4�ΰ�� ������ �ټ���° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� �ټ���° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 5);
				break;
			case 5: stra1.replace(5, 1, stra2);	// 5�ΰ�� ������ ������° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� ������° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 6);
				break;
			case 6: stra1.replace(6, 1, stra2);	// 6�ΰ�� ������ �ϰ���° �ܾ �Է��� �ܾ�� �����ϹǷ� ������� ���� ����(stra1)�� �ϰ���° �ܾ �Է��� �ܾ�� �����
				checknum = strp.find(stra2, 7);
			}
			cout << "ã���÷��� ���ڿ� �� �ܾ �ֽ��ϴ�!" << endl;	// ������ �ش� ���ڰ� �ִٴ� ���� ǥ��
			if (stra1.compare(strp) == 0) {		// ���ݱ��� �������� ���� �ܾ��(stra1)�� ������ �ش��ϴ� �ܾ���� ������ ��ġ�� ���
				answercount = 1;				// answercount�� 1�� �ٲٰ� do while���� ��������
			}
		}
	} while (lifecount > 0 && answercount == 0);	// ������ ���缭 answercount�� 1�̵ǰų� ���� ��ȸ�� 0�� �� ������ �ݺ�

	if (lifecount == 0) {	// ���� ��ȸ�� 0�� �� ��� ������
		system("cls");
		cout << "�����Դϴ�. ������ �ٽ� �����ϼ���." << endl;
		cout << "����: " << strp << endl;
	}
	if (answercount == 1) {	// answercount�� 1�� ��� ������
		system("cls");
		cout << "�����Դϴ�. ���ϵ帳�ϴ�!" << endl;
		cout << "����: " << stra1 << endl;
	}
	return 0;
}