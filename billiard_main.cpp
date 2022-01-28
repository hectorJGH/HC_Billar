#include "billiard.h"
#include <iostream>
#include <cmath>
#include <vector>

int main(int argc, char *argv[]){

  double xo=std::atof(argv[1]);//std::atoi(argv[1]);
    double yo=std::atof(argv[2]);//std::atoi(argv[2]);
  double vxo= std::atof(argv[3]);//std::atoi(argv[3]); //Tengo problemas cuendo meto decimales al atoi
    double vyo=std::atof(argv[4]);//std::atoi(argv[4]);
  double alpha=std::atof(argv[5]);//std::atoi(argv[5]);
  double totaltime= std::atof(argv[6]);//std::atoi(argv[6]);

  std::vector<double> infovec{0};
  infovec.resize(5);
  int choques=0;
  reflexiones(infovec,vxo,vyo,xo,yo,choques,totaltime,alpha);

  for(int ii=0;ii<=choques;++ii){
    std::cout<<infovec[5*ii]<<"\t"<<infovec[5*ii+1]<<"\t"<<infovec[5*ii+2]<<"\t"<<infovec[5*ii+3]<<"\t"<<infovec[5*ii+4]<<"\n";
  }

  return 0;

}
