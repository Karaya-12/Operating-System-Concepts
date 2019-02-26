#include "ipc.h"

int main(int argc, char*argv[])
{
    common_setup();

    //Mutex Semaphore of The Smokers --> Only One Smoker is Available At One Time
    sem_num = 1;
    //Get The Mutex Synchronizing Semaphore of The Smokers
    smtx_sem = set_sem(smtx_key, sem_num, sem_flg);

    if ((pid[0] = fork()) == 0)  //The First Smoker Process --> Tobacco Possessed
    {
        char smoker_possess = 'T';  //Initially Had Tobacco
        while (1)  //Simulating The Smokers Keep Smoking
        {
            //If Buffer is Empty --> Hold Off Smokers
            down(smok_sem);

            if (!(smoker_possess != buff_ptr[0] && smoker_possess != buff_ptr[1]))
            {   //If Current Smoker Got Tobacco --> Wake Up Current Smoker
                up(smok_sem);  //Wake Up Holding off Smokers
                continue;
            }

            printf("Smoker No.1 Got Tobacco --> Get Glue & Paper    --> Smoking !\n");
            sleep(1);

            //Wake Up Stucked Providers
            up(prod_sem);
        }
    }
    else
    {
        if ((pid[1] = fork()) == 0)  //The Second Smoker Process --> Paper Possessed
        {
            char smoker_possess = 'P';
            while (1)  //Simulating The Smokers Keep Smoking
            {
                //If Buffer is Empty --> Hold Off Smokers
                down(smok_sem);

                if (!(smoker_possess != buff_ptr[0] && smoker_possess != buff_ptr[1]))
                {   //If Current Smoker Got Paper --> Wake Up Current Smoker
                    up(smok_sem);  //Wake Up Holding off Smokers
                    continue;
                }

                printf("Smoker No.2 Got Paper   --> Get Glue & Tobacco  --> Smoking !\n");
                sleep(1);

                //Wake Up Stucked Providers
                up(prod_sem);
            }
        }
        else  //The Third Smoker Process --> Glue Possessed
        {
            char smoker_possess = 'G';
            while (1)  //Simulating The Smokers Keep Smoking
            {
                //If Buffer is Empty --> Hold Off Smokers
                down(smok_sem);

                if (!(smoker_possess != buff_ptr[0] && smoker_possess != buff_ptr[1]))
                {   //If Current Smoker Got Glue --> Wake Up Current Smoker
                    up(smok_sem);  //Wake Up Holding off Smokers
                    continue;
                }

                printf("Smoker No.3 Got Glue    --> Get Tobacco & Paper --> Smoking !\n");
                sleep(1);

                //Wake Up Stucked Providers
                up(prod_sem);
            }
        }
    }
}
