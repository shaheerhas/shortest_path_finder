#pragma once
#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <queue>
#define MAX 10000
template<class t>
class BinaryHeap {
private:
	t* heap;
	int size;
	int curElement;

	void swap(t *a, t *b) {
		t temp = *a;
		*a = *b;
		*b = temp;
		return;
	}
	int parent(int i) {
		return ((int)i / 2);
	}
	int left(int in) {
		return (2 * in);
	}
	int right(int in) {
		return ((2 * in) + 1);
	}
	void allocate() {
		t *temp = new t[size * 2];
		for (int i = 1; i < size; i++)
			temp[i] = heap[i];
		delete[]heap;
		heap = temp;
		size = size * 2;
	}
	//to percolate down after delete min

	void percolateDown(int i) {

		int l = left(i);
		int r = right(i);
		int smallest = i;

		if (l < curElement && heap[l] < heap[i])
			smallest = l;

		if (r < curElement && heap[r] < heap[smallest])
			smallest = r;

		if (smallest != i)
		{
			swap(&heap[i], &heap[smallest]);
			percolateDown(smallest);
		}
	}
public:
	BinaryHeap(int s, t* arr) {
		heap = new t[s];
		for (int i = 0; i < s; i++) { heap[i] = arr[i]; }
		size = s;
		curElement = 1;
	}
	BinaryHeap() {
		heap = new t[2];
		size = 2;
		//		for (int i = 0; i < size; i++) { heap[i] = -1; }
		curElement = 1;
	}

	~BinaryHeap() {

		delete[] heap;
	}

	bool isEmpty() {
		if (curElement == 1 || curElement == 0) return 1;
		else return 0;
	}

	void insert(const t &element) {

		if (curElement == size) {
			allocate();
		}
		heap[curElement] = element;
		int temp = curElement;
		curElement++;
		//check till root for violation
		//percolate up
		while (temp != 1 && heap[parent(temp)] > heap[temp]) {
			swap(&heap[temp], &heap[parent(temp)]);
			temp = parent(temp);
		}
	}
	//insertEnds
	t deleteMin() {
		if (!isEmpty())
		{
			t temp = heap[1];
			curElement--;
			heap[1] = heap[curElement];
			percolateDown(1);
			return temp;
		}
	}
};

