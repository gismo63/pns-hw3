#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

typedef std::vector<double> Vec;
using std::cout;

#include "grid.h"

Vec line_B(int n_x){
  Vec B;
  int k = n_x/5;
  for(int i=0;i<(k*3);i++){
    B.push_back((i+k)*(n_x+1)+(4*k));
  }
  for(int i=0;i<(k*3+1);i++){
    B.push_back((4*k)*(n_x+1)+i+k);
  }
  return B;
}

Vec line_A(int n_x){
  Vec A;
  int k = n_x/5;
  for(int i =0;i<(k*2+1);i++){
    A.push_back(k*(n_x+1)+i+k);
  }
  return A;
}

int main(int argc, char const *argv[]) {
  int n_x = 10*4;
  int n_y = n_x;
  int n = (n_x+1)*(n_y+1);
  double omega = 1;
  Vec phi(n,0.0);
  Vec B = line_B(n_x);
  Vec A = line_A(n_x);
  int m = A.size();
  int l = B.size();
  for(int i = 0;i<m;i++){
    phi[A[i]] = 1;
  }
  for(int i = 0;i<l;i++){
    phi[B[i]] = -1;
  }
  Vec fixed;
  fixed.reserve(m+l);
  fixed.insert(fixed.end(),A.begin(),A.end());
  fixed.insert(fixed.end(),B.begin(),B.end());
  Grid grid(omega, n, n_x, n_y, phi, fixed);

  std::clock_t start;
  Vec omega_arr;
  for(int i = 0; i<10; i++){
    omega_arr.push_back((i+1)*0.1);
  }
  for(int i = 0; i<99; i++){
    omega_arr.push_back(1+(i+1)*0.01);
  }
  int n_w = omega_arr.size();
  for(int i = 0;i<n_w;i++){
    grid = Grid(omega_arr[i], n, n_x, n_y, phi, fixed);
    start = std::clock();
    grid.solve();
    cout << omega_arr[i] << ' ' << (std::clock() - start) / double(CLOCKS_PER_SEC) << '\n';
  }

  return 0;
}
