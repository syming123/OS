#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define BUFSZ 256
#define FLG IPC_CREAT | 0644

#define WAITING_MAX 13
#define SOFA_MAX 4
#define CHAIR_MAX 3
#define PAY_MAX 1

#define NOT_FULL 1
#define FULL 2

#define WAITING_QUEST 1
#define SOFA_QUEST 2
#define CHAIR_QUEST 3
#define PAY_QUEST 4
#define BARBER_PAY_QUEST 5
#define BARBER_CHAIR_QUEST 6
#define CUSTOMER 7
#define CUSTOMER_SUCCESS 8

#define SND_KEY 201
#define REC_KEY 202

/*信号灯控制用的共同体*/
typedef union semuns {
    int val;
} Sem_uns;

/* 消息结构体*/
typedef struct msgbuf {
    long mtype;
    int mid;
} Msg_buf;

int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);
