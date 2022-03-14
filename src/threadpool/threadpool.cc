#include <pthread.h>
#include <stdexcept>

#include "threadpool.h"
#include "common.h"

ThreadPool::ThreadPool(int thread_num, int max_wait_task)
        : m_thread_num(thread_num), m_max_wait_task(max_wait_task), m_stop(false) {
    if (m_thread_num <= 0 || max_wait_task <= 0)
        throw std::range_error("In class ThreadPool: invalid init parameter");
    pthread_attr_t detach_attr;
    pthread_attr_init(&detach_attr);
    pthread_attr_setdetachstate(&detach_attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < m_thread_num; ++i) {
        pthread_t thread;
        int err = pthread_create(&thread, &detach_attr, worker, this);
        if (err == -1) {
            pthread_attr_destroy(&detach_attr);
            throw std::runtime_error("In class ThreadPool: create thread error");
        }
    }

    pthread_attr_destroy(&detach_attr);
}

ThreadPool::~ThreadPool() {
    m_stop = true;
}

bool ThreadPool::appendTask(Runner *runner) {
    m_queue_mutex.lock();
    if (m_task_queue.size() >= m_max_wait_task) {
        m_queue_mutex.unlock();
        return false;
    }
    m_task_queue.push(runner);
    m_queue_mutex.unlock();
    m_sem.post();
    return true;
}

void *ThreadPool::worker(void *arg) {
    auto runner = static_cast<ThreadPool *>(arg);
    runner->run();
    return runner;
}

void ThreadPool::run() {
    while (!m_stop) {
        m_sem.wait();
        m_queue_mutex.lock();
        Runner *runner = nullptr;
        if (!m_task_queue.empty()) {
            runner = m_task_queue.front();
            m_task_queue.pop();
        }
        m_queue_mutex.unlock();
        if (runner != nullptr)
            runner->run();
    }
}
