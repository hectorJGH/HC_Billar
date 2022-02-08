#include "billiard.h"
#include <iostream>
#include <cmath>
#include <vector>

int main(int argc, char *argv[]){

  
  double alpha = std::atof(argv[1]);
  double totaltime= 30.0;
  
  //double speed = 0.0;
  double x=0, y=0.0E-5, vx=0.6, vy=0.6;

  std::vector<double> infovec1{0}, infovec2{0}, separvec{0};
  infovec1.resize(5);
  infovec2.resize(5);
  
  
  double delta=0.01;
  int separsize;
  separsize = totaltime/delta;
  separvec.resize(2*separsize);

  int choques=0;
  reflexiones(infovec1,vx,vy,x,y,choques,totaltime,alpha);
  
  int Nb = 10;
  for (int ii = 0; ii<Nb; ii++) {
      x = (ii+1)*1E-5;
      y = 0.0;
      vx = 0.6;
      vy = 0.6;
      choques = 0;
      reflexiones(infovec2,vx,vy,x,y,choques,totaltime,alpha);
      d_balls(infovec1, infovec2, separvec, totaltime, 0.1);
  }
  for (int ii = 0; ii< separsize; ii++) separvec[2*ii + 1] /= Nb;

  for (int ii = 0; ii< separsize; ii++) std::cout<<separvec[ii*2]<<"\t"<<separvec[ii*2 +1]<<"\n";


  return 0;

}