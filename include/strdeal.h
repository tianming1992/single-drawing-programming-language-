/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file strseal.h
/*@author 邹天明
/*@date    2011.11.11
/*@brief   字符串处理
/*
/*********************************************************************************************************************/

#ifndef  _STRSEAL_H_
#define   _STRSEAL_H_

#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <io.h>
#include<ctype.h>
#include <sstream>
#include <ctime>
#include<queue>

using namespace std;

void delSpace(string &str);
void split(const string&s , char c , vector<string>&v);
bool getString(string filename , string &storeStr);
bool isNumOrAlpha(const string &check);
bool isIllIdentifer(const string &check);//检查是否是合法标识符
int getLine(const string & str );
void splitExpression(string src , vector<string> & result);//分割表达式
//是否为转义字符
bool  isChangeMean(long int i , const string & src);
//某个字符串中有多少【】匹配序列
int blockPairs(const string &  tempCmd);
bool isVal(string param);//判断是否是变量
bool isConstStr(string & param);//是否为字符串常量
//判断一个数是否为整数
bool isInt(float f);
string turnFstrTostand(string src);
//处理字符串转义字符
string  toChangeMean(string src);
//字符串转小写
void  toLower_(string & src);
#endif