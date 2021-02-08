#include <iostream>
#include <utility>
#include "omp.h"

using namespace std;

//
// Check to see if a number is prime.
//
bool is_prime(long long x) {
  if (x<2) return false;
  long long t=2;
  while (t*t <= x) {
    if (x%t == 0) {
      return false;
    }
    t++;
  }
  return true;
}

// Count the number of primes between a and b, inclusive

long long count_primes(long long a, long long b) {
  long long temp1;
  #pragma omp parallel private(temp1)
  temp1 = omp_get_thread_num();
  long long temp2 = omp_get_num_threads();
  long long n = b - a;
  long  long limit;
  if((temp1 + 1) == temp2){
    limit = n;
  }else{
    limit = (n/temp2) * (temp1+1);
  }
  long long sum=0;
  std::pair<long long, long long> debug_info[temp2];
  limit += a;
  #pragma omp parallel for reduction (+:sum)
  for (long long i = ((n/temp2)*temp1) + a ; i <= limit ; i++) {
    debug_info[temp1] = std::make_pair((n/temp2)*temp1, limit);
    if (is_prime(i)) sum++;
  }
  for(long long i = 0; i < temp2; i++){
    cout << debug_info[i].first << ", " << debug_info[i].second << '\n';
  }
 
  return sum;
}

int main() {
  long long a;
  long long b;

  cout << "Enter two large integers " << endl;
  cin >> a;
  cin >> b;

  cout << a << " Start " << endl;
  cout << b << " End " << endl;
  long long total = 0;
  //#pragma omp parallel reduction (+:total)
  total = count_primes(a,b);
  
  cout << "Number of prime numbers between " << a << " and " << b << " = " << total << endl;
}
