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

    snd_id = set_msq(SND_KEY,FLG);
    rec_id = set_msq(REC_KEY,FLG);

    printf("control start...\n");
    while (1)
    {
        //barber finished
        if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),BARBER_PAY_QUEST,IPC_NOWAIT) >= 0) 
        {
            pay--;
            printf("%d customer payed and leave\n",msg_arg.mid);
            msg_arg.mtype = CUSTOMER_SUCCESS;
            msgsnd(snd_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
        }
        if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),BARBER_CHAIR_QUEST,IPC_NOWAIT) >= 0) 
        {
            chair--;
            printf("%d customer cutted\n",msg_arg.mid);
            msg_arg.mtype = PAY_QUEST;
            msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
        }

        //pay
        while(pay < PAY_MAX)
        {
            if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),PAY_QUEST,IPC_NOWAIT) >= 0)
            {
                pay++;
                msg_arg.mtype = BARBER_PAY_QUEST;
                msgsnd(snd_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
            }
            else break;
        }

        //sofa to chair and cut
        while (chair < CHAIR_MAX)
        {
            if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),CHAIR_QUEST,IPC_NOWAIT) >= 0)
            {
                chair++;
                sofa--;
                msg_arg.mtype = BARBER_CHAIR_QUEST;
                msgsnd(snd_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
                printf("%d customer sit on the chair\n",msg_arg.mid);
            }
            else break;
        }

        //sofa
        while (sofa < SOFA_MAX)
        {
            if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),SOFA_QUEST,IPC_NOWAIT) >= 0)
            {
                sofa++;
                waiting--;
                msg_arg.mtype = CHAIR_QUEST;
                msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
                printf("%d customer sit on the sofa\n",msg_arg.mid);
            }
            else break;
        }

        //waiting
        while (waiting < WAITING_MAX)
        {
            if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),WAITING_QUEST,IPC_NOWAIT) >= 0)
            {
                waiting++;
                msg_arg.mtype = SOFA_QUEST;
                msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
                printf("%d customer go into the waitingroom\n",msg_arg.mid);
            }
            else break;
        }

        //enter
        if(msgrcv(rec_id,&msg_arg,sizeof(msg_arg.mid),CUSTOMER,IPC_NOWAIT) >= 0)
        {
            if(waiting < WAITING_MAX)
            {
                msg_arg.mtype = WAITING_QUEST;
                msgsnd(rec_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);

                msg_arg.mtype = CUSTOMER;
                msg_arg.mid = NOT_FULL;
                msgsnd(snd_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
            }
            else
            {
                msg_arg.mtype = CUSTOMER;
                msg_arg.mid = FULL;
                msgsnd(snd_id, &msg_arg, sizeof(msg_arg.mid), IPC_NOWAIT);
            }
        
        }
    }
}