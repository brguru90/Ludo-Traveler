#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <unistd.h>
#define n 5
int mat1[5][5],mat2[5][5];
void display_table();
void init();
void copy_mat(int[n][n],int);
void show_mat(int[n][n]);
void play();
void swap_h(int[n][n]);
void move_coin(int,int,int);

struct coin_data
{
	int coin_val,i,j;
};
struct player
{
		struct coin_data coin[4];
}p[2];

int main()
{
	//display_table();
	init();
	play();
	return 0;
}
void init()
{
	int i,j;
	int mat[5][5]={
	{11,10,9,8,7},
	{12,19,20,21,6},
	{13,18,25,22,5},
	{14,17,24,23,4},
	{15,16,1,2,3}
	};
	printf("Before\n");
	show_mat(mat);
	copy_mat(mat,0);
	swap_h(mat);
	printf("swapped1\n");
	show_mat(mat);	
	copy_mat(mat,1);
}

void copy_mat(int mat[n][n],int f)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(f==0)
				mat1[i][j]=mat[i][j];
			else				
				mat2[i][j]=mat[i][j];
		}
	}
}

void show_mat(int mat[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d%d=%d\t",i,j,mat[i][j]);
		}
		printf("\n");
	}
}
void swap_h(int mat[n][n])
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++)
		{			
			if((i>=n/2 && j>=n/2 && i==j) )
			continue;
				temp=mat[n-i-1][n-j-1];
				mat[n-i-1][n-j-1]=mat[i][j];
				mat[i][j]=temp;
		}
	}
}
/*
void swap_v(int mat[n][n])
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{			
			if((i>=n/2 && j>=n/2 && i==j) )
			continue;
			
				temp=mat[n-i-1][n-j-1];
				mat[n-i-1][n-j-1]=mat[i][j];
				mat[i][j]=temp;
			
		}
	}
}
*/
void play()
{
	int c,ch;
	int flag=1;		
	printf("enter value>4 stop any time or anything else to through dice\n");
	while(true)
	{		
		if(flag==0)
		{
			flag=1;
			printf("----------------Player 2----------------\n");
		}			
		else
		{
			flag=0;
			printf("----------------Player 1----------------\n");
		}
		printf("Chose coin 1,2,3,4: ");
		//scanf("%d",&ch);
		ch=rand();
		sleep(2);
		printf("%d",ch);
		if(ch<0)
			exit(0);
		system("cls");
		c=(rand()+6)%7;
		if(c==0) 
			c=1;
		printf("enter -ve value to stop any time or anything else to through dice\n");
		printf("Dice value:%d\n",c);		
		ch=ch%5;
		if(ch==0)
			ch++;
		ch--;		
		move_coin(flag,ch,c);	
	}
}
void move_coin(int f,int ch,int c)
{
	int i,j,k,m,temp=0;
	if(p[f].coin[ch].coin_val+c<=25)
		p[f].coin[ch].coin_val+=c;	
	printf("palyer %d score of %d coin=%d\n",f+1,ch,p[f].coin[ch].coin_val);
	
	for(k=0;k<4;k++)
		temp+=p[0].coin[k].coin_val;
	if(temp==100) exit(0);
	temp=0;
	for(k=0;k<4;k++)
		temp+=p[1].coin[k].coin_val;
	if(temp==100) exit(0);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i%2==0 && j%2==0)
	   		{
	   			printf("{");
	   			for(k=0;k<4;k++)
	   			if(mat1[i][j]==p[0].coin[k].coin_val)
	   			{
	   				p[0].coin[k].i=i;
	   				p[0].coin[k].j=j;
					printf("P1 %d,",k+1);
				}
				else
				if(mat2[i][j]==p[1].coin[k].coin_val)
				{
					p[1].coin[k].i=i;
	   				p[1].coin[k].j=j;
					printf("P2 %d,",k+1);
				}							
	   			printf("}\t\t\t\t");
			}
			else
			{
				printf("[");
				for(k=0;k<4;k++)			
	   			if(mat1[i][j]==p[0].coin[k].coin_val)
	   			{
	   				p[0].coin[k].i=i;
	   				p[0].coin[k].j=j;
					printf("P1 %d,",k+1);
				}
				else
				if(mat2[i][j]==p[1].coin[k].coin_val)
				{
					p[1].coin[k].i=i;
	   				p[1].coin[k].j=j;
					printf("P2 %d,",k+1);
				}						
				printf("]\t\t\t\t");
			}	
		}
		printf("\n");
		for(m=0;m<n;m++)
			printf("%d%d\t\t\t\t",i,m);
		printf("\n\n\n\n");		
	}	
	for(k=0;k<4;k++)
	if(p[0].coin[k].i==p[1].coin[k].i && p[0].coin[k].j==p[1].coin[k].j && i!=2 && j!=2 && i%2!=1 && j%2!=1)
	{
		 p[(f) ? 1 : 0].coin[k].coin_val=0;
		 printf("Out or Not used: P%d-%d\n",(f) ? 2 : 1,k+1);
	}
}

void display_table()
{
	int i,j=1;
	for(i=1;i<=n*n;i++)
	{
   		
   		if(i%2==1 && j%2==1)
   		{
   			printf("{}");
		}
		else
		{
			printf("[]");
		}
   		if(i%5==0)
   		{
   			printf("\n");
   			j++;
   			
   		}	
   		
   		
	}
	printf("\n\n");
}
