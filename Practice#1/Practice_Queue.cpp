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

class MyQueue :public BaseArray {
	int head, tail;
	int size;
public:
	MyQueue(int capacity);
	void enqueue(int n);	// 큐에 입력
	int dequeue();			// 큐에서 제거
	int capacity();	// 용량
	int length();	// 개수
};

MyQueue::MyQueue(int capcity) : BaseArray(this->capacity) {		// 이쪽 에러 설명을 해주셔도 도저히 모르겠어요 ㅠㅠ;
	head = 0;
	tail = -1;
	size = 0;
}

void MyQueue::enqueue(int n) {
	if (size == capacity()) {
		return;
	}
	put(head, n);
	head++;
	head = head % capacity();
	size++;
}

int MyQueue::dequeue() {
	if (size == 0)
		return -1;
	size--;
	tail++;
	tail = tail % capacity();
	return get(tail);
}

int MyQueue::capacity() {
	return getCapacity();
}

int MyQueue::length() {
	return size;
}

int main(void) {
	MyQueue mQ(100);
	int n;
	cout << "큐에 삽입할 5개의 정수를 입력:";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mQ.enqueue(n);
	}
	cout << "큐의 용량:" << mQ.capacity()
		<< ", 큐의 크기:" << mQ.length() << endl;

	cout << "큐의 원소를 순서대로 제거하여 출력:";
	while (mQ.length() != 0) {
		cout << mQ.dequeue() << "";
	}
	cout << endl << "큐의 현재 크기:" << mQ.length() << endl;

}

