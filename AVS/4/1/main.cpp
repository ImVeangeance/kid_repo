#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <random>
#include <x86intrin.h>

static const int64_t proc_tc = 2200000000;

double_t a = 1.0;
std::vector <double_t> sumary;
int64_t saxpy_blas(std::vector <int64_t> &X, std::vector <int64_t> &Y);

int main()
{
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution <int64_t> uid(0, 100000);
    int64_t v_size = 0;
    std::cout << "Vector size - ";
    std::cin >> v_size;
    std::cout << "A - ";
    //std::cin >> a;
    sumary.resize(v_size, 0);
    std::vector <int64_t> X(v_size);
    std::vector <int64_t> Y(v_size);
    std::generate(X.begin(), X.end(), std::rand);
    std::generate(Y.begin(), Y.end(), std::rand);
    /*std::cout << "X\n";
    for(auto &i : X)
        std::cout << i << "\n";
    std::cout << "\nY\n";
    for(auto &i : Y)
        std::cout << i << "\n";
    */saxpy_blas(X,Y);
    /*std::cout << "\nSumary vector\n";
    for(auto &i : sumary)
        std::cout << i << " ";
    */return 0;
}

int64_t saxpy_blas(std::vector <int64_t> &X, std::vector <int64_t> &Y)
{
    int64_t start = __rdtsc();
    for(auto iterator = 0 ; iterator < sumary.size(); iterator++)
        sumary[iterator] = X[iterator] * a + Y[iterator];
    std::cout << "\n\nTime(TSC) - " << std::fixed << std::setprecision(10) << (double_t)(__rdtsc() - start) / proc_tc;
}