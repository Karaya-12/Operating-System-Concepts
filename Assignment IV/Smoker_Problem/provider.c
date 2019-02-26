#include "ipc.h"

int main(int argc, char* argv[])
{
    common_setup();

    srand((unsigned)time(NULL));

    int count = 0;
    while (1)  //Simulating The Providers Keep Providing Essential Metarials
    {
        //If Buffer is Full --> Providers Get Stucked
        down(prod_sem);

        if (count == 0) {
            buff_ptr[0] = 'T';
            printf("Provider A: Tobacco,  ");
            buff_ptr[1] = 'G';
            printf("Provider B: Glue...\n");
        }
        if (count == 1) {
            buff_ptr[0] = 'G';
            printf("Provider A: Glue,     ");
            buff_ptr[1] = 'P';
            printf("Provider B: Paper...\n");
        }
        if (count == 2) {
            buff_ptr[0] = 'P';
            printf("Provider A: Paper,    ");
            buff_ptr[1] = 'T';
            printf("Provider B: Tobacco...\n");
        }
        count++;
        count = count % 3;

        //Wake Up The Stucked Smokers
        up(smok_sem);
    }
    return EXIT_SUCCESS;
}
