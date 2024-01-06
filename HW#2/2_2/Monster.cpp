/*
	2019253025 윤광현
	몬스터들이 각기 다른 모양으로 화면에 출력되며 각 칸에는 아이템이 하나씩 놓인다.
	몬스터들이 인접한 8 방향의 이웃 칸들 중에 하나를 무작위로 선택하여 움직이면서 아이템을 먹고
	시시각각 변화하는 상황과 몬스터의 상태를 출력하는 게임이다.
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "Monster.h"
using namespace std;

int main(void) {

	Monster m1(10, 5);
	Monster m2(15, 7);
	Monster m3(5, 3);
	Monster m4(5, 7);
	Monster m5(15, 3);
	
	m1.name = "몬스터";
	m2.name = "도깨비";
	m3.name = "고스트";
	m4.name = "흡혈귀";
	m5.name = "구미호";

	m1.symbol = "＃";
	m2.symbol = "★";
	m3.symbol = "§";
	m4.symbol = "♬";
	m5.symbol = "♥";
	
	
	do {
		system("cls");					// 화면 비우기
		m1.moving(&m1.x, &m1.y);		// Monster m1을 이동
		showing(m1, m2, m3, m4, m5);	// 이동시킨 현재 상황을 화면으로 출력
		statement(m1, m2, m3, m4, m5);	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다 
		Sleep(300);
		
		system("cls");					// 화면 비우기
		m2.moving(&m2.x, &m2.y);		// Monster m2를 이동
		showing(m1, m2, m3, m4, m5);	// 이동시킨 현재 상황을 화면으로 출력
		statement(m1, m2, m3, m4, m5);	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다
		Sleep(500);
		
		system("cls");					// 화면 비우기
		m3.moving(&m3.x, &m3.y);		// Monster m3를 이동
		showing(m1, m2, m3, m4, m5);	// 이동시킨 현재 상황을 화면으로 출력
		statement(m1, m2, m3, m4, m5);	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다
		Sleep(500);

		system("cls");					// 화면 비우기
		m4.moving(&m4.x, &m4.y);		// Monster m4를 이동
		showing(m1, m2, m3, m4, m5);	// 이동시킨 현재 상황을 화면으로 출력
		statement(m1, m2, m3, m4, m5);	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다
		Sleep(500);

		system("cls");					// 화면 비우기
		m5.moving(&m5.x, &m5.y);		// Monster m5를 이동
		showing(m1, m2, m3, m4, m5);	// 이동시킨 현재 상황을 화면으로 출력
		statement(m1, m2, m3, m4, m5);	// 전체 이동 횟수, 남은 아이템 수, 각 Monster의 이름 상징 획득한 아이템 수를 출력한다
		Sleep(500);
	} while (m1.foodcount + m2.foodcount + m3.foodcount + m4.foodcount + m5.foodcount < 195);	// 모든 아이템을 획득할 때 까지 반복

	return 0;
}
