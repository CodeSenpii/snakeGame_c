#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<stdbool.h>

#define ROW 20
#define COL 40

int trackHead_r,trackHead_c;
int place_xr,place_xc;
bool x_on_grid = false;
int collision_count,tail_segment;
int lastTailSegmentAdd_r, lasttailSegmentAdd_c;
int trackTail_r,trackTail_c;
int tail_r[50]={0},tail_c[50]={0};

enum move
{
    STOP,LEFT,RIGHT,UP,DOWN,ENDGAME
}direction;

//void move_snakeHL();
//void move_snakeHR();
//void move_snakeHU();
//void move_snakeHD();
void snake_direction(enum move dir);
void place_x();
void collision_x();
void endgame();
void insert_tailsegment();
void move_tail_segments();
void remove_plus();


void print_grid();


char grid[ROW][COL]=
{
"***************************************",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                o                    *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"*                                     *",
"***************************************"};

int main()
{
trackHead_r=9;
trackHead_c=17;
collision_count=0;
tail_segment=0;
lasttailSegmentAdd_c=0;
lastTailSegmentAdd_r=0;
trackTail_r=9;
trackTail_c=17;
char ch;

direction = STOP;
int i,counter=50;

        print_grid();


    while(direction!=ENDGAME)
    {

          // endgame();
           place_x();

            //if(_kbhit())

              switch(ch=_getch())
            {
                case ',':
                    {
                        //move_snakeHL();
                        direction = LEFT;
                        break;
                    }
                case '.':
                    {
                        //move_snakeHR();
                        direction = RIGHT;
                        break;
                    }
                case 'l':
                    {
                       // move_snakeHU();
                       direction = UP;
                        break;
                    }
                case '/':
                    {
                        //move_snakeHD();
                        direction = DOWN;
                        break;
                    }
                default:;

           }

        system("cls");
        snake_direction(direction);
        //insert_tailsegment();
        remove_plus();

        trackTail_r=trackHead_r;
        trackTail_c=trackHead_c;

        move_tail_segments();



        endgame();
        print_grid();
        Sleep(300);


        collision_x();
    }


 return 0;
}
/*void move_snakeHL()
{
    direction = LEFT;
    grid[trackHead_r][trackHead_c]=' ';
    grid[trackHead_r][trackHead_c-1]='o';
    trackHead_c--;
}
void move_snakeHR()
{
    direction = RIGHT;
    grid[trackHead_r][trackHead_c]=' ';
    grid[trackHead_r][trackHead_c+1]='o';
    trackHead_c++;
}

void move_snakeHU()
{
   direction = UP;
   grid[trackHead_r][trackHead_c]=' ';
   grid[trackHead_r-1][trackHead_c]='o';
   trackHead_r--;
}
void move_snakeHD()
{
    direction = DOWN;
    grid[trackHead_r][trackHead_c]=' ';
    grid[trackHead_r+1][trackHead_c]='o';
    trackHead_r++;
}*/
void print_grid()
{
    int i;
    for(i=0;i<ROW;i++)
        {
            printf("%s\n",grid[i]);
        }
        for(i=0;i<collision_count;i++)
        {
            printf("%02d ",tail_r[i]);
        }
        putchar('\n');
        for(i=0;i<collision_count;i++)
        {
            printf("%02d ",tail_c[i]);
        }
        printf("\nHr: %d Hc: %d Trow:%d Tcol: %d\n",trackHead_r,trackHead_c,trackTail_r,trackTail_c);
}
void place_x()
{
    if(x_on_grid==false)
    {
        srand((unsigned)time(NULL));
        place_xr =rand()%19;
        place_xc= rand()%38;

        if(place_xr == 0)
            place_xr++;
        if(place_xc==0)
            place_xc++;

        grid[place_xr][place_xc]='x';
        x_on_grid = true;

    }
}
void collision_x()
{
   if(grid[trackHead_r][trackHead_c]==grid[place_xr][place_xc])
    {
       collision_count++;

       x_on_grid = false;

       if (direction == LEFT)
       {
          // grid[trackHead_r][trackHead_c+1]='+';
           tail_c[tail_segment]=trackHead_c+1;
           tail_r[tail_segment]=trackHead_r;
           lasttailSegmentAdd_c=tail_c[tail_segment];
           lastTailSegmentAdd_r=tail_r[tail_segment];
       }
       if (direction == RIGHT)
       {
           //grid[trackHead_r][trackHead_c-1]='+';
           tail_c[tail_segment]=trackHead_c-1;
           tail_r[tail_segment]=trackHead_r;
           lasttailSegmentAdd_c=tail_c[tail_segment];
           lastTailSegmentAdd_r=tail_r[tail_segment];
       }

       if (direction == UP)
       {
           //grid[trackHead_r+1][trackHead_c]='+';
           tail_c[tail_segment]=trackHead_c;
           tail_r[tail_segment]=trackHead_r+1;
           lasttailSegmentAdd_c=tail_c[tail_segment];
           lastTailSegmentAdd_r=tail_r[tail_segment];
       }

       if (direction == DOWN)
       {
          // grid[trackHead_r-1][trackHead_c]='+';
           tail_c[tail_segment]=trackHead_c;
           tail_r[tail_segment]=trackHead_r-1;
           lasttailSegmentAdd_c=tail_c[tail_segment];
           lastTailSegmentAdd_r=tail_r[tail_segment];
       }

        tail_segment++;
        //printf("\nCollision\n");
    }
}
void snake_direction(enum move dir)
{
   int i=0;
    if(dir==UP)
    {
        grid[trackHead_r][trackHead_c]=' ';
        grid[trackHead_r-1][trackHead_c]='o';
        trackHead_r--;
       // trackTail_r=trackHead_r+1;
    }
    else if(dir==DOWN)
    {
        grid[trackHead_r+1][trackHead_c]='o';
        grid[trackHead_r][trackHead_c]=' ';
        trackHead_r++;
       // trackTail_r=trackHead_r-1;
    }
    if(dir==LEFT)
    {
        grid[trackHead_r][trackHead_c]=' ';
        grid[trackHead_r][trackHead_c-1]='o';
        trackHead_c--;
        //trackTail_c=trackHead_c+1;

    }
    else if(dir==RIGHT)
    {
        grid[trackHead_r][trackHead_c]=' ';
        grid[trackHead_r][trackHead_c+1]='o';
        trackHead_c++;
       // trackTail_c=trackHead_c-1;
    }
}
void endgame()
{
    if(grid[trackHead_r][trackHead_c]==grid[0][trackHead_c])
        direction=ENDGAME;
    if(grid[trackHead_r][trackHead_c]==grid[trackHead_r][0])
        direction=ENDGAME;
    if(grid[trackHead_r][trackHead_c]==grid[ROW-1][trackHead_c])
        direction=ENDGAME;
    if(grid[trackHead_r][trackHead_c]==grid[trackHead_r][38])
        direction=ENDGAME;
}

void move_tail_segments()
{
    int i,x,y,x1,y1;

    x=tail_r[0];
    y=tail_c[0];

    tail_r[0]=trackTail_r;
    tail_c[0]=trackTail_c;

    for(i=1;i<=tail_segment;i++)
    {
        grid[x][y]='+';
        x1 = tail_r[i];
        y1 = tail_c[i];

        tail_r[i]=x;
        tail_c[i]=y;

        x=x1;
        y=y1;
    }

}
void remove_plus()
{
    int x,y;
    for(x=0;x<ROW;x++)
        for(y=0;y<COL;y++)
    {
        if(grid[x][y]=='+')
            grid[x][y]=' ';
    }

}
