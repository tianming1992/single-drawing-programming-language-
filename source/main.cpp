/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file main.cpp
/*@author  ������
/*@date    2011.11.11
/*@brief   ������ ������ڵ�
/*
/*********************************************************************************************************************/

#include <math.h>
#include"command.h"
#include "val.h"
#include "sys_execu.h"

int main ( int argc, char *argv[ ] )
{
   if (argc <=1)//����̫�� �˳�
	{
		perror("too less parameters to exe!");
		return 1;
	}
  
    int i = 1;
   vector <string>inputCmds;
   while(i < argc)//��ȡ�����в���
   {
	  inputCmds.push_back(argv[i]);
	  ++i;
    }
   
    struct stSysInfo *pSys = new struct stSysInfo ;
    string strPro;//�����ı�
    
    initSys(pSys , inputCmds);//��ʼ��
	if (false == getString(pSys->m_programFile , strPro))//��ȡ�����ı�
	{
		perror("can not open program file!");
		exit(0);
	}

	preScan(pSys->m_funcTable , strPro , pSys->m_programFile);//Ԥɨ����
    parase(pSys->m_execuCmdLists ,strPro ,pSys->m_funcTable,SYS_CMD,0 ,pSys->m_programFile);//��������
	execu_cmds(pSys , pSys->m_execuCmdLists);//ִ�г���
	prinError();//�������
    destroy_psy(pSys);//����ϵͳ��Ϣ
    return 0 ;
}
