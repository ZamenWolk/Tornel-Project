#ifndef SINGLETON
#define SINGLETON

template <class T>
T &singleton()
{
    static T instance;
    return instance;
}

#endif