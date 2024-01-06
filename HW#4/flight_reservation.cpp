/* 2019253025 ������ */
#include <iostream>
#include <Windows.h>
using namespace std;

class Seat {	// �ڸ��� ������ �̸��� �ش� �¼��� ����Ǿ������� ������ �ٷ�� Ŭ����
	string owner[10];	// 1~10���ڸ��� ������ �̸�
	int reserving_seat[10] = { 0 };	// 1~10���ڸ��� ���� �Ǿ������� 1 ���� �����ϴٸ� 0
public:
	void reservation(string b, int c) {	// �ڸ��� �����ϴ� �Լ�
		if (c > 0 && c < 11) {	// �¼��� ��ȣ�� 1���� 10�̸�
			if (reserving_seat[c - 1] == 0) {	// �¼��� ���� �����ϴٸ� �¼��� �����ϰ� �������� �̸��� ����, ������ �Ϸ��ߴٰ� �޼��� ���
				this->reserving_seat[c - 1] = 1;	
				this->owner[c - 1] = b;
				cout << "�����Ͽ����ϴ�." << endl;
			}
			else {	// ���� �Ұ����ϴٸ� �̹� ����� �ڸ���
				cout << "�̹� ����� �ڸ��Դϴ�." << endl;
			}
		}
		else {	// �¼��� ��ȣ�� 1���� 10�� �ƴ϶�� �������� �ʴ� �¼���
			cout << "�������� �ʴ� �¼��Դϴ�." << endl;
		}
	}
	void cancel_reservation(string b, int c) {	// �ڸ��� ������ ����ϴ� �Լ�
		if (c > 0 && c < 11) {	// �¼��� ��ȣ�� 1���� 10�̸�
			if (reserving_seat[c - 1] == 1) {	// �¼��� ����Ǿ������� 
				if (owner[c - 1] == b) {		// �������� �̸��� �Է��� �̸��� ���ٸ� �¼��� ������ ����ϰ� �������� �̸��� �ʱ�ȭ�ϰ� ��Ҹ� �Ϸ��ߴٰ� �޼��� ���
					this->reserving_seat[c - 1] = 0;
					this->owner[c - 1] = '0';
					cout << "������ ����Ͽ����ϴ�." << endl;
				}
				else {	// �������� �̸��� �߸��� ��� �ٸ� �ڸ��̰ų� �Է��� �߸��� ��
					cout << "�߸��� �ڸ��Դϴ�.(�����ڰ� �ٸ�)" << endl;
				}
			}
			else {	// ������ �Ǿ����� �ʴٸ� ������� ���� �ڸ��̰ų� �Է��� �߸��� �����
				cout << "�߸��� �ڸ��Դϴ�.(������� ���� �ڸ�)" << endl;
			}
		}
		else {	// �¼��� ��ȣ�� 1���� 10�� �ƴ϶�� �������� �ʴ� �¼���
			cout << "�������� �ʴ� �¼��Դϴ�." << endl;
		}
	}
	void print_reservation(string b, int c) {	// �¼��� ���� ��Ȳ�� ���
		for (int i = 0; i < 10; i++) {	
			if (reserving_seat[i] == 1) {	// ������ �Ǿ��ִٸ� ���� �Ұ�ǥ�� - ���
				cout << "-";
			}
			else {							// ������ �����ϴٸ� ���� ����ǥ�� o ���
				cout << "o";
			}
		}
	}
};

class Schedule {// �� ������� ������(���� �ð��� ���� �¼�)
	int time;	// ���� �ð�
	Seat s;		// ���� �¼�
public:
	void settime(int a) {	// �ð��� ����
		if (a == 6) {		// 6�̶�� ����ð��� 6��
			this->time = 6;
		}
		else if (a == 12) {	// 12�̶�� ����ð��� 12��
			this->time = 12;
		}
		else if (a == 20) {	// 20�̶�� ����ð��� 20��
			this->time = 20;
		}
	};
	void reservation(string b, int c) {	// ������ �ϴ� �Լ�(�Լ��� �̿��Ͽ� s�� ����)
		s.reservation(b, c);
	}
	void cancel(string b, int c) {	// ���� ��Ҹ� �ϴ� �Լ�(�Լ��� �̿��Ͽ� s�� ����)
		s.cancel_reservation(b, c);
	}
	void print(string b, int c) {	// �¼��� ���� ��Ȳ�� ����ϴ� �Լ�(�Լ��� �̿��Ͽ� s�� ����) 
		s.print_reservation(b, c);
	}
};

