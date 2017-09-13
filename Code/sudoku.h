#ifndef __SUDOKU__ 

#define __SUDOKU__

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

int sudoku[9][9] = {0};
int sum = 0;
int num = 0;
int flag = 0;
char ch[200];

bool stringtonum(string str)//检查输入的数字合法性
{
  int count = 0;
  int stringlen = str.length();
  while(stringlen)
  {
    if(48>str[stringlen-1] || str[stringlen-1]>57)
    {
      return false;
    }
	num += (str[stringlen-1]-48)*pow(10,count);
	count++;
	stringlen--;
	if(num > 1000000)return false;
  }
  return true;
}
bool Yesdis(int count)//检查某位置是否可以填入该数
{
  int x = count/9;
  int y = count%9;
  int value;

  for(value = 0; value < 9; ++value)
  {
    if(sudoku[x][value] == sudoku[x][y] && value != y)//检查行
    {
      return false;
    }
  }
  for(value = 0; value < 9; ++value)
  {
    if(sudoku[value][y] == sudoku[x][y] && value != x)//检查列
    {
      return false;
    }
  }
  int wightx = x/3*3;
  int wighty = y/3*3;
  int temp;
  for(value = wightx; value < wightx + 3; ++value)//检查九宫格里
  {
  	for( temp = wighty; temp < wighty + 3; ++temp)
  	{
  		if(sudoku[value][temp] == sudoku[x][y] && value != x)
    	{
      		return false;
    	}
  	}
    
  }
  return true;
}

void backtrace(int count,FILE* fp)//回溯调用
{
    if(count == 81)
    {
    	sum++;
    	if(sum >= num)exit(0);

    	for(int i = 0;i<9;++i)
      {
          for(int j = 0;j<9;++j)
          {
            	ch[flag++] = sudoku[i][j]+'0';
            	ch[flag++] = ' ';
          }
          ch[flag++] = '\n';
      }
			ch[flag++] = '\n';
			fputs(ch,fp);
			flag = 0;
      return ;
    }

    int row = count/9;
    int col = count%9;
    if(sudoku[row][col] == 0)
    {
        for(int i = 1;i<=9;++i)
        {
            sudoku[row][col] = i;
            if(Yesdis(count))
            {
                backtrace(count+1, fp);
            }
            sudoku[row][col]=0;
        }
        sudoku[row][col] = 0;
    }
    else
    {
        backtrace(count+1,fp);
    }
}


#endif 
