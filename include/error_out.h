/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file  error_out.h
/*@author  ������
/*@date    2011.11.11
/*@brief   ������
/*
/*********************************************************************************************************************/

#ifndef   _ERROR_OUT_
#define    _ERROR_OUT_

#include <stdio.h>
#include <string>
#include<vector>
#include <list>
#include <iostream>

using namespace std;

struct stErrorInfo //������Ϣ�ṹ��
{
	string fileName;//���������ļ�
	vector<string>errorInfo;//������Ϣ
};

void  error_out_pos(const string &out , const int & pos , const string & srcProgram);
int getLineNumBer(const int & pos , const string & srcProgram);
void pFileName(const string & fileName);
void  error_out_line(const string &out , const int & line );
void prinError();
#endif