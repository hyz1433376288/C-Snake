#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define ROW 32
#define LINE 17
int Search(int a,int b,int x[],int y[],int len)//���ʳ���Ƿ�����������ϣ�������ͷ�Ƿ���������
{
    int i,j;
    for(i=1;i<len;i++)
    {
        if(x[i]==a&&y[i]==b)
            return 1;
    }
    return 0;
}
void HideCursor()//���ع��
{

    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}
void gotoxy(int x,int y)//��궨λ����
{
	COORD p;//����ṹ�����p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ�������
	p.X=x;p.Y=y;//������Ŀ���ƶ�λ�ô��ݸ��ṹ��
	SetConsoleCursorPosition(handle,p);//�ƶ����
}
int main()
{
     system("title Snake");
     system("mode con cols=47 lines=20");
    system("color 04");
     int i,j;
     gotoxy(14,6);
     printf("Snake");
     Sleep(2000);
      char announcement[]={"--Houyz Products"};
      for(i=0;i<17;i++)
      {
          gotoxy(16,8);
          for(j=0;j<=i;j++)
          {
              printf("%c",announcement[j]);
          }
          Sleep(200);
      }
      Sleep(2500);
    int a[LINE][ROW];
    int flag=0;//�Ƿ��µı�־
    for(i=0;i<LINE;i++)
    {
        for(j=0;j<ROW;j++)
        {
            if((i==0||i==LINE-1)||(j==0||j==ROW-1)) a[i][j]=1;
            else a[i][j]=0;
        }
    }
    int head_x=LINE/2,head_y=ROW/2;
    int rear_x=LINE/2,rear_y=ROW/2-2;
    for(i=0;i<3;i++)
    {
        a[head_x][head_y-i]=2;//�����ʼ��
    }
    int x[60]={LINE/2,LINE/2,LINE/2},y[60]={ROW/2,ROW/2-1,ROW/2-2};
    srand(time(NULL));
    int food=0;//ʳ�����
    int socre=0;//����
    int len=3;//�߳���
    int pause=0;//������ͣ
    int lag=200;//ˢ�¼��
    system("color 02");
    while(1)
    {
        HideCursor();
       gotoxy(0,0);
        int food_x,food_y;
        if(food!=1)
        {
            food_x=1+rand()%15;
            food_y=1+rand()%30;
            while(Search(food_x,food_y,x,y,len)==1)//���ʳ��������Լ����ϣ�������ȡֱ
            {
                food_x=1+rand()%15;
                food_y=1+rand()%30;
            }
            a[food_x][food_y]=3;
            food=1;
        }
           printf("\n");
        for(i=0;i<LINE;i++)
        {
             printf("\t");
            for(j=0;j<ROW;j++)
            {
                if(a[i][j]==1) printf("+");//Χ��
                else if(a[i][j]==2)
                {
                    if(i==x[0]&&j==y[0])
                    {
                         printf("O");//��ͷ
                    }
                    else printf("*");//����
                }
                else if(a[i][j]==3) printf("$");//ʳ��
                else printf(" ");
            }
            printf("\n");
        }
        Sleep(lag);
        char input;
        int direction;
        if(flag==0) direction=4;
        if(kbhit())
        {
             input=getch();
             if(input=='w'||input=='a'||input=='s'||input=='d') pause=0;
             else pause=1;
            flag=1;
        }
            if((input=='w'&&direction!=3)||(input=='s'&&direction==1))
                {a[--head_x][head_y]=2;direction=1;}
            if(input=='a'&&direction!=4||(input=='d'&&direction==2))
                {a[head_x][--head_y]=2;direction=2;}
            if(input=='s'&&direction!=1||(input=='w'&&direction==3))
                {a[++head_x][head_y]=2;direction=3;}
            if(input=='d'&&direction!=2||(input=='a'&&direction==4))
                {a[head_x][++head_y]=2;direction=4;}

        if(head_x==0||head_x==16||head_y==0||head_y==31)//�鿴��ͷ�Ƿ������߽�
        {
             printf("\tSOCRE:%d  CURSPEED:%d m/s",socre*10,300-lag);
            printf("\n         YOU CRUSHED!\n");
            Sleep(2000);
            break;
        }
        if(Search(head_x,head_y,x,y,len)==1)//��ͷ�Ƿ�ײ�Լ�
        {
            printf("\tSOCRE:%d  CURSPEED:%d m/s",socre*10,300-lag);
            printf("\n         YOU EAT YOURSELF!\n");
            Sleep(2000);
            break;
        }
        int k;
        if(head_x==food_x&&head_y==food_y) //����Ե�ʳ��
            {
                food=0;
                len++;
                socre++;
                if(lag>10) lag-=10;
                for(k=0;k<len;k++)//������ȡ��������ͷ��
                {
                    x[len-k]=x[len-1-k];
                    y[len-k]=y[len-1-k];
                }
            x[0]=head_x;//ͷ������ȡ��
            y[0]=head_y;
            }
        else //û�гԵ�ʳ��
        {
            if(flag==1&&pause==0)
            {
                 a[x[len-1]][y[len-1]]=0;//��ӡ��֮��������β
                for(k=0;k<len-1;k++)//������ȡ��������ͷ��
                {
                    x[len-1-k]=x[len-1-k-1];
                    y[len-1-k]=y[len-1-k-1];
                }
                x[0]=head_x;//ͷ������ȡ��
                y[0]=head_y;
                for(k=0;k<len;k++)
                    a[x[k]][y[k]]=2;
            }
        }
        printf("\tSOCRE:%d  CURSPEED:%d m/s",socre*10,300-lag);
    }
}