//Linked List class
template <class DT> class Node {
public:
	DT value;
	Node *next;
};
template <class DT> class List {//index from 0 onwords
public:
	int count;
	Node <DT>*head;
	Node <DT>*cursor;

	List() {
		cursor = head = NULL;
		count = 0;
	}
	~List() {
		cursor = head;
		while (cursor)
		{

			Node<DT> *temp = cursor->next;
			delete cursor;
			cursor = temp;

		}

	}
	void insert(const DT &newDataItem)
	{
		cursor = head;
		Node <DT>*temp = new Node<DT>;
		temp->next = NULL;
		temp->value = newDataItem;
		if (!cursor)
			head = cursor = temp;
		else
		{
			while (cursor->next)
			{
				cursor = cursor->next;
			}
			cursor->next = temp;
			cursor = temp;
		}
		count++;
	}
	void insertAt(const DT &newDataItem, int index)
	{
		if (index < 0)
			cout << "Index out of Range" << endl;
		else {
			count++;
			Node<DT> *temp = new Node<DT>;
			temp->value = newDataItem;
			if (index == 0)
			{
				temp->next = head;
				head = temp;
			}

			else {
				cursor = head;
				int tempInd = 1;

				while (cursor->next && tempInd < index)
				{
					cursor = cursor->next;
					tempInd++;
				}
				if (cursor->next) {
					temp->next = cursor->next;
					cursor->next = temp;
					cursor = temp->next;

				}
				else
				{
					cout << "Index out of Range" << endl;
					count--;
				}
			}
		}
	}
	DT returnAt(int index)
	{
		if (index < 0)
			cout << "1Index out of Range" << endl;
		else {
			if (index == 0)
				return head->value;
			else {
				cursor = head->next;
				int tempInd = 1;
				while (cursor && tempInd < index)
				{
					cursor = cursor->next;
					tempInd++;
				}
				if (cursor)
					return cursor->value;
				else
					cout << "2Index out of Range" << endl;
			}
		}
	}
	void returnAt(int index, DT &obj)
	{
		if (index <= 0)
			cout << "Index out of Range" << endl;
		else {
			if (index == 1)
				obj = head->value;
			else {
				cursor = head->next;
				int tempInd = 2;
				while (cursor && tempInd < index)
				{
					cursor = cursor->next;
					tempInd++;

				}
				if (cursor) {
					obj = cursor->value;
				}
				else
					cout << "Index out of Range" << endl;
			}
		}
	}
	DT returnEdge(int index)
	{
		cursor = head;
		while (cursor)
		{
			if (cursor->value.index == index)
			{
				return cursor->value;
			}
			cursor = cursor->next;
		}
		cout << "Failed Returning Edge" << endl;
	}
	void remove() {
		if (cursor)
		{
			count--;
			if (cursor->next)
			{
				Node<DT> *temp = cursor->next;
				cursor->value = temp->value;
				cursor->next = temp->next;
				delete temp;
			}
			else
			{
				if (cursor != head) {
					Node<DT> *temp = head;
					while (temp->next != cursor) {
						temp = temp->next;

					}
					temp->next = NULL;
					delete cursor;
					cursor = head;
				}
				else
				{
					delete cursor;
					cursor = head = NULL;

				}
			}
		}

	}
	bool removeAt(int index)
	{
		if (index >= 0 && head)
		{
			cursor = head;
			int tempInd = 0;
			while (cursor && tempInd != index)
			{
				cursor = cursor->next;
				tempInd++;
			}
			if (cursor)
			{
				remove();
				return 1;
			}
			else
			{
				cout << "Index out of Range" << endl;
				return 0;
			}
		}
		else
		{
			cout << "Index out of Range" << endl;
			return 0;
		}

	}
	void replaceAt(const DT &newDataItem, int index)
	{
		if (index >= 0 && head)
		{
			Node <DT> *temp = head;
			int tempInd = 0;
			while (temp && tempInd != index)
			{
				temp = temp->next;
				tempInd++;

			}
			if (temp)
			{
				cursor = temp;
				cursor->value = newDataItem;
			}
			else
				cout << "Index out of Range" << endl;
		}
		else
			cout << "Index out of Range" << endl;
	}
	void clear() {
		if (head)
		{
			cursor = head;
			while (cursor)
				remove();
		}
	}
	bool isEmpty() {

		if (head) return 0;
		else return 1;
	}
	void display() {
		if (!isEmpty())
		{
			cursor = head;
			while (cursor) {
				cout << cursor->value;
				cursor = cursor->next;

			}
			cout << endl;
		}
		else
			cout << "No Edge" << endl << endl;
	}
	bool find(DT value, int &index)
	{
		cursor = head;
		index = 0;
		while (cursor) {
			if (cursor->value == value)
				return 1;
			cursor = cursor->next;
			index++;
		}
		return 0;

	}
};
//List class ends

//utility functions

int stringtoi(string s) {

	int l = s.length() - 1;
	int number = 0;
	for (int i = 0; l >= 0; l--, i++)
		number += (pow(10.0, double(i)))*(int(s[l]) - 48);
	return number;
}
string itos(int n) {

	string st = "";
	while (n) {  //int to string 

		st += char(n % 10) + 48;
		n = n / 10;
	}
	int l = st.length();
	char temp;
	for (int i = 0; i < l / 2; ++i) {//for inverting string 
		temp = st[i];
		st[i] = st[l - i - 1];
		st[l - i - 1] = temp;
	}
	return st;
}
string toLower(string str) {
	for (int a = 0; a < str.length(); a++)
		if (str[a] > 'A' && str[a] < 'Z')
			str[a] = tolower(int(str[a]));
	return str;

}

