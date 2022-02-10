#include "billiard.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string.h>
#include <fstream>

int main(int argc, char *argv[]){

  
  double alpha = std::atof(argv[1]);
  double totaltime= 70.0;
  double delta=0.1;

  //double speed = 0.0;
  double x=-1.0E-5, y=0.0, vx=0.6, vy=0.6;

  std::vector<double> infovec1{0}, infovec2{0}, separvec{0};
  infovec1.resize(5);
  infovec2.resize(5);
  
  
  
  int separsize;
  separsize = totaltime/delta;
  separvec.resize(2*separsize);

  int choques=0;
  elipse_reflexiones(infovec1,vx,vy,x,y,choques,totaltime,alpha);
  
  int Nb = 10;
  for (int ii = 0; ii<Nb; ii++) {
      x = (ii+1)*1E-5;
      y = 0.0;
      vx = 0.6;
      vy = 0.6;
      choques = 0;
      elipse_reflexiones(infovec2,vx,vy,x,y,choques,totaltime,alpha);
      d_balls(infovec1, infovec2, separvec, totaltime, 0.1);
  }
  for (int ii = 0; ii< separsize; ii++) separvec[2*ii + 1] /= Nb;

  //for (int ii = 0; ii< separsize; ii++) std::cout<<separvec[ii*2]<<"\t"<<separvec[ii*2 +1]<<"\n";

  int beta=alpha*100;
  std::string elipse="elipse";
  std::string tipo=".txt";
  std::string nombre=std::to_string(beta);
  nombre=elipse+nombre+tipo;
  std::ofstream MyFile(nombre.c_str());
  // Write to the file
  for (int ii = 0; ii< separsize; ii++) MyFile << separvec[ii*2]<<"\t"<<separvec[ii*2 +1]<<"\n";
  // Close the file
  MyFile.close();

  return 0;

}
