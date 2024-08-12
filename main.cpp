#include <iostream>
#include "black_scholes.h"
#include "binomial.h"

int main()
{
    double S = 100;      // spot
    double K = 95;      // strike
    double t = 1;        // time to maturity (years)
    double r = 0.1;      // risk-free interest rate
    double q = 0.06;        // dividend yield
    double sigma = 0.25; // volatility

    Euro_call call(S, K, r, q, sigma, t);
    Euro_put put(S, K, r, q, sigma, t);
    call.print();

    std::cout << std::endl;
    put.print();
    std::cout << std::endl;

    Euro_call_bin call_bin(S, K, r, q, sigma, t, 100);
    call_bin.print();
    Euro_put_bin put_bin(S, K, r, q, sigma, t, 100);
    put_bin.print();
    std::cout << std::endl;

    American_call a_call(S, K, r, q, sigma, t, 100);
    a_call.print();
    American_put a_put(S, K, r, q, sigma, t, 100);
    a_put.print();
    American_future_call a_fut(S, K, r, q, sigma, t, 100);
    a_fut.print();
    American_future_put a_fup(S, K, r, q, sigma, t, 100);
    a_fup.print();
    std::cout << std::endl;
    Euro_future_call fut(S, K, r, q, sigma, t);
    fut.print();
    Euro_future_put fup(S, K, r, q, sigma, t);
    fup.print();

    return 0;
}
