/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file strdeal.cpp
/*@author  邹天明
/*@date    2011.11.11
/*@brief   字符串处理的一些操作
/*
/*********************************************************************************************************************/

#include "strdeal.h"

/********************************************************************************************************************
/*@brief 删除空白
/*@author 邹天明
/*@param[in]  string &str
/*@param[out]  string &str
/*@return  void
/*@pre  注意这里的空白符包含换行符
/*@exception
/********************************************************************************************************************/
void delSpace(string &str) 
{  
	string::iterator it;
	string::reverse_iterator rit;
	while (!str.empty())
	{
		it = str.begin();
		if (*it == ' ' || *it == '\n' || *it == '\t')
		{
			str.erase(it);
			continue;
		}
		break;
	}
	while (!str.empty())
	{
		rit = str.rbegin();
		if (*rit == ' '|| *rit == '\n' || *rit == '\t')
		{
			str = str.substr(0,str.length() - 1);
			continue;
		}
		break;
	}
}

/********************************************************************************************************************
/*@brief 按照某个字符分割字符串
/*@author 邹天明
/*@param[in]  const string&s char c
/*@param[out]  vector<string>&v
/*@return  void
/*@pre  
/*@exception
/********************************************************************************************************************/
void split(const string&s , char c , vector<string>&v)//分割字符串
{
	long int i =0 ,j =0;
	j = s.find(c);
    if (j == string::npos)
    {
		v.push_back(s);
		return;
    }
	while(j != string::npos)
	{
		v.push_back(s.substr(i , j -i));
		i = ++j;
		j = s.find(c , j);

		if (j == string::npos)
		{
			v.push_back(s.substr(i ,s.length()));
		}
	}
}

/********************************************************************************************************************
/*@brief 读取文本文件
/*@author 邹天明
/*@param[in]  string filename
/*@param[out]  string &storeStr
/*@return bool  true 成功 false 失败
/*@pre  
/*@exception
/********************************************************************************************************************/
bool getString(string filename , string &storeStr)
{
	char ch;
	ifstream infile(filename.c_str() , ios::in);
	if (!infile)
	{
		return false;
	}
	while (infile.get(ch))
	{
		storeStr.push_back(ch);
	}
	return true;
}

/********************************************************************************************************************
/*@brief 判断某字符串是否由数字与字母组成
/*@author 邹天明
/*@param[in]  const string &check
/*@param[out]  
/*@return bool  true 满足条件 false 不满足条件
/*@pre  
/*@exception
/********************************************************************************************************************/
bool isNumOrAlpha(const string &check)
{
	unsigned int i = 0 ;
	while(i<check.length())
	{
		if (0 == isalnum(check[i]))
		{
			return false ;
		}
		i++ ;
	}
	return true ;
}

//判断标识符是否合法
bool isIllIdentifer(const string &check)
{
	long int i =0;
    if (check.length() > 0)//长度大于0
    {  
		if (0 !=  isalpha(check[0]) || check[0] == '_')//开头为字母或下划线
		{
			while(i<check.length())
			{
				if (0 == isalnum(check[i]) && check[i] != '_')//如果不为字母数字并且不为下划线，非法
				{
					return false ;
				}
				i++ ;
			}
			return true;
		}
        
    }
	return false ;
}

/********************************************************************************************************************
/*@brief 获取某个字符串行数
/*@author 邹天明
/*@param[in]  const string & str
/*@param[out]  
/*@return 行数值
/*@pre  
/*@exception
/********************************************************************************************************************/
int getLine(const string & str )
{
	long int i =0;
	int nLine =0;
	while(i < str.length())
	{
        if (str[i] == '\n')
        {
			++nLine;
        }
		i++ ;
	}
	return nLine ;
}

/********************************************************************************************************************
/*@brief 判断是否为操作符
/*@author 邹天明
/*@param[in] char c
/*@param[out]  
/*@return true 是  false 否
/*@pre  
/*@exception
/********************************************************************************************************************/
bool isOperate(char c)
{
	if (c == '>' || c == '<' || c == '=' || c == '+' || c == '-' || c== '*' || c == '/')
	{
		return true;
	}
	return false;
}

/********************************************************************************************************************
/*@brief//获取字符串src位置i下一个非空字符
/*@author 邹天明
/*@param[in] long int i , const string & src
/*@param[out]  
/*@return char
/*@pre  
/*@exception
/********************************************************************************************************************/
char getNextNoEmptyChar(long int i , const string & src)
{
   while(++i < src.length())
   {
         if (src[i] != '\n' && src[i] != '\t' && src[i] != ' ')
         {
			 return src[i];
         }
   }
   return -1;
}

/********************************************************************************************************************
/*@brief///判断某个字符串中某个位置字符是否为转义字符
/*@author 邹天明
/*@param[in] long int i , const string & src
/*@param[out]  
/*@return bool
/*@pre  
/*@exception
/********************************************************************************************************************/
bool  isChangeMean(long int i , const string & src)
{  
	int amount =0;
    while(i >0 &&src[--i] == '\\')
	{
          ++ amount;
	}
	if(amount % 2 != 0) return true;
	return false;
}

