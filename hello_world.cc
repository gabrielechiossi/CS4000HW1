/**
 *   @file: hello_world.cc
 * @author: Gabriele Chiossi
 *   @date: 02/07/21
 */
#include<iostream>
#include "omp.h"

using namespace std;

//prints out the threads in parallel
void Hello() {
  #pragma omp critical
  {
    cout << "Greetings from Thread " << omp_get_thread_num() << endl;
    cout << "There are " << omp_get_num_threads() << " threads " << endl;
  }
}
//main function
int main() {
  #pragma omp parallel //the problem was on this line, you have to insert #pragma omp parallel
                      //and before there just was #pragma parallel
                      //to find this I used -Wall that told me right away where the problem was
  Hello();
}
