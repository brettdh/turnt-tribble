#ifndef _MUTEX_H
#define _MUTEX_H

class mutex {
public:
    mutex();
    ~mutex();

    void lock();
    void unlock();

    struct impl;                        // defined by the thread library
    impl *impl_ptr;                     // used by the thread library
};

#endif /* _MUTEX_H */
