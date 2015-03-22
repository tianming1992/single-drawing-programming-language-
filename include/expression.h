/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file expression.h
/*@author 戴潜
/*@date    2011.11.11
/*@brief   表达式模块
/*
/*********************************************************************************************************************/
#ifndef  _EXPRESSION_H_
#define   _EXPRESSION_H_

#include <iostream>
#include <vector>
#include <stack>
#include<string>
using namespace std; 

bool ValueExpression(string sExpression,float &lastvalue);  //计算表达式的值

#endif  