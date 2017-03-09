#include"2048.h"
void Menu()
{
	mvaddstr(9,0,"*********************");
	int i=10;
	for(;i<=19;i++)
	{
		move(i,0);
		addch('*');
		move(i,20);
		addch('*');
	}
	mvaddstr(11,5,"SHANG:W I");
	mvaddstr(12,5,"XIA:S K ");
	mvaddstr(13,5,"ZUO:A H");
	mvaddstr(14,5,"YOU:D L");
	mvaddstr(15,5,"EXIT:Q q");
	mvaddstr(17,5,"MADE BY FENG");
	mvaddstr(18,5,"QQ:763608087");
	mvaddstr(20,0,"*********************");
}
void init()
{
	int x,y;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	empty=15;
	srand(time(0));
	x =rand()%4;
	y =rand()%4;
	a[y][x]=2;
	draw();
}
void draw()
{
	int n,m,x,y;//n,m单元格的下标，y,x数字的下标

	char c[4]={'0','0','0','0'};
	clear();
	for(n =0; n<9;n+=2)//绘制横线,n代表行，m代表竖线
		for(m=0;m<21;m++)
		{
			move(n,m);
			addch('-');
			refresh();
		}
	for(m =0;m<22;m+=5)//绘制竖线
		for(n =1; n<8;n++)
		{
			move(n,m);
			addch('|');
			refresh();
		}
	for(y=0;y<4;y++)
		for(x=0;x<4;x++)
		{
			draw_one(y,x);
		}
	Menu();
}
void draw_one(int y,int x)
{
	int i,m,k,j;
	char c[5]={0x00};
	i= a[y][x];
	m =0;
	while(i>0)
	{
		j=i%10;
		c[m++]=(char)j+'0';
		i=i/10;
	}
	m =0;
	k =	(x+1)*5-1;//每个格子占四个字元    | _  _ _ 2|
	while(c[m]!=0x00)
	{
		move(2*y+1,k);
		addch(c[m++]);
		k--;
	}
}

