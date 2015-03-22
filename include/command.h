/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file command.h
/*@author  邹天明
/*@date    2011.11.11
/*@brief   程序解析模块
/*
/*********************************************************************************************************************/

#ifndef  _COMMAND_H_
#define  _COMMAND_H_

#include <string>
#include <vector>
#include <list>
#include<ctype.h>
#include <stdio.h>
#include "val.h"
#include "error_out.h"
#include "strdeal.h"

#define   SYS_CMD  0 //系统命令
#define   FUNC_CMD  1 //自定义过程
#define   SET_CMD  2 //命令集合

using namespace std;

//命令结构体
struct stCommand{
string  m_cmdName;//命令名
int m_argc;//命令参数个数
vector<string> m_argvs;//命令参数表
char m_cmdKind ;//命令的类型
string m_beforeParse;//该条命令被解析前原文
int m_lineNumber; //该命令所在行数
string m_fileName;//所在文件名
};

//自定义过程
struct stFunc{
string m_funcName;//过程名
string m_conntext;//函数内容
int m_argc; //函数参数个数
list<stVal>m_parmTable; //参数表
int m_lineNumber; //该函数所在行数
string m_fileName;//所在文件名
};


//预扫程序，获得用户自定义过程表  结果装入funcTables内 
void preScan(list<stFunc>&funcTables ,  string & sProgram, const  string &fileName);
//解析命令
//命令名  命令参数  命令参数个数  命令类型
void parase(list<stCommand>&cmds , string & sProgram,const list<stFunc>&fucTables , int cmd_kind , int base_line,const  string &fileName);
//判断是否为函数
bool isFunc(const string& check ,const list<stFunc>&fucTables );
//从当前位置开始寻找下一个关键字出现的首个位置 及关键字长度
int firstKey(int currPos , string & sProgram , int &nlength,const list<stFunc>&fucTables ,string &temp);
//获取程序所有函数表
void getFuncTable(list<stFunc>&funcTables ,  string & sProgram , const  string & fileName);

//判断是否为内置命令
bool isKeyWord(const string& check  );
#endif