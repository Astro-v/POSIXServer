#ifndef THREAD_VECTOR_HPP
#define THREAD_VECTOR_HPP

#include <vector>
#include <thread>
#include <future>

class ThreadVector
{
    struct ThreadItem
    {
        std::thread thread;
        std::promise<void> promise;
        std::future<void> future;

        ThreadItem(std::thread t, std::promise<void> p)
            : thread(std::move(t)), promise(std::move(p)), future(promise.get_future()) {}
    };

    std::vector<ThreadItem> m_threads;

public:
    ThreadVector() = default;

    ~ThreadVector();

    void add_thread(std::thread t);
    void update();
};

#endif // THREAD_VECTOR_HPP