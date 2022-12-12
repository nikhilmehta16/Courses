#include <iostream>  //Importing necessary libraries
#include <stdlib.h>
using namespace std;
class Tuple {        //Class to hold 3 integers (start - Starting point of array segment, end - end point, sorted - whether the segment is sorted or not)
	public:          //Class variables and functions are public
	int start;
	int end;
	int sorted;
	Tuple(int st, int en, int sor){  //Constructor to initialize the three values
		start = st;
		end = en;
		sorted = sor;
	}
	Tuple(const Tuple& tup){        //Contructor to copy a tuple object
		start = tup.start;
		end = tup.end;
		sorted = tup.sorted;
	}
};

class Block {       //This class represents a block in the stack to store tuple data. It uses the concept of doubly linked list
	public:         //Variables are public
	Tuple val;      //Main data
	Block *next;    //Pointer to next block
	Block *prev;    //Pointer to previous block
};

class Stack{       //
	public:
	Block* top;
	Tuple pop() {
		if(top != NULL){
			Tuple temp = top->val;
			top = top->prev;
			if(top != NULL){
				top->next = NULL;
			}
			return temp;
		}
		else
			throw "Empty Stack!!";
	}
	void push(Tuple num) {
		Block* new_b = (Block*)malloc(sizeof(Block));
		new_b->val = num;
		new_b->next = NULL;
		new_b->prev = top;
		top = new_b;
	}
	bool is_empty(){
		if(top == NULL)
			return true;
		return false;
	}
	Stack(){
		top = NULL;
	}
};

int *final_arr;

void merge(int* A, int i, int j, int k){
    int p = i;
    int q = j+1;
    int r = i;
    while(r <= k){
        if(p <= j && q <= k && A[p] <= A[q]){
            final_arr[r++] = A[p++];
        }
        else if(p <= j && q <= k && A[p] >= A[q]){
            final_arr[r++] = A[q++];
        }
        else if(p <= j && q > k){
            final_arr[r++] = A[p++];
        }
        else if(p > j && q <= k){
            final_arr[r++] = A[q++];
        }
    }
    for(int no = i; no <= k; no++){
        A[no] = final_arr[no];
    }
}

void merge_sort(int* A, Stack* S){
	while(! S->is_empty()){
		Tuple temp = S->pop();
		int i = temp.start;
		int k = temp.end;
		int j = (i+k)/2;
		if(temp.sorted == 1){
			merge(A, i, j, k);
		}
		else{
			if(k > i){
				S->push(Tuple(i, k, 1));
				S->push(Tuple(j+1, k, 0));
				S->push(Tuple(i, j, 0));
			}
		}
	}
}

int main() {
	unsigned short int t;                 //No of test cases
	cin >> t;
	while(t>0){
		unsigned int n;                   //Size of an array used in each test case
		cin >> n;
		int *A = (int*)malloc(n * sizeof(int));       //Allocating space for main array(A) and buffer array(final_arr)
		final_arr = (int*)malloc(n * sizeof(int));
		for(int i = 0;i < n; i++){
			cin >> A[i];
			Stack* S = new Stack();
			Tuple tup(0, i, 0);
			S->push(tup);
			merge_sort(A, S);
		}
		t -= 1;
		for(int i=0; i<n; i++){
			cout<< A[i] << " ";
		}
		cout << endl;
		free(final_arr);
	}
}