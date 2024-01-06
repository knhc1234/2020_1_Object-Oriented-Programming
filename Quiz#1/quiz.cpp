#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

class Num {
public:
	int checknum;		// Num(a)�� ���� a�� 1�̸� Ȧ���� �̵��� 1�� �Ǹ� a�� 2�� ¦���� �̵��� 2�� �ȴ�.
	Num(int a);
	void next();		// 0~Rand_MAX�� ���̿��� checknum�� ���� Ȧ�� �Ǵ� ¦���� 10�� ���
	void next_range(int a, int b);	// a~b�� ���� ���̿��� checknum�� ���� Ȧ�� �Ǵ� ¦���� 10�� ���
};

Num::Num(int a) {
	if (a % 2 == 1) {	// a�� 1�� ��� Ȧ��, a�� 2�� ��� ¦���� �����ϵ��� ����
		checknum = 1;
	}
	else
		checknum = 2;
}

void Num::next() {	// 0~Rand_MAX�� ���̿��� checknum�� ���� Ȧ�� �Ǵ� ¦���� 10�� ���
	srand(time(NULL));
	int checkcount = 0;			// ��� Ƚ���� 10�� �Ǹ� �ݺ����� �����ϵ��� �ϱ� ���� ����(������ ��� Ƚ��)
	while (checkcount < 10) {	// 10�� �ݺ�
		int answer = rand() % (RAND_MAX + 1);	// ���� ���� ����
		
		if (checknum == 1) {			// checknum�� 1(Ȧ���� ����)�� ���
			if (answer % 2 == 1) {		// �������� ���� ���ڰ� Ȧ���� ���(¦���� ��� ��� x �ٽ� ����)
				cout << answer << " ";	// ���
				checkcount++;			// ��������Ƿ� ��� Ƚ�� 1 ����
			}
		}
		
		else if (checknum == 2) {		// checknum�� 2(¦���� ����)�� ���
			if (answer % 2 == 0) {		// �������� ���� ���ڰ� ¦���� ���(Ȧ���� ��� ��� x �ٽ� ����)
				cout << answer << " ";	// ���
				checkcount++;			// ��������Ƿ� ��� Ƚ�� 1 ����
			}
		}
	}
	cout << endl;
}

void Num::next_range(int a, int b) {	// a~b�� ���� ���̿��� checknum�� ���� Ȧ�� �Ǵ� ¦���� 10�� ���
	srand(time(NULL));
	int checkcount = 0;			// ��� Ƚ���� 10�� �Ǹ� �ݺ����� �����ϵ��� �ϱ� ���� ����(������ ��� Ƚ��)
	while (checkcount < 10) {	// 10�� �ݺ�
		int answer = rand() % (RAND_MAX + 1);	// ���� ���� ����

		if (answer<a || answer>b) {
			// ������ �ƴϹǷ� �ٽ� �õ�
		}

		else {	// ������ ���� �Ǵ� ���
			if (checknum == 1) {			// checknum�� 1(Ȧ���� ����)�� ���
				if (answer % 2 == 1) {		// �������� ���� ���ڰ� Ȧ���� ���(¦���� ��� ��� x �ٽ� ����)
					cout << answer << " ";	// ���
					checkcount++;			// ��������Ƿ� ��� Ƚ�� 1 ����
				}
			}

			else if (checknum == 2) {		// checknum�� 2(¦���� ����)�� ���
				if (answer % 2 == 0) {		// �������� ���� ���ڰ� ¦���� ���(Ȧ���� ��� ��� x �ٽ� ����)
					cout << answer << " ";	// ���
					checkcount++;			// ��������Ƿ� ��� Ƚ�� 1 ����
				}
			}
		}
	}
	cout << endl;
}

int main(void) {

	int a;	// Ȧ�� ¦���� �����ϴ� ����
	while (1) {
		cout << "Ȧ��(1), ¦��(2)�� �������ּ���.: ";
		cin >> a;
		if (a == 1) {		// 1(Ȧ��)�� �� ��� �ݺ����� ��������
			break;
		}
		else if (a == 2) {	// 2(¦��)�� �� ��� �ݺ����� ��������
			break;
		}
		else {				// 1,2�� ���� ���� ��� �߸��� ���� �� ���̹Ƿ� �ٽ� ����
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	
	Num answer1(a);			
	answer1.next();			// 0~RAND_MAX���̿��� 10���� Ȧ���Ǵ� ¦���� ���
	
	while (1) {
		cout << "Ȧ��(1), ¦��(2)�� �������ּ���.: ";
		cin >> a;
		if (a == 1) {		// 1(Ȧ��)�� �� ��� �ݺ����� ��������
			break;
		}
		else if (a == 2) {	// 2(¦��)�� �� ��� �ݺ����� ��������
			break;
		}
		else {				// 1,2�� ���� ���� ��� �߸��� ���� �� ���̹Ƿ� �ٽ� ����
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	
	Num answer2(a);				
	answer2.next_range(2, 50);	// ����(�� ��� 2���� 50)���̿��� 10���� Ȧ���Ǵ� ¦���� ���

	return 0;
}