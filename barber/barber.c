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
    int cut_time = 1,pay_time = 1;

    snd_id = set_msq(SND_KEY,FLG);
    rec_id = set_msq(REC_KEY,FLG);

    if(argc > 1) {
        cut_time = atoi(argv[1]);
        if(argc > 2)
            pay_time = atoi(argv[2]);
    }

    while (1)
    {
        if(msgrcv(snd_id,&msg_arg,sizeof(msg_arg.mid),BARBER_PAY_QUEST,IPC_NOWAIT) >= 0)
        {
            msg_arg.mtype = BARBER_PAY_QUEST;
            sleep(pay_time);
            msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
            printf("%d costomer pay to %d barber \n",msg_arg.mid,getpid());
        }
        if(msgrcv(snd_id,&msg_arg,sizeof(msg_arg.mid),BARBER_CHAIR_QUEST,IPC_NOWAIT) >= 0)
        {
            msg_arg.mtype = BARBER_CHAIR_QUEST;
            sleep(cut_time);
            msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
            printf("%d costomer cutted by %d barber \n",msg_arg.mid,getpid());
        }
    }
    
}