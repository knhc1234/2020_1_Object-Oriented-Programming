// 2019253025 윤광현
#include <iostream>
using namespace std;

class BaseArray {
private:
	int capacity;
	int* mem;
protected:
	BaseArray(int capacity = 100) {
		this->capacity = capacity; mem = new int[capacity];
	}
	~BaseArray() { delete[]mem; }

	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class MyStack :public BaseArray {
	int in, out;
	int size;
public:
	MyStack(int capacity);
	void push(int n);	// 스택에 추가
	int pop();			// 스택에서 제거
	int capacity();	// 용량
	int length();	// 개수
};

MyStack::MyStack(int capacity) : BaseArray(capacity) {
	in = 0;
	out = in + 1;
	size = 0;
}

void MyStack::push(int n) {
	if (size == capacity()) {
		return;
	}
	put(in, n);
	in++;
	out++;
	size++;
}

int MyStack::pop() {
	if (size == 0)
		return -1;
	size--;
	out--;
	in--;
	return get(out);
}

int MyStack::capacity() {
	return getCapacity();
}

int MyStack::length() {
	return size;
}

int main(void) {
	MyStack mS(100);
	int n;
	cout << "스택에 삽입할 5개의 정수를 입력:";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mS.push(n);
	}
	cout << "스택의 용량:" << mS.capacity()
		<< ", 스택의 크기:" << mS.length() << endl;

	cout << "스택의 원소를 순서대로 제거하여 출력:";
	while (mS.length() != 0) {
		cout << mS.pop() << "";
	}
	cout << endl << "스택의 현재 크기:" << mS.length() << endl;

}