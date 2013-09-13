#ifndef _CV_H
#define _CV_H

#include "mutex.h"

class cv {
public:
    cv();
    ~cv();

    void wait(mutex &);                 // wait on this condition variable
    void signal();                      // wake up one thread on this condition
                                        // variable
    void broadcast();                   // wake up all threads on this condition
                                        // variable

    struct impl;                        // defined by the thread library
    impl *impl_ptr;                     // used by the thread library
};

#endif /* _CV_H */
