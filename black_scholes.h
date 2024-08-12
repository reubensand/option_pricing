#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include <cmath>
#include <iostream>
#include "math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 0.7071067811865476
#endif

class BlackScholes
{
protected:
    double S, K, r, q, sigma;
    double t;

    /*
        S - underlying price per share
        K - strike price
        sigma - volatility
        r - continuously compounded risk-free interest rate
        q - continuously compounded dividend yield
        t - time to expiration (years)
    */

public:
    // Constructor initalizes member variables
    BlackScholes(double S, double K, double r, double q, double sigma, double t) : S(S), K(K), r(r), q(q), sigma(sigma), t(t) {}

    // In case destructor is necessary
    virtual ~BlackScholes();

    // Cumulative distribution function
    double norm_cdf(const double &x) const;

    // probability density function
    double norm_pdf(const double &x) const;

    // Set methods for member variables
    virtual void set_S(const double &S) { this->S = S; }
    virtual void set_K(const double &K) { this->K = K; }
    virtual void set_r(const double &r) { this->r = r; }
    virtual void set_q(const double &q) { this->q = q; }
    virtual void set_sigma(const double &sigma) { this->sigma = sigma; }
    virtual void set_t(const double &t) { this->t = t; }

    /*      Pure Virtual        */

    // Function to print outputs of member functions
    virtual void print() = 0;

    // Option price and greek calculation functions
    virtual double option_price() const = 0;
    virtual double calc_delta() const = 0;
    virtual double calc_gamma() const = 0;
    virtual double calc_vega() const = 0;
    virtual double calc_theta() const = 0;
    virtual double calc_rho() const = 0;
};

class Euro_call : public BlackScholes
{

public:
    // Constructor and Destructor
    Euro_call(double S, double K, double r, double q, double sigma, double t) : BlackScholes(S, K, r, q, sigma, t) {};
    ~Euro_call();

    // Prints the option price of a Europeans Call
    void print();

    // Option price and greek calculation functions
    double option_price() const override;
    double calc_delta() const override;
    double calc_gamma() const override;
    double calc_vega() const override;
    double calc_theta() const override;
    double calc_rho() const override;
};

class Euro_put : public BlackScholes
{

public:
    // Constructor and Destructor
    Euro_put(double S, double K, double r, double q, double sigma, double t) : BlackScholes(S, K, r, q, sigma, t) {}
    ~Euro_put();

    // Prints the option price of a Europeans Put
    void print();

    // Option price and greek calculation functions
    double option_price() const override;
    double calc_delta() const override;
    double calc_gamma() const override;
    double calc_vega() const override;
    double calc_theta() const override;
    double calc_rho() const override;
};

class Euro_future_call : public BlackScholes
{

public:
    Euro_future_call(double S, double K, double r, double q, double sigma, double t) : BlackScholes(S, K, r, q, sigma, t) {}
    ~Euro_future_call();

    // Prints the option price of a European call on a future
    void print();

    // Calculate call price
    double option_price() const override;

    // Greek calculation weren't gonna provide too much value
    double calc_delta() const override;
    double calc_gamma() const override;
    double calc_vega() const override;
    double calc_theta() const override;
    double calc_rho() const override;
};

class Euro_future_put : public BlackScholes
{

public:
    Euro_future_put(double S, double K, double r, double q, double sigma, double t) : BlackScholes(S, K, r, q, sigma, t) {}
    ~Euro_future_put();

    // Prints the option price of a European put on a futures
    void print();

    // Calculate put price
    double option_price() const override;

    // Greek calculation weren't gonna provide too much value
    double calc_delta() const override;
    double calc_gamma() const override;
    double calc_vega() const override;
    double calc_theta() const override;
    double calc_rho() const override;
};
#endif