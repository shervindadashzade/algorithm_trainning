#include<iostream>

using namespace std;

struct node{
	node *next;
	node *prev;
	int value;
};


class linkedList{
	int length=0;
	struct node *head;
	struct node *tail;
	public:
	bool isEmpty(){
		if(length == 0)
			return true;
		else
			return false;
	}
	void add(int val){
		struct node *node = new struct node;
		node->value = val;
		if(isEmpty()){
		head = node;
		tail = node;
		}else{
		tail->next = node;
		node->prev = tail;
		tail = node;
		}
		length++;
	}
	int get(int n){
		if(isEmpty() || n > length){
			return NULL;
		}
		struct node *current;
		current = head;
		for(int i=0;i<n;i++){
			current = current->next;
		}
		return current->value;
	}	
};

int main(){
	//for test
	linkedList l;
	l.add(2);
	l.add(5);
	l.add(44);
        cout<<l.get(1)<<endl;
}
