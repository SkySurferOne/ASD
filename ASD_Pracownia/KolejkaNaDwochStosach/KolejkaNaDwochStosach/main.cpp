#include <iostream>
#include <stack>
using namespace std;

class Queue {
	public:
		void put(int);
		int get();
		bool isEmpty();
	private:
		stack < int > stack1; // in
		stack < int > stack2; // out
};
	
void Queue::put(int num) {
	if (stack1.empty()) {
		while (!stack2.empty()) {
			stack1.push(stack2.top());
			stack2.pop();
		}
		stack1.push(num);
	} else {
		stack1.push(num);
	}
}

int Queue::get() {
	if (stack2.empty()) {
		while (!stack1.empty()) {
			stack2.push(stack1.top());
			stack1.pop();
		}
	} 
	int num = stack2.top();
	stack2.pop();
	return num;
}

bool Queue::isEmpty() {
	return (stack1.empty() && stack2.empty());
}

int main() {
	Queue q;
	q.put(1);
	q.put(2);
	q.put(3);
	q.put(4);
	while (!q.isEmpty())
		cout << q.get() << endl;

	system("pause");
	return 0;
}