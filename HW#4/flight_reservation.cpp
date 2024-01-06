/* 2019253025 윤광현 */
#include <iostream>
#include <Windows.h>
using namespace std;

class Seat {	// 자리의 예약자 이름과 해당 좌석이 예약되었는지의 정보를 다루는 클래스
	string owner[10];	// 1~10번자리의 예약자 이름
	int reserving_seat[10] = { 0 };	// 1~10번자리가 예약 되어있으면 1 예약 가능하다면 0
public:
	void reservation(string b, int c) {	// 자리를 예약하는 함수
		if (c > 0 && c < 11) {	// 좌석의 번호가 1부터 10이면
			if (reserving_seat[c - 1] == 0) {	// 좌석이 예약 가능하다면 좌석을 예약하고 예약자의 이름을 저장, 예약을 완료했다고 메세지 출력
				this->reserving_seat[c - 1] = 1;	
				this->owner[c - 1] = b;
				cout << "예약하였습니다." << endl;
			}
			else {	// 예약 불가능하다면 이미 예약된 자리임
				cout << "이미 예약된 자리입니다." << endl;
			}
		}
		else {	// 좌석의 번호가 1부터 10이 아니라면 존재하지 않는 좌석임
			cout << "존재하지 않는 좌석입니다." << endl;
		}
	}
	void cancel_reservation(string b, int c) {	// 자리의 예약을 취소하는 함수
		if (c > 0 && c < 11) {	// 좌석의 번호가 1부터 10이면
			if (reserving_seat[c - 1] == 1) {	// 좌석이 예약되어있으면 
				if (owner[c - 1] == b) {		// 예약자의 이름이 입력한 이름과 같다면 좌석의 예약을 취소하고 예약자의 이름을 초기화하고 취소를 완료했다고 메세지 출력
					this->reserving_seat[c - 1] = 0;
					this->owner[c - 1] = '0';
					cout << "예약을 취소하였습니다." << endl;
				}
				else {	// 예약자의 이름이 잘못된 경우 다른 자리이거나 입력을 잘못한 것
					cout << "잘못된 자리입니다.(예약자가 다름)" << endl;
				}
			}
			else {	// 예약이 되어있지 않다면 예약되지 않은 자리이거나 입력을 잘못한 경우임
				cout << "잘못된 자리입니다.(예약되지 않은 자리)" << endl;
			}
		}
		else {	// 좌석의 번호가 1부터 10이 아니라면 존재하지 않는 좌석임
			cout << "존재하지 않는 좌석입니다." << endl;
		}
	}
	void print_reservation(string b, int c) {	// 좌석의 예약 현황을 출력
		for (int i = 0; i < 10; i++) {	
			if (reserving_seat[i] == 1) {	// 예약이 되어있다면 예약 불가표시 - 출력
				cout << "-";
			}
			else {							// 예약이 가능하다면 예약 가능표시 o 출력
				cout << "o";
			}
		}
	}
};

class Schedule {// 각 비행기의 스케쥴(예약 시간과 예약 좌석)
	int time;	// 예약 시간
	Seat s;		// 예약 좌석
public:
	void settime(int a) {	// 시간을 설정
		if (a == 6) {		// 6이라면 예약시간이 6시
			this->time = 6;
		}
		else if (a == 12) {	// 12이라면 예약시간이 12시
			this->time = 12;
		}
		else if (a == 20) {	// 20이라면 예약시간이 20시
			this->time = 20;
		}
	};
	void reservation(string b, int c) {	// 예약을 하는 함수(함수를 이용하여 s에 접근)
		s.reservation(b, c);
	}
	void cancel(string b, int c) {	// 예약 취소를 하는 함수(함수를 이용하여 s에 접근)
		s.cancel_reservation(b, c);
	}
	void print(string b, int c) {	// 좌석의 예약 현황을 출력하는 함수(함수를 이용하여 s에 접근) 
		s.print_reservation(b, c);
	}
};

class Airplane {	
	string name;	// 비행기의 이름(비행기 종류)
	Schedule *sch;	// 각 비행기의 스케쥴
public:
	Airplane();
	void getAirplane_name(string s) {	// 비행기의 이름 설정
		this->name = s;
	}
	string return_airplanename() {		// 비행기의 이름을 리턴
		return name;
	}
	void reservation(int a, string b, int c) {	// 예약을 하는 함수(함수를 이용하여 스케쥴(sch)에 접근)
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
			cout << "잘못된 입력입니다." << endl;
		}
	}
	void cancel(int a, string b, int c) {	// 예약 취소를 하는 함수(함수를 이용하여 스케쥴(sch)에 접근) 
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
			cout << "잘못된 입력입니다." << endl;
		}
	}
	void print(int a, string b, int c) {	// 좌석의 예약 현황을 출력하는 함수(함수를 이용하여 스케쥴(sch)에 접근) 
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
			cout << "잘못된 입력입니다." << endl;
		}
	}
};

Airplane::Airplane() {
	sch = new Schedule[3];	// 비행기의 스케쥴을 크기가 3인 배열로 만듦(6시, 12시, 20시)
}

