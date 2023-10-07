#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 256

int array[MAX], num_of_frames, algo, num_of_inputs;

void fifo(int x, int y);
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
            num_of_inputs = j;

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
        fifo(num_of_frames, num_of_inputs);
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

void fifo(int max_num_of_frames, int num_of_inputs)
{
    int pages[MAX], number_of_frames_created = 0, oldest_frame = 0;
    int frames[4];

    // Hitta vilken page nummret tillhör
    for (int i = 0; i < num_of_inputs; i++)
    {
        int k = array[i] / 256;
        bool cont = true;

        if (number_of_frames_created == 0)
        {
            printf("Adress %04x is not in physical memory\n", array[i]);
            printf("Page %d paged in\n", k);
            frames[number_of_frames_created] = k;
            number_of_frames_created++;
            continue;
        }

        for (int j = 0; j < number_of_frames_created; j++)
        {
            if (k == frames[j])
            {
                printf("Adress %04x is on page %d which is already in physical memoroy\n", array[i], k);
                // number_of_frames_created++;
                //  Tilldelning till befintlig sida.
                cont = false;
            }
        }

        if (cont)
        {
            if (number_of_frames_created < max_num_of_frames)
            {
                printf("Adress %04x is not in physical memory\n", array[i]);
                printf("Page %d paged in\n", k);
                frames[number_of_frames_created] = k;
                number_of_frames_created++;
            }
            else
            {
                // Ta ersätt första sidan med nya k värdet.
                printf("Adress %04x is not in physical memory\n", array[i]);
                printf("Page %d paged out\n", frames[oldest_frame]);
                printf("Page %d paged in\n", k);
                frames[oldest_frame] = k;
                if (oldest_frame = max_num_of_frames)
                {
                    oldest_frame = 0;
                }
                else
                {
                    oldest_frame++;
                }
            }
        }

        // printf("Address 0X%04x is in page %d\n", array[i], k);
    }

    /*for (int i = 0; i < num_of_inputs; i++)
    {
        if (array[i] == 0)
        {
            break;
        }
        // printf("Value for hex: %d\n", array[i]);

        if (number_of_frames_created != 0)
        {
            for (int j = 0; j < number_of_frames_created; j++)
            {
                if (array[i] > pages[j] && array[i] < (pages[j] + 255))
                {
                    pages[number_of_frames_created] = array[i];
                    printf("HEX 0x%04X med värde %d från array[%i] har placerats på sida %d\n", array[i], array[i], i, j);
                    break;
                }
            }
        }
        else
        {
            pages[number_of_frames_created] = array[i];
            printf("Page %d har skapats för HEX 0x%04X med värde %d.\n", number_of_frames_created, array[i], array[i]);
            number_of_frames_created++;
        }

        // if (number_of_frames_created < max_num_of_frames && frames[number_of_frames_created] == 0)
        if (number_of_frames_created < max_num_of_frames)
        {
            pages[number_of_frames_created] = array[i];
            printf("Sida %d har skapats för HEX 0x%04X med värde %d.\n", number_of_frames_created, array[i], array[i]);
            number_of_frames_created++;
        }
        else if (number_of_frames_created == max_num_of_frames)
        {
            // Skapa parameter med namn "oldest frame som ökar varje gång upp till max frame"
            pages[number_of_frames_created - max_num_of_frames] = array[i];
        }
    }*/
}

void optimal()
{
    printf("optimal\n");
}
void lru()
{
    printf("lru\n");
}
