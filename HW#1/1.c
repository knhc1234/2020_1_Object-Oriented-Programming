#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int com_choice(int i, int com_array[]);			// 컴퓨터가 랜덤하게 1~10의 값을 선택(중복 x)
int player_choice(int i, int player_array[]);	// 플레이어가 1~10의 값을 선택(중복x)
void show(int i, int total, int com_array[], int player_array[]);	// 현재까지 선택한 숫자들과 합을 표기

int com[10] = { 0 };	// 1~10까지 숫자 중 랜덤으로 선택한 순서대로 배열에 넣음
int player[10] = { 0 };	// 1~10까지 숫자 중 랜덤으로 선택한 순서대로 배열에 넣음

int main(void) {
	
	int total = 0;	// 나온 숫자들의 합 (100이상이 되면 게임 종료)
	int i = 0;		// 턴을 세기 위한 숫자(배열의 index역할)
	int wincount = 0;	// 승자를 가리기 위한 인수
	int num1 = 0;		// player가 이번턴에 선택한 숫자(total 계산용)
	int num2 = 0;		// com이 이번턴에 선택한 숫자(total 계산용)

	while (total < 100) {	// 총 합이 100이상 되면 게임 종료
		num2 = com_choice(i,com);		// com이 랜덤으로 숫자 선택
		total += num2;					// 이를 총합에 더함
		show(i, total, com, player);	// 현재 상황 표시(서로가 선택한 숫자들과 총합)
		if (total >= 100) {				// com이 랜덤으로 숫자를 선택할 때 100이상인 경우 
			wincount = 1;				// wincount가 1이됨(com 승리)
			break;
		}
		num1 = player_choice(i,player);	// player가 숫자 선택
		total += num1;					// 이를 총합에 더함
		i++;							// 턴 증가(배열의 index증가)
	}
	if (wincount == 0) {				// wincount가 1이아닌 상태로 끝난 경우 플레이어가 승리
		printf("Player의 승리입니다!");
	}
	else {								// wincount가 1인 상태로 끝난 경우 com이 승리
		printf("Computer의 승리입니다!");
	}
}

int com_choice(int i, int com_array[10]) {	// 컴퓨터가 랜덤으로 값을 선택
	int checkcount = 0;						// 중복 확인용
	int com_num = 0;						// 컴퓨터가 선택한 숫자를 담을 인수
	srand(time(NULL));
	do {
		checkcount = 0;						// 아래에서 중복으로 checkcount가 1이되어 다시 반복할 경우 0으로 다시 초기화
		com_num = rand() % 10 + 1;			// 1~10중 랜덤하게 선택
		for (int j = 0; j < i; j++) {
			if (com_array[j] == com_num) {	// 중복이 확인된 경우 checkcount가 1이됨
				checkcount = 1;
			}
		}
	} while (checkcount != 0);				// checkcount가 1 즉 중복이 확인된 경우 다시 선택
	com_array[i] = com_num;					// 중복이 되지 않도록 선택한 경우 이를 배열에 저장하고
	return com_num;							// total값에 더하기 위해 return해줌
}

int player_choice(int i, int player_array[10]) {	// 플레이어가 값을 선택
	int checkcount = 0;								// 중복 확인용
	int player_num = 0;								// 플레이어가 선택한 숫자를 담을 인수
	do {
		checkcount = 0;
		printf("숫자를 선택해주세요:");				// 아래에서 중복으로 checkcount가 1이되어 다시 반복할 경우 0으로 다시 초기화
		scanf("%d", &player_num);					// 숫자 하나를 선택
		for (int j = 0; j < i; j++) {
			if (player_array[j] == player_num || player_num < 1 || player_num > 10) {	// 중복이 되거나 1보다 작거나 10보다 큰 숫자를 골랐을 경우 
				checkcount = 1;															// checkcount가 1이됨
				printf("오류! 숫자를 다시 골라주세요.\n");
			}
		}
	} while (checkcount != 0);						// 중복 혹은 조건에 맞지 않는 숫자를 선택했을 경우 다시 선택
	player_array[i] = player_num;					// 중복이 아니고 1~10사이의 적절한 숫자를 선택했을 경우 이 값을 배열에 저장
	return player_num;								// total값에 더하기 위해 return해줌
}

void show(int i, int total, int com_array[], int player_array[]) {		// 현재 컴퓨터와 플레이어가 선택한 숫자들과 합을 표로 보여줌
	system("cls");							// 화면을 깨끗하게 비움
	printf("com_choice:");					// com이 고른 숫자들을 나열함
	for (int j = 0; j <= i; j++) {
		printf("%3d", com_array[j]);
	}
	printf("\n");
	printf("player_choice:");				// plyaer가 고른 숫자들을 나열함
	for (int j = 0; j <= i; j++) {
		printf("%3d", player_array[j]);
	}
	printf("\n");
	printf("총 숫자의 합: %d\n", total);	// 총 숫자의 합을 표기
}
