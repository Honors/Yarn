#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 10

pthread_t tid[THREAD_COUNT];
int counter = 0;
int* resps;
pthread_mutex_t lock;

void* run(void *arg) {
  // Avoid race conditions in updating the current counter value within a lock.
  pthread_mutex_lock(&lock);
  int my_counter = counter;
  counter += 1;
  pthread_mutex_unlock(&lock);
  // Run a job.
  printf(">", my_counter);
  int i, x = 1, c = 256;
  for(i = 1; i < 100000000; i++) {
    x += i;
  }
  // Save return value.
  resps[my_counter] = x; 
  printf("<", my_counter);
  return NULL;
}

int main() {
  resps = malloc(sizeof (int) * 2);
  int i = 0;
  // make a lock
  pthread_mutex_init(&lock, NULL) != 0;
  while(i < THREAD_COUNT) {
    pthread_create(&(tid[i]), NULL, &run, NULL);
    i += 1;
  }
  // Merge in the threads
  int j = 0;
  while(j < THREAD_COUNT) {
    pthread_join(tid[j], NULL);
    j += 1;
  }
  // Unlock.
  pthread_mutex_destroy(&lock);
  // Utilize responses...
  return 0;
}

