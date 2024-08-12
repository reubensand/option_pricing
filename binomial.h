#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

class Binomial
{

protected:
    double S, K, r, q, sigma, t;
    int steps;

    /*
        S - underlying price per share
        K - strike price
        r - continuously compounded risk-free interest rate
        q - continuously compounded dividend yield
        sigma - volatility
        t - time to expiration (years)
        steps - number of iterations
    */

public:
    // Constructor initalizes member variables
    Binomial(double S, double K, double r, double q, double sigma, double t, int steps) : S(S), K(K), r(r), q(q), sigma(sigma), t(t), steps(steps) {}
    // destructor if necessary
    virtual ~Binomial();

    // Set methods for member variables
    virtual void set_S(const double &S) { this->S = S; }
    virtual void set_K(const double &K) { this->K = K; }
    virtual void set_r(const double &r) { this->r = r; }
    virtual void set_sigma(const double &sigma) { this->sigma = sigma; }
    virtual void set_t(const double &t) { this->t = t; }
    virtual void set_steps(const int &steps) { this->steps = steps; }

    // Function to print outputs of member functions
    virtual void print() = 0;

    // Option price function (greek could be implemented in the same function to save calculations)
    // or vectors would need to be member variables and changed accordingly
    virtual double option_price() const = 0;
};

class Euro_call_bin : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    Euro_call_bin(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~Euro_call_bin();

    // Prints the option price of a European call
    void print();

    // redefining the option price
    double option_price() const override;
};

class Euro_put_bin : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    Euro_put_bin(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~Euro_put_bin();

    // Prints the option price of a European put
    void print();

    // redefining the option price
    double option_price() const override;
};

class American_call : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    American_call(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~American_call();

    // Prints the option price of an American call
    void print();

    // redefining the option price
    double option_price() const override;
};

class American_put : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    American_put(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~American_put();

    // Prints the option price of an American put
    void print();

    // redefining the option price
    double option_price() const override;
};

class American_future_call : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    American_future_call(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~American_future_call();

    // Prints the option price of an American call on a future
    void print();

    // redefining the option price
    double option_price() const override;
};

class American_future_put : public Binomial
{

public:
    // Constructor utilizes base class to initiate variables
    American_future_put(double S, double K, double r, double q, double sigma, double t, int steps) : Binomial(S, K, r, q, sigma, t, steps) {}
    ~American_future_put();

    // Prints the option price of an American put on a future
    void print();

    // redefining the option price
    double option_price() const override;
};