/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file turtle.h
/*@author  ������
/*@date    2011.11.11
/*@brief   ��������ṹ��
/*
/*********************************************************************************************************************/

#ifndef  _VAL_H_
#define  _VAL_H_

#include<string>
using namespace std;

#define     VAL_STRING  0  //�ַ�������
#define     VAL_FLOAT    1  //��ֵ����
#define   UNDEFINED 3 

//��������ṹ��
struct stVal{
string m_valName; //������
string m_str_value;//�ַ�������ֵ
float  m_f_value;//��ֵ����ֵ
char m_valKind;//����������
};

#endif