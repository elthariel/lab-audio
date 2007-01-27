

#ifndef CROSS_CV_H
# define CROSS_CV_H

# include <iostream>

using namespace std;

/*
 * Ask me sur msn sur comment ca marche, tu te demerde pour l'add a
 * ton truc
 */

struct point
{
  double        x;
  double        y;

  inline point():x(0.0), y(0.0){}
  inline point(double a_x, double a_y):x(a_x), y(a_y){}

  inline point operator+(point p) { return point(x + p.x, y + p.y); }

  inline point operator*(double factor) { return point(x * factor, y * factor); }

  inline point &operator=(point p) { x = p.x; y = p.y; return *this; }
};

struct crossdata
{
  crossdata(unsigned int a_step)
    :p0(0.0, 1.0), p2(1.0, 0.0), p1(0.5, 0.5), step(a_step)
    //// !! Do not touch to p1.x !! ////
  {
    data = new double[step];
    compute();
  }
  ~crossdata(){ delete data; }

  inline const double &operator[](unsigned int i)const { return data[i]; }
  inline void          set_curve(double y)
  { p1.y = y; compute(); }

protected:
  point         p0, p1, p2, tmp;
  unsigned int  step;
  double        *data;

  void          compute()
  {
    unsigned int i;
    double      t;

    for (i = 0; i < step; i++)
      {
        t = 1.0 / step * i;
        tmp = p0 * (1 - t) *(1 - t) +
          p1 * 2 * t * (1 - t)+
          p2 * t * t;
        data[i] = tmp.y;
        //cout << i <<": X : " << tmp.x << "\t\t Y : \t" << tmp.y << endl;
      }
  }
};


#endif
