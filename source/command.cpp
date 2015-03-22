/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file command.cpp
/*@author  ������
/*@date    2011.11.11
/*@brief   �������ģ��
/*
/*********************************************************************************************************************/

#include "command.h"

/********************************************************************************************************************
/*@brief //Ԥɨ���򣬻���û��Զ�����̱�  ���װ��funcTables�� 
/*@author ������
/*@param[in]  string & sProgram,const  string & fileName
/*@param[out]  list<stFunc>&funcTables
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void preScan(list<stFunc>&funcTables ,  string & sProgram,const  string & fileName)
{  
	long int i =0 ;
	//�Դ�Сд�����У���תΪСд
	int nQuote = 0;
	for (string::iterator it= sProgram.begin() ; it != sProgram.end() ;  )
	{   
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}
		if ( (*it >= 'A' ) && (*it <= 'Z' ) &&nQuote ==0)//���ַ����ַ�תСд
		{
			*it = tolower(*it);
		}
		++i; 
		++it;
	}

	//����\r
	while(string::npos  !=   (i   =   sProgram.find('\r'))) 
	{
		sProgram.erase(i , 1);
	}
   
	i=0;
	nQuote =0;
	//����ע��
	while(i < sProgram.length())  
	{  
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}

		if (sProgram[i] == ';' && nQuote ==0)//���ַ������ҷ���;
		{
			int j = i;
			while( i++ < sProgram.length() && sProgram[i] != '\n');//�ҵ�����ĩβɾ��ע��
			if(i ==sProgram.length() )
			{
				sProgram.erase(j , sProgram.length());
				break;
			}
			sProgram.erase(j , i - j);
			i = j;
			continue;
		}
		++i;
	}

	nQuote = 0;
	int nBrace =0;
	int nBlock =0;
	i =0 ;
	int last =0;
	int last_small_right =0 ,  last_small_left =0 ;
	int last_block_right =0 ,  last_block_left =0 ;
	//�����﷨����
	while(i < sProgram.length())  //�����Ƿ�ƥ��
	{  
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
				last = i ;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}

		if (sProgram[i] == '('  &&  nQuote ==0)//�����Ų��ҷ��ַ�����
		{
			++nBrace;
			last_small_left = i;
		}
		if (sProgram[i] == ')' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
		{
			--nBrace;
			last_small_right = i;
		}
		if (sProgram[i] == '['  &&  nQuote ==0)//�����Ų��ҷ��ַ�����
		{
			++nBlock;
			last_block_left = i;
		}
		if (sProgram[i] == ']' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
		{
			--nBlock;
			last_block_right = i;
		}

		if(nQuote == 1 && sProgram[i] == '\n')//���ַ������л���
		{
			pFileName(fileName);
			error_out_pos("error symbol \" can not end in different line  "  , i , sProgram);
		}
		++i;
	}
	if (nQuote == 1 )
	{
		pFileName(fileName);
        error_out_pos("error symbol \" mismatch " , last , sProgram);
	}
	if (nBrace > 0)
	{
		pFileName(fileName);
		 error_out_pos("too many symbol ( to match " , last_small_left , sProgram);
	}
	if (nBrace < 0)
	{
		pFileName(fileName);
		error_out_pos("too many symbol ) to match " , last_small_right, sProgram);
	}
	if (nBlock > 0)
	{
		pFileName(fileName);
		error_out_pos("too many symbol [ to match " , last_block_left , sProgram);
	}
	if (nBlock < 0)
	{
		pFileName(fileName);
		error_out_pos("too many symbol ] to match " , last_block_right, sProgram);
	}

	//Ѱ�ҹ��̶������
	getFuncTable(funcTables , sProgram , fileName);
	return ;
}

/********************************************************************************************************************
/*@brief //��ȡ�������к�����
/*@author ������
/*@param[in]  string & sProgram , const  string & fileName
/*@param[out]  list<stFunc>&funcTables
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void getFuncTable(list<stFunc>&funcTables ,  string & sProgram , const  string & fileName)
{
	int nTo =0;
	int nEnd =0,nFunc =0;
	string tempKey1 , tempKey2;
    long int  i =0;
	int length;
	string tempPro = sProgram;
	static vector<string>haveFinded;//�洢�Ѿ�Ѱ�ҹ����ļ� ��ֹ�ظ�����
    
	haveFinded.push_back(fileName);
	//�Դ�Сд�����У���תΪСд
	int nQuote = 0;
	for (string::iterator it= tempPro.begin() ; it != tempPro.end() ;  )
	{   
		char ch = *it;
		if (tempPro[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}
		if ( (*it >= 'A' ) && (*it <= 'Z' ) &&nQuote ==0)//���ַ����ַ�תСд
		{
			*it = tolower(*it);
		}
		++i; 
		++it;
	}

     i =0;
	if (true == sProgram.empty())
	{
		return;
	}
	i = firstKey(0 , tempPro ,length,funcTables,tempKey1);//Ѱ�ҵ�һ���ؼ���
	if (-1 == i)
	{
		return ;
	}
	while(true)
	{
		if (tempKey1 == "import")
		{
			long int j = tempPro.find("\n" , i);
			if (j == string::npos)
			{
				pFileName(fileName);
				error_out_pos("keyword \" import \" wrong parameters " , nEnd , sProgram);
				return;
			}
			string _file = tempPro.substr(i+6 , j - i - 6);
			delSpace(_file);
			string pro1;
			vector<string>::iterator it_;
			bool read = true;
			for( it_ = haveFinded.begin() ; it_ != haveFinded.end() ;++it_)
			{
                if (*it_ == _file)
                {
					read = false;//�Ѿ��������ļ������ظ���ȡ
					break;
                }
			}
			if(read == true )
			{
				if (false == getString(_file ,pro1 ))
				{
					pFileName(fileName);
					error_out_pos("fata error unable to open file : " +_file , nEnd , sProgram);
					return;
				}
				getFuncTable(funcTables , pro1 , _file);
			}
		  }
		if (tempKey1 == "to" && nFunc ==0 )
		{
			nTo = i;
			nFunc =  1;

		}
		if (tempKey1 == "end" && nFunc == 1)
		{
			nEnd = i ;  nFunc = 0; //�ҵ�ĳ���� end ��to
            //���end�Ƿ񵥶�ռ��һ��
			long int line_left = tempPro.rfind("\n" , nEnd );
			long int  line_right = tempPro.find("\n" , nEnd);
			if (line_left != string::npos)
			{
				string check;
				if(line_right != string::npos)
				check = tempPro.substr(line_left ,  line_right - line_left);
				else  check = tempPro.substr(line_left , tempPro.length());
				delSpace( check);
				if (check != "end")
				{
					pFileName(fileName);
					error_out_pos("keyword \" end \" should on a independent line " , nEnd , sProgram);
					 return;
				}
			}
			//��麯��ͷ�Ƿ񵥶�ռ��һ��
			line_left = tempPro.rfind("\n" , nTo);
		    line_right = tempPro.find("\n" , nTo);
			if (line_left != string::npos)
			 {
				 string check = tempPro.substr(line_left , nTo - line_left);
				 delSpace(check);
				 if (!check.empty())
				 {
					 pFileName(fileName);
					 error_out_pos("function header should be on a independent line " , nTo , sProgram);
					 return;
				 }
			 }
			if (line_right != string::npos)
			{
				string check = tempPro.substr(nTo + 2  , line_right - nTo -2);
				delSpace(check);
				if (true == check.empty())
				{
					pFileName(fileName);
					error_out_pos("function header should be on a independent line " , nTo , sProgram);
				 return;
				}
			}

             string sFunc = tempPro.substr(nTo + 2 , nEnd - nTo - 2);
			  long int j = sFunc.find('\n');//δ����ռһ��
			 if (j ==string::npos)
			 {
				 pFileName(fileName);
				 error_out_pos("function define error" , nTo , sProgram);
				 return;
			 }
			// delSpace(sFunc);
			 string sFuncHeader = sFunc.substr(0 , j);//��ȡ����ͷ
			 delSpace(sFuncHeader);
			 if (sFuncHeader.empty())
			 {
				 pFileName(fileName);
				 error_out_pos("wrong  define  function name can not be empty"   , nTo , sProgram);
				 return;
			 }
			  string sFuncBody;
			 if (j < sFunc.length())
			 {
				 sFuncBody   = sFunc.substr(j , sFunc.length());//��ȡ������ 
			 }
			 else
			 {
				 sFuncBody.clear();
			 }
		
			 delSpace(sFuncBody);
			 vector<string>params ;
			 split(sFuncHeader,':' , params);//��ȡ��������
			 stFunc funToAdd;
			 funToAdd.m_argc = params.size() -1;
			 funToAdd.m_lineNumber = getLineNumBer(nTo , sProgram);//���¸ú������к�
			 funToAdd.m_conntext = sFuncBody;
			 delSpace(funToAdd.m_conntext);//��������

			 funToAdd.m_funcName = params[0];//��ȡ������
			 delSpace(funToAdd.m_funcName);
			 if (false == isIllIdentifer(funToAdd.m_funcName))//��麯�����Ƿ�Ϸ�
			 {
				 pFileName(fileName);
				 error_out_pos("wrong identifier  \" " + funToAdd.m_funcName+" \""  , nTo , sProgram);
				   return;
			 }
			 //��麯�����Ƿ�͹ؼ���ͬ��
             
			 if (true == isKeyWord(funToAdd.m_funcName))//��麯�����Ƿ�Ϸ�
			 {
				 pFileName(fileName);
				 error_out_pos("function name can not be same to keyword \" " + funToAdd.m_funcName+" \""  , nTo , sProgram);
				 return;
			 }
			 for (list<stFunc>::iterator it = funcTables.begin() ; it != funcTables.end() ; ++it)//�ж��Ƿ��ظ�����
			 {
				 if((*it).m_funcName == funToAdd.m_funcName)
				 {
					 pFileName(fileName);
					 error_out_pos("redefine function name  \" " + funToAdd.m_funcName+" \""  , nTo , sProgram);
					 return;
				 }
			 }
           
			 for (vector<string>::iterator it = params.begin() +1 ; it != params.end() ; ++it)
			 {
				 stVal  tempVal ;
				 tempVal.m_valName = (*it);//��ȡ���������б�
				 delSpace(tempVal.m_valName );//ȡ���ո�
				 if (false == isIllIdentifer(tempVal.m_valName))//���������Ƿ�Ϸ�
				 {
					 pFileName(fileName);
					 error_out_pos("wrong  identifier \" " + tempVal.m_valName +" \"" , nTo , sProgram);//�������
				     return;
				 }
				 //���������Ƿ��ظ�
				 for (list<stVal>::iterator it = funToAdd.m_parmTable.begin() ; it != funToAdd.m_parmTable.end() ; ++it)
				 {
					 if (tempVal.m_valName == (*it).m_valName)//��⵽ͬ������
					 {
						 pFileName(fileName);
						 error_out_pos("function same params name \" " + tempVal.m_valName+" \""  , nTo , sProgram);//�������
						 return;
					 }
				 }
				 funToAdd.m_parmTable.push_back(tempVal);
			 }
			 funToAdd.m_fileName = fileName;
			 funcTables.push_back(funToAdd);
		
		}
		i = firstKey(i +length  , tempPro ,length,funcTables,tempKey1);
		if(i == -1)
		{
			if (nFunc == 1)
			{
				return;
			}
			break;
		}
	}
}

/********************************************************************************************************************
/*@brief //�ж��Ƿ�Ϊ����
/*@author ������
/*@param[in] const string& check ,const list<stFunc>&fucTables
/*@param[out] 
/*@return  bool  true Ϊ���� false ����
/*@pre
/*@exception
/********************************************************************************************************************/
bool isCmd(const string& check ,const list<stFunc>&fucTables )
{
     if (check== "fd" || check== "bk" || check== "rt" || check == "lt" || check == "pu" ||
		 check == "pd" || check== "cs" || check == "home" || check== "setx" || check== "sety"
		 || check =="setxy" || check=="seth" || check=="make" || check == "print" || check== "stop" || check == "import"
		 || check =="setc" || check == "dc" || check == "dmake")
     {
		 return true ;
     }

	 if (check == "repeat" || check == "to" || check == "end" || check =="if" || check == "ifelse")
	 {
		 return true;
	 }
	 for(list<stFunc>::const_iterator it = fucTables.begin() ; it!=fucTables.end() ; ++it)//���Զ������
	 {
		 if ((*it).m_funcName == check)
		 {
			 return true;
		 }
	 }
	 return false;
}

