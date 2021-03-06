// a4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

/*leonardo vasilev
assignment #6
2000213591
section 1005
*/
#include <iostream>
#include <sstream>	

using namespace std; 
struct node
{
	int id;
	int value;
	string name;
	node * parent, *leftchild, *rightchild;

};


class thestack
{
public:
	node ** nodes;
	int i = 0;
	void push(node* );
	node * pop();

	thestack();
	~thestack();

private:

};

void thestack::push(node* a) {
	nodes[i] = a;
	i++;
}

node * thestack::pop() {
	i --;
	return nodes[i];
}


thestack::thestack()
{
	nodes = new node*[1000];
	for (size_t i = 0; i < 1000; i++)
	{
		nodes[i] = new node;
	}
	i = 0;
}

thestack::~thestack()
{
}

node * buildHeap(int*, node*,  int , int );
node * buildHeap2(int*, int*, int, int, int&, int*);


void inOrd(node*);
void preOrd(node*);
void postOrd(node*);
void bf(int *, int);
int main()
{
	/*	int * read = new int;
	int * arr = new int[10000];
	int arrsize = 0;


	//used for building linked list 
	thestack stack;
	//init the array to -1 
	for (int i = 0; i < 10000; i++)
	{
		arr[i] = -1;
	}

	int valid = scanf("%d", read);


	while (valid != EOF)
	{
		arr[arrsize] = *read;
		arrsize++;
		valid = scanf("%d", read);
	}
	
	node * root = new node;
	 root = buildHeap(arr, root, 0, arrsize);
	 
	 cout << "Inorder:::" << endl;
	inOrd(root);
	cout << endl;
	cout << "Preorder:" << endl;
	preOrd(root);
	cout << endl;
	cout << "Postorder::" << endl;
	postOrd(root);
	cout << endl;
	cout << "BF/Level Order:" << endl;
	bf(arr, arrsize);
	cout << endl;


	 */

	int* inor = new int[10000];
	int * postor = new int[10000];
	string inorder, postorder;
	getline(std::cin, inorder);
	getline(std::cin, postorder);
	std::istringstream is(inorder);
	std::istringstream ps(postorder);
	
	int count1 = 0;
	string extracted;

	while (std::getline(is,extracted,' '	))
	{
		std::stringstream convert(extracted);
		convert >> inor[count1];
		count1++;
	}
	count1 = 0;
	while (std::getline(ps, extracted, ' '))
	{
		std::stringstream convert(extracted);
		convert >> postor[count1];
		count1++;
	}

	count1--;
	int iter = count1;
	int * arrr = new int[1000];
	node * root = buildHeap2(inor, postor, 0, count1, iter,arrr);

	cout << "Inorder:::" << endl;
	inOrd(root);
	cout << endl;
	cout << "Preorder:" << endl;
	preOrd(root);
	cout << endl;
	cout << "Postorder::" << endl;
	postOrd(root);
	cout << endl;
	cout << "BF/Level Order:" << endl;

	


	return 0;
}

/*func to build a linked list heap from a binary heap array 
arr - binary heap  
first - a root pointer to the tree heap 
i - used to iterate over the array 
size - the size of the array . */
node * buildHeap(int * arr, node * first,  int i, int size) {
	if (i < size )
	{
		
	
	
	node * temp = new node;
	first = temp;

	first->value = arr[i];
	first->leftchild = first->rightchild = NULL;

	first->leftchild = buildHeap(arr,first->leftchild, 2*i+1, size);
	first->rightchild = buildHeap(arr, first->rightchild,2*i+2, size	);
	}
	return first;

}

/*
func to build a heap from the inorder and preorder sequence of elements in a binary tree
it makes use of the rule that every element in a postorder sequence(starting from the last) 
coresponds to traversing the tree starting at the left branch 
on the other hand an inorder sequence coresponds to branches in the tree so we can split 
the inorder sequence at elements which will be nodes and recursively iterate on the left and right 
branches to fully build the tree 
*/
node * buildHeap2(int inorder[], int postorder[], int start, int end, int &postIndex , int  arr[]) {
	int inorderIndex = 0; //used to split the inorder array 
	if (start>end)
	{
		return NULL;
	}

	node * n = new node;
	n->leftchild = n->rightchild = NULL;
	n->value = postorder[postIndex];
	postIndex--;

	
	//check if there are any elements in this section of the array 
	if (start==end)
	{
		return n;//if not everything else is null 
	}

	for (size_t ii = start; ii <= end; ii++)
	{
		if (inorder[ii]==postorder[postIndex])
		{
			inorderIndex = ii;
			break;
		}
	}

	//if there is an index to split then try to get left and right leaves or branches
	n->rightchild = buildHeap2(inorder, postorder, inorderIndex + 1, end, postIndex,arr); //this will always be the right half
	//left half 
	n->leftchild = buildHeap2(inorder, postorder, start, inorderIndex - 1, postIndex,arr);

	return n;
}

/*function to traverse a binary heap in a post order fashion and print each visited node*/
void postOrd( node* root)
{
	if (root == NULL) {
		return;
	}

	postOrd(root->leftchild);
	postOrd(root->rightchild);
	cout << root->value << " ";
}

/*function to traverse a binary heap in a in order fashion and print each visited node*/
void inOrd( node* root)
{
	if (root == NULL) {
		return;
	}

	inOrd(root->leftchild);
	cout << root->value << " ";
	inOrd(root->rightchild);
}

/*
function to traverse a binary heap in a pre order fashion and print each visited node*/
void preOrd(node * root) {
	if (root == NULL)
	{
		return;
	}
	
	cout << root->value << " ";
	preOrd(root->leftchild);
	preOrd(root->rightchild);
}

/*
function to print the queue in bfs fashion
it is much easier to do this with an array than with a pointer structure
(since it is linear)
*/
void bf(int * arr, int size) {
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}