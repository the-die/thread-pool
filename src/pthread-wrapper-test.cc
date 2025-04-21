#include "BS_thread_pool.hpp"

#include <dlfcn.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <print>

void print_current_thread_stack_size()
{
    pthread_attr_t attr;
    size_t stack_size = 0;

    if (pthread_getattr_np(pthread_self(), &attr) != 0)
    {
        perror("pthread_getattr_np");
        return;
    }

    if (pthread_attr_getstacksize(&attr, &stack_size) != 0)
    {
        perror("pthread_attr_getstacksize");
        return;
    }

    auto tid = (pid_t)syscall(SYS_gettid);
    std::println("{} Current thread stack size: {} bytes", tid, stack_size);

    pthread_attr_destroy(&attr);
}

int main()
{
    BS::light_thread_pool pool(8);
    for (int i = 0; i < 10; ++i)
    {
        [[maybe_unused]] auto future = pool.submit_task(
            []()
            {
                print_current_thread_stack_size();
            });
    }
    pool.wait();
}
