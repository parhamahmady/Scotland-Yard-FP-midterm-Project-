#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <unistd.h>
#define red 4 
#define blue 1
#define green 2 
#define purple 5

int matrix[50][77] ; //hole gameboard;
int w,l,ps,pm; //width,length,police starion,policemen;
int criminal_x,criminal_y;//the location of the criminal;
int ps_finder[20]={0};//the police stations that know the direction of the criminal;
bool catched=false;
int  ps_move;
int  criminal_move;


void direction_first(int[50][77],int *,int*);
void ps_finder_cleaner(int[20]);
void ps_finder_printer(int[20]);
int wakieTakie(int,int);
void police_move(int,int,int,int);
void crime_move(int,int,int,int);
void police_direction(int[50][77],int,int,int *,int *);
void police_random_direction(int[50][77],int,int,int*,int*);
int police_judge(int[50][77]);
void criminal_random_direction(int*,int*);
int criminal_judge(void);
void direction_printer(void);
void SetColor(int);
void printer(int x[50][77]);


int main ()
{   SetColor(green);
    printf("\t\t\t\t<<<<Welcome to the Scotland Yard>>>>\n\n");
    printf("\t\t\tPlease enter the lenght of your game board:");
    scanf("%d",&l);
    printf("\n");
    printf("\t\t\tPlease enter the width of your game board:");
    scanf("%d",&w);
    printf("\n");
    printf("\t\t\tPlease enter the number of your Police Stations:");
    scanf("%d",&ps);
    printf("\n");

    srand(time(NULL));

    ps_finder_cleaner(ps_finder);

    for(int i=0 ; i<50 ; i++) // fill every where as -100;
    {
        for(int j=0 ; j<77; j++)
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
      direction_first(matrix,&tempx,&tempy);
      matrix[tempx][tempy]=psi;
    }
    }

    direction_first(matrix,&criminal_x,&criminal_y);
    matrix[criminal_x][criminal_y]=0;
    //direction_printer();
    printer(matrix);
   // printf("\t\t\tReady!\n");
    // getchar();
    // getchar();
    sleep(2);
    /////////////////////////////////
    
    while(true)
    {   ps_finder_cleaner(ps_finder);
        //printf("started\n");
        police_judge(matrix);
       // sleep(0.5);
       // printf("criminal time\n");
        //direction_printer();
         if(!catched){
        criminal_judge();}
        else{
            break;
        }
        //direction_printer();
        printer(matrix);

    if(matrix[criminal_x][criminal_y]!=0)
    {
        break;
    }
    sleep(2);
    // printf("Press enter to continue");
    // getchar();
    }
    // getchar();
    sleep(2);
    //system("cls");
    SetColor(green);
 //   ps_finder_printer(ps_finder);
    printf("\n\t\t\t Criminal moves : %d ",criminal_move);
    printf("\n\t\t\t Police moves : %d", ps_move);
   // direction_printer();
    printf("\n\n\t\t\t\tFinish");

}


//graphical zone;

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