void play()
{
	int x,y,i,new_x,new_y,temp;
	int old_empty,move;
	char ch;
	while(1)
	{
		move =0;
		old_empty=empty;
		ch =getch();
		switch(ch)
		{
		case 97:
		case 65:
		case 104:
		case 72://左
			for(y=0;y<4;y++)
				for(x=0;x<4;)
				{
					if(a[y][x]==0)
					{
						x++;
						continue;
					}
					else
					{
						for(i =x+1;i<4;i++)
						{
							if(a[y][i]==0)
							{
								continue;
							}
							else
							{
								if(a[y][x]==a[y][i])
								{
									a[y][x]+=a[y][i];
									a[y][i]=0;
									empty++;
									break;
								}
								else
								{
									break;
								}

							}
						}
						x=i;
					}
				}
			for(y=0;y<4;y++)
				for(x=0;x<4;x++)
				{
					if(a[y][x]==0)
					{
						continue;
					}
					else
					{
						for(i=x;(i>0)&&(a[y][i-1]==0);i--)
						{
							a[y][i-1]=a[y][i];
							a[y][i]=0;
							move =1;
						}
					}
				}
			break;//左结束
		case 'D':
		case 'd':
		case 'L':
		case 'l':
			for(y=0;y<4;y++)
				for(x=0;x<4;)
				{
					if(a[y][x]==0)
					{
						x++;
						continue;
					}
					else
					{
						for(i =x+1;i>=0;i++)
						{
							if(a[y][i]==0)
							{
								continue;
							}
							else
							{
								if(a[y][x]==a[y][i])
								{
									a[y][i-1]+=a[y][i];
									a[y][i]=0;
									empty++;
									break;
								}
								else
								{
									break;
								}

							}
						}
						x=i;
					}
				}
			for(y=0;y<4;y++)
				for(x=3;x>=0;x--)
				{
					if(a[y][x]==0)
					{
						continue;
					}
					else
					{
						for(i=x;(i<3)&&(a[y][i+1]==0);i++)
						{
							a[y][i+1]=a[y][i];
							a[y][i]=0;
							move =1;
						}
					}
				}
			break;
		case 'I':
		case 'i':
		case 'w':
		case 'W':
			for(x=0;x<4;x++)
				for(y=0;y<4;y++)
				{
					if(a[y][x]==0)
					{
						y++;
						continue;
					}else
					{
						for(i=y+1;i<4;i++)
						{
							if(a[i][x]==0)
							{
								continue;
							}

							else if(a[i][x]==a[y][x])
							{
								a[y][x]+=a[i][x];
								a[i][x]=0;
								empty++;
								break;
							}else
							{
								break;
							}
						}
						y=i;
					}
				}
			for(x=0;x<4;x++)
				for(y=0;y<4;y++)
				{
					if(a[y][x]==0)
					{
						continue;
					}else
					{
						for(i=y;(i>0)&&(a[i-1][x]==0);i--)
						{
							a[i-1][x]=a[i][x];
							a[i][x]=0;
							move =1;
						}
					}
				}
			break;
		case 'S':
		case 's':
		case 'k':
		case 'K':	
			for(x=0;x<4;x++)
				for(y=3;y>=0;y--)
				{
					if(a[y][x]==0)
					{
						y--;
						continue;
					}else
					{
						for(i=y-1;i>=0;i--)
						{
							if(a[i][x]==0)
							{
								continue;
							}

							else if(a[i][x]==a[y][x])
							{
								a[y][x]+=a[i][x];
								a[i][x]=0;
								empty++;
								break;
							}else
							{
								break;
							}
						}
						y=i;
					}
				}
			for(x=0;x<4;x++)
				for(y=3;y>=0;y--)
				{
					if(a[y][x]==0)
					{
						continue;
					}else
					{
						for(i=y;(i<3)&&(a[i+1][x]==0);i++)
						{
							a[i+1][x]=a[i][x];
							a[i][x]=0;
						//	empty++;
							move =1;
						}
					}
				}
			break;
		case 'Q':
		case 'q':
			exit(1);
			break;
		default:
			continue;
			break;
		}
		if(empty<=0)
			game_over();
		if((empty!=old_empty)||(move ==1))
		{
			do{
				new_x =rand()%4;
				new_y =rand()%4;
			}while(a[new_y][new_x]!=0);
			cnt_value(&new_y,&new_x);
			do{
				temp =rand()%4;
			}while(temp ==0 ||temp ==2);
			a[new_y][new_x]=temp+1;
			empty--;
		}
		draw();
	}
}
int cnt_one(int y,int x)
{
	int value =0;
	if(y-1>0)
		a[y-1][x]?0:value++;
	if(y+1<4)
		a[y+1][x]?0:value++;
	if(x-1>=0)
		a[y][x-1]?0:value++;
	if(x+1<4)
		a[y][x+1]?0:value++;
	if(y-1>=0&&x-1>=0)
		a[y-1][x+1]?0:value++;
	if(y+1<4&&x+1<4)
		a[y][x]?0:value++;
	if(y+1<4&&x-1>=0)
		a[y+1][x-1]?0:value++;
	if(y-1>=0&&x+1<4)
		a[y-1][x+1]?0:value++;
	return value;

}
void cnt_value(int *new_y ,int *new_x)
{
	int max_x,max_y,x,y,value;
	int max=0;
	max=cnt_one(*new_y,*new_x);
	for(y=0;y<4;y++)
		for(x =0;x<4;x++)
		{
			if(!a[y][x])
			{
				value= cnt_one(y,x);
				if(value>max&&old_y !=y&&old_x!=x)
				{
					*new_y= y;
					*new_x =x;
					old_x=x;
					old_y =y;
					break;
				}
			}
		}
}
int game_over()
{
	sleep(1);
	endwin();
	return -1;
}
