#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int array[75], num_of_frames, algo;
void fifo();
void optimal();
void lru();

int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; i++)
    {
        if (strcasecmp(argv[i], "-f") == 0)
        {
            FILE *fp = fopen(argv[i + 1], "r");
            if (fp == NULL)
            {
                printf("Can't open file: %s\n", argv[i + 1]);
                return 1;
            }
            int j = 0;
            while (fscanf(fp, "%x", &array[j]) == 1)
            {
                // printf("Test %X\n", array[j]);
                // printf("Value for hex: %d\n", array[j]);

                j++;
            }

            printf("\n");
            fclose(fp);
        }
        else if (strcasecmp(argv[i], "-n") == 0)
        {
            if (atoi(argv[i + 1]) <= 0)
            {
                printf("Frames must larger than 0, choose new number of frames: ");
                scanf("%d", &num_of_frames);
                if (atoi(argv[i + 1]) <= 0)
                {
                    printf("Are you stupid, frames must be bigger than zero, setting it to four\n");
                    num_of_frames = 4;
                }
            }
            else
            {
                num_of_frames = atoi(argv[i + 1]);
            }
        }
        else if (strcasecmp(argv[i], "-a") == 0)
        {
            algo = i + 1;
        }
    }
    
    if (strcasecmp(argv[algo], "fifo") == 0)
    {
        fifo();
    }
    else if (strcasecmp(argv[algo], "optimal") == 0)
    {
        optimal();
    }
    else if (strcasecmp(argv[algo], "lru") == 0)
    {
        lru();
    }
    else
    {
        printf("No such algorithm.");
    }

    return 0;
}

void fifo()
{

    for (int i = 0; i < 10; i++)
    {
        printf("Test %04X\n", array[i]);
        printf("Value for hex: %d\n", array[i]);
    }

    printf("fifo\n");
}

void optimal()
{
    printf("optimal\n");
}
void lru()
{
    printf("lru\n");
}
