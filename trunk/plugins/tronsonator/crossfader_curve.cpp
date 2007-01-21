
#include <iostream>

using namespace std;

/*
 * Ask me sur msn sur comment ca marche, tu te demerde pour l'add a ton truc
 */

struct point
{
  double        x;
  double        y;

  point():x(0.0), y(0.0){}
  point(double a_x, double a_y):x(a_x), y(a_y){}

  point         operator+(point p)
  {
    point       np;

    np.x = x + p.x;
    np.y = y + p.y;
    return np;
  }

  point         operator*(double factor)
  {
    point       np;

    np.x = x * factor;
    np.y = y * factor;
    return np;
  }

  point         &operator=(point p)
  { x = p.x; y = p.y; return *this; }
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

  void          set_curve(double y)
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
  const double &operator[](unsigned int i) { return data[i]; }
};