//vector class
template <class T>
class Vector {
	int size;

public:
	T *p;
	int count;
	Vector() {
		count = 0;
		size = 1;
		p = new T[size];
	}
	int operator [](T value)const {
		for (int i = 0; i < count; ++i)
			if (value == p[i])
				return i;


		return -1;
	}
	T operator [](int index)const {
		if (index < count)
			return p[index];
		else cout << "Index Out of range in VECTOR" << endl;
	}
	T& operator [](int index) {
		if (index < count)
			return p[index];
		else cout << "Index Out of range in VECTOR" << endl;
	}
	Vector<T> operator -= (T item)
	{
		for (int i = 0; i < count; i++) {
			if (p[i] == item) {
				for (int j = i; j < count; j++)
					p[j] = p[j + 1];
				break;
			}
		}
		count--;
		return *this;
	}
	void display()
	{
		for (int i = 0; i < count; ++i)
			cout << p[i] << endl;
	}
	Vector<T> operator += (T item)
	{
		if (count < size)
		{
			p[count] = item;
			count++;
		}
		else {
			T *temp = new T[size * 2];
			for (int i = 0; i < size; ++i)
				temp[i] = p[i];
			delete[] p;
			temp[size] = item;
			size = 2 * size;
			count++;
			p = temp;
		}
		return *this;
	}
	Vector<T> operator = (Vector<T> list)
	{
		if (list.p == p)
			return *this;
		else {
			size = list.size;
			count = list.count;
			delete[] p;
			p = new T[size];
			for (int i = 0; i < count; ++i)
				p[i] = list.p[i];
		}
		return *this;
	}
	Vector<T> operator += (Vector<T> list)
	{
		if (list.count)
			for (int i = 0; i < list.count; ++i)
				(*this) += list.p[i];

		return *this;
	}
};

//graph class node
template<class T>
class edge {
public:
	T weight;
	int index;

	edge<T> operator =(edge<T> obj) {

		weight = obj.weight;
		index = obj.index;
		return *this;
	}
	bool operator ==(edge<T> obj) {
		return (/*weight == obj.weight &&*/	index == obj.index);
	}
	bool operator < (edge<T> obj) {

		if (weight < obj.weight)
			return 1;
		else return 0;

	}
	bool operator > (edge<T> obj) {

		if (weight > obj.weight)
			return 1;
		else return 0;

	}

};
class dijextranode
{
	int weight;
	int myindex;
	dijextranode *previous;
	dijextranode *queuelink;
	int previous_index;

public:

	dijextranode()
	{
		myindex = -1;
		weight = 10000000;
		previous = NULL;
		queuelink = NULL;
		previous_index = -1;
	}
	int &get_previous_index() {
		return previous_index;
	}

	int &get_weight()
	{
		return weight;
	}
	int &get_myindex()
	{
		return myindex;
	}
	dijextranode *&get_previous()
	{
		return previous;
	}
	dijextranode *&get_queuelink()
	{
		return queuelink;
	}
	void operator=(dijextranode &p) {
		this->get_myindex() = p.get_myindex();
		this->get_weight() = p.get_weight();
		this->get_previous_index() = p.get_previous_index();
		this->get_previous() = p.get_previous();
		this->get_queuelink() = p.get_queuelink();

	}
};
struct node1
{
	string data;
	struct node1 *next;
};

// Creating a class STACK
class stack
{
	struct node1 *top;

public:
	int size;
	stack() // constructor
	{
		top = NULL;
		size = 0;
	}
	void push(string a); // to insert an element
	string pop();  // to delete an element
};
// PUSH Operation
void stack::push(string a)
{

	struct node1 *ptr;

	ptr = new node1;
	ptr->data = a;
	ptr->next = NULL;
	if (top != NULL)
		ptr->next = top;
	top = ptr;
	size += 1;

}

// POP Operation
string stack::pop()
{
	struct node1 *temp;
	if (top == NULL)
	{
		cout << "\nThe stack is empty!!!";
	}
	temp = top;
	top = top->next;
	size = size - 1;
	return temp->data;
}



class Queue {
	struct node {
		node* next;
		dijextranode data;
	};

	node * front;
	node* rear;
	int numberItems;
public:
	Queue();
	~Queue();
	dijextranode get_front();
	void enqueue(dijextranode item);
	dijextranode dequeue();
	void clear();
	void sort();
	int get_size();
	bool isEmpty() const;
};


Queue::Queue()
{
	rear = NULL;
	front = NULL;
	numberItems = 0;
}

int Queue::get_size()
{
	return numberItems;

}

Queue::~Queue()
{
	clear();
}


void Queue::enqueue(dijextranode item)
{
	node *newItem = new node;
	newItem->data = item;
	newItem->next = NULL;
	if (isEmpty() == true)
	{
		front = newItem;
		rear = newItem;
	}
	else
	{
		rear->next = newItem;
		rear = newItem;
	}
	numberItems++;
}
dijextranode Queue::dequeue()
{

	if (isEmpty()) {
		cout << "Queue is empty";
	}
	else {
		dijextranode num;
		node * temp = front->next;
		num = front->data;
		delete front;
		front = temp;
		numberItems--;
		return num;
	}

}


void Queue::clear()
{

	while (!isEmpty())
	{
		dequeue();
	}

}


