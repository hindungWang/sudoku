#include<iostream>
#include<stdlib.h> 
#include<fstream>
#include<stdio.h>
#include<cstring>
using namespace std;
  
int sudoku[9][9]={0};
int test1[9][9]={0};
int test2[9][9]={0};

bool Judge1(int x, int y, int n)
{
            int i;
            
            for(i=0;i<9;i++)
            {
                        //判断列
                        if((sudoku[i][y]==n)&& (i!=x))
                                    return false;
                        //判断行
                        if((sudoku[x][i]==n)&& (i!=y))
                                    return false;
            }
  
            return true;
}
  
//判断填在空白位置的数字在九宫格之内是否符合要求
bool Judge2(int x, int y, int n)
{
            int x0,y0,i,j;
            x0=x/3;
            y0=y/3;
            for(i=x0*3;i<x0*3+3;i++)
            {
            	for(j=y0*3;j<y0*3+3;j++)
                {
                	if(sudoku[i][j]==n)
                	{
                		if(i==x && j==y)
                        continue;
                        else
                        return false;
                	}
                    
                }  	
            }                     
            return true;
}

//填充空白数组
bool insertNum(int num)
{
            int n,x,y;
            x=num/9;
            y=num%9;
            if (num>=81)
                        return true;
            if (sudoku[x][y]==0)
            {
                        for(n=1;n<=9;n++)
                        {
                                    sudoku[x][y]=n;
                                    if(Judge1(x,y,n)&&Judge2(x,y,n))
                                                if(insertNum(num+1))
                                                            return true;
                                    sudoku[x][y]=0;
                                                
                        }
            }
            else return insertNum(num+1);
			return false;
}

void aArrange(int a[],int j,FILE* fp)
{
	int i,k;
	int temp;
	for(i=j;i<8;i++)
	{
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		aArrange(a,j+1,fp);
		if(j==7)
		{
			for(k=0;k<8;k++)
			{
				sudoku[0][k+1]=a[k];
			}
			
			if(insertNum(0))
    		{
            	for(i=0;i<9;i++)
            	{
                	for(j=0;j<9;j++)
                	{
                    	fprintf(fp,"%d",sudoku[i][j]);
                    	fprintf(fp, " ");
                	}
                	fprintf(fp, "\n");
            	}
				fprintf(fp, "\n");	
			}		
		}
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
}
void random(FILE* fp)
{
	int a[]={1,2,3,4,6,7,8,9};
	sudoku[0][0]=5;
	aArrange(a,0,fp);
}
int main(int argc,char *argv[])
{
	FILE* fp;
	fp = fopen("sudoku.txt","w");
	random(fp);
	fclose(fp);
	return 0;
}
