#include <stdlib.h>
#include <stdio.h>

void    click(int x, int y, int *row, int *col)
{
    if (x >= 100 && x <= 300)
        *col = 0;
    if (x >= 310 && x <= 500)
        *col = 1;
    if (x >= 510 && x <= 700)
        *col = 2;
    if (y >= 100 && y <= 300)
        *row = 0;
    if (y >= 310 && y <= 500)
        *row = 1;
    if (y >= 510 && y <= 700)
        *row = 2;
}

int is_win(int **plat)
{
    int count;
    for (int i = 1; i <= 2; i++)
    {
        count = 0;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c  < 3; c++)
            {
                if (plat[r][c] == i)
                    count++;
            }
            if (count == 3)
                return (i);
            count = 0;
        }
    }
    for (int i = 1; i <= 2; i++)
    {
        count = 0;
        for (int c = 0; c < 3; c++)
        {
            for (int r = 0; r  < 3; r++)
            {
                if (plat[r][c] == i)
                    count++;
            }
            if (count == 3)
                return (i);
            count = 0;
        }
    }
    for (int i = 1; i <= 2; i++)
    {
        if ((plat[0][0] == i && plat[1][1] == i && plat[2][2] == i) || (plat[0][2] == i && plat[1][1] == i && plat[2][0] == i))
            return (i);
    }
    return (0);
}

int board(int **plat,int col, int row, int forme)
{
    if (plat[col][row] != 0)
        return (-1);
    plat[col][row] = forme;
    return (1);
}
/*
int main(void)
{
    int **plat;
    int res;

    plat = malloc(sizeof(int*) * 3);
    if(!plat)
    {
        free(plat);
        return (1);
    }
    for (int i = 0; i < 3; i++)
    {
        plat[i] = calloc(3, sizeof(int));;
        if (!plat[i])
        {
            for (int j = 0; j < i; j++)
                free(plat[j]);
            free(plat);
            return(1);
        }
    }
    plat[0][2] = 2;
    plat[1][1] = 2;
    plat[2][0] = 2;
    res = is_win(plat);
    printf("%d\n", res);
}
*/