#ifndef CLASSES_SINGLETON_HPP
#define CLASSES_SINGLETON_HPP

template <class T>
T &singleton()
{
    static T instance;
    return instance;
}

#endif