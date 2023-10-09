#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 256

int array[MAX], num_of_frames, algo, num_of_inputs;
int mem_acc = 0;
int p_hits = 0;
int p_faults = 0;
int p_replacements = 0;

void fifo(int x, int y);
void optimal();
void lru();
void print(char *);

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

    printf("Running simulation...\n\n");
    int number_of_frames_created = 0, oldest_frame = 0;
    int frames[4];
    // int pages[MAX]

    // Hitta vilken page nummret tillhör
    for (int i = 0; i < num_of_inputs; i++)
    {
        int k = array[i] / 256;
        bool cont = true;


        //First time something comes to memory, page it in
        if (number_of_frames_created == 0)
        {
            printf("Adress %04x is not in physical memory\n", array[i]);
            printf("Page %d paged in\n", k);
            frames[number_of_frames_created] = k;
            oldest_frame=k;
            number_of_frames_created++;
            mem_acc++;
            p_faults++;
            continue;
        }

        for (int j = 0; j < number_of_frames_created; j++)
        {
            if (k == frames[j])
            {
                printf("Adress %04x is on page %d which is already in physical memoroy\n", array[i], k);
                // number_of_frames_created++;
                //  Tilldelning till befintlig sida.
                p_hits++;
                mem_acc++;
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
                mem_acc++;
                p_faults++;
            }
            else
            {
                // Ta ersätt första sidan med nya k värdet.
                printf("Adress %04x is not in physical memory\n", array[i]);
                printf("Page %d paged out\n", frames[oldest_frame]);
                printf("Page %d paged in\n", k);
                mem_acc++;
                p_faults++;
                p_replacements++;
                frames[oldest_frame] = k;
                if (oldest_frame == max_num_of_frames-1)
                {
                    oldest_frame = 0;
                }
                else
                {
                    oldest_frame++;
                }
            }
        }
    }
  
    


    print("FIFO");

}

void optimal()
{
    print("Optimal");
}
void lru()
{
    print("LRU");
}
void print(char alg[]){
    
    printf("\nRunning simulation...Done.\n");
    
    printf("\nSimulation summary\n\n");
    printf("%-25s %s\n", "Algorithm:", alg);
    printf("%-25s %d\n", "Frames:", num_of_frames);
    printf("%-25s %d\n", "Memory accesses:", mem_acc);
    printf("%-25s %d\n", "Page hits:", p_hits);
    printf("%-25s %d\n", "Page faults:", p_faults);
    printf("%-25s %d\n", "Page replacements", p_replacements);
}
