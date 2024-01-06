/*
	Monster�� ���� ���� (������ x��ǥ, y��ǥ, ���� �������� ��, ������ Ƚ��, ������ ���(symbol))�� �ٷ�� Ŭ������ �ۼ��ϰ�
	Ŭ���� �̸��� ������ ��� �Լ��� �����ڸ� �����ϰ�
	����Լ� moving�� �̿��Ͽ� Monster�� �̵���Ű�� �ٲ� �������� �����Ѵ�
	�� �� �ٲ� �������� ȭ��� ��Ÿ�� �� ����Լ��� �̿��� ������ �Ͽ�����
	�ϳ��� ���� ������ ���� ������ ���� Monster�� ������ ����Լ��� �̿��� ��Ⱑ �����
	showing�Լ��� statement�Լ��� �̿��� ���� ��Ÿ������. 
	showing�Լ��� ���� ��ºο� �ش��ϸ� statement�� ���� ��ºο� �ش��Ѵ�.
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
};  // ���� ������(1)�� ���� �� ������ Monster(2)���� ���� �ڸ��� ���ڸ�(0)�� �ȴ�.

class Monster {
public:
	int y;					// ������ ���� y��ǥ
	int x;					// ������ ���� x��ǥ
	int foodcount = 0;		// ���Ͱ� ���� �������� ����
	int movingcount = 0;	// ���Ͱ� ������ Ƚ��
	string name;			// ������ �̸�
	string symbol;			// ������ ��¡(ȭ��� ��µǴ� ���)
	Monster();
	Monster(int a);
	Monster(int a, int b);

	void moving(int* a, int* b);
};

Monster::Monster() {		// Monster()�� ���� ������ ��� ������ ���� x��ǥ�� 1, y��ǥ�� 1�̴�.
	x = 1;
	y = 1;
}

Monster::Monster(int a) {	// Monster(int a)�� ���� ������ ��� ������ ���� x��ǥ�� a, y��ǥ�� 1�̴�.
	x = a;
	y = 1;
}

Monster::Monster(int a, int b) {	// Monster(int a, int b)�� ���� ������ ��� ������ ���� x��ǥ�� a, y��ǥ�� b�̴�.
	x = a;
	y = b;
}

void Monster::moving(int* a, int* b) {	// ���͸� �����̰� �ϰ� �� ������ �����ϴ� �Լ�
	srand(time(NULL));
	int checkcount = 0;		// ����� �̵��� �̷�������� Ȯ���ϱ� ���� ����(�̵��� ��� 1�̵�, �̵��� ���� ��� 0�� ������)
	map[*b][*a] = 0;		// �̵��� ��ġ�� ���� �� ����(0)���� ����(�̵��� ���� �غ�(�̵� �� ��ġ�� ����� �̵� �� ��ġ�� ǥ���ϱ� ����))
	do {
		int i = rand() % 8;	// rand���� 0~7�� ���� �޾� 0�� ��� �»���, 1�ϰ�� ����, 2�ϰ�� �����, 3�ϰ�� ����, 4�ϰ�� ����, 5�ϰ�� ������, 6�ϰ�� ����, 7�ϰ�� ���������� �̵��Ѵ�.
		switch (i) {
		case 0:												// 0�� ��� �»������� �̵�
			if (*a != 0 && *b != 0) {						// �»������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b - 1][*a - 1] != 2) {				// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b - 1][*a - 1] == 1) {			// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b - 1][*a - 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;
						*b = *b - 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						foodcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
						movingcount++;
					}
					else if (map[*b - 1][*a - 1] == 0) {	// �������� ���� ���
						map[*b - 1][*a - 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;						
						*b = *b - 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �̵� Ƚ���� �����Ѵ�.
					}
				}
			}
			break;
		case 1:												// 1�� ��� �������� �̵�
			if (*b != 0) {									// �������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b - 1][*a] != 2) {					// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b - 1][*a] == 1) {				// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b - 1][*a] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*b = *b - 1;
						checkcount = 1;
						foodcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
					}
					else if (map[*b - 1][*a] == 0) {		// �������� ���� ���
						map[*b - 1][*a] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*b = *b - 1;
						checkcount = 1;
						movingcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
					}										// �̵� Ƚ���� �����Ѵ�.
				}
			}
			break;
		case 2:												// 2�� ��� ��������� �̵�
			if (*a != 19 && *b != 0) {						// ��������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b - 1][*a + 1] != 2) {				// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b - 1][*a + 1] == 1) {			// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b - 1][*a + 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						*b = *b - 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						foodcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
						movingcount++;
					}
					else if (map[*b - 1][*a + 1] == 0) {	// �������� ���� ���
						map[*b - 1][*a + 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						*b = *b - 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �̵� Ƚ���� �����Ѵ�.
					}
				}
			}
			break;
		case 3:												// 3�� ��� �������� �̵�
			if (*a != 0) {									// �������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b][*a - 1] != 2) {					// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b][*a - 1] == 1) {				// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b][*a - 1] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;
						checkcount = 1;
						foodcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
					}
					else if (map[*b][*a - 1] == 0) {		// �������� ���� ���
						map[*b][*a - 1] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;
						checkcount = 1;
						movingcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
					}										// �̵� Ƚ���� �����Ѵ�.
				}
			}
			break;
		case 4:												// 4�� ��� �������� �̵�
			if (*a != 19) {									// �������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b][*a + 1] != 2) {					// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b][*a + 1] == 1) {				// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b][*a + 1] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						checkcount = 1;
						foodcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
					}
					else if (map[*b][*a + 1] == 0) {		// �������� ���� ���
						map[*b][*a + 1] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						checkcount = 1;
						movingcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
					}										// �̵� Ƚ���� �����Ѵ�.
				}
			}
			break;
		case 5:												// 5�� ��� ���������� �̵�
			if (*a != 0 && *b != 9) {						// ���������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b + 1][*a - 1] != 2) {				// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b + 1][*a - 1] == 1) {			// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b + 1][*a - 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;
						*b = *b + 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						foodcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
						movingcount++;
					}
					else if (map[*b + 1][*a - 1] == 0) {	// �������� ���� ���
						map[*b + 1][*a - 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a - 1;
						*b = *b + 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �̵� Ƚ���� �����Ѵ�.
					}
				}
			}
			break;
		case 6:												// 6�� ��� �������� �̵�
			if (*b != 9) {									// �������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b + 1][*a] != 2) {					// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b + 1][*a] == 1) {				// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b + 1][*a] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*b = *b + 1;
						checkcount = 1;
						foodcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
					}
					else if (map[*b + 1][*a] == 0) {		// �������� ���� ���
						map[*b + 1][*a] = 2;				// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*b = *b + 1;
						checkcount = 1;
						movingcount++;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
					}										// �̵� Ƚ���� �����Ѵ�.
				}
			}
			break;
		case 7:												// 7�� ��� ���������� �̵�
			if (*a != 19 && *b != 9) {						// ���������� �̵��� �� ���� ��� do while������ �ٸ� ������ �̵�
				if (map[*b + 1][*a + 1] != 2) {				// �ش� ��ǥ�� Monster�� ��ġ�� ���� ��� do while������ �ٸ� ������ �̵�
					if (map[*b + 1][*a + 1] == 1) {			// �� �� ��찡 �ƴ϶�� �̵��� �� �ִ� ��ǥ�̸� �������� �ִ� ��� 
						map[*b + 1][*a + 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						*b = *b + 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						foodcount++;						// �������� ������Ƿ� �ش� ������ foodcount�� �����ǰ� �̵� Ƚ���� �����Ѵ�.
						movingcount++;
					}
					else if (map[*b + 1][*a + 1] == 0) {	// �������� ���� ���
						map[*b + 1][*a + 1] = 2;			// �ش� ��ǥ�� �̵�(2�� map�� ����)�ϰ� �̵��� �� ��ǥ�� Monster�� x, y�� �����ϸ�
						*a = *a + 1;
						*b = *b + 1;
						checkcount = 1;						// �̵��� �Ͽ����Ƿ� checkcount�� 1�� �Ǿ� do while���� ����������.
						movingcount++;						// �̵� Ƚ���� �����Ѵ�.
					}
				}
			}
		}
	} while (checkcount == 0);	// checkcount�� 1�� �� ������(�̵��� �� ������) do while�� �ݺ�
}

void statement(Monster m1, Monster m2, Monster m3, Monster m4, Monster m5) {	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ�
	cout << "��ü �̵� Ƚ�� = " << m1.movingcount + m2.movingcount + m3.movingcount + m4.movingcount + m5.movingcount << endl;		
	cout << "���� ������ �� = " << 195 - (m1.foodcount + m2.foodcount + m3.foodcount + m4.movingcount + m5.movingcount) << endl;
	cout << "       " << m1.name << m1.symbol << m1.foodcount << endl;
	cout << "       " << m2.name << m2.symbol << m2.foodcount << endl;
	cout << "       " << m3.name << m3.symbol << m3.foodcount << endl;
	cout << "       " << m4.name << m4.symbol << m4.foodcount << endl;
	cout << "       " << m5.name << m5.symbol << m5.foodcount << endl;
}

void showing(Monster m1, Monster m2, Monster m3, Monster m4, Monster m5) {		// map�� Monster���� ������ ���� �� Monster�� ���� ��ġ�� �������� �ִ� ������ ���� ������ ȭ��� ����Ѵ�
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
				cout << "��";
			}
			else if (map[i][j] == 1) {
				cout << "��";
			}
		}
		cout << endl;
	}
	cout << endl;
};