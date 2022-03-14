#ifndef TINYSERVER_THREADPOOL_H
#define TINYSERVER_THREADPOOL_H

#include <queue>
#include <mutex>

#include "locker.h"

class Runner;

class ThreadPool {
public:
    ThreadPool(int thread_num = 16, int max_wait_task = 23333);
    ~ThreadPool();

    bool appendTask(Runner *runner);

private:
    static void *worker(void *arg);
    void run();

private:
    int m_thread_num;
    int m_max_wait_task;

    std::queue<Runner *> m_task_queue;
    std::mutex m_queue_mutex;
    Sem m_sem;
    bool m_stop;
};

#endif //TINYSERVER_THREADPOOL_H
