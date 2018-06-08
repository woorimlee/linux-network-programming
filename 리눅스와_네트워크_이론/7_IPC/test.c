#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

union semun
{
    int val;
};

int main (int argc, char **argv) {
    int shmid;
    int semid;
    int *cal_num;
    void *shared_memory = NULL;
    int local_var;
    union semun sem_union;

    struct sembuf semopen = {0, -1, SEM_UNDO};
    struct sembuf semclose = {0, -1 ,SEM_UNDO};

    shmid = shmget((key_t)1234, sizeof(int), 0666|IPC_CREAT);
    
    //두 번째 인자 세마포어 세트 개수
    semid = semget((key_t)2345, 1, IPC_CREAT|0666);

    //특별히 주려고하는 가상 메모리 시작 주소와 플래그는 각각 널과 0
    shared_memory = shmat(shmid, NULL, 0);
    
    cal_num = (int *)shared_memory;

    sem_union.val = 1;
    //세마포어 ID, 인덱스, 동작 명령, 가변 인수. val과 SETVAL은 세트
    semctl(semid, 0, SETVAL, sem_union);

    while(1)
    {	//1은 버퍼 구조체의 갯수
	semop(semid, &semopen, 1);
	
	cal_num 수정.

	semop(semid, &semclose, 1);
    }
    return 1;
}
