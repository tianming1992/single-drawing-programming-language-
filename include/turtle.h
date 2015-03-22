/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file turtle.h
/*@author  戴潜
/*@date    2011.11.11
/*@brief   绘图命令执行模块
/*
/*********************************************************************************************************************/

#ifndef  _TURTLE_
#define  _TURTLE_

#include  <cairo-pdf.h>
#include  <cairo.h>
#include <string>
#include <iostream>
#include <cmath> 
#include <vector>
#include <list>

#define   PNG   0
#define   PDF   1
using namespace std;
#define PI 3.14159265

//存储历史绘图命令 用于页边距重绘
struct hisCmd{
	string m_name;
	vector<float> params;
	string txtname;
};

//乌龟结构体
struct stTurtle{
	float m_currX;//当前x坐标
	float m_currY;//当前y坐标
	float m_last_currX;//上次x坐标
	float m_last_currY;//上次y坐标
	float m_max_positive_x;  //最大x轴正向坐标
	float m_max_negtive_x;  //最大x轴负向坐标
	float m_max_positive_y;  //最大y轴正向坐标
	float m_max_negtive_y;  //最大y轴负向坐标
	bool flag_max_isset;  //是否赋值
	float m_max_y;  //最大y轴坐标
	float m_currAngle;//当前角度
	bool  m_write;//是否落笔
	cairo_surface_t *surface;//绘图信息
	cairo_t *cr;
	int margin; //边距  如果margin小于0  表示无-m参数  若大于等于0  表示有-m参数 其值在本参数中
	string filename;     //如若filename为空 生成默认 slogo为文件名的文件 否则生成该文件名
	int type;//如果type为0 生成png  为1生成pdf
	bool record;
	list<hisCmd> cmds;//历史命令
	string initfilename;
};

void initpaint(stTurtle &stCurrTurtle);       //初始化
void FD(stTurtle &stCurrTurtle,float length);    //前进
void BK(stTurtle &stCurrTurtle,float length); //后退
void RT(stTurtle &stCurrTurtle,float angle); //右转
void LT(stTurtle &stCurrTurtle,float angle); //左转
void PU(stTurtle &stCurrTurtle);  //抬笔;
void PD(stTurtle &stCurrTurtle);  //落笔;
void CS(stTurtle &stCurrTurtle); //清空图形，回到原点，朝向0度
void HOME(stTurtle &stCurrTurtle); //清空图形
void SETX(stTurtle &stCurrTurtle,float fx_axis); //设定x坐标
void SETY(stTurtle &stCurrTurtle,float fy_axis); //设定y坐标
void SETXY(stTurtle &stCurrTurtle,float fx_axis,float fy_axis);//设定x,y坐标
void SETH(stTurtle &stCurrTurtle,float angle); //角度
void print(stTurtle &stCurrTurtle,string txt); //打印字符
void  destroy_turtle(stTurtle &stCurrTurtle); //第二遍运行命令
void setcolor(stTurtle &stCurrTurtle,float red,float green, float blue);
void drawcircle(stTurtle &stCurrTurtle,float radius);
#endif 