/********************************************************************************************************************
/*@brief//分割一个字符串为单个表达式 ， 其中 表达式的定义为 :
/*表达式 是 变量 字符常量  数值常量 操作符 小括号组成的某种有序序列。 一个表达式的结束条件由以下断言确立
/*1. 在括号外
/*2.当前字符不是操作符且非空
/*3.下一个非空字符不是操作符
/*4.下一个字符是空字符
/*@author 邹天明
/*@param[in] string src
/*@param[out]   vector<string> & result
/*@return void
/*@pre  
/*@exception
/********************************************************************************************************************/
void splitExpression(string src , vector<string> & result)//分割表达式
{
	int nBracePair = 0;
	int nBrace = 0;
	int nQuote = 0;
	int i =0 ;
	while(i < src.length())  //检查是否有正确的括号匹配数目
	{  
		
		if (src[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
                 if (false == isChangeMean(i , src))//在字符串内且引号非转义字符
                 {
					 nQuote = 0;
                 }
			}
		}
	
		if (src[i] == '('  &&  nQuote ==0)//开括号并且非字符串内
		{
			++nBrace;
		}
		if (src[i] == ')' &&  nQuote ==0)////闭括号并且非字符串内
		{
			--nBrace;
		}

		if(nBrace == 0 && nQuote == 0)//在括号及字符串外
		{
             if(false == isOperate(src[i]) && (src[i] != ' '|| src[i] != '\n' || src[i] != '\t' ))//当前字符不是操作符且非空
			 {
                  if (false == isOperate( getNextNoEmptyChar(i , src)))//下一个非空字符不是操作符或者字符串结束
                  {
                        if ( (i + 1) < src.length() && (src[i + 1] == ' '|| src[i+1] == '\n' || src[i+1] == '\t' ))//下一个字符为空字符
                        {
                             result.push_back(src.substr(0 , i+1));
							 src.erase(0 , i+1);
							 delSpace(src);
							 i =  0;
							 continue;
                        }

                  }
			 }
		}
		++i;
	}
	delSpace(src);
	if(false == src.empty()) result.push_back(src);
}


/********************************************************************************************************************
/*@brief///判断某个字符串中某个位置字符是否为转义字符
/*@author 邹天明
/*@param[in] long int i , const string & src
/*@param[out]  
/*@return bool
/*@pre  
/*@exception
/********************************************************************************************************************/
int blockPairs(const string &  tempCmd)
{
	int nBracePair = 0;
	int nBrace = 0;
	int nQuote = 0;
	int i =0 ;
	bool find = false;
	while(i < tempCmd.length())  //检查是否有正确的括号匹配数目
	{  
		if (tempCmd[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , tempCmd))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}

		if (tempCmd[i] == '['  &&  nQuote ==0)//开括号并且非字符串内
		{
			++nBrace;
			find = true ;
		}
		if (tempCmd[i] == ']' &&  nQuote ==0)////闭括号并且非字符串内
		{
			--nBrace;
		}

		if(nBrace == 0 && nQuote == 0 &&tempCmd[i]==']' ) ++nBracePair;
		++i;
	}
	return nBracePair;
}

/********************************************************************************************************************
/*@brief//判断是否是变量
/*@author 邹天明
/*@param[in] string  & param
/*@param[out]  
/*@return bool
/*@pre  
/*@exception
/********************************************************************************************************************/
bool isVal(string  & param)
{
	delSpace(param);
	if (param.length() > 0 && param[0] == ':')
	{
		return true;
	}
	return false;
}

/********************************************************************************************************************
/*@brief//是否为字符串常量
/*@author 邹天明
/*@param[in] string  & param
/*@param[out]  
/*@return bool
/*@pre  
/*@exception
/********************************************************************************************************************/
bool isConstStr(string & param)
{
    delSpace(param);
	if (param.length()> 1 && param[0] == '\"' && param[param.length() -1] == '\"')
	{
		return true ;
	}
	return false ;
}

/********************************************************************************************************************
/*@brief//判断一个数是否为整数
/*@author 邹天明
/*@param[in] float f
/*@param[out]  
/*@return bool
/*@pre  
/*@exception
/********************************************************************************************************************/
bool isInt(float f)
{
     if (f == int(f + 0.5))
     {
		 return true;
     }
	 return false;
}

/********************************************************************************************************************
/*@brief//将一个数值字符串转为标准类型   所谓标准类型也就是小数点后长度不大于4且无多余0
/*@author 邹天明
/*@param[in] string src
/*@param[out]   
/*@return string
/*@pre  
/*@exception
/********************************************************************************************************************/
string turnFstrTostand(string src)
{
    if(src.empty())
	{
		return "";
	}
    long int i = src.rfind('.');
	if (i == string::npos)
	{
		return "";
	}
	string dotTail = src.substr(i+1 , src.length());
	src.erase(i , src.length());
	if (dotTail.length()>4)
	{
		dotTail.erase(4 , dotTail.length());
	}

	while(!dotTail.empty() && dotTail[dotTail.length()-1] == '0')
	{
	   dotTail.erase(dotTail.length()-1 ,1);
	}
	if (dotTail.empty())
	{
        return src;
	}
     return src + '.' + dotTail;
}

/********************************************************************************************************************
/*@brief//处理字符串转义字符
/*@author 邹天明
/*@param[in] string src
/*@param[out]   
/*@return string
/*@pre  
/*@exception
/********************************************************************************************************************/
string  toChangeMean(string src)
{
	long int i =0;
   while(i < src.length())
   {
	   if (src[i] == '\\')//碰到转义符号
	   {
		   ++i;      //获取下一个字符
           if (i < src.length() && (src[i] == '\\' || src[i] == '\"'))
           {
			   src.erase(i-1 , 1);
			    continue;
           }

	   }
	   ++i;
   }
   return src;
}

/********************************************************************************************************************
/*@brief//字符串转小写
/*@author 邹天明
/*@param[in] string & src
/*@param[out] string & src  
/*@return void
/*@pre  
/*@exception
/********************************************************************************************************************/
void  toLower_(string & src)
{
	for (string::iterator it = src.begin() ; it != src.end() ; ++it)
      {
		  if ((*it) >= 'A' && (*it) <= 'Z')
		  {
			  (*it) = tolower((*it));
		  }
      }
	return;
}