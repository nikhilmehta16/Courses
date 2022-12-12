#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 1000000
// to maintain history of sorted elemnts
class tupple {
   public:
    int isSorted;
    int first;
    int end;

    tupple(int f, int l, bool s) {
        first = f;
        end = l;
        isSorted = s;
    }
};

class Stack {
   private:
    tupple* arr[MAX];
    int len;

   public:
    Stack() {
        len = 0;
    }
    // pushes the history to stack
    void push(tupple* val) {
        arr[len] = val;
        len += 1;
    }
    // pops the top element and removes it
    tupple* pop() {
        len -= 1;
        return arr[len];
    }
    // return the top element without removing it
    tupple* top() {
        return arr[len - 1];
    }
    // returns 1 if array is not empty
    int isEmpty() {
        if (len > 0) {
            return 0;
        } else {
            return 1;
        }
    }
};
// as done in the first assignment , merges two sorted arrays
void merge(int* arr, int start, int end) {
    int mid = start + (end - start) / 2;
    int i = start, j = mid + 1;
    int temp[end - start + 1];
    for (int k = 0; k <= end - start; k++) {
        if (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {
                temp[k] = arr[i++];
            } else {
                temp[k] = arr[j++];
            }

            continue;
        }
        if (i > mid && j <= end) {
            temp[k] = arr[j];
            j += 1;
            continue;
        }
        if (i <= mid && j > end) {
            temp[k] = arr[i];
            i += 1;
            continue;
        }
    }

    for (int k = start; k <= end; k++)
        arr[k] = temp[k - start];

    return;
}
// this function sort the array itteratively by constantly pushing and popping the elements which is basically stack implementation
void mergeSort(int* arr, int len) {
    Stack s;
    tupple* t = new tupple(0, len - 1, false);
    s.push(t); // pushes the current history to tupple

    while (!s.isEmpty()) {
        t = s.pop(); 

        if (t->isSorted) {
            merge(arr, t->first, t->end);
        } else {
            if (t->first < t->end) {
                int mid = t->first + (t->end - t->first) / 2;
                s.push(new tupple(t->first, t->end, true));
                s.push(new tupple(t->first, mid, false));
                s.push(new tupple(mid + 1, t->end, false));
            }
        }
    }
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n; 
        cin >> n; // no of elements in the array
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        mergeSort(arr, n);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << '\n';
    }

    return 0;
}