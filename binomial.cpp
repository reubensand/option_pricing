#include "binomial.h"

/*          Base Class          */

// Destructor if necessary
Binomial::~Binomial() {}

/*          Derived Class : European Call Binomial          */

// Destructor if necessary
Euro_call_bin::~Euro_call_bin() {}

void Euro_call_bin::print()
{
    std::cout << "Euro Call Approx: " << Euro_call_bin::option_price() << std::endl;
}

double Euro_call_bin::option_price() const
{
    double R = std::exp((r - q) * (t / steps));        // interest rate for each step
    double Rinv = 1.0 / R;                             // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (R - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying
    prices[0] = S * pow(d, steps);         // fill in endnodes

    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> call_values(steps + 1); // value of corresponding call
    for (int i = 0; i <= steps; ++i)
        call_values[i] = std::max(0.0, (prices[i] - K));
    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
    }
    return call_values[0];
}

/*          Derived Class : European Put Binomial          */

// Destructor if necessary
Euro_put_bin::~Euro_put_bin() {}

void Euro_put_bin::print()
{
    std::cout << "Euro Call Approx: " << Euro_put_bin::option_price() << std::endl;
}

double Euro_put_bin::option_price() const
{
    double R = std::exp((r - q) * (t / steps));        // interest rate for each step
    double Rinv = 1.0 / R;                             // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (R - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying
    prices[0] = S * pow(d, steps);         // fill in endnodes

    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> put_values(steps + 1); // value of corresponding call
    for (int i = 0; i <= steps; ++i)
        put_values[i] = std::max(0.0, (K - prices[i]));

    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
            put_values[i] = (p_up * put_values[i + 1] + p_down * put_values[i]) * Rinv;
    }
    return put_values[0];
}

/*          Derived Class : American Call Binomial          */

// Destructor if necessary
American_call::~American_call() {}

void American_call::print()
{
    std::cout << "American Call Approx: " << American_call::option_price() << std::endl;
}

double American_call::option_price() const
{
    double R = std::exp((r - q) * (t / steps));        // interest rate for each step
    double Rinv = 1.0 / R;                             // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (R - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying

    // Set up prices at maturity
    prices[0] = S * std::pow(d, steps);
    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> call_values(steps + 1); // value of corresponding call

    // Calculate call payoffs at maturity
    for (int i = 0; i <= steps; ++i)
        call_values[i] = std::max(0.0, (prices[i] - K));

    // Step back through tree
    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K); // check for exercise
        }
    }
    return call_values[0];
}

/*          Derived Class : American Put Binomial          */

// Destructor if necessary
American_put::~American_put() {}

void American_put::print()
{
    std::cout << "American Put Approx: " << American_put::option_price() << std::endl;
}

double American_put::option_price() const
{
    double R = std::exp((r - q) * (t / steps));        // interest rate for each step
    double Rinv = 1.0 / R;                             // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (R - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying

    // Set up prices at maturity
    prices[0] = S * std::pow(d, steps);
    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> put_values(steps + 1); // value of corresponding call

    // Calculate call payoffs at maturity
    for (int i = 0; i <= steps; ++i)
        put_values[i] = std::max(0.0, (K - prices[i]));

    // Step back through tree
    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
        {
            put_values[i] = (p_up * put_values[i + 1] + p_down * put_values[i]) * Rinv;
            prices[i] = prices[i + 1] / u;
            put_values[i] = std::max(put_values[i], K - prices[i]); // check for exercise
        }
    }
    return put_values[0];
}

/*          Derived Class : American Call on Future Binomial          */

// Destructor if necessary
American_future_call::~American_future_call() {}

void American_future_call::print()
{
    std::cout << "American Future approx: " << American_future_call::option_price() << std::endl;
}

double American_future_call::option_price() const
{
    double Rinv = std::exp(-r * (t / steps));          // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (1 - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying

    // Set up prices at maturity
    prices[0] = S * std::pow(d, steps);
    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> call_values(steps + 1); // value of corresponding call

    // Calculate call payoffs at maturity
    for (int i = 0; i <= steps; ++i)
        call_values[i] = std::max(0.0, (prices[i] - K));

    // Step back through tree
    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K); // check for exercise
        }
    }
    return call_values[0];
}

/*          Derived Class : American Put on Future Binomial          */

// Destructor if necessary
American_future_put::~American_future_put() {}

void American_future_put::print()
{
    std::cout << "American Put approx: " << American_future_put::option_price() << std::endl;
}

double American_future_put::option_price() const
{
    double Rinv = std::exp(-r * (t / steps));          // inverse of interest rate
    double u = std::exp(sigma * std::sqrt(t / steps)); // up movement
    double d = 1.0 / u;                                // down movement
    double p_up = (1 - d) / (u - d);                   // probability of upward
    double p_down = 1.0 - p_up;                        // probability of downward

    std::vector<double> prices(steps + 1); // price of underlying

    // Set up prices at maturity
    prices[0] = S * std::pow(d, steps);
    for (int i = 1; i <= steps; ++i)
        prices[i] = prices[i - 1] * u * u;

    std::vector<double> put_values(steps + 1); // value of corresponding call

    // Calculate call payoffs at maturity
    for (int i = 0; i <= steps; ++i)
        put_values[i] = std::max(0.0, (K - prices[i]));

    // Step back through tree
    for (int step = steps - 1; step >= 0; --step)
    {
        for (int i = 0; i <= step; ++i)
        {
            put_values[i] = (p_up * put_values[i + 1] + p_down * put_values[i]) * Rinv;
            prices[i] = prices[i + 1] * d;
            put_values[i] = std::max(put_values[i], K - prices[i]); // check for exercise
        }
    }
    return put_values[0];
}
