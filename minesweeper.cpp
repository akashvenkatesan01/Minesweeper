#include<iostream>
#include<windows.h>
using namespace std;

void recursive(int ,int ,int ,int );

struct mine
{
	char data,flag;
}access[100][100];

int x,y,row,column,r,c,count=0,input,flag1=0,bombcount=0,point=0;

void begin()
{
	cin>>row>>column;
	for( r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			access[r][c].flag=(char)1;
		}
	}
	for(r=0;r<(2*row);r++)
	{
		x=rand()%(row-1);
		y=rand()%(column-1);
		if(access[x][y].data=='M')
		{
			access[x+1][y].data='M';
			bombcount++;
		}
		else
		{
			access[x][y].data='M';
			bombcount++;
		}
	}
	for( r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			if(access[r][c].data!='M')
			{
				access[r][c].data='0';
			}
		}
	}
}

void dataloading()
{
	for( r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			if(access[r][c].data!='M')
			{
				if(access[r-1][c].data=='M')
				{
					count++;
				}
				if(access[r+1][c].data=='M')
				{
					count++;
				}
				if(access[r-1][c-1].data=='M')
				{
					count++;
				}
				if(access[r+1][c+1].data=='M')
				{
					count++;
				}
				if(access[r][c-1].data=='M')
				{
					count++;
				}
				if(access[r][c+1].data=='M')
				{
					count++;
				}
				if(access[r-1][c+1].data=='M')
				{
					count++;
				}
				if(access[r+1][c-1].data=='M')
				{
					count++;
				}
				access[r][c].data='0'+count;
			}
			count=0;
		}
	}
}

void gameplay()
{
	while(1)
	{
		label:
		cout<<"Number of Flags that can be placed:"<<bombcount-count<<endl;
		cout<<"Choose the corresponding number:"<<endl<<"Flag=0"<<endl<<"Open=1"<<endl<<"unflag=2"<<endl;
		cin>>input;
		system("cls");
		cout<<"Enter the x and y position:";
		if(input==1)
		{
			cin>>x>>y;
			if(access[x][y].flag==(char)1)
			{
				if(access[x][y].data=='M')
				{
					for( r=0;r<row;r++)
					{
						for(c=0;c<column;c++)
						{
							if(access[r][c].data=='M')
							{
								access[r][c].flag='M';
								flag1=1;
							}
						}
					}
				}
				else if(access[x][y].data=='0')
				{
					recursive(x,y,row,column);
				}
				else
				{
					access[x][y].flag=access[x][y].data;
				}
			}
			else
			{
				cout<<"Already opened"<<endl;
				goto label;
			}
		}
		if(input==0)
		{
			cin>>x>>y;
			access[x][y].flag='F';
			if(access[x][y].data=='M')
			{
				point++;
			}
			count++;
		}
		if(input==2)
		{
			cin>>x>>y;
			access[x][y].flag=(char)1;
			count--;
		}
		if(count==bombcount || flag1==1)													// checking whether the bombs are placed accordingly
		{
			for( r=0;r<row;r++)
			{
				for(c=0;c<column;c++)
				{
					if(access[r][c].data!='M' && access[r][c].flag=='F')
					{
						access[r][c].flag='X';
					}
				}
			}
			flag1=1;
		}
		for( r=0;r<row;r++)
		{
			for(c=0;c<column;c++)
			{
				cout<<access[r][c].flag;
			}
			cout<<endl;
		}
		if(flag1==1)
		{
			if(point==bombcount)
			{
				cout<<"WIN";
			}
			else
			{
				cout<<"POINT :"<<point<<endl<<"GAME OVER(You have opened a bomb)";
			}
			break;
		}
	}
}

void recursive(int x,int y,int row,int column)								//exploring empty  spaces
{
	if(x<0||y<0||x>row-1||y>column-1)
	{
		return;
	}
	else if(access[x][y].data=='0' &&	access[x][y].flag!='0')
	{
		access[x][y].flag='0';
		
		recursive(x+1,y,row,column);
		recursive(x-1,y,row,column);
		recursive(x+1,y+1,row,column);
		recursive(x-1,y-1,row,column);
		recursive(x,y+1,row,column);
		recursive(x,y-1,row,column);
		recursive(x+1,y-1,row,column);
		recursive(x-1,y+1,row,column);				
	}
	else if(access[x][y].data>'0' && access[x][y].data<='9')
	{
		access[x][y].flag=access[x][y].data;
		return;
	}
	else 
	{
		return;
	}
}
int main()
{
	
	cout<<"You can place flags equal to the number of bombs"<<endl;
	cout<<"Enter the number of rows and columns:";
	begin();
	dataloading();
	gameplay();
	return 0;
}

