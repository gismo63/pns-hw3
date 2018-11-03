class Grid{
  private:
     Vec phi;
     Vec fixed_vals;
     double omega;
     int n;
     int n_x;
     int n_y;
   public:
     Grid(double,int,int,int,const Vec&,const Vec&);
     void sweep();
     double gauss_seidel(int);
     Vec return_phi();


};

Grid::Grid(double omega_,int n_,int n_x_, int n_y_, const Vec& phi_i, const Vec& fixed_) {
  omega = omega_;
  n = n_;
  n_x = n_x_;
  n_y  = n_y_;
  int l = phi_i.size();
  int m = fixed_.size();
  phi.reserve(l);
  phi.insert(phi.end(),phi_i.begin(),phi_i.end());
  fixed_vals.reserve(m);
  fixed_vals.insert(fixed_vals.end(),fixed_.begin(),fixed_.end());
}

void Grid::sweep(){
  for(int i = 1;i<n_x;i++){
    for(int j = 1;j<n_y;j++){
      if(!std::binary_search(fixed_vals.begin(),fixed_vals.end(),(i*(n_x+1)+j))){
        phi[i*(n_x+1)+j] = gauss_seidel(i*(n_x+1)+j);
      }
    }
  }
}

double Grid::gauss_seidel(int i){
  double new_val = (omega/4)*(phi[i-1]+phi[i+1]+phi[i-(n_x+1)]+phi[i+(n_x+1)])+(1-omega)*phi[i];
  return new_val;
}

Vec Grid::return_phi(){
  return phi;
}
