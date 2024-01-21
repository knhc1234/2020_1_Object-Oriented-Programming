
class UpDownGame {
	static int answer;
	static int top;
	static int bottom;
private:
	static void init(); // answer 변수 랜덤 초기화
	static void msg(); // top과 bottom 출력
public:
	static void run(); // 게임 진행
	static bool check(int answer); // top과 bottom을 조절하고, 정답을 맞추었으면 true 리턴
};
