/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file strseal.h
/*@author ������
/*@date    2011.11.11
/*@brief   �ַ�������
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
bool isIllIdentifer(const string &check);//����Ƿ��ǺϷ���ʶ��
int getLine(const string & str );
void splitExpression(string src , vector<string> & result);//�ָ���ʽ
//�Ƿ�Ϊת���ַ�
bool  isChangeMean(long int i , const string & src);
//ĳ���ַ������ж��١���ƥ������
int blockPairs(const string &  tempCmd);
bool isVal(string param);//�ж��Ƿ��Ǳ���
bool isConstStr(string & param);//�Ƿ�Ϊ�ַ�������
//�ж�һ�����Ƿ�Ϊ����
bool isInt(float f);
string turnFstrTostand(string src);
//�����ַ���ת���ַ�
string  toChangeMean(string src);
//�ַ���תСд
void  toLower_(string & src);
#endif