class Menuclass {	// 각 비행기의 예약, 예약 취소, 예약이 가능한지 현 상황을 출력을 맡는 클래스
	Airplane *a;	// 각 비행기
public:
	Menuclass();
	void reservation() {	// 예약을 하는 함수(함수를 이용하여 비행기(a)에 접근)
		int airplane;	// 비행기의 종류
		int b;			// 비행시간
		int c;			// 좌석번호
		string d;		// 사용자이름
		cout << "원하시는 비행기를 입력하세요(1:1번비행기, 2:2번비행기, 3:3번비행기)>>";	// 원하는 비행기 번호를 입력
		cin >> airplane;	
		if (airplane == 1 || airplane == 2 || airplane == 3) {		// 비행기 번호가 1, 2, 3인 경우	비행시간, 사용자이름, 좌석번호를 입력
			cout << "비행시간, 사용자이름, 좌석번호를 입력하세요>>";	
			cin >> b >> d >> c;
			system("cls");
			a[airplane - 1].reservation(b, d, c);	// 이 정보들을 토대로 예약을 진행
		}
		else {	// 비행기 번호가 1, 2, 3이 아닌 경우 잘못된 입력임
			system("cls");
			cout << "잘못된 입력입니다." << endl;
		}
	}
	void cancel() {		// 예약 취소를 하는 함수(함수를 이용하여 비행기(a)에 접근) 
		int airplane;	// 비행기의 종류
		int b;			// 비행시간
		int c;			// 좌석번호
		string d;		// 사용자이름
		cout << "원하시는 비행기를 입력하세요(1:1번비행기, 2:2번비행기, 3:3번비행기)>>";	// 원하는 비행기 번호를 입력
		cin >> airplane;
		if (airplane == 1 || airplane == 2 || airplane == 3) {		// 비행기 번호가 1, 2, 3인 경우	비행시간, 사용자이름, 좌석번호를 입력
			cout << "비행시간, 사용자이름, 좌석번호를 입력하세요>>";
			cin >> b >> d >> c;
			system("cls");
			a[airplane - 1].cancel(b, d, c);	// 이 정보들을 토대로 예약 취소를 진행
		}
		else {	// 비행기 번호가 1, 2, 3이 아닌 경우 잘못된 입력임
			cout << "잘못된 입력입니다." << endl;
		}
	}
	void print() {		// 좌석의 예약 현황을 출력하는 함수(함수를 이용하여 비행기(a)에 접근) 
		system("cls");
		cout << "예약 현황표(o:예약 가능, -:이미 예약된 자리)" << endl;	// 예약 현황표를 출력
		cout << "1번 비행기" << endl;
		string s1 = a[0].return_airplanename();	// s1에 1번 비행기의 이름값을 저장
		cout << "6시: ";
		a[0].print(6, s1, 0);	// 1번 비행기의 6시 예약 현황에 해당하는 정보 출력
		cout << " 12시: ";
		a[0].print(12, s1, 0);	// 1번 비행기의 12시 예약 현황에 해당하는 정보 출력
		cout << " 20시: ";
		a[0].print(20, s1, 0);	// 1번 비행기의 20시 예약 현황에 해당하는 정보 출력
		cout << endl;
		cout << "2번 비행기" << endl;			
		string s2 = a[1].return_airplanename();	// s2에 2번 비행기의 이름값을 저장
		cout << "6시: ";
		a[1].print(6, s2, 0);	// 2번 비행기의 6시 예약 현황에 해당하는 정보 출력
		cout << " 12시: ";
		a[1].print(12, s2, 0);	// 2번 비행기의 12시 예약 현황에 해당하는 정보 출력
		cout << " 20시: ";
		a[1].print(20, s2, 0);	// 2번 비행기의 20시 예약 현황에 해당하는 정보 출력
		cout << endl;
		cout << "3번 비행기" << endl;
		string s3 = a[2].return_airplanename();	// s3에 3번 비행기의 이름값을 저장
		cout << "6시: ";
		a[2].print(6, s2, 0);	// 3번 비행기의 6시 예약 현황에 해당하는 정보 출력
		cout << " 12시: ";
		a[2].print(12, s2, 0);	// 3번 비행기의 12시 예약 현황에 해당하는 정보 출력
		cout << " 20시: ";
		a[2].print(20, s2, 0);	// 3번 비행기의 20시 예약 현황에 해당하는 정보 출력
		cout << endl;
	}
	void getAirplane_name(int i,string s) {	// 비행기의 각 이름을 저장하기 위한 함수( i+1번째 비행기의 이름: s (ex i=0, s=1번비행기 일때 1번째 비행기의 이름은 1번 비행기))
		a[i].getAirplane_name(s);
	}
};

Menuclass::Menuclass() {
	a = new Airplane[3];	// 비행기를 크기가 3인 배열로 만듦(1번비행기, 2번비행기, 3번비행기)
}

int main(void) {
	Menuclass m;
	m.getAirplane_name(0, "1번비행기");	// a[0](첫번째 비행기)의 이름에 1번비행기를 저장
	m.getAirplane_name(1, "2번비행기");	// a[1](두번째 비행기)의 이름에 2번비행기를 저장
	m.getAirplane_name(2, "3번비행기"); // a[2](세번째 비행기)의 이름에 3번비행기를 저장
	while (1) {	
		int option = 0;	// 옵션 저장을 위한 번호
		cout << "안녕하세요 \"연세 항공\"입니다. 옵션을 입력해주세요(1:예약, 2:취소, 3:출력, 4:종료) >>";	// 옵션을 입력
		cin >> option;
		if (option == 1) {	// 옵션이 1인경우 예약 진행
			m.reservation();
		}
		else if (option == 2) {	// 옵션이 2인경우 예약 취소 진행
			m.cancel();
		}
		else if (option == 3) {	// 옵션이 3인경우 좌석의 예약 현황을 출력
			m.print();
		}
		else if (option == 4) {	// 옵션이 4인경우 while문을 빠져나와 종료함
			break;
		}
		else {	// 옵션이 1,2,3,4가 아닌 경우 잘못된 입력임
			system("cls");
			cout << "잘못된 입력입니다." << endl;
		}
	}
}