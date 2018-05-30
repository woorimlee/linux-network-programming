#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define MAX_THREAD 2

void *t_func(void *data) {
	int *count = (int *)data;
	int tmp;
	pthread_t thread_id = pthread_self();
	while(1) {
		printf("%lu %d\n", thread_id, *count);
		*count = *count + 1;
		//tmp = *count;
		sleep(1);
		//*count = tmp + 1;

	}
}

int main(int argc, char **argv) {
	pthread_t thread_id[MAX_THREAD];
	int i = 0;
	int count = 0;

	for(i = 0; i < MAX_THREAD; i++) {
		pthread_create(&thread_id[i], NULL, t_func, (void *)&count);
		usleep(5000);
	}
	while(1) {
		//printf("Main Thread : %d\n", count);
		sleep(2);
	}
	for(i = 0; i < MAX_THREAD; i++) {
		pthread_join(thread_id[i], NULL);
	}
	return 0;
}
