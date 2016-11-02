
inline int truncate(const char *p, off_t l){
  int fd = open(p, O_WRONLY);
  if (fd == -1){
    errno = EACCES;
    return -1;
  }
  if (ftruncate(fd, l) == -1){
    close(fd);
    errno = EACCES;
    return -1;
  }
  return close(fd);
}

inline int symlink(const char*, const char*){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}


inline ssize_t readlink(const char*, char*, size_t){
  // vxWorks has no symlinks -> always return an error!
  errno = EACCES;
  return -1;
}

inline int gettimeofday(struct timeval *tv, void * /*tzv*/) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  tv->tv_sec  = ts.tv_sec;
  tv->tv_usec = ts.tv_nsec / 1000;
  return 0;
}


inline clock_t times(struct tms *t){
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  clock_t ticks(static_cast<clock_t>(static_cast<double>(ts.tv_sec)  * CLOCKS_PER_SEC +
                                     static_cast<double>(ts.tv_nsec) * CLOCKS_PER_SEC / 1000000.0));
  t->tms_utime  = ticks/2U;
  t->tms_stime  = ticks/2U;
  t->tms_cutime = 0; // vxWorks is lacking the concept of a child process!
  t->tms_cstime = 0; // -> Set the wait times for childs to 0
  return ticks;
}
