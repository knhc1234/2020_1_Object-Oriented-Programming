#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int com_choice(int i, int com_array[]);			// ��ǻ�Ͱ� �����ϰ� 1~10�� ���� ����(�ߺ� x)
int player_choice(int i, int player_array[]);	// �÷��̾ 1~10�� ���� ����(�ߺ�x)
void show(int i, int total, int com_array[], int player_array[]);	// ������� ������ ���ڵ�� ���� ǥ��

int com[10] = { 0 };	// 1~10���� ���� �� �������� ������ ������� �迭�� ����
int player[10] = { 0 };	// 1~10���� ���� �� �������� ������ ������� �迭�� ����

int main(void) {
	
	int total = 0;	// ���� ���ڵ��� �� (100�̻��� �Ǹ� ���� ����)
	int i = 0;		// ���� ���� ���� ����(�迭�� index����)
	int wincount = 0;	// ���ڸ� ������ ���� �μ�
	int num1 = 0;		// player�� �̹��Ͽ� ������ ����(total ����)
	int num2 = 0;		// com�� �̹��Ͽ� ������ ����(total ����)

	while (total < 100) {	// �� ���� 100�̻� �Ǹ� ���� ����
		num2 = com_choice(i,com);		// com�� �������� ���� ����
		total += num2;					// �̸� ���տ� ����
		show(i, total, com, player);	// ���� ��Ȳ ǥ��(���ΰ� ������ ���ڵ�� ����)
		if (total >= 100) {				// com�� �������� ���ڸ� ������ �� 100�̻��� ��� 
			wincount = 1;				// wincount�� 1�̵�(com �¸�)
			break;
		}
		num1 = player_choice(i,player);	// player�� ���� ����
		total += num1;					// �̸� ���տ� ����
		i++;							// �� ����(�迭�� index����)
	}
	if (wincount == 0) {				// wincount�� 1�̾ƴ� ���·� ���� ��� �÷��̾ �¸�
		printf("Player�� �¸��Դϴ�!");
	}
	else {								// wincount�� 1�� ���·� ���� ��� com�� �¸�
		printf("Computer�� �¸��Դϴ�!");
	}
}

int com_choice(int i, int com_array[10]) {	// ��ǻ�Ͱ� �������� ���� ����
	int checkcount = 0;						// �ߺ� Ȯ�ο�
	int com_num = 0;						// ��ǻ�Ͱ� ������ ���ڸ� ���� �μ�
	srand(time(NULL));
	do {
		checkcount = 0;						// �Ʒ����� �ߺ����� checkcount�� 1�̵Ǿ� �ٽ� �ݺ��� ��� 0���� �ٽ� �ʱ�ȭ
		com_num = rand() % 10 + 1;			// 1~10�� �����ϰ� ����
		for (int j = 0; j < i; j++) {
			if (com_array[j] == com_num) {	// �ߺ��� Ȯ�ε� ��� checkcount�� 1�̵�
				checkcount = 1;
			}
		}
	} while (checkcount != 0);				// checkcount�� 1 �� �ߺ��� Ȯ�ε� ��� �ٽ� ����
	com_array[i] = com_num;					// �ߺ��� ���� �ʵ��� ������ ��� �̸� �迭�� �����ϰ�
	return com_num;							// total���� ���ϱ� ���� return����
}

int player_choice(int i, int player_array[10]) {	// �÷��̾ ���� ����
	int checkcount = 0;								// �ߺ� Ȯ�ο�
	int player_num = 0;								// �÷��̾ ������ ���ڸ� ���� �μ�
	do {
		checkcount = 0;
		printf("���ڸ� �������ּ���:");				// �Ʒ����� �ߺ����� checkcount�� 1�̵Ǿ� �ٽ� �ݺ��� ��� 0���� �ٽ� �ʱ�ȭ
		scanf("%d", &player_num);					// ���� �ϳ��� ����
		for (int j = 0; j < i; j++) {
			if (player_array[j] == player_num || player_num < 1 || player_num > 10) {	// �ߺ��� �ǰų� 1���� �۰ų� 10���� ū ���ڸ� ����� ��� 
				checkcount = 1;															// checkcount�� 1�̵�
				printf("����! ���ڸ� �ٽ� ����ּ���.\n");
			}
		}
	} while (checkcount != 0);						// �ߺ� Ȥ�� ���ǿ� ���� �ʴ� ���ڸ� �������� ��� �ٽ� ����
	player_array[i] = player_num;					// �ߺ��� �ƴϰ� 1~10������ ������ ���ڸ� �������� ��� �� ���� �迭�� ����
	return player_num;								// total���� ���ϱ� ���� return����
}

void show(int i, int total, int com_array[], int player_array[]) {		// ���� ��ǻ�Ϳ� �÷��̾ ������ ���ڵ�� ���� ǥ�� ������
	system("cls");							// ȭ���� �����ϰ� ���
	printf("com_choice:");					// com�� �� ���ڵ��� ������
	for (int j = 0; j <= i; j++) {
		printf("%3d", com_array[j]);
	}
	printf("\n");
	printf("player_choice:");				// plyaer�� �� ���ڵ��� ������
	for (int j = 0; j <= i; j++) {
		printf("%3d", player_array[j]);
	}
	printf("\n");
	printf("�� ������ ��: %d\n", total);	// �� ������ ���� ǥ��
}