/********************************************************************************************************************
/*@brief //�ж��Ƿ�Ϊ�ؼ���  ���ؼ��ְ��������������������
/*@author ������
/*@param[in]const string& check 
/*@param[out] 
/*@return  bool  true Ϊ���� false ����
/*@pre
/*@exception
/********************************************************************************************************************/
bool isKeyWord(const string& check  )
{
	if (check== "fd" || check== "bk" || check== "rt" || check == "lt" || check == "pu" ||
		check == "pd" || check== "cs" || check == "home" || check== "setx" || check== "sety"
		|| check =="setxy" || check=="seth" || check=="make" || check == "print" || check== "stop" || check == "import"
	    || check == "setc" || check == "dc" || check == "dmake")
	{
		return true ;
	}

	if (check == "repeat" || check == "to" || check == "end" || check =="if" || check == "ifelse")
	{
		return true;
	}
	return false;
}

/********************************************************************************************************************
/*@brief //�ж��Ƿ�Ϊ����
/*@author ������
/*@param[in]const string& check  const list<stFunc>&fucTables
/*@param[out] 
/*@return  bool  true �Ǻ��� false ����
/*@pre
/*@exception
/********************************************************************************************************************/
bool isFunc(const string& check ,const list<stFunc>&fucTables )
{
	for(list<stFunc>::const_iterator it = fucTables.begin() ; it!=fucTables.end() ; ++it)//���Զ������
	{
		if ((*it).m_funcName == check)
		{
			return true;
		}
	}
	return false;
} 

