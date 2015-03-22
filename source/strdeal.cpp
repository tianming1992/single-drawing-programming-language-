/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file strdeal.cpp
/*@author  ������
/*@date    2011.11.11
/*@brief   �ַ��������һЩ����
/*
/*********************************************************************************************************************/

#include "strdeal.h"

/********************************************************************************************************************
/*@brief ɾ���հ�
/*@author ������
/*@param[in]  string &str
/*@param[out]  string &str
/*@return  void
/*@pre  ע������Ŀհ׷��������з�
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
/*@brief ����ĳ���ַ��ָ��ַ���
/*@author ������
/*@param[in]  const string&s char c
/*@param[out]  vector<string>&v
/*@return  void
/*@pre  
/*@exception
/********************************************************************************************************************/
void split(const string&s , char c , vector<string>&v)//�ָ��ַ���
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
/*@brief ��ȡ�ı��ļ�
/*@author ������
/*@param[in]  string filename
/*@param[out]  string &storeStr
/*@return bool  true �ɹ� false ʧ��
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
/*@brief �ж�ĳ�ַ����Ƿ�����������ĸ���
/*@author ������
/*@param[in]  const string &check
/*@param[out]  
/*@return bool  true �������� false ����������
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

//�жϱ�ʶ���Ƿ�Ϸ�
bool isIllIdentifer(const string &check)
{
	long int i =0;
    if (check.length() > 0)//���ȴ���0
    {  
		if (0 !=  isalpha(check[0]) || check[0] == '_')//��ͷΪ��ĸ���»���
		{
			while(i<check.length())
			{
				if (0 == isalnum(check[i]) && check[i] != '_')//�����Ϊ��ĸ���ֲ��Ҳ�Ϊ�»��ߣ��Ƿ�
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
/*@brief ��ȡĳ���ַ�������
/*@author ������
/*@param[in]  const string & str
/*@param[out]  
/*@return ����ֵ
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
/*@brief �ж��Ƿ�Ϊ������
/*@author ������
/*@param[in] char c
/*@param[out]  
/*@return true ��  false ��
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
/*@brief//��ȡ�ַ���srcλ��i��һ���ǿ��ַ�
/*@author ������
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
/*@brief///�ж�ĳ���ַ�����ĳ��λ���ַ��Ƿ�Ϊת���ַ�
/*@author ������
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
/*@brief//�ָ�һ���ַ���Ϊ�������ʽ �� ���� ���ʽ�Ķ���Ϊ :
/*���ʽ �� ���� �ַ�����  ��ֵ���� ������ С������ɵ�ĳ���������С� һ�����ʽ�Ľ������������¶���ȷ��
/*1. ��������
/*2.��ǰ�ַ����ǲ������ҷǿ�
/*3.��һ���ǿ��ַ����ǲ�����
/*4.��һ���ַ��ǿ��ַ�
/*@author ������
/*@param[in] string src
/*@param[out]   vector<string> & result
/*@return void
/*@pre  
/*@exception
/********************************************************************************************************************/
void splitExpression(string src , vector<string> & result)//�ָ���ʽ
{
	int nBracePair = 0;
	int nBrace = 0;
	int nQuote = 0;
	int i =0 ;
	while(i < src.length())  //����Ƿ�����ȷ������ƥ����Ŀ
	{  
		
		if (src[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
                 if (false == isChangeMean(i , src))//���ַ����������ŷ�ת���ַ�
                 {
					 nQuote = 0;
                 }
			}
		}
	
		if (src[i] == '('  &&  nQuote ==0)//�����Ų��ҷ��ַ�����
		{
			++nBrace;
		}
		if (src[i] == ')' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
		{
			--nBrace;
		}

		if(nBrace == 0 && nQuote == 0)//�����ż��ַ�����
		{
             if(false == isOperate(src[i]) && (src[i] != ' '|| src[i] != '\n' || src[i] != '\t' ))//��ǰ�ַ����ǲ������ҷǿ�
			 {
                  if (false == isOperate( getNextNoEmptyChar(i , src)))//��һ���ǿ��ַ����ǲ����������ַ�������
                  {
                        if ( (i + 1) < src.length() && (src[i + 1] == ' '|| src[i+1] == '\n' || src[i+1] == '\t' ))//��һ���ַ�Ϊ���ַ�
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
/*@brief///�ж�ĳ���ַ�����ĳ��λ���ַ��Ƿ�Ϊת���ַ�
/*@author ������
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
	while(i < tempCmd.length())  //����Ƿ�����ȷ������ƥ����Ŀ
	{  
		if (tempCmd[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , tempCmd))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}

		if (tempCmd[i] == '['  &&  nQuote ==0)//�����Ų��ҷ��ַ�����
		{
			++nBrace;
			find = true ;
		}
		if (tempCmd[i] == ']' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
		{
			--nBrace;
		}

		if(nBrace == 0 && nQuote == 0 &&tempCmd[i]==']' ) ++nBracePair;
		++i;
	}
	return nBracePair;
}

/********************************************************************************************************************
/*@brief//�ж��Ƿ��Ǳ���
/*@author ������
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
/*@brief//�Ƿ�Ϊ�ַ�������
/*@author ������
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
/*@brief//�ж�һ�����Ƿ�Ϊ����
/*@author ������
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
/*@brief//��һ����ֵ�ַ���תΪ��׼����   ��ν��׼����Ҳ����С����󳤶Ȳ�����4���޶���0
/*@author ������
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
/*@brief//�����ַ���ת���ַ�
/*@author ������
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
	   if (src[i] == '\\')//����ת�����
	   {
		   ++i;      //��ȡ��һ���ַ�
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
/*@brief//�ַ���תСд
/*@author ������
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