class Airplane {	
	string name;	// ������� �̸�(����� ����)
	Schedule *sch;	// �� ������� ������
public:
	Airplane();
	void getAirplane_name(string s) {	// ������� �̸� ����
		this->name = s;
	}
	string return_airplanename() {		// ������� �̸��� ����
		return name;
	}
	void reservation(int a, string b, int c) {	// ������ �ϴ� �Լ�(�Լ��� �̿��Ͽ� ������(sch)�� ����)
		if (a == 6) {
			sch[0].reservation(b, c);
		}
		else if (a == 12) {
			sch[1].reservation(b, c);
		}
		else if (a == 20) {
			sch[2].reservation(b, c);
		}
		else {
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	void cancel(int a, string b, int c) {	// ���� ��Ҹ� �ϴ� �Լ�(�Լ��� �̿��Ͽ� ������(sch)�� ����) 
		if (a == 6) {
			sch[0].cancel(b, c);
		}
		else if (a == 12) {
			sch[1].cancel(b, c);
		}
		else if (a == 20) {
			sch[2].cancel(b, c);
		}
		else {
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	void print(int a, string b, int c) {	// �¼��� ���� ��Ȳ�� ����ϴ� �Լ�(�Լ��� �̿��Ͽ� ������(sch)�� ����) 
		if (a == 6) {
			sch[0].print(b, c);
		}
		else if (a == 12) {
			sch[1].print(b, c);
		}
		else if (a == 20) {
			sch[2].print(b, c);
		}
		else {
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
};

Airplane::Airplane() {
	sch = new Schedule[3];	// ������� �������� ũ�Ⱑ 3�� �迭�� ����(6��, 12��, 20��)
}

class Menuclass {	// �� ������� ����, ���� ���, ������ �������� �� ��Ȳ�� ����� �ô� Ŭ����
	Airplane *a;	// �� �����
public:
	Menuclass();
	void reservation() {	// ������ �ϴ� �Լ�(�Լ��� �̿��Ͽ� �����(a)�� ����)
		int airplane;	// ������� ����
		int b;			// ����ð�
		int c;			// �¼���ȣ
		string d;		// ������̸�
		cout << "���Ͻô� ����⸦ �Է��ϼ���(1:1�������, 2:2�������, 3:3�������)>>";	// ���ϴ� ����� ��ȣ�� �Է�
		cin >> airplane;	
		if (airplane == 1 || airplane == 2 || airplane == 3) {		// ����� ��ȣ�� 1, 2, 3�� ���	����ð�, ������̸�, �¼���ȣ�� �Է�
			cout << "����ð�, ������̸�, �¼���ȣ�� �Է��ϼ���>>";	
			cin >> b >> d >> c;
			system("cls");
			a[airplane - 1].reservation(b, d, c);	// �� �������� ���� ������ ����
		}
		else {	// ����� ��ȣ�� 1, 2, 3�� �ƴ� ��� �߸��� �Է���
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	void cancel() {		// ���� ��Ҹ� �ϴ� �Լ�(�Լ��� �̿��Ͽ� �����(a)�� ����) 
		int airplane;	// ������� ����
		int b;			// ����ð�
		int c;			// �¼���ȣ
		string d;		// ������̸�
		cout << "���Ͻô� ����⸦ �Է��ϼ���(1:1�������, 2:2�������, 3:3�������)>>";	// ���ϴ� ����� ��ȣ�� �Է�
		cin >> airplane;
		if (airplane == 1 || airplane == 2 || airplane == 3) {		// ����� ��ȣ�� 1, 2, 3�� ���	����ð�, ������̸�, �¼���ȣ�� �Է�
			cout << "����ð�, ������̸�, �¼���ȣ�� �Է��ϼ���>>";
			cin >> b >> d >> c;
			system("cls");
			a[airplane - 1].cancel(b, d, c);	// �� �������� ���� ���� ��Ҹ� ����
		}
		else {	// ����� ��ȣ�� 1, 2, 3�� �ƴ� ��� �߸��� �Է���
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
	void print() {		// �¼��� ���� ��Ȳ�� ����ϴ� �Լ�(�Լ��� �̿��Ͽ� �����(a)�� ����) 
		system("cls");
		cout << "���� ��Ȳǥ(o:���� ����, -:�̹� ����� �ڸ�)" << endl;	// ���� ��Ȳǥ�� ���
		cout << "1�� �����" << endl;
		string s1 = a[0].return_airplanename();	// s1�� 1�� ������� �̸����� ����
		cout << "6��: ";
		a[0].print(6, s1, 0);	// 1�� ������� 6�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 12��: ";
		a[0].print(12, s1, 0);	// 1�� ������� 12�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 20��: ";
		a[0].print(20, s1, 0);	// 1�� ������� 20�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << endl;
		cout << "2�� �����" << endl;			
		string s2 = a[1].return_airplanename();	// s2�� 2�� ������� �̸����� ����
		cout << "6��: ";
		a[1].print(6, s2, 0);	// 2�� ������� 6�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 12��: ";
		a[1].print(12, s2, 0);	// 2�� ������� 12�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 20��: ";
		a[1].print(20, s2, 0);	// 2�� ������� 20�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << endl;
		cout << "3�� �����" << endl;
		string s3 = a[2].return_airplanename();	// s3�� 3�� ������� �̸����� ����
		cout << "6��: ";
		a[2].print(6, s2, 0);	// 3�� ������� 6�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 12��: ";
		a[2].print(12, s2, 0);	// 3�� ������� 12�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << " 20��: ";
		a[2].print(20, s2, 0);	// 3�� ������� 20�� ���� ��Ȳ�� �ش��ϴ� ���� ���
		cout << endl;
	}
	void getAirplane_name(int i,string s) {	// ������� �� �̸��� �����ϱ� ���� �Լ�( i+1��° ������� �̸�: s (ex i=0, s=1������� �϶� 1��° ������� �̸��� 1�� �����))
		a[i].getAirplane_name(s);
	}
};

Menuclass::Menuclass() {
	a = new Airplane[3];	// ����⸦ ũ�Ⱑ 3�� �迭�� ����(1�������, 2�������, 3�������)
}

int main(void) {
	Menuclass m;
	m.getAirplane_name(0, "1�������");	// a[0](ù��° �����)�� �̸��� 1������⸦ ����
	m.getAirplane_name(1, "2�������");	// a[1](�ι�° �����)�� �̸��� 2������⸦ ����
	m.getAirplane_name(2, "3�������"); // a[2](����° �����)�� �̸��� 3������⸦ ����
	while (1) {	
		int option = 0;	// �ɼ� ������ ���� ��ȣ
		cout << "�ȳ��ϼ��� \"���� �װ�\"�Դϴ�. �ɼ��� �Է����ּ���(1:����, 2:���, 3:���, 4:����) >>";	// �ɼ��� �Է�
		cin >> option;
		if (option == 1) {	// �ɼ��� 1�ΰ�� ���� ����
			m.reservation();
		}
		else if (option == 2) {	// �ɼ��� 2�ΰ�� ���� ��� ����
			m.cancel();
		}
		else if (option == 3) {	// �ɼ��� 3�ΰ�� �¼��� ���� ��Ȳ�� ���
			m.print();
		}
		else if (option == 4) {	// �ɼ��� 4�ΰ�� while���� �������� ������
			break;
		}
		else {	// �ɼ��� 1,2,3,4�� �ƴ� ��� �߸��� �Է���
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
}