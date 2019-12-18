#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#define red 4 
#define blue 1
#define green 2 

int matrix[77][50] = { -100 }; //hole gameboard;
int w,l,ps,pm; //width,length,police starion,policemen;
int police_move,criminal_move;//a counter for polices and the criminal moves;
int criminal_x,criminal_y;//the location of the criminal;
int ps_catcher;// the police office that catch the criminal
int ps_finder[20];//the offices that know the diriction of the criminal;
bool end=false;
void police_diriction_first(int [77][50],int *,int *);//make the direction for the polices at first time;it can use for the criminal too;
void police_random_diriction(int [77][50],int i,int j,int *,int *);//make the next diriction for the police if they ps dont see the criminal;
void police_diriction(int [77][50],int i,int j,int *,int *);//make the next diriction for the police if they ps dont see the criminal;
void ps_finder_cleaner(int[]);
int  walkieTalkie (int,int);
void police_judge(int [77][50]);
void criminal_random_diriction(int[77][50],int ,int ,int *,int *);
void criminal_judge(void);
void SetColor(int);
void printer(int[77][50]);


int main () {SetColor(green);
    printf("\t\t\t\t<<<<Welcome to the Scotland Yard>>>>\n\n");
    printf("\t\t\tPlease enter the lenght of your game board:\n");
    scanf("%d",&l);
    printf("\t\t\tPlease enter the width of your game board:\n");
    scanf("%d",&w);
    printf("\t\t\tPlease enter the number of your Police Stations:\n");
    scanf("%d",&ps);

    srand(time(NULL));

    
    ps_finder_cleaner(ps_finder);
  

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
    printf("\t\t\tPlease enter police number of the station number %d :",psi);
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
      //sleep(500);
    getchar();
    printf("ready");
    getchar();
  while(true)
  { 
    ps_finder_cleaner(ps_finder);
    
   police_judge(matrix);
    //printer(matrix);
    //  getchar();
    criminal_judge();
   
   // getchar();
    
    printer(matrix);
    printf("criminal_x : %d,criminal_y : %d \n",criminal_x,criminal_y);
    getchar();
    if(matrix[criminal_x][criminal_y]!=0)
        break;
  }
    printf("finish");
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

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void printer(int x[77][50])
{ //system("cls");
  for (int i = 0; i < w; i++)
  {   
    for (int j = 0; j < l; j++)
    { 
      if (fabs(x[i][j])>0 && x[i][j]!=-100)
      { matrix[i][j]=fabs(matrix[i][j]);
        SetColor(blue);
        printf("\t D%d ",x[i][j]);

      }
      else
      {
        if (x[i][j]==0)
        {   SetColor(red);
          printf("\t T ");

        }
        else
        {   SetColor(green);
          printf("\t - ");

        }
        
        
      }
      
      
    }
    printf("\n\n");
  }
  
}


void police_random_diriction(int x[77][50],int i,int j,int *p_tempx,int *p_tempy)
{ 
  int temp_x,temp_y;
  bool same=false;
  do
  {
    temp_x=fabs(i+(int)((rand()%l)%3 - 1));
    temp_y=fabs(j+(int)((rand()%w)%3 - 1));
    if(temp_x == i)
    {
       if(temp_y == j )
            same = true;
    }
  } while((x[temp_x][temp_y]!=-100 && !same) || temp_x >l || temp_y >w || (x[temp_x][temp_y] < 0 && x[temp_x][temp_y]!=-100) );
  *p_tempx=temp_x;
  *p_tempy=temp_y;
}

void police_diriction(int x[77][50],int i,int j,int *p_tempx,int *p_tempy)
{
     int dir_x=criminal_x-i;
     int dir_y=criminal_y-j;
     if(dir_x>0)
     {
        if(x[i++][j]==-100){
            (*p_tempx)++;
        }
     }
     else
     {
          if(x[i--][j]==-100){
            (*p_tempx)--;
          }
        }
    if(dir_y>0)
     {
        if(x[i][j++]==-100){
            (*p_tempy)++;
        }
     }
     else
     {
          if(x[i][j--]==-100){
            (*p_tempy)--;
        }
     }

  

}

void ps_finder_cleaner (int x[])
{
    for(int i=0 ; i < ps ; i++)
    {
        x[i]=0;
    }
}

int walkieTalkie (int  i,int j)
{
	
	float dtc=(float)sqrt( pow(i-criminal_x,2) + pow(j-criminal_y,2) );
	if (dtc<=2){
		ps_finder[matrix[i][j]]=matrix[i][j];
		}
	if(ps_finder[matrix[i][j]]==matrix[i][j])
		{
		if(dtc<=(float)sqrt(2)){
			return 1;}
		
			else{
			return 2;}}
	else 	
		{return 0;}
			
}


void police_judge(int x[77][50])
{ 

  for( int i=0 ; i < w ; i++ )
  {
    
    for( int j=0; j < l ; j++){
      if(x[i][j]>0)
      {
        int ps_number=matrix[i][j]; // save the number of the police station who is moving ;
        int tempx,tempy;
        tempx=tempy=0;
        //printf("i:%d , j:%d\n",i,j);
        switch(walkieTalkie(i,j))
        {
	        case 1: // its time to catch;

                tempx=criminal_x;
                tempy=criminal_y;        

	        break;

	        case 2: // just need to get a little closer;

               police_diriction(matrix,i,j,&tempx,&tempy);

	        break;
	        case 0: //random moving;

            police_random_diriction(matrix,i,j,&tempx,&tempy);

	        break;
          
                    }	
             // police_random_diriction(matrix,i,j,&tempx,&tempy);
            //printf("ps : %d i : %d , j : %d , x: %d , y: %d\n ",fabs(matrix[tempx][tempy]),i,j,tempx,tempy);
          matrix[i][j]=-100;
          matrix[tempx][tempy]=-ps_number;
          
          // matrix[i][j]!=matrix[tempx][tempy] ? police_move++ : police_move; 
      }
      else
      {
        continue;
      }
    }
  }
}


///criminal zone;

void criminal_random_diriction(int x[77][50],int i,int j,int *p_tempx,int *p_tempy)
{
  int temp_x,temp_y;
  do{
    temp_x=fabs(i+(int)((rand()%(l))%3 - 1));
    temp_y=fabs(j+(int)((rand()%(w))%3 - 1));
  }while( temp_y >=w || temp_x >= l);
    *p_tempx=temp_x;
    *p_tempy=temp_y;
}

void criminal_judge(void)
{
    int tempx,tempy;
    tempx=criminal_x;
    tempy=criminal_y;
    criminal_random_diriction(matrix,criminal_x,criminal_y,&criminal_x,&criminal_y);
    if( matrix[tempx][tempy] == 0 )
    {
    matrix[tempx][tempy]=-100;}
    
     matrix[criminal_x][criminal_y]=0;
    
    //printf("criminal_x : %d,criminal_y : %d \n",criminal_x,criminal_y);
    //matrix[tempx][tempy] == matrix[criminal_x][criminal_y] ? criminal_move++ : criminal_move;
}
