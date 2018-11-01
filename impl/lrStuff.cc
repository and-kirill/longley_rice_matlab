#include <math.h>
    
int mymin(const int &i, const int &j)
{ if(i<j)
    return i;
  else
    return j;
}

int mymax(const int &i, const int &j)
{ if(i>j)
    return i;
  else
    return j;
}

double mymin(const double &a, const double &b)
{ if(a<b)
    return a;
  else
    return b;
}

double mymax(const double &a, const double &b)
{ if(a>b)
    return a;
  else
    return b;
}

double FORTRAN_DIM(const double &x, const double &y)
{ // This performs the FORTRAN DIM function.
  // result is x-y if x is greater than y; otherwise result is 0.0
  if(x>y)
    return x-y;
  else
    return 0.0;
}

double qerfi( double q )
{ 
  double x, t, v;
  double c0  = 2.515516698;
  double c1  = 0.802853;
  double c2  = 0.010328;
  double d1  = 1.432788;
  double d2  = 0.189269;
  double d3  = 0.001308;

  x = 0.5 - q;
  t = mymax(0.5 - fabs(x), 0.000001);
  t = sqrt(-2.0 * log(t));
  v = t - ((c2 * t + c1) * t + c0) / (((d3 * t + d2) * t + d1) * t + 1.0);
  if (x < 0.0) v = -v;
  return v;
}

double deg2rad(double d)
{
  return d * 3.1415926535897 / 180.0;
}

double aknfe(const double &v2)
{
  double a;
  if(v2<5.76)
    a=6.02+9.11*sqrt(v2)-1.27*v2;
  else
    a=12.953+4.343*log(v2);
  return a;
}


