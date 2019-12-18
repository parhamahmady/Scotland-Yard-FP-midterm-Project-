#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

int matrix[77][50]; //hole gameboard;
int w,l,ps,pm; //width,length,police starion,policemen;
int police_move,criminal_move;//a counter for polices and the criminal moves;
int criminal_x,criminal_y;//the location of the criminal;
int ps_catcher;// the police office that catch the criminal
bool end=false;
void police_diriction_first(int [77][50],int *,int *);//make the direction for the polices at first time;it can use for the criminal too;
void random_diriction(int [77][50],int i,int j,int *,int *);//make the next diriction for the police if they ps dont see the criminal;
void police_diriction(int [77][50],int i,int j,int *,int *);//make the next diriction for the police if they ps dont see the criminal;
void police_judge(int [77][50]);
void printer(int[77][50]);


int main () {
    printf("\t\t\t\t<<<<Welcome to the Scotland Yard>>>>\n\n");
    printf("\t\t\tPlease enter the lenght of your game board:\n");
    scanf("%d",&l);
    printf("\t\t\tPlease enter the width of your game board:\n");
    scanf("%d",&w);
    printf("\t\t\tPlease enter the number of your Police Stations:\n");
    scanf("%d",&ps);

    srand(time(NULL));

  

    for (int  i = 0; i < w; i++) // filling everywhere with -100;
    {
        for (int  j = 0; j < l; j++)
        {
            matrix[i][j]=-100;
        }
  
        
    }
    
    for (int psi = 1; psi <= ps; psi++)
    {
    int pmi=0;
    printf("\t\t\tPlease enter police number of the starion number %d :",psi);
    scanf("%d",&pmi);
    for (;pmi >0; pmi--)
    {
       int tempx=0,tempy=0;
      police_diriction_first(matrix,&tempx,&tempy);
      //printf("tempx: %d tempy: %d \n",tempx,tempy);
      matrix[tempx][tempy]=psi;
    }
    }
    int tempx=0,tempy=0;
    police_diriction_first(matrix,&tempx,&tempy);
    criminal_x=tempx;
    criminal_y=tempy;
    matrix[tempx][tempy]=0;
    printer(matrix);
    getchar();
  while(end==0)
  {
    police_judge(matrix);
    printer(matrix);
    
    getchar();
    getchar();
  }

}


void police_diriction_first(int x[77][50],int *p_tempx,int *p_tempy)
{
int temp_x;
int temp_y;
do
{
  temp_x=(int)(rand()%l);
  temp_y=(int)(rand()%w);
} while (x[temp_x][temp_y]!=-100);
*p_tempx=temp_x;
*p_tempy=temp_y;
}


void printer(int x[77][50])
{ system("cls");
  for (int i = 0; i < w; i++)
  {   
    for (int j = 0; j < l; j++)
    { 
      if (fabs(x[i][j])>0 && x[i][j]!=-100)
      { matrix[i][j]=fabs(matrix[i][j]);
        printf("\t D%d ",x[i][j]);

      }
      else
      {
        if (x[i][j]==0)
        {
          printf("\t T ");

        }
        else
        {
          printf("\t - ");

        }
        
        
      }
      
      
    }
    printf("\n\n");
  }
  
}


void random_diriction(int x[77][50],int i,int j,int *p_tempx,int *p_tempy)
{ 
  int temp_x,temp_y;
  do
  {
    temp_x=i+(int)((rand()%l)%3 - 1);
    temp_y=j+(int)((rand()%w)%3 - 1);
  } while(x[temp_x][temp_y]!=-100 && x[temp_x][temp_y]!=x[i][j]);
  *p_tempx=temp_x;
  *p_tempy=temp_y;
}

void police_diriction(int x[77][50],int i,int j,int *p_tempx,int *p_tempy)
{
  int temp_x;
  if(criminal_x-i);
  int temp_y=criminal_y-j;
  

}

void police_judge(int x[77][50])
{ int police_finder=0;
  for(int i=0 ; i < w ; i++ )
  {
    for(int j=0 ; j < l ; j++){
      if(x[i][j]>0)
      {
           float dtc= (float)sqrt((i-criminal_x)*(i-criminal_x) + (j-criminal_y)*(j-criminal_y));
           printf("%f",dtc);
           if(dtc<=2){
             int tempx,tempy;
             int number_ps=matrix[i][j];
             police_finder = x[i][j];
             if(dtc==(float)sqrt(2))
             { 
               tempx=criminal_x;
               tempy=criminal_y;
               //end=true;
               ps_catcher=matrix[i][j];
             }
             else
             {
              
             }
             matrix[i][j]!=matrix[tempx][tempy] ? police_move++ : police_move;
             matrix[i][j]=-100;
             matrix[tempx][tempy]=-number_ps;

           }
           else
           {
            int tempx,tempy;
            int number_ps=matrix[i][j];
            if(x[i][j]==police_finder)
            {
              
            }
            else
            {
            random_diriction(matrix,i,j,&tempx,&tempy);  
            
          //  printf("ps : %d , i : %d , j : %d , tempx : %d ,tempy : %d \n",number_ps,i,j,tempx,tempy);  
            }
          matrix[i][j]!=matrix[tempx][tempy] ? police_move++ : police_move;  
          matrix[i][j]=-100;
          matrix[tempx][tempy]=-number_ps;
           }
      }
      else
      {
        continue;
      }
    }
  }
}