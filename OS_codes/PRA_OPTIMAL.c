#include <stdio.h>

int main()
{
    int i, j, k, n, f, max, pf = 0;
    int rs[25], frame[10], next[25];

    printf("\nEnter the length of reference string: ");
    scanf("%d", &n);

    printf("\nEnter the reference string: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &rs[i]);
    }

    printf("\nEnter no. of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        frame[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        int flag = 0;

        for (j = 0; j < f; j++)
        {
            if (frame[j] == rs[i])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {

            int flag1 = 0; 
            for (j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = rs[i];
                    flag1 = 1;
                    pf++;
                    break; 
                }
            }

            if (flag1 == 0)
            {
                max = -1;
                int index = 0;
                for (j = 0; j < f; j++)
                {
                    int found = 0;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == rs[k])
                        {
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0)
                    {
                        next[j] = n;
                    }
                    else
                    {
                        next[j] = k;
                    }
                    if (next[j] > max)
                    {
                        max = next[j];
                        index = j;
                    }
                }
                frame[index] = rs[i];
                pf++;
            }
        }

        printf("%d\t", rs[i]);
        for (j = 0; j < f; j++)
        {
            printf("%d\t", frame[j]);
        }

        if (flag == 0)
        {
            printf("PF No. %d", pf);
        }
        printf("\n");
    }
    int hit = n - pf;
    float hitr = 100*(float)hit/n;
    float miss = 100*(float)pf/n;
    printf("\nThe number of page faults using Optimal algorithm are %d\n", pf);
    printf("Total hit= %d\n", hit);
    printf("Hit ratio = %0.2f percentage\n", hitr);
    printf("Miss ratio = %0.2f percentage\n", miss);
    return 0;
}
