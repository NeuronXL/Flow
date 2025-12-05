#include "thread_pool.h"

#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <vector>

int main() {
    ThreadPool pool(8);

    constexpr int kTasks = 100000;
    std::atomic<int> counter{0};

    std::vector<std::future<void>> futures;
    futures.reserve(kTasks);

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < kTasks; ++i) {
        futures.emplace_back(pool.submit([&counter] {
            counter.fetch_add(1, std::memory_order_relaxed);
        }));
    }
    for (auto& f : futures) {
        f.get();
    }
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count();

    std::cout << "Completed " << counter.load() << " tasks in "
              << elapsed_ms << " ms" << std::endl;

    return counter.load() == kTasks ? 0 : 1;
}