void Queue::sort()
{
	node *current = front;
	node *temp = front;
	while (current != NULL)
	{
		while (temp != NULL)
		{

			if (current->data.get_weight()>temp->data.get_weight())
			{
				dijextranode a = current->data;
				current->data = temp->data;
				temp->data = a;

			}
			temp = temp->next;
		}
		current = current->next;
	}


}


bool Queue::isEmpty() const
{
	if (numberItems == 0)
		return true;
	else
	{
		return false;
	}
}

#include <vector>
template<typename t>
class Graph {
private:

	//data members

	List <edge<t>>** AdjacencyList; //create Adjacency list for storing vertices (an array of linked lists)
	Vector<string> cities;//vector to store city names
	int count; // total cities atm in the graph
			   //bool MatrixCheck;
			   //t **AdjacencyMatrix;
			   //t **AdjacencyMatrix2;
			   //int **Parent1;//floyd's method for finding all shortest paths
			   //int **Parent2;//floyd's method for finding all shortest paths

public:
	Graph() {
		count = 0;
		AdjacencyList = 0;
	}
	//-----------------------------//

	~Graph() {

		if (AdjacencyList)
		{
			for (int i = 0; i < count; ++i)
				if (AdjacencyList[i])
					delete AdjacencyList[i];
			delete[] AdjacencyList;
		}

	}

	//read the cities file
	bool ReadFile(string path) {
		ifstream file(path);

		if (!file)
		{
			cout << "Can't open file. Invalid path" << endl;
			return 0;
		}
		else {
			count = 0;
			string line = "";
			string sheher = "";
			getline(file, line);
			int ln = line.length();
			for (int i = 0; i < ln; i++)
				if (line[i] == ',')//as seperator for eaach city 
					count++;

			AdjacencyList = new List<edge<t>>*[count];//list for cities count No
			for (int i = 0; i < count; ++i)
				AdjacencyList[i] = new List<edge<t>>;

			for (int i = 1; i < ln; i++) {//starting from 1 as first seperator  ',',getting cities name
				while (i < ln && line[i] != ',') {
					sheher += line[i];
					i++;
				}
				cities += sheher;//overloaded fn in vector class,add city in city vector 
				sheher = "";
			}
			//extract edges
			string weight;
			for (int k = 0; k < count && file; k++) {//for count many rows
				line = "";
				getline(file, line);
				ln = line.length();
				int i = 0;
				while (line[i] != ',')//skipping first name so till first coma
					i++;

				i++;

				for (int e = 0; i < ln; e++) {//end of line

					while (i < ln && line[i] != ',') {//getting weight in char form
						weight += line[i];
						i++;
					}
					//current edge
					i++;//skipping of coma
					t w = stringtoi(weight);//conversion string to integer
					weight = "";

					if (w != 0 || e == k) { //e==k for it's own edge;as if w==0 no edge so we will skip

						edge<t> obj;
						obj.weight = w;
						obj.index = e;
						AdjacencyList[k]->insert(obj);
					}
				}

			}
			file.close();
			return 1;

		}//elseEnds

	}
	//printing

	void display() {

		if (AdjacencyList) {

			cout << "Graph with indexes and cities are :" << endl;

			for (int i = 0; i < count; ++i)
				cout << "Index :" << i << " -> " << cities[i] << endl;
			cout << '\n';


			for (int i = 0; i < count; i++) {

				if (AdjacencyList[i])
				{
					cout << cities[i] << " Has: " << endl;
					AdjacencyList[i]->display();
				}
			}
		}


	}
	//-----------------------------//

	string getCityAt(int index) {

		if (index >= 0 && index < count)
			return cities[index];
		else return "";
	}

	int giveCityIndex(string city) {
		city = toLower(city);
		for (int i = 0; i < count; i++) {
			string temp = toLower(cities[i]);
			if (city == temp)
				return i;
		}
		return -1;
	}
	//-----------------------------//

	void AddCity(string city) {

		List<edge<t>>** temp = new List<edge<t>>*[count + 1];
		for (int i = 0; i <= count; i++)
			temp[i] = new List<edge<t>>;
		//copy old list to temp

		for (int i = 0; i < count; i++) {
			int ecount = AdjacencyList[i]->count;
			for (int j = 0; j < ecount; j++) {
				edge<t>t = AdjacencyList[i]->returnAt(j);
				temp[i]->insert(t);
			}
		}

		for (int i = 0; i < count; i++)
			delete AdjacencyList[i];
		delete[]AdjacencyList;
		AdjacencyList = temp;
		edge<t> tempEdge;//adding edge to itself
		tempEdge.index = count;
		tempEdge.weight = 0;
		AdjacencyList[count]->insert(tempEdge);
		count++;
		city[0] = toupper(city[0]);//pehla letter capital.#grammar
		cities += city;
	}

