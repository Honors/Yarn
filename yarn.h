#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define LOCK(lock) pthread_mutex_lock(&lock);
#define UNLOCK(lock) pthread_mutex_unlock(&lock);

void CONCURRENT_FOR(int start, int end, pthread_mutex_t *lock, void* (*action)(void*), int* resps) { 
  pthread_t tid[end-start]; 
  /* make a lock */ 
  pthread_mutex_init(lock, NULL) != 0; 
  int i = start; 
  while(i < end) { 
    pthread_create(&(tid[i]), NULL, action, NULL); 
    i += 1; 
  } 
  /* Merge in the threads. */ 
  int j = start; 
  while(j < end) { 
    void* ptr; 
    pthread_join(tid[j], &ptr); 
    int resp = *(int*)ptr; 
    j += 1; 
  } 
  pthread_mutex_destroy(lock); 
}

