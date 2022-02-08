#ifndef BILLIARD_H
#define BILLIARD_H

#include <iostream>
#include <cmath>
#include <vector>

double circle(double x);
double line(double xo, double yo, double vxo, double vyo, double x);
double delta(double speed,double xo, double yo, double x1, double y1);


void reflexiones(std::vector<double> & infovec, double & vxo,double & vyo,double & xo,double & yo,int & choques,double totaltime,double alpha);
void posiciones_choque(double & xo, double & yo, double vxo, double vyo, double alpha);
void velocidad_reflejada(double xo, double yo, double & vxo, double & vyo, double alpha);
void fillinfo(std::vector<double> & infovec, double vxo,double vyo,double xo,double yo,double dt,int choques);
void d_balls(std::vector<double> & m, std::vector<double> & n, std::vector<double> & k, double time, double delta_t);

#endif
