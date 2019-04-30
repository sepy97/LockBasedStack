#include <iostream>
#include <thread>
#include <mutex>

#define MAX_THREAD_NUM 10

class LockStack {
public:
	LockStack() :head(NULL) {}
	
	void push(int d)
	{
		Node *pv = new Node;
		
		m.lock ();
		
		pv->d = d;
		pv->p = head;
		head = pv;
		
		m.unlock ();
	}
	int pop()
	{
		if (head == NULL) return NULL;
		/*if (isEmpty())
		{
   			return -1;
		}*/
		m.lock ();
		
		int temp = head->d;
		Node *pv = head;
		head = head->p;
		
		m.unlock ();
		
		delete pv;
		return temp;
	}
	bool isEmpty()
	{
		return (this->head == NULL);
		
	}
	void display();

private:
	struct Node {
		int d;
		Node *p;
	};
	
	Node *head;
	std::mutex m;
};

void testPush (LockStack* toTest, int data)
{
	toTest->push (data);
}

int main()
{
	LockStack toTest;
	
	std::thread thr[MAX_THREAD_NUM];
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		//toTest.push (i);
		thr[i] = std::thread (testPush, &toTest, i);
	}
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		thr[i].join ();
	}
	
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		printf ("%d\n", toTest.pop());
	}
	
	return 0;
}