/********************************************************************************************************************
/*@brief //�ӵ�ǰλ�ÿ�ʼѰ����һ���ؼ��ֳ��ֵ��׸�λ�� ���ؼ��ֳ���
/*@author ������
/*@param[in]int currPos , string & sProgram const list<stFunc>&fucTables
/*@param[out] string &temp �ؼ���ֵ   int &nlength �ؼ��ֳ���
/*@return  С��0Ѱ��ʧ��  ����ɹ�
/*@pre
/*@exception
/********************************************************************************************************************/
int firstKey(int currPos , string & sProgram , int &nlength,const list<stFunc>&fucTables ,string &temp)
{
    string tempKey ;
	long int i = currPos ;
	int nFuncBound =0;
	int nSetBound =0;
	int nQuote =0 ;
   while(i  < sProgram.length())
   {
	   while ( i < sProgram.length() && sProgram.at(i) != ' ' && sProgram.at(i) != '\t' && sProgram.at(i) != '\n' )//��Ϊ�հ׷�
	{  
		if (sProgram[i] == '[') //��������
		{
			nSetBound ++;
		}
		if (sProgram[i] == ']')
		{
			nSetBound --;
		}

		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}
		tempKey.push_back(sProgram[i]);
		i++;
	}
  
	 if (true == isCmd(tempKey,fucTables))//��һ������ؼ���
	 {  
		 if ( nSetBound ==0 && nQuote == 0)//���������ڲ� �Լ��ַ����ڲ�
		 {
			 nlength = tempKey.length();
			 temp = tempKey;
			 return i - tempKey.length();
		 }
	 }
	 tempKey.clear();
	 i++ ;
    }
   return -1;
}

