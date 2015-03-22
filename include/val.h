/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file turtle.h
/*@author  邹天明
/*@date    2011.11.11
/*@brief   定义变量结构体
/*
/*********************************************************************************************************************/

#ifndef  _VAL_H_
#define  _VAL_H_

#include<string>
using namespace std;

#define     VAL_STRING  0  //字符串变量
#define     VAL_FLOAT    1  //数值变量
#define   UNDEFINED 3 

//定义变量结构体
struct stVal{
string m_valName; //变量名
string m_str_value;//字符串变量值
float  m_f_value;//数值变量值
char m_valKind;//变量的类型
};

#endif