/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file error_out.cpp
/*@author  ������
/*@date    2011.11.11
/*@brief   ������ľ��
/*
/*********************************************************************************************************************/

#include "error_out.h"

static  int  g_error_num = 0; //�����ļ���������
static  list<stErrorInfo> errorList;//����������  �ؼ���Ϊ�ļ���
static  string sFileName;  //��ǰ������ļ���

/********************************************************************************************************************
/*@brief//�������ַ�����λ�ñ���
/*@author ������
/*@param[in]  const string &out , const int & pos , const string & srcProgram
/*@param[out] 
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void  error_out_pos(const string &out , const int & pos , const string & srcProgram)
{
	int i = 0 ;
	int nLine = 1;

	while( i != pos)
	{
       if (srcProgram[i] == '\n')
       {
		   ++nLine ;
       }
	   ++i;
	}
	char error[250];
	sprintf(error , "%s --- line at : %d\n" , out.c_str() , nLine);
	string sError =  error;
	for (list<stErrorInfo>::iterator it =errorList.begin() ; it != errorList.end() ;++it)
	{
		if ((*it).fileName == sFileName)
		{
			(*it).errorInfo.push_back(sError);//��������Ϣ������Ӧ���ļ�������
		}
	}
	++g_error_num;
	return;
}

/********************************************************************************************************************
/*@brief�����������������µĹؼ���
/*@author ������
/*@param[in] const string & fileName
/*@param[out] 
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void pFileName(const string & fileName)
{
	char cFileName[100];
	sprintf(cFileName , "File Name:  %s" ,  fileName.c_str());
	sFileName = cFileName;
	for (list<stErrorInfo>::iterator it =errorList.begin() ; it != errorList.end() ;++it)
	{
		if ((*it).fileName == sFileName)
		{
			return;
		}
	}
	stErrorInfo errorToAdd;
	errorToAdd.fileName = sFileName;
	errorList.push_back(errorToAdd);//Ϊ���ļ�������������
	return;
}

/********************************************************************************************************************
/*@brief//�������ַ�����λ�û�ȡ�к�
/*@author ������
/*@param[in] const int & pos , const string & srcProgram
/*@param[out] 
/*@return  int �����к�
/*@pre
/*@exception
/********************************************************************************************************************/
int getLineNumBer(const int & pos , const string & srcProgram)
{
	int i = 0 ;
	int nLine = 1;

	while( i != pos)
	{
		if (srcProgram[i] == '\n')
		{
			++nLine ;
		}
		++i;
	}
	return nLine ;
}

/********************************************************************************************************************
/*@brief////�������ַ������кű���
/*@author ������
/*@param[in] const int & pos , const string & srcProgram
/*@param[out] 
/*@return  void 
/*@pre
/*@exception
/********************************************************************************************************************/
void  error_out_line(const string &out , const int & line )
{
	char error[250];
	sprintf(error , "%s --- line at : %d\n"  , out.c_str() , line);
	string sError =  error;
	for (list<stErrorInfo>::iterator it =errorList.begin() ; it != errorList.end() ;++it)
	{
		if ((*it).fileName == sFileName)
		{
			(*it).errorInfo.push_back(sError);//��������Ϣ������Ӧ���ļ�������
		}
	}
	++g_error_num;
	return;
}


/********************************************************************************************************************
/*@brief�������������׼����
/*@author ������
/*@param[in] 
/*@param[out] 
/*@return  void 
/*@pre
/*@exception
/********************************************************************************************************************/
void prinError()//�������������׼����
{
	if(g_error_num)
	{
		for (list<stErrorInfo>::iterator it =errorList.begin() ; it != errorList.end() ;++it)
	    {  
       	     fprintf(stderr , "\n\n-------------%s-----------------------------\n\n"  , (*it).fileName.c_str());
	         int i =0;
		     while(i < (*it).errorInfo.size())
		    {
			    fprintf(stderr , "error %d :" , i+1);
			    fprintf(stderr , "%s" , (*it).errorInfo[i].c_str());
			    ++i;
		     }
	     }
         fprintf(stderr, "\n\n***********  %d errors  *********  SeedPk By ZMQ  @2011  *********\n" ,g_error_num);
	}
}