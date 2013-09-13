/*
 * cpu.h -- interface to the simulated CPU
 *
 * This interface is meant to be used by the thread library.
 * The only part that is used by application programs is cpu::boot()
 */
#ifndef _CPU_H
#define _CPU_H

#include "thread.h"

typedef void (*interrupt_handler_t) (void);

class cpu {
public:
    /*
     * cpu::boot() starts the thread library and creates the initial
     * thread, which is initialized to call the function pointed to by
     * func with the single argument arg.  A user program should call
     * cpu::boot() exactly once (before calling any other thread functions).
     * On success, cpu::boot() does not return.
     *
     * "deterministic" specifies if the thread library should be deterministic
     * or not.  Setting deterministic to zero makes the scheduling of threads
     * non-deterministic, i.e., different runs may generate different results.
     * Setting deterministic to a non-zero value forces the scheduling of
     * threads to be deterministic, i.e., a program will generate the same
     * results if it is run with the same value for deterministic (different
     * non-zero values for deterministic will lead to different results).
     */
    static void boot(thread_startfunc_t func, void *arg,
                     unsigned int deterministic);

    /*
     * interrupt_disable() disables interrupts on the executing CPU.  Any
     * interrupt that arrives while interrupts are disabled will be saved
     * and delivered when interrupts are re-enabled.
     *
     * interrupt_enable() and interrupt_enable_suspend() enable interrupts
     * on the executing CPU.
     *
     * interrupt_enable_suspend() atomically enables interrupts and suspends
     * the executing CPU until it receives an interrupt from another CPU.
     * The CPU will ignore timer interrupts while suspended.
     *
     * These functions should only be called by the thread library (not by
     * an application).  They are static member functions because they always
     * operate on the executing CPU, regardless of which object they were
     * called on.
     *
     * Each CPU starts with interrupts disabled.
     */
    static void interrupt_disable();
    static void interrupt_enable();
    static void interrupt_enable_suspend();

    /*
     * interrupt_send() sends an inter-processor interrupt to the specified CPU.
     * E.g., c_ptr->interrupt_send() sends an IPI to the CPU pointed to by c_ptr.
     */
    void interrupt_send();

    /*
     * The interrupt vector table specifies which function that will be called
     * for each type of interrupt.
     */
#define TIMER 0
#define IPI 1
    interrupt_handler_t interrupt_vector_table[IPI+1];

    cpu(thread_startfunc_t, void *);    // should only be called by infrastructure

    static cpu *self();                 // returns pointer to the cpu this thread
                                        // is running on

    struct impl;                        // defined by thread library
    impl *impl_ptr;                     // used by thread library

    struct infrastructure;              // defined by infrastructure
    infrastructure *infra_ptr;          // used by infrastructure
                                        // NOT FOR USE BY STUDENTS

private:
    /*
     * cpu::init() initializes a CPU.  It is provided by the thread library
     * and called by boot(); it should not be called by applications.
     * After a CPU is initialized, it should run user threads as they become
     * available.
     * On success, cpu::init() should not return to the caller.
     *
     * If func is not nullptr, cpu::init() also creates a user thread
     * that executes func(arg).
     */
    void init(thread_startfunc_t, void *);
};

/*
 * guard_test_and_set() and guard_clear() are used to atomically manipulate
 * a guard variable (which is allocated for you by the infrastructure).
 *
 * guard_test_and_set() atomically sets the guard to 1 and returns the prior
 * value.
 *
 * guard_clear() atomically sets the guard to 0.
 *
 * These functions should only be called by the thread library (not by
 * an application).
 *
 * The guard variable is initially false.
 */
bool guard_test_and_set();
void guard_clear();

/*
 * assert_interrupts_disabled() and assert_interrupts_enabled() can be used
 * as error checks inside the thread library.  They will assert (i.e. abort
 * the program and dump core) if the condition they test for is not met.
 */
#ifdef NDEBUG

#define assert_interrupts_disabled()
#define assert_interrupts_enabled()

#else // NDEBUG

#define assert_interrupts_disabled()                                    \
                assert_interrupts_private(__FILE__, __LINE__, true)
#define assert_interrupts_enabled()                                     \
                assert_interrupts_private(__FILE__, __LINE__, false)

/*
 * assert_interrupts_private() is a private function for the interrupt
 * functions.  Your thread library should not call it directly.
 */
extern void assert_interrupts_private(const char *, int, bool);

#endif // NDEBUG

#endif /* _CPU_H */
