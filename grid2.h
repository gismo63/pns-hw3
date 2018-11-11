class Grid{
  private:
     Vec phi;
     Vec phi_0;
     Vec fixed_vals;
     double omega;
     int n;
     int n_x;
     int n_y;
   public:
     Grid(double,int,int,int,const Vec&,const Vec&);
     double sweep();
     void solve();
     double gauss_seidel(int);
     double x_slope(double, double);
     /*
     void set_omega(double);
     void reset_phi();
     */
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
  phi_0.reserve(l);
  phi_0.insert(phi_0.end(),phi_i.begin(),phi_i.end());
}

double Grid::sweep(){
  double diff = 0;
  double old;
  for(int i = 0;i<(n_x+1);i++){
    for(int j = 0;j<(n_y+1);j++){
      if(j==0){
        phi[i*(n_x+1)+j] = (4*phi[i*(n_x+1)+j+1]-phi[i*(n_x+1)+j+2])/3;
      }
      else if(j==n_x){
        phi[i*(n_x+1)+j] = (4*phi[i*(n_x+1)+j-1]-phi[i*(n_x+1)+j-2])/3;
      }
      else if(i==0){
        phi[i*(n_x+1)+j] = (4*phi[(i+1)*(n_x+1)+j]-phi[(i+2)*(n_x+1)+j])/3;
      }
      else if(i==n_y){
        phi[i*(n_x+1)+j] = (4*phi[(i-1)*(n_x+1)+j]-phi[(i-2)*(n_x+1)+j])/3;
      }
      else{
        if(!std::binary_search(fixed_vals.begin(),fixed_vals.end(),(i*(n_x+1)+j))){
          old = phi[i*(n_x+1)+j];
          phi[i*(n_x+1)+j] = gauss_seidel(i*(n_x+1)+j);
          diff += fabs(old-phi[i*(n_x+1)+j]);
        }
      }
    }
  }
  return diff;
}

void Grid::solve(){
  double diff = 1;
  while (diff>(0.000000001*(n_x*n_x))){
    diff = sweep();
  }
}

double Grid::gauss_seidel(int i){
  double new_val = (omega/4)*(phi[i-1]+phi[i+1]+phi[i-(n_x+1)]+phi[i+(n_x+1)])+(1-omega)*phi[i];
  return new_val;
}

double Grid::x_slope(double x, double y){
  int x_ind = x*n_x;
  int y_ind = y*n_x;
  double s_l = (phi[y_ind*(n_x+1)+x_ind]-phi[y_ind*(n_x+1)+x_ind-1])*n_x;
  double s_r = (phi[y_ind*(n_x+1)+x_ind+1]-phi[y_ind*(n_x+1)+x_ind])*n_x;
  return (s_l+s_r)/2;

}
/*
void Grid::set_omega(double omega_new){
  omega = omega_new;
}

void Grid::reset_phi(){
  phi = phi_0;
}
*/
Vec Grid::return_phi(){
  return phi;
}
