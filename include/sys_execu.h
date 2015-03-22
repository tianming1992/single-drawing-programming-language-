/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file sys_execu.h
/*@author  邹天明
/*@date    2011.11.11
/*@brief   程序运行模块
/*
/*********************************************************************************************************************/

#ifndef   _SYS_EXECU_H_
#define   _SYS_EXECU_H_

#include <list>
#include <queue>
#include <stack>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "expression.h"
#include "turtle.h"
#include "command.h"
#include "val.h"


#define  MAX_FUNCTION_STACK   200

using namespace std;
//系统运行信息
struct stSysInfo{
stack<stFunc>m_funcStack;//函数展开栈
list<stVal>m_globalValTable;//全局变量表
list<stFunc>m_funcTable;//自定义过程表
stTurtle currTurtle;//绘图乌龟
list<stCommand> m_execuCmdLists; //命令执行队列
int m_rootFucCallerLine;//函数栈的起始调用者
bool havePicName;
int  reTurnToFunc ;
string m_programFile;
string m_pic_fileName;
};

void	initSys(stSysInfo * pSy ,vector<string> & cmds );//初始化
//执行命令序列
void exeu( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue);
void execu_cmds( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue);
//获取变量值
stVal get_val_value(string valName , stSysInfo * pstSys);
//寻找某个表达式内部变量  并且将该变量使用真值替换
bool replaceVeri(string &srcEpre , stSysInfo * pstSys);
//获取条件表达式值
int  getConditionExVal(string sExpr , stSysInfo * pstSys);


void cmd_make(stCommand & currCmd ,stSysInfo * pstSys);
//执行函数
void cmd_func(stCommand & currCmd ,stSysInfo * pstSys);
//ifelse命令
void cmd_ifelse(stCommand & currCmd ,stSysInfo * pstSys);
//ifelse命令
void cmd_if(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_repeat(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_print(stCommand & currCmd ,stSysInfo * pstSys);
//stop命令
void cmd_stop(stCommand & currCmd ,stSysInfo * pstSys, list<stCommand> & stCommdQueue);
//import 命令 导入模块库
void cmd_import(stCommand & currCmd ,stSysInfo * pstSys);

//基本绘图命令
void cmd_draw_fd(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_bk(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_rt(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_lt(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_pu(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_pd(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_cs(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_home(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_setx(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_sety(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_setxy(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_seth(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_set_color(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_draw_dc(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_dmake(stCommand & currCmd ,stSysInfo * pstSys);//增强的make命令 如果命令出现在主程序中，则定义全局变量 
                                                                                       //在过程中则定义局部变量
void  destroy_psy(stSysInfo*psy);//销毁系统信息
#endif