#ifndef __2048_H__
#define __2048_H__
#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>

#define NUM 4
static int a[4][4]={0};//4*4格子的地图
int empty;//空格字数
int old_y,old_x;//坐标

void draw();//绘制游戏界面
void play();//游戏逻辑主体
void init();//初始化一些必要的初始化操作
void draw_one(int x, int y);//绘制单个数字
void cnt_value(int *new_y, int *new_x);
int game_over();//游戏结束
int cnt_one(int y, int x);



#endif 
