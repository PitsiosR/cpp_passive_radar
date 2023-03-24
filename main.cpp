#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "resample.h"

using namespace std;

void worker_func(int kUpfactor, int kDownfactor, vector<double> input, vector<double> output)
{
    resample<double>(kUpfactor, kDownfactor, input, output);
}

int main()
{
    const int kUpfactor = 1;
    const int kDownfactor = 32728;

    vector<double> input(4194304), output;
    std::iota(input.begin(), input.end(), 0.00005);
    auto start = std::chrono::high_resolution_clock::now();
    const int num_threads = 40;
    std::vector<std::thread> threads(num_threads);
    for (int i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(worker_func, kUpfactor, kDownfactor, input, output);
    }

    // Wait for the threads to finish
    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto dur_d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "double elapsed: " << dur_d.count() / 1e9l << " secs";
    cout << endl
         << endl;

    // vector<float> input_f(10), output_f;
    // std::iota(input_f.begin(), input_f.end(), 1.0);
    // start = std::chrono::high_resolution_clock::now();
    // resample<float>(kUpfactor, kDownfactor, input_f, output_f);
    // stop = std::chrono::high_resolution_clock::now();
    // cout << "float : ";
    // for (int i = 0, n = output_f.size(); i < n; i++)
    //     cout << output_f[i] << " ";
    // cout << endl;
    // auto dur_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    // cout << "float  elapsed: " << dur_f.count() / 1e9l << " secs";
    // cout << endl
    //      << endl;

    return 0;
}
