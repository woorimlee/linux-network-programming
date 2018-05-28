#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
union semun
{
	int val;
};
int main(int argc, char **argv)
{
	int shmid;
	int semid;
	int *cal_num;
	void *shared_memory = NULL;
	int local_var;
	union semun sem_union;
	struct sembuf semopen = {0, -1, SEM_UNDO};
	struct sembuf semclose = {0, 1, SEM_UNDO};
	shmid = shmget((key_t)1234, sizeof(int), 0666|IPC_CREAT);
	if (shmid == -1)
	{
		return 1;
	}
	semid = semget((key_t)3477, 1, IPC_CREAT|0666);
	if(semid == -1)
	{
		return 1;
	}
	shared_memory = shmat(shmid, NULL, 0);
	if (shared_memory == (void *)-1)
	{
		return 1;
	}
	cal_num = (int *)shared_memory;
	sem_union.val = 1;
	if ( -1 == semctl( semid, 0, SETVAL, sem_union))
	{
		return 1;
	}
	while(1)
	{
		if(semop(semid, &semopen, 1) == -1)
		{
			return 1;
		}
		local_var = *cal_num;
		sleep(1);
		*cal_num = local_var + 1;
		printf("P:%d\n", *cal_num);
		semop(semid, &semclose, 1);
	}
	return 1;
}
