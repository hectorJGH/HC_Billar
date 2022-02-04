#include "billiard.h"
#include <iostream>
#include <cmath>
#include <vector>

void reflexiones(std::vector<double> & infovec, double & vxo,double & vyo,double & xo,double & yo,int & choques,double totaltime,double alpha){
  int simtime=0;
  double dt=0;
  double speed=std::sqrt(std::pow(vxo,2)+std::pow(vyo,2));
  infovec[0]=xo;
  infovec[1]=yo;
  infovec[2]=vxo;
  infovec[3]=vyo;
  infovec[4]=0;
  while(simtime<totaltime){
    choques+=1;
    if(vxo>0){
      if(line(xo,yo,vxo,vyo,1)<=alpha && line(xo,yo,vxo,vyo,1)>=0){//toca la pared recta derecha del estadio
	dt=delta(speed,xo,yo,1,line(xo,yo,vxo,vyo,1));
	simtime+=dt;
	xo=1;
	yo=line(xo,yo,vxo,vyo,1);
	vxo=-vxo;
	fillinfo(infovec,vxo,vyo,xo,yo,dt,choques);
      }
      else{//toca el semicirculo superior o inferior
	double xinicial=xo;//guardo las posiciones viejas
	double yinicial=yo;
	posiciones_choque(xo,yo,vxo,vyo,alpha);//actualiza xo y yo a las coordenadas del punto de choque
	dt=delta(speed,xinicial,yinicial,xo,yo);//calcula el nuevo delta t
	velocidad_reflejada(xo,yo,vxo,vyo,alpha);//actualiza las velocidad a la reflejada
	simtime+=dt;
	fillinfo(infovec,vxo,vyo,xo,yo,dt,choques);
      }

    }
    else{//vxo<0
      if((line(xo,yo,vxo,vyo,-1)<=alpha && line(xo,yo,vxo,vyo,-1)>=0)){//toca la pared recta izquierda del estadio
	dt=delta(speed,xo,yo,-1,line(xo,yo,vxo,vyo,-1));
	simtime+=dt;
	xo=-1;
	yo=line(xo,yo,vxo,vyo,-1);
	vxo=-vxo;
	fillinfo(infovec,vxo,vyo,xo,yo,dt,choques);
      }
      else{//toca el semicirculo inferior o superior
	double xinicial=xo;//guardo las posiciones viejas
	double yinicial=yo;
	posiciones_choque(xo,yo,vxo,vyo,alpha);//actualiza xo y yo a las coordenadas del punto de choque
	dt=delta(speed,xinicial,yinicial,xo,yo);//calcula el nuevo delta t
	velocidad_reflejada(xo,yo,vxo,vyo,alpha);//actualiza las velocidad a la reflejada
	simtime+=dt;
	fillinfo(infovec,vxo,vyo,xo,yo,dt,choques);
      }
    }
  }
}

void d_balls(std::vector<double> & m, std::vector<double> & n, std::vector<double> k, double time, double delta_t)
{
  double t=0.0;
  int ii = 0, jj = 0, kk = 0;
  while(t<time)
  {
    if(t < m[ii*5 + 4])
    {
      if(t < n[jj*5 + 4])
      {
        k[kk] = t;
        k[kk+1] = std::sqrt(std::pow(m[ii*5] - n[jj*5], 2) + std::pow(m[ii*5 + 4] - n[jj*5 + 1], 2));
      }
      else
      {
        ++jj;
        k[kk] = t;
        k[kk+1] = std::sqrt(std::pow(m[ii*5] - n[jj*5], 2) + std::pow(n[jj*5 + 1] - m[ii*5 + 4], 2));
      }
    }
    else
    {
      ++ii;
      if(t < n[jj*5 + 4])
      {
        k[kk] = t;
        k[kk+1] = std::sqrt(std::pow(m[ii*5] - n[jj*5], 2) + std::pow(m[ii*5 + 4] - n[jj*5 + 1], 2));
      }
      else
      {
        ++jj;
        k[kk] = t;
        k[kk+1] = std::sqrt(std::pow(m[ii*5] - n[jj*5], 2) + std::pow(m[ii*5 + 4] - n[jj*5 + 1], 2));
      }
    }
    kk+=2;
    t+=delta_t;
  }
}

void fillinfo(std::vector<double> & infovec, double vxo,double vyo,double xo,double yo,double dt,int choques){
        infovec.resize(5*(choques+1));
	infovec[5*(choques)]=xo;
	infovec[5*(choques)+1]=yo;
	infovec[5*(choques)+2]=vxo;
	infovec[5*(choques)+3]=vyo;
	infovec[5*(choques)+4]=infovec[5*choques-1]+dt;
}

void posiciones_choque(double & xo, double & yo, double vxo, double vyo, double alpha){
  double a=0;
  double m=vyo/vxo;
  double b=yo-m*xo;
  if(vxo>0){
    if(line(xo,yo,vxo,vyo,1)>alpha)a=alpha;
    double root= std::sqrt(std::pow(2*m*(b-a),2)-4*(1+std::pow(m,2))*(std::pow(b-a,2)-1));
    xo=(-m*(b-a)/((std::pow(m,2)+1)))+(root/(2*(std::pow(m,2)+1)));
  }
  else{
    if(line(xo,yo,vxo,vyo,-1)>alpha)a=alpha;
    double root= std::sqrt(std::pow(2*m*(b-a),2)-4*(1+std::pow(m,2))*(std::pow(b-a,2)-1));
    xo=(-m*(b-a)/((std::pow(m,2)+1)))-(root/(2*(std::pow(m,2)+1)));
  }
  yo=m*xo+b;
}

void velocidad_reflejada(double xo, double yo, double & vxo, double & vyo, double alpha){
  if(yo>alpha){//choca arriba
    double escalar=-2*((xo*vxo)+(circle(xo)*vyo));
    vxo+=xo*escalar;
    vyo+=circle(xo)*escalar;
  }
  else{ //choca abajo
    double escalar=2*((xo*vxo)-(circle(xo)*vyo));
    vxo-=xo*escalar;
    vyo+=circle(xo)*escalar;
  }
}

double line(double xo, double yo, double vxo, double vyo, double x){
  return (vyo/vxo)*(x-xo) +yo;
}

double delta(double speed, double xo, double yo, double x1, double y1){
  double l=std::sqrt(std::pow(x1-xo,2)+std::pow(y1-yo,2));
  return l/speed;
}

double circle(double x){
  return std::sqrt(1-std::pow(x,2));
}
