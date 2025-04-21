#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>

static const size_t KiB = 1024;
static const size_t MiB = 1024 * KiB;
static const size_t GiB = 1024 * MiB;

int pthread_create(pthread_t* restrict thread, const pthread_attr_t* restrict attr, typeof(void*(void*))* start_routine, void* restrict arg)
{
    static bool initialized = false;
    static pthread_attr_t new_attr;
    printf("[debug] [%s%d]\n", __FILE_NAME__, __LINE__);
    if (initialized == false)
    {
        initialized = true;
        pthread_attr_init(&new_attr);
        pthread_attr_setstacksize(&new_attr, GiB);
    }
    typeof(pthread_create)* real = dlsym(RTLD_NEXT, "pthread_create");
    return real(thread, &new_attr, start_routine, arg);
}
