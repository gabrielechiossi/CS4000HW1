#include<iostream>
#include "omp.h"

using namespace std;


void Hello() {
  #pragma omp critical
  {
    cout << "Greetings from Thread " << omp_get_thread_num() << endl;
    cout << "There are " << omp_get_num_threads() << " threads " << endl;
  }
}
int main() {
  #pragma parallel
  Hello();
}
