#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using namespace std::chrono;
using namespace std::chrono_literals;

void do_something(std::vector<uint64_t>& vec, uint64_t& x) {
    for (auto& each : vec) {
        x += 1;
    }
}

uint64_t sumAsync(std::vector<uint64_t>& vec, uint64_t start, uint64_t end) {
    uint64_t sum = 0;

    for (size_t i = start; i < end; i++) {
        sum += vec[i];
    }

    return sum;
}

uint64_t sum_in_async(std::vector<uint64_t>& vec, uint64_t thread_count) {
    size_t current_limit = 0;
    size_t limit_diff = vec.size() / thread_count;
    uint64_t sum = 0;

    std::vector<std::future<uint64_t>> threads;

    for (size_t i = 0; i < thread_count; i++) {
        if (i != thread_count - 1) {
            threads.push_back(std::async(std::launch::async, sumAsync,
                                         std::ref(vec), current_limit,
                                         current_limit + limit_diff));
            current_limit += limit_diff;
        } else {
            threads.push_back(std::async(std::launch::async, sumAsync,
                                         std::ref(vec), current_limit,
                                         vec.size()));
        }
    }

    for (auto& each : threads) {
        each.wait();
        sum += each.get();
    }

    return sum;
}

int main() {
    uint64_t count = 1'000'000'000;
    vector<uint64_t> vec(count, 1);
    uint64_t x = 0;

    auto t1 = high_resolution_clock::now();
    { x = sum_in_async(vec, 3); }
    auto time_span = duration_cast<duration<double, std::milli>>(
                         high_resolution_clock::now() - t1)
                         .count();
    cout << "It took " << time_span << " ms." << '\n';
    std::cout << x << std::endl;

    return 0;
}
