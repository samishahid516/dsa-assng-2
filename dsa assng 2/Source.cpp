#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

#define MAX 100

class PriorityQueue {
private:
	int front, rear;
	pair<char, string> queue[MAX];

public:
	PriorityQueue() {
		front = -1;
		rear = -1;
	}


	bool isEmpty() {
		return (front == -1);
	}


	bool isFull() {
		return ((rear + 1) % MAX == front);
	}


	void insert(char priority, const string& name) {
		if (isFull()) {
			cout << "Priority Queue is full!" << endl;
			return;
		}


		if (isEmpty()) {
			front = 0;
			rear = 0;
			queue[rear] = make_pair(priority, name);
		}
		else {
			int i, j;

			for (i = rear; i >= front; i--) {
				if (priorityLevel(priority) > priorityLevel(queue[i].first)) {
					queue[(i + 1) % MAX] = queue[i];
				}
				else {
					break;
				}
			}
			queue[(i + 1) % MAX] = make_pair(priority, name);
			rear = (rear + 1) % MAX;
		}
	}

	//Priority levels for elements: 'P' > 'T' > 'S'
	int priorityLevel(char element) {
		if (element == 'P') return 3;
		if (element == 'T') return 2;
		if (element == 'S') return 1;
		return 0;
	}


	pair<char, string> remove() {
		if (isEmpty()) {
			cout << "Priority Queue is empty!" << endl;
			return make_pair('\0', "");
		}

		pair<char, string> element = queue[front];
		if (front == rear) {
			front = rear = -1;  // Queue becomes empty
		}
		else {
			front = (front + 1) % MAX;
		}
		return element;
	}

	// Display the queue
	void display() {
		if (isEmpty()) {
			cout << "Priority Queue is empty!" << endl;
			return;
		}

		cout << "Priority Queue: ";
		for (int i = front; i != rear; i = (i + 1) % MAX) {
			cout << queue[i].first << ": " << queue[i].second << " " << endl;
		}
		cout << queue[rear].first << ": " << queue[rear].second << endl;
	}
};


void processQueueFromFile(const string& filename, PriorityQueue& pq) {
	ifstream infile(filename);
	if (!infile) {
		cout << "Error opening file!" << endl;
		return;
	}

	string line;
	while (getline(infile, line)) {
		char priority;
		string name;


		if (line.size() > 2 && line[1] == ':') {
			priority = line[0];
			name = line.substr(3);
			pq.insert(priority, name);
		}
	}

	infile.close();
}

int main() {
	PriorityQueue pq;


	string filename = "user.txt";
	processQueueFromFile(filename, pq);


	pq.display();

	return 0;
}
