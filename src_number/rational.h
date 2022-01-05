#ifndef DEFINE_RATIONAL_H
#define DEFINE_RATIONAL_H



/*
  A rational class supposed to build integers.
  
 */
template<typename Tint>
struct Rational {
private:
  Tint num;
  Tint den;
public:
  Rational() : num(0), den(1) {
  }
  Rational(Tint const& x) : num(x), den(1) {
  }
  Rational(int const& x) : num(x), den(1) {
  }
  Rational(Rational<Tint> const& x) : num(x.num), den(x.den) {
  }
  Rational<Tint> operator=(int const& u) { // assignment operator from int
    Rational<Tint> x;
    x.num = u;
    x.den = 1;
    return x;
  }
  Rational<Tint> operator=(Rational<Tint> const& x) { // assignment operator
    Rational<Tint> y;
    y.num = x.num;
    y.den = x.den;
    return y;
  }
private: // A few internal functions.
  Tint comp_gcd(Tint const& m, Tint const& n) {
    Tint f = m;
    if (m < 0) f = -m;
    Tint g = n;
    if (n < 0) g = -n;
    Tint h;
    while (g != 0) {
      h = g;
      g = f % g;
      f = h;
    }
    return f;
  }
  void gcd_reduction() {
    Tint gcd = comp_gcd(num,den);
    num = num / gcd;
    den = den / gcd;
  }
  void operator+=(Rational<Tint> const&x) {
    Tint gcd = comp_gcd(den, x.den);
    Tint new_den = den * x.den / gcd;
    num = num * (x.den / gcd) + x.num * (den/gcd);
    den = new_den;
    gcd_reduction(); // Yes, it is needed: example 1/2 + 1/2
  }
  void operator-=(Rational<Tint> const&x) {
    Tint gcd = comp_gcd(den, x.den);
    Tint new_den = den * x.den / gcd;
    num = num * (x.den / gcd) - x.num * (den/gcd);
    den = new_den;
    gcd_reduction(); // Yes, it is needed: example 1/2 - 1/2
  }
  friend Rational<Tint> operator+(Rational<Tint> const&x, Rational<Tint> const&y) {
    Rational<Tint> z;
    Tint gcd = comp_gcd(den, x.den);
    z.den = y.den * x.den / gcd;
    z.num = y.num * (x.den / gcd) + x.num * (y.den/gcd);
    gcd_reduction();
    return z;
  }
  friend Rational<Tint> operator-(Rational<Tint> const&x, Rational<Tint> const&y) {
    Tint gcd = comp_gcd(den, x.den);
    z.den = x.den * y.den / gcd;
    z.num = x.num * (y.den / gcd) - y.num * (x.den/gcd);
    gcd_reduction();
    return z;
  }
  friend Rational<Tint> operator/(int const&x, Rational<Tint> const&y) {
    Rational<Tint> z;
    if (y.num > 0) {
      z.num = x * y.den;
      z.den = y.num;
    } else {
      z.num = -x * y.den;
      z.den = -y.num;
    }
    gcd_reduction();
    return z;
  }
  friend Rational<Tint> operator/(Rational<Tint> const&x, Rational<Tint> const&y) {
    Rational<Tint> z;
    if (y.num > 0) {
      z.num = x.num * y.den;
      z.den = x.den * y.num;
    } else {
      z.num = -x.num * y.den;
      z.den = -x.den * y.num;
    }
    gcd_reduction();
    return z;
  }
  void operator*=(Rational<Tint> const& x) {
    num = num * x.num;
    den = den * x.den;
    gcd_reduction();
  }
  friend QuadField<T,d> operator*(QuadField<T,d> const&x, QuadField<T,d> const&y) {
    Rational<Tint> z;
    z.num = x.num * y.num;
    z.den = x.den * y.den;
    gcd_reduction();
    return z;
  }
  friend Rational<Tint> operator*(int const&x, Rational<Tint> const&y) {
    Rational<Tint> z;
    z.num = x * y.num;
    z.den = y.den;
    gcd_reduction();
    return z;
  }
  friend std::ostream& operator<<(std::ostream& os, Rational<Tint> const &v) {
    if (v.den == 1)
      return os << v.num;
    else
      return os << v.num << "/" << v.den;
  }
  friend std::istream& operator>>(std::istream &is, QuadField<T,d> &v) {
    XXXXX
    return is;
  }





};