	bool RemoveCity(string city) {
		int cityno = giveCityIndex(city);
		if (cityno > count || cityno < 0) {
			cout << "City not found";
			return 0;
		}
		cities -= city;
		List<edge<t>>** temp = new List<edge<t>>*[count - 1];
		for (int i = 0; i < count - 1; i++)
			temp[i] = new List<edge<t>>;

		for (int i = 0, k = 0; i < count; i++) {

			if (i != cityno) {
				int ecount = AdjacencyList[i]->count;
				for (int j = 0; j < ecount; j++) {
					edge<t>t = AdjacencyList[i]->returnAt(j);
					if (t.index != cityno)
					{
						if (t.index > cityno)
							t.index = t.index - 1;
						temp[k]->insert(t);
					}
				}
				k++;
			}
		}

		for (int i = 0; i < count; i++)
			delete AdjacencyList[i];
		delete[]AdjacencyList;
		AdjacencyList = temp;

		count--;
		return 1;
	}

	//-----------------------------//

	//----------------------------------------//
	bool AddEdge(string city1, string city2, t weight) {

		int city1No = giveCityIndex(city1);//city bahir se input hua
		int city2No = giveCityIndex(city2);

		if (city1No > count || city1No<0 || city2No >count || city2No < 0) {
			cout << "City/Cities Not Found" << endl;
			return 0;
		}

		else {
			int ind;
			edge<t> obj;
			obj.weight = weight;
			obj.index = city2No;
			if (AdjacencyList[city1No]->find(obj, ind))
				AdjacencyList[city1No]->replaceAt(obj, ind);
			else
				AdjacencyList[city1No]->insert(obj);

			return 1;
		}
	}
	//--------------------------------------//

	bool RemoveEdge(string city1, string city2) {


		int city1no = giveCityIndex(city1);//city bahir se input hua
		int city2no = giveCityIndex(city2);
		if (city1no > count || city1no<0 || city2no>count || city2no < 0) {
			cout << "City not found" << endl;
			return 0;
		}
		else {
			edge<t> temp;
			temp.index = city2no;
			int in;
			if (AdjacencyList[city1no]->find(temp, in))
			{
				AdjacencyList[city1no]->removeAt(in);
				return 1;
			}
			else return 0;
		}
	}

	//-------------------------------------------------//

	bool RemoveEdge(string city1, string city2,List<edge<t>> **&Newlist) {


		int city1no = giveCityIndex(city1);//city bahir se input hua
		int city2no = giveCityIndex(city2);
		if (city1no > count || city1no<0 || city2no>count || city2no < 0) {
			cout << "City not found" << endl;
			return 0;
		}
		else {
			edge<t> temp;
			temp.index = city2no;
			int in;
			if (Newlist[city1no]->find(temp, in))
			{
				Newlist[city1no]->removeAt(in);
				return 1;
			}
			else return 0;
		}
	}

	//------------------------------------------------//

	int SecondShortestpathC2All(string city)
	{
		int index = giveCityIndex(city);
		if (index == -1) {

			cout << "City is not valid" << endl;
			return 0;
		}
		dijextranode *temp;
		dikhestra(index, temp);
		for (int i = 0; i < count; i++)
		{
			Secondshortestalgo(index, i, temp);
		}
		return 0;
	}




	//-------------------------------------------------//

	int SecondShortestpathC2C(string city,string city2)
	{
		int index1 = giveCityIndex(city);
		int index2= giveCityIndex(city2);
		if (index1 == -1 || index2 == -1) {

			cout << "City is not valid" << endl;
			return 0;
		}
		dijextranode *temp;
		dikhestra(index1, temp);
		Secondshortestalgo(index1, index2, temp);
		return 0;
	}


	//------------------------------------------------//

