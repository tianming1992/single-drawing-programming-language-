/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file command.h
/*@author  ������
/*@date    2011.11.11
/*@brief   �������ģ��
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

#define   SYS_CMD  0 //ϵͳ����
#define   FUNC_CMD  1 //�Զ������
#define   SET_CMD  2 //�����

using namespace std;

//����ṹ��
struct stCommand{
string  m_cmdName;//������
int m_argc;//�����������
vector<string> m_argvs;//���������
char m_cmdKind ;//���������
string m_beforeParse;//�����������ǰԭ��
int m_lineNumber; //��������������
string m_fileName;//�����ļ���
};

//�Զ������
struct stFunc{
string m_funcName;//������
string m_conntext;//��������
int m_argc; //������������
list<stVal>m_parmTable; //������
int m_lineNumber; //�ú�����������
string m_fileName;//�����ļ���
};


//Ԥɨ���򣬻���û��Զ�����̱�  ���װ��funcTables�� 
void preScan(list<stFunc>&funcTables ,  string & sProgram, const  string &fileName);
//��������
//������  �������  �����������  ��������
void parase(list<stCommand>&cmds , string & sProgram,const list<stFunc>&fucTables , int cmd_kind , int base_line,const  string &fileName);
//�ж��Ƿ�Ϊ����
bool isFunc(const string& check ,const list<stFunc>&fucTables );
//�ӵ�ǰλ�ÿ�ʼѰ����һ���ؼ��ֳ��ֵ��׸�λ�� ���ؼ��ֳ���
int firstKey(int currPos , string & sProgram , int &nlength,const list<stFunc>&fucTables ,string &temp);
//��ȡ�������к�����
void getFuncTable(list<stFunc>&funcTables ,  string & sProgram , const  string & fileName);

//�ж��Ƿ�Ϊ��������
bool isKeyWord(const string& check  );
#endif