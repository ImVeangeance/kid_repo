#include <iostream>
#include <chrono>
#include <iomanip>
#include <pthread.h>
#include <vector>
#include <string>
#include <random>

int_fast64_t $size = 0, pthread_size, thread_id;
std::vector <int_fast64_t > x, result;
std::vector <std::vector <double_t>> matrix;

void *num_gen(void *arg);
void *multiply(void *arg);

int main()
{
    pthread_t *threads;
    std::cout << "Size of V and M: ";
    std::cin >> $size;
    std::cout << "Input the thread's size: ";
    std::cin >> pthread_size;
    x.resize($size, 0);
    matrix.resize($size, std::vector <double_t>($size));
    threads = new pthread_t[pthread_size];
    for(auto i = 0; i < pthread_size; ++i)
    {
        thread_id = i;
        pthread_create(&threads[i], nullptr, num_gen, &thread_id);
    }
    for(int i = 0; i < pthread_size; i++)
    {
        pthread_join(pthread_size, nullptr);
    }
    for(auto i = 0; i < pthread_size; ++i)
    {
        thread_id = i;
        pthread_create(&threads[i], nullptr, multiply, &thread_id);
    }
    return 0;
}

void *num_gen(void *arg)
{

    std::default_random_engine generator;
    std::uniform_int_distribution <int_fast64_t> distribution(1, 500);
    int_fast64_t threadID, chunk, alpha, omega;
    threadID = *(int_fast64_t *)arg;
    chunk = $size / pthread_size;
    alpha = threadID * chunk;
    omega = (threadID + 1) * chunk;
    for(auto i = alpha; i < omega; ++i)
    {
        x[i] = distribution(generator);
        for(auto j = 0; j < $size; ++j)
        {
            matrix[i][j] = distribution(generator);
        }
    }
    pthread_exit(nullptr);
}

void *multiply(void *arg)
{
    int_fast64_t threadID, chunk, alpha, omega;
    threadID = *(int_fast64_t *)arg;
    chunk = $size / pthread_size;
    alpha = threadID * chunk;
    omega = (threadID + 1) * chunk;
    for(auto i = alpha; i < omega; ++i)
    {
        for(auto j = 0; j < $size; ++j)
        {
            result[i] = matrix[i][j] * x[j];
        }
    }
    pthread_exit(nullptr);
}