/********************************************************************************************************************
/*@brief //��������
/*�ֽ�Ϊ ������  �������  �����������  ��������
/*cmd_kind ��ʾ��ǰ�����ĳ�������  ��Ϊ  ������  ����  �����[��repeat ���֧���]
/*base_line ��ʾ��ǰ�������������Ļ���ַ  �� ������Ϊ0  �����뼯�ϼ����Ӧ������
/*@author ������  
/*@param[in]int currPos , string & sProgram const list<stFunc>&fucTables
/*    string & sProgram,const list<stFunc>&fucTables, int cmd_kind , int base_line,const  string &fileName
/*@param[out]list<stCommand> & cmds
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void parase(list<stCommand> & cmds , string & sProgram,const list<stFunc>&fucTables, int cmd_kind , int base_line,const  string &fileName)
{
    string tempKey1 ;
	string tempKey2;
	string tempPro = sProgram;
	long int i , j;
	int length;
	list<string>tempCmds;
   
	if (true == sProgram.empty())
	{
		return;
	}
	i = firstKey(0 , sProgram ,length,fucTables,tempKey1);//Ѱ�ҵ�һ���ؼ���
	if (-1 == i)
	{
		pFileName(fileName);
		error_out_line("fata error can not find the program entry point " , 0);
		return ;
	}
	string test = sProgram.substr(0 , i );//����ʼ���һ���ؼ���֮�䲻Ϊ�հ׷����з�  ����
	delSpace(test);
	if (!test.empty())
	{
		pFileName(fileName);
		error_out_line("undefine symbol " + test, 1);
	}

	int nTo =0;
	int nEnd =0,nFunc =0;
	while(true)
	{
		if (tempKey1 == "to" && nFunc ==0 )
		{
           nTo = i;
		   nFunc =  1;
         
		}
		if (tempKey1 == "end" && nFunc == 1)
		{
			nEnd = i ;  nFunc = 0;
			tempPro.insert(nEnd + 3 , getLine(tempPro.substr(nTo,nEnd - nTo + 3)),'\n');
			tempPro.erase(nTo , nEnd - nTo + 3); //�ͷź�������
			i =nTo;
			length =0;
		}
		i = firstKey(i + length  , tempPro ,length,fucTables,tempKey1);
		if(i == -1)
		{
			if (nFunc == 1)
			{
				pFileName(fileName);
				error_out_pos("mismatch to func keyword \" to \"", nTo , sProgram);
				return;
			}
			break;
		}
	}
/////////////////////////////////////////////////////////////////////////

	i = firstKey(0 , tempPro ,length,fucTables,tempKey1);//Ѱ�ҵ�һ���ؼ���
	if (-1 == i)
	{
		pFileName(fileName);
		error_out_line("fata error can not find the program entry point " , 0);
		return ;
	}
	stCommand stTempcmd ;
    while(true)
	{
         j = firstKey(i + length , tempPro ,length,fucTables,tempKey2);//Ѱ�ҵڶ����ؼ���
		 if(j == -1)
		 {  
			 stTempcmd.m_cmdName = tempKey1 ;//��ȡ������
			 stTempcmd.m_beforeParse = tempPro.substr(i , sProgram.length());//��������
             stTempcmd.m_lineNumber = base_line + getLineNumBer(i , tempPro);//���������к�
			 stTempcmd.m_fileName = fileName;//�����ļ���
			  delSpace( stTempcmd.m_beforeParse);
             cmds.push_back(stTempcmd);
             break;
		 }
		 stTempcmd.m_cmdName = tempKey1 ;
		 stTempcmd.m_beforeParse = tempPro.substr(i , j-i);
		 delSpace( stTempcmd.m_beforeParse);
		 stTempcmd.m_lineNumber =  base_line + getLineNumBer(i , tempPro);
		 stTempcmd.m_fileName = fileName;
          cmds.push_back(stTempcmd);
		 i = j;
		 tempKey1 = tempKey2;
	}
   
	for  (list<stCommand> ::iterator it = cmds.begin() ; it != cmds.end() ; it ++)
	{  
		if (cmd_kind != SET_CMD)//���ڷǼ�����������  ����Ƿ���ڷǷ����з�
		{
			string  tempStr = (*it).m_beforeParse;
			delSpace(tempStr);
			i = 0;
			int nQuote =0;
			int nBlock = 0;
			while (i < tempStr.length())
			{
			
					if (tempStr[i] == '\"')
					{ 
						if (nQuote == 0)//��һ���������� ���������ַ���
						{
							nQuote = 1;
						}
						else if(nQuote == 1)//�������ַ���
						{
							if (false == isChangeMean(i , sProgram))//���ַ����������ŷ�ת���ַ�
							{
								nQuote = 0;
							}
						}
					}
					if (tempStr[i] == '['  &&  nQuote ==0)//�����Ų��ҷ��ַ�����
					{
						++nBlock;
					}
					if (tempStr[i] == ']' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
					{
						--nBlock;
					}
					if (nBlock == 0 &&tempStr[i] == '\n')//�ڷ������� ���л��з�
					{
						pFileName(fileName);
						int _line = getLineNumBer(i , tempStr);
						error_out_line("can not change line outside blocks", (*it).m_lineNumber + _line);
					}
					++i;
			}
		}

        i =0;
        if ((*it).m_cmdName == "repeat")//repeat ����
        {
			string tempCmd = (*it).m_beforeParse;
			i = tempCmd.find("repeat");
			tempCmd.erase(i, 6 );
			i =0 ;
			string tempPara;
			while(i < tempCmd.length() && tempCmd[i] != '[' )//��ȡ����
			{  
				 tempPara.push_back(tempCmd[i]);
				 ++i;
			 }
			if (i == tempCmd.length())
			{
			    pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//�������󣬽�����һ������
			   continue;
			}
			 tempCmd.erase(0 , i);
			delSpace(tempPara);
			if (tempPara.empty())//ѭ����������Ϊ��
			{
				pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//�������󣬽�����һ������
				continue;
			}
			(*it).m_argvs.push_back(tempPara);//��ò���
			delSpace(tempCmd);
			j = tempCmd.rfind(']');
			if (string::npos == j)
			{
				pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//�������󣬽�����һ������
				continue;
			}
			int nBracePair = blockPairs(tempCmd);
			if (nBracePair != 1)//����ƥ�����
			{
			   pFileName(fileName);
				error_out_line("params wrong of repeat ", (*it).m_lineNumber);//�������󣬽�����һ������
				continue;
			}
			(*it).m_argvs.push_back(tempCmd.substr(1 , j-1));
			(*it).m_argc = 2;
          }
        
		else  if ((*it).m_cmdName == "if")//if ����
		 {
			 string tempCmd = (*it).m_beforeParse;
			 i = tempCmd.find("if");
			 tempCmd.erase(i, 2 );
			 i =0 ;
			 string tempPara;
			 while(i < tempCmd.length() && tempCmd[i] != '[' )//��ȡ����
			 {  
				 tempPara.push_back(tempCmd[i]);
				 ++i;
			 }
			 if (i == tempCmd.length())
			 {
				 pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//�������󣬽�����һ������
				 continue;
			 }
			 tempCmd.erase(0 , i);
			 delSpace(tempPara);
			 if (tempPara.empty())//�������ʽ����Ϊ��
			 {
				 pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//�������󣬽�����һ������
				 continue;
			 }
			 (*it).m_argvs.push_back(tempPara);//��ò���
			 delSpace(tempCmd);
			 j = tempCmd.rfind(']');
			 if (string::npos == j)
			 {
				  pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//�������󣬽�����һ������
				 continue;
			 }
			 int nBracePair = blockPairs(tempCmd);
			 if (nBracePair != 1)//����ƥ�����
			 { 
				 pFileName(fileName);
				 error_out_line("params wrong of if ", (*it).m_lineNumber);//�������󣬽�����һ������
				 continue;
			 }

			 (*it).m_argvs.push_back(tempCmd.substr(1 , j-1));
			 (*it).m_argc = 2;
         }
         else  if ((*it).m_cmdName == "ifelse")//ifelse ����
		  {
			  string tempCmd = (*it).m_beforeParse;
			  i = tempCmd.find("ifelse");
			  tempCmd.erase(i, 6);
			  i =0 ;
			  string tempPara;
            
			  delSpace(tempCmd);
              //��ȡ�������ʽ
			  while(i < tempCmd.length() && tempCmd[i] != '[' )//�ԡ�Ϊ�ֽ��
			  {  
				  tempPara.push_back(tempCmd[i]);
				  ++i;
			  }
			  if (i == tempCmd.length())//�Ҳ����ֽ����
			  {
			  	  pFileName(fileName);
				  error_out_line("params wrong of ifelse", (*it).m_lineNumber);//�������󣬽�����һ������
				  continue;
			  }
			  tempCmd.erase(0 , i);
			  delSpace(tempPara);
			  if (tempPara.empty())//�������ʽ����Ϊ��
			  {
				   pFileName(fileName);
				  error_out_line("params wrong of ifelse", (*it).m_lineNumber);//�������󣬽�����һ������
				  continue;
			  }
			  (*it).m_argvs.push_back(tempPara);//��ò���
			  delSpace(tempCmd);
              
			  int nBracePair = blockPairs(tempCmd);
			  if (nBracePair != 2)//����ƥ�����
			  {
				  pFileName(fileName);
				  error_out_line("params wrong of ifelse  ", (*it).m_lineNumber);//�������󣬽�����һ������
				  continue;
			  }
			  
			  i =0;
			  int nBrace = 0;
			  int nQuote = 0;
			  while(i < tempCmd.length())  //��ȡ����
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
				  }
				  if (tempCmd[i] == ']' &&  nQuote ==0)////�����Ų��ҷ��ַ�����
				  {
					  --nBrace;
				  }
                  if(nBrace == 0 && nQuote == 0)//һ������ƥ�����н���
				  {  
                      (*it).m_argvs.push_back(tempCmd.substr(1 , i - 1));//��ʾһ������ƥ��Խ���
					  tempCmd.erase(0 , i +1);
					  delSpace(tempCmd);
					  i = tempCmd.find('['); 
					  if (i != 0 && i != string::npos)
					  {  
						  pFileName(fileName);
						  error_out_line("params error of ifelse \""  + tempCmd + "\" " , (*it).m_lineNumber);
						  break;
					  }
					  if (string::npos == i)
					  {   
						  (*it).m_argc = 3;
						  break;
					  }
					  continue;
				  }
				  ++i;
			  }
          }
		 else if((*it).m_cmdName != "repeat" && (*it).m_cmdName != "if" && (*it).m_cmdName != "ifelse")
		 {
			 string tempCmd = (*it).m_beforeParse;
			 i = tempCmd.find((*it).m_cmdName);
			 tempCmd.erase(i, (*it).m_cmdName.length());
			 i =0 ;
			 string tempPara;
			 vector<string>tempResults;
             delSpace(tempCmd);
             splitExpression(tempCmd , tempResults);//�ָ�������ʽ
             (*it).m_argc = tempResults.size();
			 for(vector<string>::iterator it_ = tempResults.begin() ; it_ != tempResults.end() ; ++it_)
			 {
				  (*it).m_argvs.push_back((*it_));//��������ӵ���������
			 }
			 continue;//��һ����
		 }
        
	}
}
