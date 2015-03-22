/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file error_out.cpp
/*@author  邹天明
/*@date    2011.11.11
/*@brief   错误处理木块
/*
/*********************************************************************************************************************/

#include "error_out.h"

static  int  g_error_num = 0; //所有文件错误数量
static  list<stErrorInfo> errorList;//错误索引表  关键字为文件名
static  string sFileName;  //当前报错的文件名

/********************************************************************************************************************
/*@brief//根据在字符串中位置报错
/*@author 邹天明
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
			(*it).errorInfo.push_back(sError);//将错误信息添加入对应的文件索引中
		}
	}
	++g_error_num;
	return;
}

/********************************************************************************************************************
/*@brief向错误索引表中添加新的关键字
/*@author 邹天明
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
	errorList.push_back(errorToAdd);//为新文件建立错误索引
	return;
}

/********************************************************************************************************************
/*@brief//根据在字符串中位置获取行号
/*@author 邹天明
/*@param[in] const int & pos , const string & srcProgram
/*@param[out] 
/*@return  int 返回行号
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
/*@brief////根据在字符串中行号报错
/*@author 邹天明
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
			(*it).errorInfo.push_back(sError);//将错误信息添加入对应的文件索引中
		}
	}
	++g_error_num;
	return;
}


/********************************************************************************************************************
/*@brief将错误输出到标准错误
/*@author 邹天明
/*@param[in] 
/*@param[out] 
/*@return  void 
/*@pre
/*@exception
/********************************************************************************************************************/
void prinError()//将错误输出到标准错误
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