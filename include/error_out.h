/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file  error_out.h
/*@author  邹天明
/*@date    2011.11.11
/*@brief   错误处理
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

struct stErrorInfo //错误信息结构体
{
	string fileName;//错误所在文件
	vector<string>errorInfo;//错误信息
};

void  error_out_pos(const string &out , const int & pos , const string & srcProgram);
int getLineNumBer(const int & pos , const string & srcProgram);
void pFileName(const string & fileName);
void  error_out_line(const string &out , const int & line );
void prinError();
#endif