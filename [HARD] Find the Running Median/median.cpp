#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

/*
 * The approach I've taken to this problem is to use two heaps,
 * that contain the lower half of the sequence, in ascending order,
 * and the upper half of the sequence, in descending order, respectively.
 * This way we can access in constant time the 2 middle elements, so we
 * can compute the median pretty much instantaneously.
 * Of course, the insertion is tricky. It takes O(log(n)) to insert an
 * element in a heap, plus we need to balance the two heaps so they
 * contain the same amount of elements (+-1 if the total amount
 * of items is off, of course).
 * That is done by taking the root of the bigger heap and inserting it
 * into the other one, with, again, a cost of O(log(n))
 * 
 * TL;DR: I use 2 heaps to keep track of the current 2 middle elements.
 * For each step:
 * MEDIAN CALCULATION: O(1)
 * INSERTION: O(log(n))
 * 
 * TOTAL TIME COMPLEXITY: O(n*log(n))
 * (While the brute-force approach would have a complexity of O(n^2 * log(n)))
 */

/* Function to order the lower heap (root = max element) */
bool maxHeap(int a, int b) {
    return a < b;
}

/* Function to order the higher heap (root = min element) */
bool minHeap(int a, int b) {
    return a > b;
}

/* Wrapper for pushing an element in a heap */
void hPush(vector<int>& heap, int x, bool (*f)(int, int)) {
    heap.push_back(x);
    push_heap(heap.begin(), heap.end(), f);
}

/* Wrapper for popping the root out of a heap */
void hPop(vector<int>& heap, bool (*f)(int, int)) {
    pop_heap(heap.begin(), heap.end(), f);
    heap.pop_back();
}

/* Checks if the heaps are unbalanced; if so, it balances them */
void balance(vector<int>& bigger, vector<int>& smaller, bool (*s)(int, int), bool (*f)(int, int)) {
    if(bigger.size() > smaller.size()+1) {
        hPush(smaller, bigger[0], f);
        hPop(bigger, s);
    }
}

/* Returns the average of the two middle elements. A will never be empty
 * because of how this function is used it the code, but if B is
 * then it returns the root of A.
 */
double avg(vector<int>& A, vector<int>& B) {
    if(B.empty())
        return A[0];
    return (double)((A[0]+B[0]))/2.0;
}

/* Computes a step of the algorithm */
void runningMedian(vector<int>& input) {
    vector<int> low_half;
    vector<int> high_half;
    for(int i=0; i<input.size(); i++) {
        //INSERTION
        int x = input[i];
        if(low_half.empty())
            hPush(low_half, x, maxHeap);
        else {
            if(x <= avg(low_half, high_half))
                hPush(low_half, x, maxHeap);
            else
                hPush(high_half, x, minHeap);
            //BALANCING
            balance(low_half, high_half, maxHeap, minHeap);
            balance(high_half, low_half, minHeap, maxHeap);
        }
        //PRINTING
        if((i+1)%2 == 0) {
            cout << avg(low_half, high_half);
        }
        else {
            if(low_half.size() > high_half.size()) {
                cout << (double)low_half[0];
            }
            else {
                cout << (double)high_half[0];
            }
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0;a_i < n;a_i++) {
       cin >> a[a_i];
    }
    cout << fixed << setprecision(1);
    runningMedian(a);
    
    return 0;
}
