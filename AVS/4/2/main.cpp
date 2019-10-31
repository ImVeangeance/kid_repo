#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>
#include <x86intrin.h>

static const int64_t proc_tc = 2200000000;

double_t dgemm_blas(std::vector<std::vector<double_t>> &first, std::vector<std::vector<double_t>> &last, int64_t f_col, int64_t s_str);

int main()
{
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<double_t> uid(0.0, 10.0);
    int64_t f_str = 0, f_col = 0, s_str = 0, s_col = 0;
    std::cout << "Matrix size, string for first - ";
    std::cin >> f_str;
    std::cout << "Matrix size, column for first - ";
    std::cin >> f_col;
    std::cout << "Matrix size, string for second - ";
    std::cin >> s_str;
    std::cout << "Matrix size, column for second - ";
    std::cin >> s_col;
    std::vector<std::vector<double_t>> first(f_str, std::vector<double_t>(f_col, 0));
    std::vector<std::vector<double_t>> last(s_str, std::vector<double_t>(s_col, 0));
    //std::cout << "First\n";
    for (auto i = 0; i < first.size(); i++)
    {
        for (auto j = 0; j < first[i].size(); j++)
        {
            first[i][j] = uid(gen);
            //std::cout << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(5) << first[i][j] << "\t";
        }
        //std::cout << "\n";
    }
    //std::cout << "Second\n";
    for (auto i = 0; i < last.size(); i++)
    {
        for (auto j = 0; j < last[i].size(); j++)
        {
            last[i][j] = uid(gen);
            //std::cout << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(5) << last[i][j] << "\t";
        }
        //std::cout << "\n";
    }
    if (f_col != s_str)
    {
        std::cout << "Matrix cannot multi\n";
        return 0;
    }
    else
        dgemm_blas(first, last, f_col, s_str);
    return 0;
}

double_t dgemm_blas(std::vector<std::vector<double_t>> &first, std::vector<std::vector<double_t>> &last, int64_t f_col, int64_t s_str)
{
    int64_t  start_time =__rdtsc();
    std::vector<std::vector<double_t>> multi(s_str, std::vector<double_t>(f_col, 0));
    //std::cout << "Multi matrix\n";
    for(auto & i : multi)
    {
        for(auto j = 0; j < i.size(); j++)
        {
            for(auto k = 0; k < f_col; k++)
                i[j] += first[j][k] * last[k][j];
        }
    }
    /*for (auto i = 0; i < multi.size(); i++)
    {
        for (auto j = 0; j < multi[i].size(); j++)
            std::cout << std::fixed << std::setprecision(2) << std::setfill('0') << std::setw(5) << multi[i][j] << "\t";
        std::cout << "\n";
    }*/
    std::cout << "\nTime of matrix multi - " << std::fixed << std::setprecision(10) << (double_t)(__rdtsc() - start_time) / proc_tc;
    return 0;
}