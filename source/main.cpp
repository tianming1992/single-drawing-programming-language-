/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file main.cpp
/*@author  邹天明
/*@date    2011.11.11
/*@brief   主函数 程序入口点
/*
/*********************************************************************************************************************/

#include <math.h>
#include"command.h"
#include "val.h"
#include "sys_execu.h"

int main ( int argc, char *argv[ ] )
{
   if (argc <=1)//参数太少 退出
	{
		perror("too less parameters to exe!");
		return 1;
	}
  
    int i = 1;
   vector <string>inputCmds;
   while(i < argc)//获取命令行参数
   {
	  inputCmds.push_back(argv[i]);
	  ++i;
    }
   
    struct stSysInfo *pSys = new struct stSysInfo ;
    string strPro;//程序文本
    
    initSys(pSys , inputCmds);//初始化
	if (false == getString(pSys->m_programFile , strPro))//获取程序文本
	{
		perror("can not open program file!");
		exit(0);
	}

	preScan(pSys->m_funcTable , strPro , pSys->m_programFile);//预扫程序
    parase(pSys->m_execuCmdLists ,strPro ,pSys->m_funcTable,SYS_CMD,0 ,pSys->m_programFile);//解析程序
	execu_cmds(pSys , pSys->m_execuCmdLists);//执行程序
	prinError();//处理错误
    destroy_psy(pSys);//销毁系统信息
    return 0 ;
}
