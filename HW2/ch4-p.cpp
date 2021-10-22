#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

#define N 2                                                     //storing number of threads in N

int a[] = {6, 4, 5, 10, 7, 9, 8, 1, 3, 2};

typedef struct Arr{
    int low;
    int high;
} Array;

void merge(int low, int high){                               //sorting algorithm and merging function
  int mid = (low + high - 1)/ 2;
  int n1 = mid - low + 1;
  int n2 = high - mid;

  // Create temp arrays
  int L[n1], R[n2];

  // Copy data to temp arrays L[] and R[]
  for (int i = 0; i < n1; i++)
      L[i] = a[low + i];
  for (int j = 0; j < n2; j++)
      R[j] = a[mid + 1 + j];

  int j = 0, i = 0;
  int k = low;

  while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
          a[k] = L[i];
          i++;
      }
      else {
          a[k] = R[j];
          j++;
      }
      k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void * mergesort(void *a){                                   //function that creates threads and calls the merge function which sorts and merges the sub sets
  Array *pa = (Array *)a;
  if (pa->low >= pa->high) return 0;
  int mid = (pa->low + pa->high - 1)/2;

  Array aIndex[N];
  pthread_t thread[N];

  aIndex[0].low = pa->low;
  aIndex[0].high = mid;

  aIndex[1].low = mid+1;
  aIndex[1].high = pa->high;



  int i;

  for(i = 0; i < N; i++)
  pthread_create(&thread[i], NULL, mergesort, &aIndex[i]);    //creating a new thread with routine mergesort and only parameter as aIndex[i]

  for(i = 0; i < N; i++)
  pthread_join(thread[i], NULL);                              //ending the thread thread[i] with return status set to NULL

  merge(pa->low, pa->high);
  return 0;
}

int main(){
  Array ai;                                                   //creating element ai of struct arr type
  ai.low = 0;
  ai.high = sizeof(a)/sizeof(a[0])-1;                         //assigning last location of the array to ai.high
  pthread_t thread;                                           //making new thread with thread label

  pthread_create(&thread, NULL, mergesort, &ai);              //creating thread with routine mergesort and only parameter ai
  pthread_join(thread, NULL);                                 //ending the thread 'thread' and returni

  int i;
  for (i = 0; i < 10; i++)
  cout << " " << a[i];
  cout << endl;
  system("pause");
  return 0;
}