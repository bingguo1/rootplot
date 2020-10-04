#include <cmath>
#include <math.h>

float setdigi(float num, int n=2){
  if(num*pow(10.,n)==int(num*pow(10.,n)))
    return num;
  else 
    {
      int re=round(num*pow(10.,n));
      return re/pow(10.,n);
      
    } 
}

double setdigi(double num, int n=2){
  if(num*pow(10.,n)==int(num*pow(10.,n)))
    return num;
  else
    {
      int re=round(num*pow(10.,n));
      return re/pow(10.,n);
    }
}
