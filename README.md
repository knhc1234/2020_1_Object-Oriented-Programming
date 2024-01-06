# 2020_1_Object-Oriented-Programming
HW#1

컴퓨터와 사용자가 1~10 숫자를 서로 한번씩 숫자를 내어 그 합이 100이 넘이면 이기는 게임

- 컴퓨터와 사용자는 각각 1~10를 선택할수 있으나 자신이 한번 낸 숫자는 다시 낼수 없다. (같은숫자는 안됨)

HW#2 

1) Hangman Game
    - string클래스 사용
    - 알파벳 a부터 z까지를 위한 자리를 만듦
    - 이미 예측 되었으면 그 알파벳을 출력하고 아니면 ‘_’문자 출력
    - 게임이 종료되면 “성공” 또는 “실패”를 출력한다.

2) Monster Game
    - 평면에서 몬스터들이 무작위로 움직임
    - 몬스터는 클래스로, 세상은 2차원 배열로 구현
    - 배열의 각 칸에는 맨 처음에 아이템이 하나씩 놓임
    - 몬스터는 각기 다른 모양으로 화면에 출력
    - 몬스터들이 움직이면서 아이템을 먹음.
    - 인접한 8 방향의 이웃 칸들 중에 하나를 무작위로 선택
    - 몬스터가 움직일 때 마다 맵의 상태와 각 몬스터의 상태 출력
    - 다수의 몬스터 출연
    - 인접한 8 방향의 이웃 칸으로 움직이며 아이템을 먹음
    - 움직일 때 마다 맵의 상태와 각 몬스터의 상태 출력

Quiz#1
랜덤 수를 발생하는 클래스를 정의하자.  이 클래스에는 생성자, next(), next_range()인 멤버 함수를 포함한다.

생성자 : 짝수 홀수를 선택할 수 있도록 생성자를 정의하자.

next() 멤버 함수 : 0~ 32767 사이의 랜덤한 정수를 갖는다. (RAND_MAX) 

next_range() 멤버 함수 : 시작 정수와 끝나는 정수를 입력 받아, 그 범위안에 있는 랜덤한 정수를 찾는다.

메인 함수 : 정의된 클래스를 이용하여 짝수 정수 10개, 홀수 정수 10개를 출력하는 프로그램을 작성해 보시오.

  - rand() 함수 이용하기

