/*
	2019253025 ������
	���͵��� ���� �ٸ� ������� ȭ�鿡 ��µǸ� �� ĭ���� �������� �ϳ��� ���δ�.
	���͵��� ������ 8 ������ �̿� ĭ�� �߿� �ϳ��� �������� �����Ͽ� �����̸鼭 �������� �԰�
	�ýð��� ��ȭ�ϴ� ��Ȳ�� ������ ���¸� ����ϴ� �����̴�.
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
	
	m1.name = "����";
	m2.name = "������";
	m3.name = "��Ʈ";
	m4.name = "������";
	m5.name = "����ȣ";

	m1.symbol = "��";
	m2.symbol = "��";
	m3.symbol = "��";
	m4.symbol = "��";
	m5.symbol = "��";
	
	
	do {
		system("cls");					// ȭ�� ����
		m1.moving(&m1.x, &m1.y);		// Monster m1�� �̵�
		showing(m1, m2, m3, m4, m5);	// �̵���Ų ���� ��Ȳ�� ȭ������ ���
		statement(m1, m2, m3, m4, m5);	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ� 
		Sleep(300);
		
		system("cls");					// ȭ�� ����
		m2.moving(&m2.x, &m2.y);		// Monster m2�� �̵�
		showing(m1, m2, m3, m4, m5);	// �̵���Ų ���� ��Ȳ�� ȭ������ ���
		statement(m1, m2, m3, m4, m5);	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ�
		Sleep(500);
		
		system("cls");					// ȭ�� ����
		m3.moving(&m3.x, &m3.y);		// Monster m3�� �̵�
		showing(m1, m2, m3, m4, m5);	// �̵���Ų ���� ��Ȳ�� ȭ������ ���
		statement(m1, m2, m3, m4, m5);	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ�
		Sleep(500);

		system("cls");					// ȭ�� ����
		m4.moving(&m4.x, &m4.y);		// Monster m4�� �̵�
		showing(m1, m2, m3, m4, m5);	// �̵���Ų ���� ��Ȳ�� ȭ������ ���
		statement(m1, m2, m3, m4, m5);	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ�
		Sleep(500);

		system("cls");					// ȭ�� ����
		m5.moving(&m5.x, &m5.y);		// Monster m5�� �̵�
		showing(m1, m2, m3, m4, m5);	// �̵���Ų ���� ��Ȳ�� ȭ������ ���
		statement(m1, m2, m3, m4, m5);	// ��ü �̵� Ƚ��, ���� ������ ��, �� Monster�� �̸� ��¡ ȹ���� ������ ���� ����Ѵ�
		Sleep(500);
	} while (m1.foodcount + m2.foodcount + m3.foodcount + m4.foodcount + m5.foodcount < 195);	// ��� �������� ȹ���� �� ���� �ݺ�

	return 0;
}
