#include <iostream>
#include <cmath>
#include <time.h>
#include <limits>

using namespace std;

/**
 * @brief Uses inversion method. Generates a uniformely distibuted
 * random variable rnd [0,1] for internal use.
 *
 * https://en.wikipedia.org/wiki/Exponential_distribution
 *
 * @param seed the rate parameter of the exponential distribution.
 * Should be greater than zero. Smaller values produce, produce more
 * spread out random numbers and vice versa.
 */
double exponential_distribution(double seed)
{
    double rnd = rand() / (double) RAND_MAX;
    return log(1 - rnd) / ( -seed);
}

/**
 * @brief triangular_distribution
 * Again, uses the built-in rand function to create a uniformely distributed random number [0,1]
 *
 * https://en.wikipedia.org/wiki/Triangular_distribution
 *
 * @param low min boundary
 * @param high max boundary
 */
double triangular_distribution(double low, double high, double mode) {
   double rnd = rand() / (double) RAND_MAX;
   double F = (mode - low) / (high - low);
   if (rnd <= F)
      return low + sqrt(rnd * (high - low) * (mode - low));
   else
      return high - sqrt((1 - rnd) * (high - low) * (high - mode));
}

/**
 * @brief Uses Box–Muller transform.
 * Again, uses the built-in rand function to create a uniformely distributed random number [0,1]
 *
 * https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
 *
 * @param mu median
 * @param sigma standard deviation
 */
double normal_distribution(double mu, double sigma)
{
    static const double epsilon = std::numeric_limits<double>::min();
    static const double two_pi = 2.0*3.14159265358979323846;

    thread_local double z0, z1;
    thread_local bool generate;
    generate = !generate;

    if (!generate)
       return z1 * sigma + mu;

    double u1, u2;
    do
     {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
     }
    while ( u1 <= epsilon );

    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}

int main(int argc, char *argv[])
{
    // seed the random-number generator to get different values each time
    srand (time(NULL));

    double a;
    printf("1. For the exponential distribution enter the seed (value greater than 1).\n"
           "NOTE: Smaller seed values produce more spread out random numbers and vice versa.\n");
    scanf("%lf",&a);
    cout<<"Exponential distribution: "<<exponential_distribution(a)<<endl;
    cout<<"--------------------------------------------------------------\n";

    double min, max, mode;
    printf("2. For the triangular distribution enter the min, max and mode values separated by spaces.\n");
    scanf("%lf %lf %lf", &min, &max, &mode);
    cout<<"Triangular distribution: "<<triangular_distribution(1, 100, 50)<<endl;
    cout<<"--------------------------------------------------------------\n";

    double mu, sigma;
    printf("3. For the normal distribution enter the median and standard deviation values separated by spaces.\n");
    scanf("%lf %lf", &mu, &sigma);
    cout<<"Normal distribution: "<<normal_distribution(mu, sigma)<<endl;
}
