/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file sys_execu.h
/*@author  ������
/*@date    2011.11.11
/*@brief   ��������ģ��
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
//ϵͳ������Ϣ
struct stSysInfo{
stack<stFunc>m_funcStack;//����չ��ջ
list<stVal>m_globalValTable;//ȫ�ֱ�����
list<stFunc>m_funcTable;//�Զ�����̱�
stTurtle currTurtle;//��ͼ�ڹ�
list<stCommand> m_execuCmdLists; //����ִ�ж���
int m_rootFucCallerLine;//����ջ����ʼ������
bool havePicName;
int  reTurnToFunc ;
string m_programFile;
string m_pic_fileName;
};

void	initSys(stSysInfo * pSy ,vector<string> & cmds );//��ʼ��
//ִ����������
void exeu( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue);
void execu_cmds( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue);
//��ȡ����ֵ
stVal get_val_value(string valName , stSysInfo * pstSys);
//Ѱ��ĳ�����ʽ�ڲ�����  ���ҽ��ñ���ʹ����ֵ�滻
bool replaceVeri(string &srcEpre , stSysInfo * pstSys);
//��ȡ�������ʽֵ
int  getConditionExVal(string sExpr , stSysInfo * pstSys);


void cmd_make(stCommand & currCmd ,stSysInfo * pstSys);
//ִ�к���
void cmd_func(stCommand & currCmd ,stSysInfo * pstSys);
//ifelse����
void cmd_ifelse(stCommand & currCmd ,stSysInfo * pstSys);
//ifelse����
void cmd_if(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_repeat(stCommand & currCmd ,stSysInfo * pstSys);
void cmd_print(stCommand & currCmd ,stSysInfo * pstSys);
//stop����
void cmd_stop(stCommand & currCmd ,stSysInfo * pstSys, list<stCommand> & stCommdQueue);
//import ���� ����ģ���
void cmd_import(stCommand & currCmd ,stSysInfo * pstSys);

//������ͼ����
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
void cmd_dmake(stCommand & currCmd ,stSysInfo * pstSys);//��ǿ��make���� �������������������У�����ȫ�ֱ��� 
                                                                                       //�ڹ���������ֲ�����
void  destroy_psy(stSysInfo*psy);//����ϵͳ��Ϣ
#endif