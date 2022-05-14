#include "ipc.h"


int waiting = 0;
int sofa = 0;
int chair = 0;
int pay = 0;

//msg_1_id
int snd_id;
int rec_id;

int main(int argc, char *argv[])
{
    Msg_buf msg_arg;
    int wait_time = 1;
    int count = 0;

    snd_id = set_msq(SND_KEY,FLG);
    rec_id = set_msq(REC_KEY,FLG);

    if(argc > 1) {
        wait_time = atoi(argv[1]);
    }

    while (1)
    {
        while(msgrcv(snd_id,&msg_arg,sizeof(msg_arg.mid),CUSTOMER_SUCCESS,IPC_NOWAIT) >= 0) 
        {
            printf("%d customer cut and pay success\n",msg_arg.mid);
        }
        msg_arg.mtype = CUSTOMER;
        msg_arg.mid = count;
        msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), 0);
        msgrcv(snd_id,&msg_arg,sizeof(msg_arg.mid),CUSTOMER,0);
        if(msg_arg.mid == FULL)
        {
            printf("%d can not enter because already full\n",count);
        }
        else
        {
            printf("%d enter\n",count);
        }
        count++;
        sleep(wait_time);
    }
}