#include "yarn.h"

#define THREAD_COUNT 10

int counter = 0;
int* resps;
pthread_mutex_t lock;

void* run(void *arg) {
  LOCK(lock);
  int my_counter = counter;
  counter += 1;
  UNLOCK(lock);
  // Run a job.
  printf(">", my_counter);
  int i, x = 1, c = 256;
  for(i = 1; i < 100000000; i++) {
    x += i;
  }
  printf("<", my_counter);
  // Save return value.
  resps[my_counter] = x;
  // Return where the return value is held.
  return resps + my_counter;
}

int main() {
  // Allocate space for return values.
  resps = malloc(sizeof (int) * 2);
  CONCURRENT_FOR(0, THREAD_COUNT, &lock, &run, resps);
  return 0;
}

