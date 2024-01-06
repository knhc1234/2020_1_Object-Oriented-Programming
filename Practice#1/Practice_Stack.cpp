// 2019253025 ������
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
	void push(int n);	// ���ÿ� �߰�
	int pop();			// ���ÿ��� ����
	int capacity();	// �뷮
	int length();	// ����
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
	cout << "���ÿ� ������ 5���� ������ �Է�:";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mS.push(n);
	}
	cout << "������ �뷮:" << mS.capacity()
		<< ", ������ ũ��:" << mS.length() << endl;

	cout << "������ ���Ҹ� ������� �����Ͽ� ���:";
	while (mS.length() != 0) {
		cout << mS.pop() << "";
	}
	cout << endl << "������ ���� ũ��:" << mS.length() << endl;

}