	void Secondshortestalgo(int index1,int index2,dijextranode *&temp)
	{
		int b = index2;
		stack rand;
		rand.push(cities[b]);
		cout << "Second shortest path between " << cities[index1] << " and " << cities[index2] << " is:" << endl;
		while ((b != index1) && (temp[b].get_previous_index() != -1))
		{
			b = temp[b].get_previous_index();
			rand.push(cities[b]);

		}
		if (b != index1)
		{
			cout << "No Connection" << endl;
		}
		else
		{
			rand.pop();
			

			int nodes = rand.size-1;
			
			if (rand.size > 1)
			{
				dijextranode **allpaths;
				allpaths = new dijextranode *[rand.size - 1];
				int *pathcost = new int[rand.size - 1];
				int counter = 0;
				while (rand.size > 1)
				{
					List <edge<t>>** Newlist;
					Newlist = new List<edge<t>>*[count];
					for (int i = 0; i < count; ++i)
					{
						Newlist[i] = new List<edge<t>>;
					}
					edge<t> temp1;
					for (int i = 0; i < count; ++i)
					{

						Node <edge<t>> *cursor = AdjacencyList[i]->head;
						while (cursor)
						{
							temp1 = cursor->value;
							temp1.index = cursor->value.index;
							Newlist[i]->insert(temp1);
							cursor = cursor->next;
						}
					}



					int removeindex = giveCityIndex(rand.pop());
					//Newlist->removeAt(removeindex);
					for (int i = 0; i < count; ++i)
					{
						if (i != removeindex)
						{
							RemoveEdge(getCityAt(i), getCityAt(removeindex), Newlist);
						}
					}

					dikhestra(index1, allpaths[counter], Newlist);
					pathcost[counter] = allpaths[counter][index2].get_weight();
					counter += 1;




				}

				int lowest = 100000;
				dijextranode *lowestpath = NULL;
				for (int i = 0; i < nodes; i++)
				{
					if (pathcost[i] < lowest)
					{
						lowest = pathcost[i];
						lowestpath = allpaths[i];
					}
				}
			

				
				int k = index2;
				stack rand1;
				rand1.push(cities[k]);

				while ((k != index1) && (lowestpath[k].get_previous_index() != -1))
				{
					k = lowestpath[k].get_previous_index();
					rand1.push(cities[k]);

				}
				if (k != index1)
				{
					cout << "No Connection" << endl;
				}
				else
				{
					while (rand1.size > 0)
					{
						if (rand1.size == 1)
						{
							cout << rand1.pop() << endl;
						}
						else
						{
							cout << rand1.pop() << "->";
						}
					}
					cout << "Distance is :" << lowestpath[index2].get_weight() << endl;


				}
			}
			else
			{
				cout << "No path" << endl;
			}

		}



	}


	//--------------------------------------------------//

	void dikhestra(int index, dijextranode *&list1)
	{
		list1 = new dijextranode[count];
		Queue que;
		for (int i = 0; i<count; i++)
		{
			list1[i].get_myindex() = i;
			if (i == index)
			{
				list1[i].get_weight() = 0;
				que.enqueue(list1[i]);
			}
		}



		dijextranode temp;
		while (!(que.isEmpty()))
		{
			temp = que.dequeue();
			for (int i = 0; i< AdjacencyList[temp.get_myindex()]->count; i++)
			{
				edge<t> t = AdjacencyList[temp.get_myindex()]->returnAt(i);
				if (list1[t.index].get_weight() > temp.get_weight() + t.weight)
				{
					list1[t.index].get_weight() = temp.get_weight() + t.weight;
					list1[t.index].get_previous_index() = temp.get_myindex();
					que.enqueue(list1[t.index]);
				}
			}
			que.sort();

		}




	}


	//-----------------------------------------------//
	void dikhestra(int index, dijextranode *&list1,List<edge<t>> **Newlist)
	{
		list1 = new dijextranode[count];
		Queue que;
		for (int i = 0; i<count; i++)
		{
			list1[i].get_myindex() = i;
			if (i == index)
			{
				list1[i].get_weight() = 0;
				que.enqueue(list1[i]);
			}
		}



		dijextranode temp;
		while (!(que.isEmpty()))
		{
			temp = que.dequeue();
			for (int i = 0; i< Newlist[temp.get_myindex()]->count; i++)
			{
				edge<t> t = Newlist[temp.get_myindex()]->returnAt(i);
			
				if (list1[t.index].get_weight() > temp.get_weight() + t.weight)
				{
					list1[t.index].get_weight() = temp.get_weight() + t.weight;
					list1[t.index].get_previous_index() = temp.get_myindex();
					que.enqueue(list1[t.index]);
				}
			}
			que.sort();

		}




	}


