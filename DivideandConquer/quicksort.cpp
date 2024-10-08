#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void swap (int *x, int *y) {
      int temp = *x;
      *x = *y;
      *y = temp;
}
int partition (int *a, int l, int r) {
  int i = l, j = i+1;
  swap(a[l] , a[(l+r)/2]); //random quick sort (typically taken middle one)
  int pivot = a[l];
  while (j < r)  {
     if (pivot > a[j]) {
     i++;
     swap(a[i],a[j]);
     }
     j++;
  }
  swap(a[l], a[i]); // doing this mistake, pivot is the local variable, I need to swap with array values
  return i;  // return pivot index
}

int randompartition (int *a, int l, int r) {
  int i = l, j = i+1;
  //swap (a[l] , a[(l+r)/2]); //random quick sort (typically taken middle one)
  int pivot = a[l];
  while (j < r)  {
     if (pivot > a[j]) {
     i++;
     swap(a[i],a[j]);
     }
     j++;
  }
  swap(a[l], a[i]); // doing this mistake, pivot is the local variable, I need to swap with array values
  return i;  // return pivot index
}

void randomquicksort (int *a, int l, int r) {
    if (l < r) {
        int pivot = randompartition(a, l, r);
        cout << pivot << " ";
        randomquicksort(a, l, pivot - 1); //left subarray 
        randomquicksort(a, pivot + 1, r); //right subarray
    }
}

void quicksort (int *a, int l, int r) {
    if (l < r) {
        int pivot = partition(a, l, r);
        cout << pivot << " ";
        quicksort(a, l, pivot - 1); //left subarray 
        quicksort(a, pivot + 1, r); //right subarray
    }
}


int main () {
  int n;
  cout << "Enter the size of the array: ";
  cin >> n;
  int *a = new int[n];
  int *b = new int[n];  // Separate array for Randomized QuickSort

    // Input array
  for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> a[i];
        b[i] = a[i];  // Copy the same array to `b` for random quicksort
  }

    // Thread for normal quicksort
    auto start_quick = chrono::high_resolution_clock::now();
    thread t1(quicksort, a, 0, n);  // Run quicksort in a separate thread
    t1.join();
    auto stop_quick = chrono::high_resolution_clock::now();
    auto quicksort_duration = chrono::duration_cast<chrono::nanoseconds>(stop_quick - start_quick);

    // Thread for randomized quicksort
    auto start_random = chrono::high_resolution_clock::now();
    thread t2(randomquicksort, b, 0, n);  // Run random quicksort in a separate thread
    t2.join();
    auto stop_random = chrono::high_resolution_clock::now();
    auto randomquicksort_duration = chrono::duration_cast<chrono::nanoseconds>(stop_random - start_random);

    // Output sorted arrays and time taken
    cout << "Sorted array by QuickSort: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Sorted array by Randomized QuickSort: ";
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    cout << "Time taken by QuickSort: " << quicksort_duration.count() << " milliseconds" << endl;
    cout << "Time taken by Randomized QuickSort: " << randomquicksort_duration.count() << " milliseconds" << endl;

    delete[] a; // Free dynamically allocated memory
    delete[] b;

    return 0;

}


///
// 4 1 2 6 7 2 0 3 4 5 6 7 
// Sorted array by QuickSort: 1 2 3 5 6 15 30 90 
// Sorted array by Randomized QuickSort: 1 2 3 5 6 15 30 90 
// Time taken by QuickSort: 311727 milliseconds
// Time taken by Randomized QuickSort: 69822 milliseconds
// --> This proves randomized quicksort is faster than normal quicksort