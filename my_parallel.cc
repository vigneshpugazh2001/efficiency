//
// File: boost_version.cc
// Author: David W. Juedes
// Purpose: Computes the last six digits of the
// sum from 1 to n (given as input) of i^i
// Uses the boost multiprecision library
// This is a "reference" implementation to test whether you are getting the
// right answer.   But, this implementation is SLOW!!!!  (
//

#include <iostream>
#include <iomanip>
#include <set>
#include <cmath>
#include <omp.h>
//#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
//using namespace boost::multiprecision;

//
// Computes a^n using multiprecision integers (cpp_int).
// Not very efficient

//  int power(int a, int n) {
//    long long int p = 1;

//   #pragma omp critical
//    for (int i=1;i<=n;i++) {
//      p*=a;
//      p = p%1000000;
//    }
//    return p % 1000000;
//  }

int power(long long int a, long long int n){

  if(n == 0){
    return 1;
  }
  if(a == 0){
    return 0;
  }
  a = a*power(a, n - 1);
  a = a%1000000;
  return a;
}



int main() {
  long long int n;
  cin >> n;
  long long int sum = 0;

  #pragma omp parallel for \
    reduction(+:sum) schedule(runtime)
  for (int i=1;i<=n;i++) {
    sum+=power(i,i) % 1000000;
  }
  // cout << " n = " << n << endl;
  // cout << sum << endl;
  // Prints leading 0's
  cout << setw(6) << setfill('0') << sum%1000000 << endl;
}
