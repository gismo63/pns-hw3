#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
  int n_x = 10*5;
  int n_y = n_x;
  int n = (n_x+1)*(n_y+1);
  double omega = 2/(1+M_PI/n_x);
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
  grid.solve();
  phi = grid.return_phi();
  for(int i = 0;i<(n_y+1);i++){
    for(int j = 0;j<(n_x+1);j++){
      cout << double(j)/n_x << ' ' << double(i)/n_y << ' ' << phi[i*(n_x+1)+j] << "\n";
    }
  }

  return 0;
}
