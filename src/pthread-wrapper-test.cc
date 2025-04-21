#include "BS_thread_pool.hpp"

#include <dlfcn.h>
#include <pthread.h>

#include <cstdio>

void print_current_thread_stack_size()
{
    pthread_attr_t attr;
    size_t stack_size = 0;

    // Get current thread's attributes
    if (pthread_getattr_np(pthread_self(), &attr) != 0)
    {
        perror("pthread_getattr_np");
        return;
    }

    // Extract stack size
    if (pthread_attr_getstacksize(&attr, &stack_size) != 0)
    {
        perror("pthread_attr_getstacksize");
        return;
    }

    printf("Current thread stack size: %zu bytes\n", stack_size);

    // Clean up
    pthread_attr_destroy(&attr);
}

int main()
{
    auto handle = dlopen("./libpthread-wrapper.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle)
    {
        printf("Failed to open new library: %s\n", dlerror());
        return 1;
    }
    BS::light_thread_pool pool(16);
    for (int i = 0; i < 10; ++i)
    {
        pool.submit_task(
            [i]()
            {
                std::printf("[debug] %d\n", i);
                print_current_thread_stack_size();
            });
    }
    pool.wait();
}
