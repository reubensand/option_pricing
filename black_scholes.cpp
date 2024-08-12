#include "black_scholes.h"


/*          Base Class          */

// destructor if necessary
BlackScholes::~BlackScholes() {}

double BlackScholes::norm_cdf(const double &x) const
{
    // uses the relation of erfc(x) = 1-erf(x) 
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

double BlackScholes::norm_pdf(const double &x) const
{
    // approximation of pdf
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}

/*          Derived Class : European Calls          */

// Derived Class destructor (define if necessary)
Euro_call::~Euro_call() {}

void Euro_call::print()
{
    std::cout << "BS Call price: " << Euro_call::option_price() << std::endl;
    std::cout << "Delta: " << Euro_call::calc_delta() << std::endl;
    std::cout << "Gamma: " << Euro_call::calc_gamma() << std::endl;
    std::cout << "Theta: " << Euro_call::calc_theta() << std::endl;
    std::cout << "Vega: " << Euro_call::calc_vega() << std::endl;
    std::cout << "Rho: " << Euro_call::calc_rho() << std::endl;
}

double Euro_call::option_price() const
{
    // standard BS call formula
    double d1 = (std::log(S / K) + (r - q + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);

    return S * std::exp(-q * t) * norm_cdf(d1) - K * std::exp(-r * t) * norm_cdf(d2);
}

double Euro_call::calc_delta() const
{
    // change in option price / change in underlying price
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    return std::exp(-q * t) * norm_cdf(d1);
}

double Euro_call::calc_gamma() const
{
    // change in delta / change in underlying price
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double constant = std::exp(-q * t) / (S * sigma * std::sqrt(t));
    return constant * norm_pdf(d1);
}

double Euro_call::calc_vega() const
{
    // change in option price / 1% change in volatility
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    return S * std::exp(-q * t) * std::sqrt(t) * norm_pdf(d1);
}

double Euro_call::calc_theta() const
{
    // change in option price / change in time
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    double part1 = (S * sigma * std::exp(-q * t) * norm_pdf(d1)) / (2 * std::sqrt(t));
    double part2 = r * K * std::exp(-r * t) * norm_cdf(d2);
    double part3 = q * S * std::exp(-q * t) * norm_cdf(d1);
    return (-part1 - part2 + part3);
}

double Euro_call::calc_rho() const
{
    // change in option price / 1% change in risk-free interest
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    return K * t * std::exp(-r * t) * norm_cdf(d2);
}

/*          Derived Class : European Put            */

// define if necessary
Euro_put::~Euro_put() {}

void Euro_put::print()
{
    std::cout << "BS Put price: " << Euro_put::option_price() << std::endl;
    std::cout << "Delta: " << Euro_put::calc_delta() << std::endl;
    std::cout << "Gamma: " << Euro_put::calc_gamma() << std::endl;
    std::cout << "Theta: " << Euro_put::calc_theta() << std::endl;
    std::cout << "Vega: " << Euro_put::calc_vega() << std::endl;
    std::cout << "Rho: " << Euro_put::calc_rho() << std::endl;
}

double Euro_put::option_price() const
{
    // standard BS call formula
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    return K * std::exp(-r * t) * norm_cdf(-d2) - S * std::exp(-q * t) * norm_cdf(-d1);
}

double Euro_put::calc_delta() const
{
    // change in option price / change in underlying price
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    return std::exp(-q * t) * (norm_cdf(d1) - 1);
}

double Euro_put::calc_gamma() const
{
    // change in delta / change in underlying price
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double constant = std::exp(-q * t) / (S * sigma * std::sqrt(t));
    return constant * norm_pdf(d1);
}

double Euro_put::calc_vega() const
{
    // change in option price / 1% change in volatility
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    return S * std::exp(-q * t) * std::sqrt(t) * norm_pdf(d1);
}

double Euro_put::calc_theta() const
{
    // change in option price / change in time
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    double part1 = (S * sigma * std::exp(-q * t) * norm_pdf(d1)) / (2 * std::sqrt(t));
    double part2 = r * K * std::exp(-r * t) * norm_cdf(-d2);
    double part3 = q * S * std::exp(-q * t) * norm_cdf(-d1);
    return (-part1 + part2 - part3);
}

double Euro_put::calc_rho() const
{
    // change in option price / 1% change in risk-free interest
    double d1 = (std::log(S / K) + (r + sigma * sigma * 0.5) * t) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    return -K * t * std::exp(-r * t) * norm_cdf(-d2);
}

/*          Derived Class : European Call on Future         */

// define if needed
Euro_future_call::~Euro_future_call() {}

void Euro_future_call::print()
{
    std::cout << "BS Future Call: " << Euro_future_call::option_price() << std::endl;
}

double Euro_future_call::option_price() const
{
    // BS price of a future call
    double d1 = (std::log(S / K) + (0.5 * sigma * sigma * t)) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    return std::exp(-r * t) * (S * norm_cdf(d1) - K * norm_cdf(d2));
}

// function to implement greeks if necessary
double Euro_future_call::calc_delta() const { return 0.0; }
double Euro_future_call::calc_gamma() const { return 0.0; }
double Euro_future_call::calc_vega()  const { return 0.0; }
double Euro_future_call::calc_theta() const { return 0.0; }
double Euro_future_call::calc_rho()   const { return 0.0; }

/*          Derived Class : European Put on Future            */

// define if needed
Euro_future_put::~Euro_future_put() {}

void Euro_future_put::print()
{
    std::cout << "BS Future Put: " << Euro_future_put::option_price() << std::endl;
}

double Euro_future_put::option_price() const
{
    // BS price of a future put
    double d1 = (std::log(S / K) + (sigma * sigma * 0.5 * t)) / (sigma * std::sqrt(t));
    double d2 = d1 - sigma * std::sqrt(t);
    return std::exp(-r * t) * (K * norm_cdf(-d2) - S * norm_cdf(-d1));
}

// function to implement greeks if necessary
double Euro_future_put::calc_delta() const { return 0.0; }
double Euro_future_put::calc_gamma() const { return 0.0; }
double Euro_future_put::calc_vega()  const { return 0.0; }
double Euro_future_put::calc_theta() const { return 0.0; }
double Euro_future_put::calc_rho()   const { return 0.0; }
