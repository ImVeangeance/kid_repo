#include <iostream>
#include <chrono>
#include <iomanip>
#include <pthread.h>
#include <ctime>
#include <vector>
#include <random>

int64_t size = 0, pthread_size;
std::vector <int64_t > x, result;
std::vector <std::vector <double_t>> matrix;

void *num_gen(void *arg);
void *multiply(void *arg);

int main()
{
    std::cout << "Size of V and M: ";
    std::cin >> size;
    std::cout << "Input the thread's size: ";
    std::cin >> pthread_size;
    x.resize(size, 0);
    result.resize(size);
    matrix.resize(size, std::vector <double_t>(size));
    auto *threadsC = new pthread_t[pthread_size];
    auto *threadsR = new pthread_t[pthread_size];
    int64_t thread_id;
    auto t1 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < pthread_size; i++)
    {
        thread_id = i;
        pthread_create(&threadsR[i], nullptr, num_gen, &thread_id);
    }
    for(int i = 0; i < pthread_size; i++)
        pthread_join(threadsR[i], nullptr);

    auto t2 = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < pthread_size; i++)
    {
        thread_id = i;
        pthread_create(&threadsC[i], nullptr, multiply, &thread_id);
    }
    for(int i = 0; i < pthread_size; i++)
        pthread_join(threadsC[i], nullptr);

    auto t3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration <double_t> elapsedSeconds{};
    std::cout << "\nRandom & computing time: ";
    elapsedSeconds = t3 - t1;
    std::cout << elapsedSeconds.count() << " seconds." << std::endl;
    /*std::cout << "\nRandom time: " << std::endl;
    elapsedSeconds = t2 - t1;
    std::cout << elapsedSeconds.count() << " seconds." << std::endl;
    std::cout << "\nComputing time: " << std::endl;
    elapsedSeconds = t3 - t2;
    std::cout << elapsedSeconds.count() << " seconds." << std::endl;
    */return 0;
}

void *num_gen(void *arg)
{
    std::mt19937(time(nullptr));
    std::default_random_engine ss;
    std::uniform_int_distribution <int64_t> distribution(1, 1000);
    int64_t threadID, chunk, alpha, omega;
    threadID = *(int64_t *)arg;
    chunk = size / pthread_size;
    alpha = threadID * chunk;
    omega = (threadID + 1) * chunk;
    for(auto i = alpha; i < omega; i++)
    {
        x[i] = distribution(ss);
        for(auto j = 0; j < size; j++)
        {
            matrix[i][j] = distribution(ss);
        }
    }
    pthread_exit(nullptr);
}

void *multiply(void *arg)
{
    int64_t threadID, chunk, alpha, omega;
    threadID = *(int64_t *)arg;
    chunk = size / pthread_size;
    alpha = threadID * chunk;
    omega = (threadID + 1) * chunk;
    for(auto i = alpha; i < omega; i++)
    {
        for(auto j = 0; j < size; j++)
        {
            result[i] += matrix[i][j] * x[j];
        }
    }
    /*
     for (int i = row_start; i < row_end; i++){
        res[i] = 0;
        for (int j = 0; j < n_SIZE; j++){
            res[i] += matrix[i][j] * vector_x[j];
        }
    }
    */
    pthread_exit(nullptr);
}