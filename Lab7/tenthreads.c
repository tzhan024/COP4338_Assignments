/*
	Student name: Tinghui Zhang
	Panther ID: 6144880
	~Affirmation of Originality: I affirm that I wrote this program myself without any help 
	from any other people or sources from the internet.
	~Program Description: This program uses 10 threads to increment a shared variable.
	Each thread must loop 6 times, incrementing the shared variable by its Thread ID
	(tid) in every iteration of the loop. Once a thread has finished looping, print
	the ID of the thread saying “Thread [ID] has finished.” It is important to make
	use of mutexes so that only one thread is incrementing the shared variable at a time.
	Output the value of the shared variable once all threads have finished incrementing it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;

/* shared data between threads */
double shared_x;
pthread_mutex_t lock_x;
/*
	This fucntion increments the variable for each threads,
	and will print if the thread is finished. 
*/
void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  /* get mutex before modifying and printing shared_x */
  pthread_mutex_lock(&lock_x);
  int i = 0;
  for(i = 0; i < 6; i++)
  {
    shared_x += data->tid;
  }
  printf("Thread [%d] has finished.\n" , data->tid);
  pthread_mutex_unlock(&lock_x);

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  pthread_t thr[NUM_THREADS];
  int i, rc;
  /* create a thread_data_t argument array */
  thread_data_t thr_data[NUM_THREADS];

  /* initialize shared data */
  shared_x = 0;

  /* initialize pthread mutex protecting "shared_x" */
  pthread_mutex_init(&lock_x, NULL);

  /* create threads */
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].tid = i;
    thr_data[i].stuff = (i + 1) * NUM_THREADS;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  /* block until all threads complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thr[i], NULL);
  }

  printf("x = %.2f\n", shared_x);
  return EXIT_SUCCESS;
}
