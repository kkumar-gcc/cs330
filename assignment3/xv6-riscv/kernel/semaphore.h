struct semaphore{
  int value;
  struct sleeplock lock;
  cond_t cv;
};
