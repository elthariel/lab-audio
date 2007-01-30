

#ifndef CROSS_CV_H
# define CROSS_CV_H

# include <iostream>


/*
 * Ask me sur msn sur comment ca marche, tu te demerde pour l'add a
 * ton truc
 */

class Point
{
public:
	friend class CurveData;
  inline Point():x(0.0), y(0.0){}
  inline Point(const double a_x, const double a_y):x(a_x), y(a_y){}

  inline Point operator+(const Point& p)const { return Point(x + p.x, y + p.y); }

  inline Point operator*(const double factor)const { return Point(x * factor, y * factor); }

  inline Point &operator=(const Point& p) { x = p.x; y = p.y; return *this; }

protected:
  double        x;
  double        y;
};

/*** array storing a curve
 *   to access the curve use the array operator []
 */
class CurveData
{
public:
  CurveData(const unsigned int a_step)
    :p0(0.0, 1.0), p2(1.0, 0.0), p1(0.5, 0.7), step(a_step)
    //// !! Do not touch to p1.x !! ////
  {
    data = new double[step];
    compute();
  }
  ~CurveData() { delete data; }

  inline const double operator[](const unsigned int i)const {
    return (data[i] > 1.0 ? 1.0 : data[i]); }

  inline void set_curve(const double y) { p1.y = y; compute(); }

protected:
  Point         p0, p1, p2, tmp;
  unsigned int  step;
  double        *data;

  void          compute()
  {
    unsigned int i;
    double      t;

    for (i = 0; i < step; i++)
      {
        t = (1.0 / step) * i;
        tmp = p0 * (1 - t) *(1 - t) +
          p1 * 2 * t * (1 - t) +
          p2 * t * t;
        data[i] = tmp.y;
        //std::cout << i <<": X : " << tmp.x << "\t\t Y : \t" << tmp.y << std::endl;
      }
  }
};


#endif
