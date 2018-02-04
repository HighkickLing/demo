#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *thread_func(void *)
{
    while (true)
    {
        usleep(1*1000*1000);
    }
    return NULL;
}

int main()
{
    pthread_t pid;
    pthread_attr_t attr_main;
    pthread_attr_t attr_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    printf("default stack size = %x\n", attr.stack_size);
    pthread_getattr_np(pthread_self(), &attr_main);
    pthread_create(&pid, NULL, thread_func, NULL);
    pthread_getattr_np(pid, &attr_thread);
    printf("%x+%x=%x\n", attr_main.stack_base, attr_main.stack_size,
        ((unsigned char*)attr_main.stack_base) + attr_main.stack_size);
    printf("%x+%x=%x\n", attr_thread.stack_base, attr_thread.stack_size,
        ((unsigned char*)attr_thread.stack_base) + attr_thread.stack_size);
    printf("pthread_internal_t*=%x\n", pid);
    while (true)
    {
        usleep(1*1000*1000);
    }
    return 0;
}
