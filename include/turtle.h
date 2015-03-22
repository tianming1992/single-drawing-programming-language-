/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file turtle.h
/*@author  ��Ǳ
/*@date    2011.11.11
/*@brief   ��ͼ����ִ��ģ��
/*
/*********************************************************************************************************************/

#ifndef  _TURTLE_
#define  _TURTLE_

#include  <cairo-pdf.h>
#include  <cairo.h>
#include <string>
#include <iostream>
#include <cmath> 
#include <vector>
#include <list>

#define   PNG   0
#define   PDF   1
using namespace std;
#define PI 3.14159265

//�洢��ʷ��ͼ���� ����ҳ�߾��ػ�
struct hisCmd{
	string m_name;
	vector<float> params;
	string txtname;
};

//�ڹ�ṹ��
struct stTurtle{
	float m_currX;//��ǰx����
	float m_currY;//��ǰy����
	float m_last_currX;//�ϴ�x����
	float m_last_currY;//�ϴ�y����
	float m_max_positive_x;  //���x����������
	float m_max_negtive_x;  //���x�Ḻ������
	float m_max_positive_y;  //���y����������
	float m_max_negtive_y;  //���y�Ḻ������
	bool flag_max_isset;  //�Ƿ�ֵ
	float m_max_y;  //���y������
	float m_currAngle;//��ǰ�Ƕ�
	bool  m_write;//�Ƿ����
	cairo_surface_t *surface;//��ͼ��Ϣ
	cairo_t *cr;
	int margin; //�߾�  ���marginС��0  ��ʾ��-m����  �����ڵ���0  ��ʾ��-m���� ��ֵ�ڱ�������
	string filename;     //����filenameΪ�� ����Ĭ�� slogoΪ�ļ������ļ� �������ɸ��ļ���
	int type;//���typeΪ0 ����png  Ϊ1����pdf
	bool record;
	list<hisCmd> cmds;//��ʷ����
	string initfilename;
};

void initpaint(stTurtle &stCurrTurtle);       //��ʼ��
void FD(stTurtle &stCurrTurtle,float length);    //ǰ��
void BK(stTurtle &stCurrTurtle,float length); //����
void RT(stTurtle &stCurrTurtle,float angle); //��ת
void LT(stTurtle &stCurrTurtle,float angle); //��ת
void PU(stTurtle &stCurrTurtle);  //̧��;
void PD(stTurtle &stCurrTurtle);  //���;
void CS(stTurtle &stCurrTurtle); //���ͼ�Σ��ص�ԭ�㣬����0��
void HOME(stTurtle &stCurrTurtle); //���ͼ��
void SETX(stTurtle &stCurrTurtle,float fx_axis); //�趨x����
void SETY(stTurtle &stCurrTurtle,float fy_axis); //�趨y����
void SETXY(stTurtle &stCurrTurtle,float fx_axis,float fy_axis);//�趨x,y����
void SETH(stTurtle &stCurrTurtle,float angle); //�Ƕ�
void print(stTurtle &stCurrTurtle,string txt); //��ӡ�ַ�
void  destroy_turtle(stTurtle &stCurrTurtle); //�ڶ�����������
void setcolor(stTurtle &stCurrTurtle,float red,float green, float blue);
void drawcircle(stTurtle &stCurrTurtle,float radius);
#endif 