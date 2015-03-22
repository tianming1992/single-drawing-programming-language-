/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file expresiion.cpp
/*@author ��Ǳ
/*@date    2011.11.11
/*@brief   ��������ģ��
/*
/*********************************************************************************************************************/
#include "expression.h"


/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  string strh  �����ַ���
/*@param[out] 
/*@return  bool
/*@pre
/*@exception  
/********************************************************************************************************************/
bool isCorrectFloat(string strh)      //�жϸ������Ƿ���ȷ
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
	if (nNumofPoint>1)           //��������С�������һ��
	{
		return false;
	}
	else
	{
		return true;
	}
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  char strh �����ַ�
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool isOperand(char strh)     //�ж��ǲ��ǲ�����
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  char strh �����ַ�
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool isAndOrSub(char strh)        //�ж��ǲ��ǼӺŻ��߼���
{
	if (strh==43||strh==45)
	{
		return true;
	}
	return false;
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  char strh �����ַ�
/*@param[out]  
/*@return  int
/*@pre
/*@exception
/********************************************************************************************************************/
int changeToInt(char strh)     //���������ת���ɶ�Ӧ��ʵ�ʲ�����
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  vfloat sub,char theta,float subed�����ַ�
/*@param[out]  
/*@return float
/*@pre
/*@exception
/********************************************************************************************************************/
float operate(float sub,char theta,float subed)    //ִ��ʵ������
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  string strh �����ַ�   ��int i���㵽��λ��
/*@param[out]  
/*@return bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool findleft(string strh,int i)    //�жϼӺ�ǰһ���ַ��ǲ��ǼӼ��˳���
{
	for (;i>=0;i--)
	{
		if (strh[i]!=' ')
		{
			if (strh[i]==43||strh[i]==45||strh[i]==100||strh[i]==101||strh[i]==60||
				strh[i]==61||strh[i]==62||strh[i]==35||strh[i]==42||strh[i]==47||strh[i]=='(')   //�жϼӺ�ǰһ���ַ��ǲ��ǼӼ��˳���
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  string strh �����ַ�   ��int i���㵽��λ��
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in] string strh �����ַ�   ��int i���㵽��λ��
/*@param[out]  
/*@return  bool
/*@pre
/*@exception
/********************************************************************************************************************/
bool findrightequal(string strh ,int i)     //�ж���һ���ַ��ǲ��ǵ��ں�
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
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  string sExpression�û����������ַ���
/*@param[out]  float &lastvalue ���������ǲ��ǺϷ�
/*@return  bool
/*@pre
/*@exception    ������������ʽ�Ϸ������ء�true�����򷵻�false
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
	double tempfloat= 1;      //��¼�����ų��ֵĴ���
	char theta;            //��¼�˴��������
	string renum="";         //��¼��λ���ֵ�ʵ��ֵ
	double sub,subed;
	lastvalue=0;            //��¼��������ֵ
	int i=-1,j=1;
	int nIsSOrBig;
	int flag=0;           //��¼������	int flag1=0;      //��¼��ʼ��������
	bool count;
	int  compareValue[11][11]={{2,2,0,0,0,2,2,2,2,2,2},            //��Ӧ�Ĳ���������ֵ
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

	while(++i<=sExpression.length()+1)         //������ǰ�ѵ������һ���ַ�
	{
		int k=sExpression.length();
		if (sExpression[i]==' ')            //����ǿո������
		{
			continue;
		}
		char w=sExpression[i];
		if (sExpression[i]>47&&sExpression[i]<58||sExpression[i]==46) //���������
		{
			float truenum;
			renum+=sExpression[i];
			if (!isCorrectFloat(renum))  //���������ȷ��float�͵�����
			{
				return false;
			}
			truenum=atof(renum.c_str());
			if (!findrightnum(sExpression,i+1))  //�ұ߲������֣����������ջ
			{
				if (flag==0)           // ����֮ǰû��������
				{
					floatStack.push(truenum);
					renum=""; 
				}
				else if (flag=1)   // ����֮ǰ��������
				{
					truenum=tempfloat*truenum;     //ת����ʵ������
					floatStack.push(truenum);
					flag=0;
					renum=""; 

				}
			}
			continue;
		}
		if (isOperand(sExpression[i]))    //����������
		{
			nIsSOrBig=findleft(sExpression,i-1);
			if (isAndOrSub(sExpression[i])&&nIsSOrBig)  //�����+�� -���������
			{
				if (sExpression[i]==45)    // ����Ǽ�������
				{
					tempfloat=tempfloat*(-1);

				}
				flag=1;
			}

			else        //�������ͨ���
			{
				if (j==0)
				{
					j=1;
				}
				if (charStack.size()==1)
				{
					if (sExpression[i]==60&&findrightequal(sExpression,i+1))  //����<=�����
					{
						sExpression[i]=sExpression[i+1]=100;
						i++;	
					}
					if (sExpression[i]==62&&findrightequal(sExpression,i+1))  //����>=�����
					{
						sExpression[i]=sExpression[i+1]=101;
						i++;	
					}
					charStack.push(sExpression[i]);
				}
				else
				{
					if (sExpression[i]==60&&findrightequal(sExpression,i+1))  //����<=�����
					{
						sExpression[i]=sExpression[i+1]=100;
						i++;	
					}
					if (sExpression[i]==62&&findrightequal(sExpression,i+1))  //����>=�����
					{
						sExpression[i]=sExpression[i+1]=101;
						i++;	
					}
					int ny=changeToInt(charStack.top());           // ���ȼ������y����
					int nx=changeToInt(sExpression[i]);         // ���ȼ������x����
					switch(compareValue[ny][nx])
				 {
					case 0:                                      //���ȼ��������ַ�С��������ջ
						charStack.push(sExpression[i]);
						break;
					case 3:                                     //�����������
						return false;	
					case 1:                        //���ȼ��������ַ���ȣ�������ջ
						charStack.pop();
						break;
					case 2:                     //���ȼ��������ַ�������㵱ǰ������
						theta=charStack.top();
						charStack.pop();
						subed=floatStack.top();
						if (subed ==0 && theta == '/')           //��ĸ��0������
						{
							return false;
						}
						floatStack.pop();           //���������
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
						if (i==(sExpression.length()-2)&&charStack.top()=='#')       //��ǰ�������
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