void printer(int x[50][77])
{ system("cls");
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
         {  SetColor(red);
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

void direction_printer(void)
{
    for(int j=0 ; j<50 ; j++)
    {   
        for(int i=0 ; i<77 ; i++)
        {
            if(matrix[j][i]!=-100)
            {   
                SetColor(purple);
                printf("i: %d , j: %d ,owner: %d\n",j,i,matrix[j][i]);
            }
        }
    }
}

//making place for everyone;


void direction_first(int x[50][77],int *p_tempx,int *p_tempy)
{
int temp_x;
int temp_y;
do
{
  temp_x=(int)(rand()%w);
  temp_y=(int)(rand()%l);
} while (x[temp_x][temp_y]!=-100);
*p_tempx=temp_x;
*p_tempy=temp_y;
}


//police zone;

void police_move (int i,int j,int x,int y)
{
     
     if(i==x)
     {
         if(j==y)
         {
             return;
         }
         else
         {
             ps_move++;
         }
     }
     else
     {
         ps_move ++;
     }
}

void ps_finder_cleaner (int x[20])
{
    for(int i=0 ; i < 20 ; i++)
    {
        x[i]=0;
    }
}

void ps_finder_printer(int x[20])
{
    for(int i=0 ; i < 20 ; i++)
    {   if(x[i]!=0)
        printf(" %d: %d ",i,x[i]);
    }
}

int walkieTalkie (int i,int j)
{
	int ps_number_temp=fabs(matrix[i][j]);
	float dtc=(float)sqrt( (int)pow(i-criminal_x,2) + (int)pow(j-criminal_y,2) );
    //printf("owner: %d , dtc: %f\n",matrix[i][j],dtc);
	if (dtc<=2*(float)sqrt(2)){
		ps_finder[ps_number_temp]=ps_number_temp;
        // ps_finder_printer(ps_finder);
    	}
	if(ps_finder[ps_number_temp]==ps_number_temp)
		{
		if(dtc<=(float)sqrt(2)){
			return 1;}
		
			else{
			return 2;}}
	else 	
		{return 0;}
			
}

void police_direction(int x[50][77],int i,int j,int *p_tempx,int *p_tempy)
{  
     int dir_x=criminal_x-i;
     int dir_y=j-criminal_y;
     int s=i;
     int y=j;
     if(dir_x>0)
     {
        if(x[s+1][y]==-100){
            (*p_tempx)++;
            s++;
        }
     }
     else
     {  if(dir_x<0)
        {
          if(x[s-1][y]==-100){
            (*p_tempx)--;
            s--;
            }
          }
        }
    if(dir_y<0)
     {
        if(x[s][y+1]==-100){
            (*p_tempy)++;
            y++;

        }
     }
     else
     {  if(dir_y>0)
        {
          if(x[s][y-1]==-100){
            (*p_tempy)--;
            y--;
          }
        }
     }
}

void police_random_direction(int x[50][77],int i,int j,int *p_tempx,int *p_tempy)
{
    int temp_x,temp_y;
    while(true)
    {
    
    temp_x=i+(((int)(rand()%w)%3)-1);
    temp_y=j+(((int)(rand()%l)%3)-1);
    if(temp_x>=w || temp_y >=l || (x[temp_x][temp_y]<0 && x[temp_x][temp_y]!=-100) || temp_x <0 || temp_y <0 || x[temp_x][temp_y]>0 );
    else
    {
        break;
    }
    }
   // printf(" i: %d , j: %d , tempx: %d , tempy: %d , owner: %d\n",i,j,temp_x,temp_y,x[i][j]);
    *p_tempx=temp_x;
    *p_tempy=temp_y;

}

int police_judge(int x[50][77])
{   int tempx,tempy;    
    tempx=tempy=0;
    int ps_number;
    for(int i=0 ; i<w ; i++)
    {
        for(int j=0 ; j<l ; j++)
        {    tempx=i;
            tempy=j;
            if(matrix[i][j]>0)
            {   ps_number=matrix[i][j];
                switch (walkieTalkie(i,j))
                {
                    case 1: //time to catch;
                     if(matrix[criminal_x][criminal_y]==0)
                         { 
                       // SetColor(purple);
                        tempx=criminal_x;
                        tempy=criminal_y;      
                               }
                        break;
                    case 2: // a little bit closer;
                      police_direction(matrix,i,j,&tempx,&tempy);
                       // police_random_direction(matrix,i,j,&tempx,&tempy);
                        break;
                    case 0: //random move;
                           // SetColor(blue);
                            police_random_direction(matrix,i,j,&tempx,&tempy);
                        break;
                }
             //  printf(" i: %d , j: %d , tempx: %d , tempy: %d , owner: %d\n",i,j,tempx,tempy,x[i][j]);
                matrix[i][j]=-100;
                matrix[tempx][tempy]=-ps_number;
                police_move(i,j,tempx,tempy);
                if(matrix[criminal_x][criminal_y]!=0)
                {
                    catched=true;
                    printer(matrix);
                    return 0;
                }
            }
        }
    }
    
}


// criminal zone;

void crime_move (int i,int j,int x,int y)
{
     
     if(i==x)
     {
         if(j==y)
         {
             return;
         }
         else
         {
             criminal_move++;
         }
     }
     else
     {
         criminal_move++;
     }
}

void criminal_random_direction(int *p_tempx,int *p_tempy)
{
    int temp_x,temp_y;
    while(true)
    {
    temp_x=criminal_x+((rand()%3)-1);
    temp_y=criminal_y+((rand()%3)-1);
    if(temp_x>=w || temp_y>=l || temp_y<0 || temp_x<0 || ( temp_x==criminal_x && temp_y==criminal_y ) );
    else{
        break;
        }
    }
    *p_tempx=temp_x;
    *p_tempy=temp_y;
}

int criminal_judge(void)
{
    int tempx,tempy;
    criminal_random_direction(&tempx,&tempy);
    crime_move(criminal_x,criminal_y,tempx,tempy);
   // printf(" i: %d , j: %d , tempx: %d , tempy: %d \n",criminal_x,criminal_y,tempx,tempy);
    if(criminal_x==tempx && criminal_y==tempy)
    {
        if(matrix[tempx][tempy]!=0)
        {
            return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(matrix[tempx][tempy]>0)
        {
            if(matrix[criminal_x][criminal_y]!=0)
            {
                return 0;
            }
            else
            {
                matrix[criminal_x][criminal_y]=-100;
                criminal_x=tempx;
                criminal_y=tempy;
            }
        }
        else
        {
            if(matrix[criminal_x][criminal_y]!=0)
            {
                return 0;
            }
            else
            {
                 matrix[criminal_x][criminal_y]=-100;
                criminal_x=tempx;
                criminal_y=tempy;
                matrix[criminal_x][criminal_y]=0;
            }
        }
    }
}