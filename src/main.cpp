#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "thread_pool.h"

int main() {
    ThreadPool pool(4);

    std::vector<std::future<std::string>> results;
    results.reserve(8);

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(pool.submit([i] {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i % 3 + 1)));
            return std::string("Task ") + std::to_string(i) + " completed on thread "
                   + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));
        }));
    }

    for (auto& fut : results) {
        std::cout << fut.get() << '\n';
    }

    std::cout << "All tasks finished.\n";
    return 0;
}
