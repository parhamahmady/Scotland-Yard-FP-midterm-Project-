#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int w,l,ps,pm;
int matrix[77][50];
int rnd(bool);
int direction_maker(int [77][50]);
bool direction_check(int[77][50],int,int);

int main () {
    printf("<<<<Welcome to the Scotland Yard>>>>\n\n");
    printf("Please enter the lenght of your game board:\n");
    scanf("%d",&l);
    printf("Please enter the width of your game board:\n");
    scanf("%d",&w);
    printf("Please enter the number of your Police Stations:\n");
    scanf("%d",&ps);

    srand(time(NULL));

    int matrix[l][w]; //hole gameboard;

    for (int  i = 0; i < w; i++) // filling everywhere with 0;
    {
        for (int  j = 0; j < l; j++)
        {
            matrix[i][j]=0;
          //  printf("0");
        }
       // printf("\n");
        
    }

    for (int psi = 1; psi <= ps; psi++)
    {
    int pmi=0;
    printf("Please enter police number of the starion number : %d",psi);
    scanf("%d",&pmi);
    for (; pmi >=0; pmi--)
    {
        
    }

    }
    
    

}

int rnd (bool hrz) {
    if (hrz) {
        return rand()%w;
    }
    else {
        return rand()%l;
    }
}


bool direction_check(int matrix[l][w],int x,int y)
{
    if(matrix[x][y]==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

int direction_maker(int matrix[l][w])
{
    int tempx=0;
    int tempy=0;
    do 
    {
    tempy = rnd(true);
    tempx = rnd(false);
    }while(!direction_check(matrix[l][w],tempx,tempy));
    

}
