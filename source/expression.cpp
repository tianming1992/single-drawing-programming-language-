/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file expresiion.cpp
/*@author 戴潜
/*@date    2011.11.11
/*@brief   程序运行模块
/*
/*********************************************************************************************************************/
#include "expression.h"


/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  string strh  命令字符串
/*@param[out] 
/*@return  bool
/*@pre
/*@exception  
/********************************************************************************************************************/
bool isCorrectFloat(string strh)      //判断浮点数是否正确
{
	int size=strh.length();
	int nNumofPoint=0;
	for (int i=0;i<size;i++)
	{
		if (strh[i]==46)
		{
			nNumofPoint++;
		}
	}
	if (nNumofPoint>1)           //浮点数的小数点大于一个
	{
		return false;
	}
	else
	{
		return true;
	}
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  char strh 命令字符
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool isOperand(char strh)     //判断是不是操作符
{
	if (strh>39&&strh<44)
	{
		return true;
	}
	if (strh>59&&strh<63)
	{
		return true;
	}
	if (strh==45||strh==47)
	{
		return true;
	}
	return false;

}

//********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  char strh 命令字符
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool isAndOrSub(char strh)        //判断是不是加号或者减号
{
	if (strh==43||strh==45)
	{
		return true;
	}
	return false;
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  char strh 命令字符
/*@param[out]  
/*@return  int
/*@pre
/*@exception
/********************************************************************************************************************/
int changeToInt(char strh)     //把运算符号转化成对应的实际操作符
{
	switch(strh)
	{
	case 43:
		return 0;
	case 45:
		return 1;
	case 42:
		return 2;
	case 47:
		return 3;
	case 40:
		return 4;
	case  41:
		return 5;
	case 60:
		return 6;
	case 62:
		return 7;
	case  61:
		return 8;
	case 100:
		return 9;
	case 101:
		return 10;
	}
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  vfloat sub,char theta,float subed命令字符
/*@param[out]  
/*@return float
/*@pre
/*@exception
/********************************************************************************************************************/
float operate(float sub,char theta,float subed)    //执行实际运算
{
	switch(theta)
	{
	case 43:
		return sub+subed;
	case 45:
		return sub-subed;
	case 42:
		return sub*subed;
	case 47:
		return sub/subed;
	case 60:
		return float(int(sub)<int(subed));
	case 62:
		return float(int(sub)>int(subed));
	case 61:
		return float(int(sub)==int(subed));
	case 100:
		return float(int(sub)<=int(subed));
	case 101:
		return float(int(sub)>=int(subed));
	}
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  string strh 命令字符   ，int i运算到的位置
/*@param[out]  
/*@return bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool findleft(string strh,int i)    //判断加号前一个字符是不是加减乘除号
{
	for (;i>=0;i--)
	{
		if (strh[i]!=' ')
		{
			if (strh[i]==43||strh[i]==45||strh[i]==100||strh[i]==101||strh[i]==60||
				strh[i]==61||strh[i]==62||strh[i]==35||strh[i]==42||strh[i]==47||strh[i]=='(')   //判断加号前一个字符是不是加减乘除号
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  string strh 命令字符   ，int i运算到的位置
/*@param[out]  
/*@return bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool findrightnum(string strh ,int i)
{
	for (;i<strh.length()-1;i++)
	{
		if (strh[i]!=' ')
		{
			if (strh[i]>47&&strh[i]<58||strh[i]==46)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in] string strh 命令字符   ，int i运算到的位置
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool findrightequal(string strh ,int i)     //判断下一个字符是不是等于号
{
	for (;i<strh.length()-1;i++)
	{
		if (strh[i]!=' ')
		{
			if (strh[i]==61)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  string sExpression用户输入命令字符串
/*@param[out]  float &lastvalue 返回命令是不是合法
/*@return  bool
/*@pre
/*@exception    若输入命令表达式合法，返回、true，否则返回false
/********************************************************************************************************************/
bool ValueExpression(string sExpression,float &lastvalue)
{
	sExpression+=')';
	sExpression='+'+sExpression;
	stack<char>charStack;
	stack<double>floatStack;
	charStack.push('#');

	if (isAndOrSub(sExpression[0]))
	{   
		sExpression ='0'+sExpression;
	}
	double tempfloat= 1;      //记录正负号出现的次数
	char theta;            //记录此次运算符号
	string renum="";         //记录多位数字的实际值
	double sub,subed;
	lastvalue=0;            //记录最终运算值
	int i=-1,j=1;
	int nIsSOrBig;
	int flag=0;           //记录正负号	int flag1=0;      //记录开始的数字数
	bool count;
	int  compareValue[11][11]={{2,2,0,0,0,2,2,2,2,2,2},            //对应的操作符优先值
	{2,2,0,0,0,2,2,2,2,2,2},
	{2,2,2,2,0,2,2,2,2,2,2},
	{2,2,2,2,0,2,2,2,2,2,2},
	{0,0,0,0,0,1,0,0,0,0,0},
	{2,2,2,2,3,2,2,2,2,2,2},
	{0,0,0,0,0,2,2,2,2,2,2},
	{0,0,0,0,0,2,2,2,2,2,2},
	{0,0,0,0,0,2,0,0,2,0,0},
	{0,0,0,0,0,2,2,2,2,2,2},
	{0,0,0,0,0,2,2,2,2,2,2}};

	while(++i<=sExpression.length()+1)         //若果当前已到达最后一个字符
	{
		int k=sExpression.length();
		if (sExpression[i]==' ')            //如果是空格，则忽略
		{
			continue;
		}
		char w=sExpression[i];
		if (sExpression[i]>47&&sExpression[i]<58||sExpression[i]==46) //如果是数字
		{
			float truenum;
			renum+=sExpression[i];
			if (!isCorrectFloat(renum))  //如果不是正确的float型的数字
			{
				return false;
			}
			truenum=atof(renum.c_str());
			if (!findrightnum(sExpression,i+1))  //右边不是数字，则加入数字栈
			{
				if (flag==0)           // 数字之前没有正负号
				{
					floatStack.push(truenum);
					renum=""; 
				}
				else if (flag=1)   // 数字之前有正负号
				{
					truenum=tempfloat*truenum;     //转换成实际数字
					floatStack.push(truenum);
					flag=0;
					renum=""; 

				}
			}
			continue;
		}
		if (isOperand(sExpression[i]))    //如果是运算符
		{
			nIsSOrBig=findleft(sExpression,i-1);
			if (isAndOrSub(sExpression[i])&&nIsSOrBig)  //如果是+或 -的特殊情况
			{
				if (sExpression[i]==45)    // 如果是减号则变号
				{
					tempfloat=tempfloat*(-1);

				}
				flag=1;
			}

			else        //如果是普通情况
			{
				if (j==0)
				{
					j=1;
				}
				if (charStack.size()==1)
				{
					if (sExpression[i]==60&&findrightequal(sExpression,i+1))  //处理<=的情况
					{
						sExpression[i]=sExpression[i+1]=100;
						i++;	
					}
					if (sExpression[i]==62&&findrightequal(sExpression,i+1))  //处理>=的情况
					{
						sExpression[i]=sExpression[i+1]=101;
						i++;	
					}
					charStack.push(sExpression[i]);
				}
				else
				{
					if (sExpression[i]==60&&findrightequal(sExpression,i+1))  //处理<=的情况
					{
						sExpression[i]=sExpression[i+1]=100;
						i++;	
					}
					if (sExpression[i]==62&&findrightequal(sExpression,i+1))  //处理>=的情况
					{
						sExpression[i]=sExpression[i+1]=101;
						i++;	
					}
					int ny=changeToInt(charStack.top());           // 优先级矩阵的y坐标
					int nx=changeToInt(sExpression[i]);         // 优先级矩阵的x坐标
					switch(compareValue[ny][nx])
				 {
					case 0:                                      //优先级比输入字符小，则加入堆栈
						charStack.push(sExpression[i]);
						break;
					case 3:                                     //括号输入错误
						return false;	
					case 1:                        //优先级与输入字符相等，则加入堆栈
						charStack.pop();
						break;
					case 2:                     //优先级比输入字符大，则计算当前字运算
						theta=charStack.top();
						charStack.pop();
						subed=floatStack.top();
						if (subed ==0 && theta == '/')           //分母是0，返回
						{
							return false;
						}
						floatStack.pop();           //弹出运算符
						if (floatStack.size()==0)
						{
							return false;
						}
						sub=floatStack.top();
						if (floatStack.size()==0)
						{
							return false;
						}
						floatStack.pop();
						float value=operate(sub,theta,subed);
						floatStack.push(value);
						i--;
						j=0;
						if (i==(sExpression.length()-2)&&charStack.top()=='#')       //当前运算完毕
						{
							lastvalue=floatStack.top();
							return true;
						}
						break;

					}
				}
			}
			continue;
		}
		return false;
	}


}

