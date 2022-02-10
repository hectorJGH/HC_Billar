#include "billiard.h"
#include <iostream>
#include <cmath>
#include <vector>

//Cambia el infovec=[x,y,vx,vy,t] después de cada choque
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

//m y n son infovec's de la forma [x,y,vx,vy,t,...] que registran los choques. k=[t,d,...] registra el tiempo y la distancia para diferencias de tiempo delta_t
void d_balls(std::vector<double> & m, std::vector<double> & n, std::vector<double> & k, double time, double delta_t)
{
  double t=0.0;
  int ii = 0, jj = 0, kk = 0;
  double xm, ym, xn, yn;
  while(t<time)
  {
    while (t >= m[(ii+1)*5 + 4]) ii++;//El tiempo m[(ii+1)*5 + 4] la primera cota superior del tiempo t, de manera que en ii hay una cota inferior
    while (t >= n[(jj+1)*5 + 4]) jj++;//tjj < t < t(jj+1)
    xm = m[ii*5] + (t-m[ii*5 + 4]) *m[ii*5 + 2];
    ym = m[ii*5 + 1] + (t-m[ii*5 + 4]) *m[ii*5 + 3];
    xn = n[jj*5] + (t-n[jj*5 + 4]) *n[jj*5 + 2];
    yn = n[jj*5 + 1] + (t-n[jj*5 + 4]) *n[jj*5 + 3];
    //k.resize(2*(kk+1));
    k[kk*2 + 1] += std::sqrt(std::pow(xm - xn, 2) + std::pow(ym - yn, 2));
    k[kk*2] = t;
    kk+=1;
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

//Cambia las posiciones xo, yo a las del siguiente choque
void posiciones_choque(double & xo, double & yo, double vxo, double vyo, double alpha){
  double a=0;
  double m=vyo/vxo;
  double b=yo-m*xo;
  if(vxo>0){//Va hacia la derecha
    if(line(xo,yo,vxo,vyo,1)>alpha)a=alpha;//si choca con el arco (de circunferencia) superior derecho
    double root= std::sqrt(std::pow(2*m*(b-a),2)-4*(1+std::pow(m,2))*(std::pow(b-a,2)-1));//raiz del discriminante
    xo=(-m*(b-a)/((std::pow(m,2)+1)))+(root/(2*(std::pow(m,2)+1)));//solucion de la interseccion linea-circunferencia
  }
  else{//Va hacia la izquierda
    if(line(xo,yo,vxo,vyo,-1)>alpha)a=alpha;//si choca con el arco superior izquierdo
    double root= std::sqrt(std::pow(2*m*(b-a),2)-4*(1+std::pow(m,2))*(std::pow(b-a,2)-1));
    xo=(-m*(b-a)/((std::pow(m,2)+1)))-(root/(2*(std::pow(m,2)+1)));
  }
  yo=m*xo+b;
}

//cambia la velocidad para choque en las semicircunferencias, con vector normal unitario (x, +-circle(x))
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
void elipse_reflexiones(std::vector<double> & infovec, double & vxo,double & vyo,double & xo,double & yo,int & choques,double totaltime,double alpha){
  
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
    double xinicial=xo;//guardo las posiciones viejas
    double yinicial=yo;
    elipse_posiciones_choque(xo,yo,vxo,vyo,alpha);//actualiza a las coordenadas del punto de choque(tiene en cuenta el vx para el signo)
    dt=delta(speed,xinicial,yinicial,xo,yo);//calcula el nuevo delta t
    elipse_velocidad_reflejada(xo,yo,vxo,vyo,alpha);//actualiza las velocidad a la reflejada
    simtime+=dt;
    fillinfo(infovec,vxo,vyo,xo,yo,dt,choques);
  }
}
void elipse_posiciones_choque(double & xo, double & yo, double vxo, double vyo, double alpha){
  double m=vyo/vxo;
  double b=yo-m*xo;
    
    double root= std::sqrt(std::pow(2*m*(b/std::pow(alpha,2)),2)-4*(std::pow(b/alpha,2)-1)*(1+std::pow(m/alpha,2)));//raiz del discriminante
    if(if vx<0)root=-root;//si va a la izquierda, tome la solución mas pequeña
    xo=(-m*(b/std::(alpha,2))/((std::pow(m/alpha,2)+1)))+(root/(2*(std::pow(m/alpha,2)+1)));//posicion en x
  
  yo=m*xo+b;
}
void elipse_velocidad_reflejada(double xo, double yo, double & vxo, double & vyo, double alpha){
  double escalar=-2*((alpha*xo*vxo)+(yo*vyo/alpha))/(1+(std::pow(alpha,2)-1)*(std::pow(xo,2)));
  vxo+=alpa*xo*escalar;
  vyo+=yo**escalar/alpha;
}

//Posicion y de la colision para paredes verticales
double line(double xo, double yo, double vxo, double vyo, double x){
  return (vyo/vxo)*(x-xo) +yo;
}

//dt, tiempo entre 2 colisiones
double delta(double speed, double xo, double yo, double x1, double y1){
  double l=std::sqrt(std::pow(x1-xo,2)+std::pow(y1-yo,2));
  return l/speed;
}

//Función y=c(x) de la semicircunferencia unitario superior
double circle(double x){
  return std::sqrt(1-std::pow(x,2));
}
