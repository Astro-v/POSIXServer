#include "ThreadVector.hpp"

ThreadVector::~ThreadVector()
{
    for (auto &thread : m_threads)
    {
        if (thread.thread.joinable())
        {
            thread.thread.join();
        }
    }
}

/**
 * @brief Add a thread to the vector
 * @param t The thread to add
 */
void ThreadVector::add_thread(std::thread t)
{
    std::promise<void> p;
    m_threads.push_back(ThreadItem(std::move(t), std::move(p)));
}

/**
 * @brief Update and destroy finished threads
 */
void ThreadVector::update()
{
    for (auto it = m_threads.begin(); it != m_threads.end();)
    {
        if (it->future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            if (it->thread.joinable())
            {
                it->thread.join();
            }
            it = m_threads.erase(it);
        }
        else
        {
            ++it;
        }
    }
}