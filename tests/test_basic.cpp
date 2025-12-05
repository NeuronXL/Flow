#include "thread_pool.h"

#include <cassert>
#include <stdexcept>
#include <vector>

int main() {
    ThreadPool pool(4);

    std::vector<std::future<int>> futures;
    futures.reserve(100);
    for (int i = 0; i < 100; ++i) {
        futures.emplace_back(pool.submit([i] { return i * 2; }));
    }
    for (int i = 0; i < 100; ++i) {
        assert(futures[i].get() == i * 2);
    }

    auto throwing = pool.submit([]() -> int {
        throw std::runtime_error("boom");
    });
    bool threw = false;
    try {
        (void)throwing.get();
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);

    return 0;
}
