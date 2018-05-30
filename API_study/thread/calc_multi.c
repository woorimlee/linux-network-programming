#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define ARRAY_SIZE 100
#define THREAD_NUM 4
pthread_mutex_t t_lock;
pthread_cond_t t_cond;
int *data_array;
int sum_array[THREAD_NUM];
struct data_info
{
	int *d_point;
	int idx;
};
void *t_func(void *data)
{
	struct data_info d_info;
	int i = 0;
	int sum=0;
	d_info = *((struct data_info *)data);
	pthread_mutex_lock(&t_lock);
	pthread_cond_wait(&t_cond, &t_lock);
	printf("Start %d Thread\n", d_info.idx);
	pthread_mutex_unlock(&t_lock);
	for(i = 0; i < 25; i++)
	{
		sum += d_info.d_point[(d_info.idx*25)+i];
	}
	printf("(%d) %d\n", d_info.idx, sum);
	sum_array[d_info.idx] = sum;
	return NULL;
}

int main(int argc, char **argv)
{
	int i=0;
	int sum=0;
	struct data_info d_info;
	pthread_t thread_id[THREAD_NUM];
	if((data_array = malloc(sizeof(int)*ARRAY_SIZE)) == NULL)
	{
		perror("Malloc Failuer");
		return 1;
	}
	pthread_mutex_init(&t_lock,NULL);
	pthread_cond_init(&t_cond, NULL);
	for(i = 0; i < THREAD_NUM; i++)
	{
		d_info.d_point = data_array;
		d_info.idx = i;
		pthread_create(&thread_id[i], NULL, t_func, (void *)&d_info);
		usleep(100);
	}

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		*data_array = i;
		*data_array++;
	}
	pthread_cond_broadcast(&t_cond);
	for(i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(thread_id[i],NULL);
		sum += sum_array[i];
	}
	printf("SUM (0-99) : %d\n",sum);
	return 0;
}
