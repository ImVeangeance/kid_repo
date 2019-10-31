#include <iostream>
#include <vector>
#include <cfloat>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <initializer_list>
#include <random>

const int64_t rand_elem_cast_size = 1000;
double_t a = 1.0;
std::vector <double_t> sumary;
int64_t saxpy_blas(std::vector <int64_t> &X, std::vector <int64_t> &Y);

int main()
{
  srand(time(nullptr));
  int64_t v_size = 0;
  std::cout << "Vector size - ";
  std::cin >> v_size;
  std::cout << "A - ";
  std::cin >> a;
  sumary.resize(v_size, 0);
  std::vector <int64_t> X(v_size);
  std::vector <int64_t> Y(v_size);
  std::generate(X.begin(), X.end(), std::rand);
  std::generate(Y.begin(), Y.end(), std::rand);
  std::cout << "X\n";
  for(auto &i : X)
    std::cout << i << " ";
  std::cout << "\nY\n";
  for(auto &i : Y)
    std::cout << i << " ";
  saxpy_blas(X,Y);
  std::cout << "\nSumary vector\n";
  for(auto &i : sumary)
    std::cout << i << " ";
  return 0;
}

int64_t saxpy_blas(std::vector <int64_t> &X, std::vector <int64_t> &Y)
{
  for(auto iterator = 0 ; iterator < sumary.size(); iterator++)
    sumary[iterator] = X[iterator] * a + Y[iterator];
}
