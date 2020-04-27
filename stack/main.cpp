#include<iostream>

using namespace std;

struct node{
	struct node *next;
	struct node  *prev;
	int value;
};

class Stack{
	int length = 0;
	struct node *top;
	public:
	bool isEmpty(){
		if(length == 0)
			return true;
		else
			return false;
	}
	void push(int val){
		struct node *node = new struct node;
		node->value = val;
		if(isEmpty() ){
			top = node;
		}else{
			node->prev = top;
			top->next = node;
			top = node;
		}
		length++;
	}
	int pop(){
		if(!isEmpty()){
		int val = top->value;
		top = top->prev;
		length--;
		return val;
		}else{
		return -1;
		}
	}
	int size(){
		return length;
	}

};

int main(){
	// for test
	Stack mystack;
	mystack.push(5);
	mystack.push(4);
	mystack.push(7);
	cout<<mystack.pop();
	cout<<mystack.pop();
	cout<<mystack.pop();
	cout<<endl;
}
