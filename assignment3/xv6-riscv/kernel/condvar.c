#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sleeplock.h"
#include "kernel/condvar.h"

void
cond_wait (cond_t *cv, struct sleeplock *lock){
    releasesleep(lock);
    acquiresleep(&cv->lk);
    condsleep(cv, &cv->lk);
    releasesleep(&cv->lk);
    acquiresleep(lock);
    return;
}

void
cond_signal (cond_t *cv){
    acquiresleep(&cv->lk);
    (&cv->lk)->locked = 1;
    releasesleep(&cv->lk);
    wakeupone(cv);
    acquiresleep(&cv->lk);
    (&cv->lk)->locked = 0;
    releasesleep(&cv->lk);
    return;
}

void
cond_broadcast (cond_t *cv){
    acquiresleep(&cv->lk);
    (&cv->lk)->locked = 1;
    releasesleep(&cv->lk);
    wakeup(cv);
    acquiresleep(&cv->lk);
    (&cv->lk)->locked = 0;
    releasesleep(&cv->lk);
}