	//-----------------------------------------------//


	void floyd(t** &AdjacencyMatrix, t** &AdjacencyMatrix2, int** &Parent1, int** &Parent2) {
		//count++;
		//initializing matrices with memory
		//MatrixCheck = 1;
		AdjacencyMatrix2 = new t*[count];
		AdjacencyMatrix = new t*[count];
		Parent2 = new int *[count];
		Parent1 = new int *[count];
		for (int i = 0; i < count; ++i) {
			AdjacencyMatrix2[i] = new t[count];
			AdjacencyMatrix[i] = new t[count];
			Parent2[i] = new int[count];
			Parent1[i] = new int[count];

		}
		//count--;
		//initializing matrices with values i.e distance max but if i==j then 0 Also parent will be 0
		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++)
			{
				AdjacencyMatrix[i][j] = AdjacencyMatrix2[i][j] = MAX;
				Parent2[i][j] = Parent1[i][j] = 0;

				if (i == j)
					AdjacencyMatrix[i][j] = 0;//for edge to itself
			}



		{
			int EdgesCount;
			edge<t> temp;
			for (int i = 0; i < count; ++i) {//for inititalizing adjancency matrix with direct edges

				EdgesCount = AdjacencyList[i]->count;
				for (int j = 0; j < EdgesCount; ++j)
				{
					temp = AdjacencyList[i]->returnAt(j);
					AdjacencyMatrix[i][temp.index] = temp.weight;
				}
			}

		}
		//applying floyd's to find all shortest distances for all the vertices
		for (int k = 0; k < count; k++) {
			for (int i = 0; i < count; i++) {
				for (int j = 0; j < count; j++) {

					if (AdjacencyMatrix[i][k] != MAX && AdjacencyMatrix[k][j] != MAX)
					{
						if (AdjacencyMatrix[i][j] > AdjacencyMatrix[i][k] + AdjacencyMatrix[k][j]) {

							if (AdjacencyMatrix[i][j] != MAX)
							{
								AdjacencyMatrix2[i][j] = AdjacencyMatrix[i][j];
								Parent2[i][j] = Parent1[i][j];
							}


							AdjacencyMatrix[i][j] = AdjacencyMatrix[i][k] + AdjacencyMatrix[k][j];
							Parent1[i][j] = k; //holds the vertex which lead to the smallest value
						}
						else if (AdjacencyMatrix2[i][j] > AdjacencyMatrix[i][k] + AdjacencyMatrix[k][j] && i != k) {

							Parent2[i][j] = k; //holds the vertex which lead to the smallest value	
							AdjacencyMatrix2[i][j] = AdjacencyMatrix[i][k] + AdjacencyMatrix[k][j];




						}
					}
				}
			}
		}




	}

	//-----------------------------//

	void path(int i, int j, int **&parent, t **&matrix) {

		int k = parent[i][j];
		if (k == 0)
		{
			cout << "From " << cities[i] << " To " << cities[j] << " :" << matrix[i][j] << endl;
			return;
		}

		path(i, k, parent, matrix);
		path(k, j, parent, matrix);
	}
	//-----------------------------//

	void ShortestPath(int &i, int &j, t** &AdjacencyMatrix, t** &AdjacencyMatrix2, int** &Parent1, int** &Parent2) {

		if ((i > count || i < 0) || (j > count || j < 0))
		{
			cout << "Given vertices aren't part of graph." << endl;
			return;
		}
		string source, destination;
		source = cities[i];
		destination = cities[j];

		if (AdjacencyMatrix[i][j] == MAX) {
			cout << "There is no path between " << source << " & " << destination << endl;
			return;
		}

		cout << "Shortest distance between " << source << " & " << destination << " is :" << AdjacencyMatrix[i][j] << endl;
		cout << "Path is :" << endl;
		path(i, j, Parent1, AdjacencyMatrix);



		if (AdjacencyMatrix2[i][j] == MAX) {
			cout << "There is no alternate path between " << source << " & " << destination << endl;
			return;
		}

		cout << "Second shortest distance between " << source << " & " << destination << " is :" << AdjacencyMatrix2[i][j] << endl;
		//cout << "Path is :" << endl;
		//	path(i, j, Parent2, AdjacencyMatrix2);
		cout << endl;


	}


	//-----------------------------//

	bool FindPathFromCity2All(string city) {



		int index = giveCityIndex(city);
		if (index == -1) {

			cout << "City is not valid" << endl;
			return 0;
		}
		else {
			t** AdjacencyMatrix; t** AdjacencyMatrix2; int** Parent1; int** Parent2;

			floyd(AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);
			for (int i = 0; i < count; ++i)
				ShortestPath(index, i, AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);
			return 1;
		}
	}


	//-----------------------------//


	int FindPathFromCity2AllD(string name)
	{
		int index1 = giveCityIndex(name);
		if (index1 == -1) {

			cout << "City is Not Valid" << endl;
			return 0;
		}
		dijextranode *temp;
		dikhestra(index1, temp);  // gives temp with array of dijextranode each stroring minimum distance of city and its previos neighbour

		for (int i = 0; i < count; i++)
		{
			int index2 = i;
			cout << "Smallest path between " << cities[index1] << " and " << cities[index2] << " is : " << endl;
			int b = index2;
			stack rand;
			rand.push(cities[b]);
			while ((b != index1) && (temp[b].get_previous_index() != -1))
			{
				b = temp[b].get_previous_index();
				rand.push(cities[b]);

			}
			if (b != index1)
			{
				cout << "No Connection" << endl;
			}
			else
			{
				while (rand.size > 0)
				{
					if (rand.size == 1)
					{
						cout << rand.pop() << endl;
					}
					else
					{
						cout << rand.pop() << "->";
					}
				}
				cout << "Distance is :" << temp[index2].get_weight() << endl;

			}
		}
		return 0;
	}

	//-----------------------------//

	bool FindPathFromAll2City(string city) {



		int index = giveCityIndex(city);
		if (index == -1) {

			cout << "City is not valid" << endl;
			return 0;
		}
		else {
			//temp matrices to store shortest and second shortest paths
			t** AdjacencyMatrix; t** AdjacencyMatrix2; int** Parent1; int **Parent2;
			floyd(AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);
			for (int i = 0; i < count; ++i)
				ShortestPath(i, index, AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);
			return 1;
		}
	}


	//------------------------------//


	bool FindPathBtwPairOfCitiesD(string city1, string city2)
	{

		int index1 = giveCityIndex(city1);
		int index2 = giveCityIndex(city2);

		if (index1 == -1 || index2 == -1) {

			cout << "City/Cities are Not Valid" << endl;
			return 0;
		}
		dijextranode *temp;
		dikhestra(index1, temp);  // gives temp with array of dijextranode each stroring minimum distance of city and its previos neighbour

		cout << "Smallest path between " << cities[index1] << " and " << cities[index2] << " is:" << endl;
		int b = index2;
		stack rand;
		rand.push(cities[b]);
		
		while ((b != index1) && (temp[b].get_previous_index() != -1))
		{
			b = temp[b].get_previous_index();
			rand.push(cities[b]);

		}
		if (b!= index1)
		{
			cout << "No Connection" << endl;
		}
		else
		{
			while (rand.size > 0)
			{
				if (rand.size == 1)
				{
					cout << rand.pop() << endl;
				}
				else
				{
					cout << rand.pop() << "->";
				}
			}
			cout << "Distance is :" << temp[index2].get_weight() << endl;




		}
	}

	//-----------------------------//


	bool FindPathBtwPairOfCities(string city1, string city2) {


		int index1 = giveCityIndex(city1);
		int index2 = giveCityIndex(city2);



		if (index1 == -1 || index2 == -1) {

			cout << "City/Cities are Not Valid" << endl;
			return 0;
		}
		else {
			//temp matrices to store shortest and second shortest paths
			t** AdjacencyMatrix; t** AdjacencyMatrix2; int** Parent1; int **Parent2;
			floyd(AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);
			cout << endl;
			for (int i = 0; i<count; i++) {
				for (int j = 0; j<count; j++)
					cout << Parent1[i][j] << " ";

				cout << endl;
			}
			cout << endl << endl;
			for (int i = 0; i<count; i++) {
				for (int j = 0; j<count; j++)
					cout << Parent2[i][j] << " ";
				cout << endl;
			}
			ShortestPath(index1, index2, AdjacencyMatrix, AdjacencyMatrix2, Parent1, Parent2);//not as scary as it looks
			return 1;
		}
	}
	//-----------------------------//


};
template<class t>
ostream& operator<<(ostream& out, edge<t> &a) {
	out << "Edge with index " << a.index << " ";
	out << "Having weight: " << a.weight << endl;
	return out;
}
