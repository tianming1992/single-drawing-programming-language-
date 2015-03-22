/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file command.cpp
/*@author  邹天明
/*@date    2011.11.11
/*@brief   程序解析模块
/*
/*********************************************************************************************************************/

#include "command.h"

/********************************************************************************************************************
/*@brief //预扫程序，获得用户自定义过程表  结果装入funcTables内 
/*@author 邹天明
/*@param[in]  string & sProgram,const  string & fileName
/*@param[out]  list<stFunc>&funcTables
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void preScan(list<stFunc>&funcTables ,  string & sProgram,const  string & fileName)
{  
	long int i =0 ;
	//对大小写不敏感，故转为小写
	int nQuote = 0;
	for (string::iterator it= sProgram.begin() ; it != sProgram.end() ;  )
	{   
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}
		if ( (*it >= 'A' ) && (*it <= 'Z' ) &&nQuote ==0)//非字符串字符转小写
		{
			*it = tolower(*it);
		}
		++i; 
		++it;
	}

	//过滤\r
	while(string::npos  !=   (i   =   sProgram.find('\r'))) 
	{
		sProgram.erase(i , 1);
	}
   
	i=0;
	nQuote =0;
	//过滤注释
	while(i < sProgram.length())  
	{  
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}

		if (sProgram[i] == ';' && nQuote ==0)//在字符串外且符号;
		{
			int j = i;
			while( i++ < sProgram.length() && sProgram[i] != '\n');//找到本行末尾删除注释
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
	//基本语法报错
	while(i < sProgram.length())  //引号是否匹配
	{  
		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
				last = i ;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}

		if (sProgram[i] == '('  &&  nQuote ==0)//开括号并且非字符串内
		{
			++nBrace;
			last_small_left = i;
		}
		if (sProgram[i] == ')' &&  nQuote ==0)////闭括号并且非字符串内
		{
			--nBrace;
			last_small_right = i;
		}
		if (sProgram[i] == '['  &&  nQuote ==0)//开括号并且非字符串内
		{
			++nBlock;
			last_block_left = i;
		}
		if (sProgram[i] == ']' &&  nQuote ==0)////闭括号并且非字符串内
		{
			--nBlock;
			last_block_right = i;
		}

		if(nQuote == 1 && sProgram[i] == '\n')//在字符串内有换行
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

	//寻找过程定义语句
	getFuncTable(funcTables , sProgram , fileName);
	return ;
}

/********************************************************************************************************************
/*@brief //获取程序所有函数表
/*@author 邹天明
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
	static vector<string>haveFinded;//存储已经寻找过的文件 防止重复包含
    
	haveFinded.push_back(fileName);
	//对大小写不敏感，故转为小写
	int nQuote = 0;
	for (string::iterator it= tempPro.begin() ; it != tempPro.end() ;  )
	{   
		char ch = *it;
		if (tempPro[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}
		if ( (*it >= 'A' ) && (*it <= 'Z' ) &&nQuote ==0)//非字符串字符转小写
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
	i = firstKey(0 , tempPro ,length,funcTables,tempKey1);//寻找第一个关键字
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
					read = false;//已经读过的文件不再重复读取
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
			nEnd = i ;  nFunc = 0; //找到某函数 end 与to
            //检查end是否单独占用一行
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
			//检查函数头是否单独占用一行
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
			  long int j = sFunc.find('\n');//未单独占一行
			 if (j ==string::npos)
			 {
				 pFileName(fileName);
				 error_out_pos("function define error" , nTo , sProgram);
				 return;
			 }
			// delSpace(sFunc);
			 string sFuncHeader = sFunc.substr(0 , j);//获取函数头
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
				 sFuncBody   = sFunc.substr(j , sFunc.length());//获取函数体 
			 }
			 else
			 {
				 sFuncBody.clear();
			 }
		
			 delSpace(sFuncBody);
			 vector<string>params ;
			 split(sFuncHeader,':' , params);//获取函数参数
			 stFunc funToAdd;
			 funToAdd.m_argc = params.size() -1;
			 funToAdd.m_lineNumber = getLineNumBer(nTo , sProgram);//记下该函数的行号
			 funToAdd.m_conntext = sFuncBody;
			 delSpace(funToAdd.m_conntext);//函数内容

			 funToAdd.m_funcName = params[0];//获取函数名
			 delSpace(funToAdd.m_funcName);
			 if (false == isIllIdentifer(funToAdd.m_funcName))//检查函数名是否合法
			 {
				 pFileName(fileName);
				 error_out_pos("wrong identifier  \" " + funToAdd.m_funcName+" \""  , nTo , sProgram);
				   return;
			 }
			 //检查函数名是否和关键字同名
             
			 if (true == isKeyWord(funToAdd.m_funcName))//检查函数名是否合法
			 {
				 pFileName(fileName);
				 error_out_pos("function name can not be same to keyword \" " + funToAdd.m_funcName+" \""  , nTo , sProgram);
				 return;
			 }
			 for (list<stFunc>::iterator it = funcTables.begin() ; it != funcTables.end() ; ++it)//判断是否重复定义
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
				 tempVal.m_valName = (*it);//获取函数参数列表
				 delSpace(tempVal.m_valName );//取出空格
				 if (false == isIllIdentifer(tempVal.m_valName))//检查参数名是否合法
				 {
					 pFileName(fileName);
					 error_out_pos("wrong  identifier \" " + tempVal.m_valName +" \"" , nTo , sProgram);//错误参数
				     return;
				 }
				 //检测参数名是否重复
				 for (list<stVal>::iterator it = funToAdd.m_parmTable.begin() ; it != funToAdd.m_parmTable.end() ; ++it)
				 {
					 if (tempVal.m_valName == (*it).m_valName)//检测到同名参数
					 {
						 pFileName(fileName);
						 error_out_pos("function same params name \" " + tempVal.m_valName+" \""  , nTo , sProgram);//错误参数
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
/*@brief //判断是否为命令
/*@author 邹天明
/*@param[in] const string& check ,const list<stFunc>&fucTables
/*@param[out] 
/*@return  bool  true 为命令 false 不是
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
	 for(list<stFunc>::const_iterator it = fucTables.begin() ; it!=fucTables.end() ; ++it)//是自定义过程
	 {
		 if ((*it).m_funcName == check)
		 {
			 return true;
		 }
	 }
	 return false;
}

/********************************************************************************************************************
/*@brief //判断是否为关键字  （关键字包含函数，而命令不包括）
/*@author 邹天明
/*@param[in]const string& check 
/*@param[out] 
/*@return  bool  true 为命令 false 不是
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
/*@brief //判断是否为函数
/*@author 邹天明
/*@param[in]const string& check  const list<stFunc>&fucTables
/*@param[out] 
/*@return  bool  true 是函数 false 不是
/*@pre
/*@exception
/********************************************************************************************************************/
bool isFunc(const string& check ,const list<stFunc>&fucTables )
{
	for(list<stFunc>::const_iterator it = fucTables.begin() ; it!=fucTables.end() ; ++it)//是自定义过程
	{
		if ((*it).m_funcName == check)
		{
			return true;
		}
	}
	return false;
} 

/********************************************************************************************************************
/*@brief //从当前位置开始寻找下一个关键字出现的首个位置 及关键字长度
/*@author 邹天明
/*@param[in]int currPos , string & sProgram const list<stFunc>&fucTables
/*@param[out] string &temp 关键字值   int &nlength 关键字长度
/*@return  小于0寻找失败  否则成功
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
	   while ( i < sProgram.length() && sProgram.at(i) != ' ' && sProgram.at(i) != '\t' && sProgram.at(i) != '\n' )//不为空白符
	{  
		if (sProgram[i] == '[') //跳过括号
		{
			nSetBound ++;
		}
		if (sProgram[i] == ']')
		{
			nSetBound --;
		}

		if (sProgram[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}
		tempKey.push_back(sProgram[i]);
		i++;
	}
  
	 if (true == isCmd(tempKey,fucTables))//是一个命令关键字
	 {  
		 if ( nSetBound ==0 && nQuote == 0)//跳过括号内部 以及字符串内部
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
/*@brief //解析命令
/*分解为 命令名  命令参数  命令参数个数  命令类型
/*cmd_kind 表示当前解析的程序类型  分为  主程序  函数  命令集合[即repeat 或分支语句]
/*base_line 表示当前命令所在行数的基地址  ， 主程序为0  函数与集合即相对应所在行
/*@author 邹天明  
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
	i = firstKey(0 , sProgram ,length,fucTables,tempKey1);//寻找第一个关键字
	if (-1 == i)
	{
		pFileName(fileName);
		error_out_line("fata error can not find the program entry point " , 0);
		return ;
	}
	string test = sProgram.substr(0 , i );//程序开始与第一个关键字之间不为空白符或换行符  报错
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
			tempPro.erase(nTo , nEnd - nTo + 3); //释放函数定义
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

	i = firstKey(0 , tempPro ,length,fucTables,tempKey1);//寻找第一个关键字
	if (-1 == i)
	{
		pFileName(fileName);
		error_out_line("fata error can not find the program entry point " , 0);
		return ;
	}
	stCommand stTempcmd ;
    while(true)
	{
         j = firstKey(i + length , tempPro ,length,fucTables,tempKey2);//寻找第二个关键字
		 if(j == -1)
		 {  
			 stTempcmd.m_cmdName = tempKey1 ;//获取命令名
			 stTempcmd.m_beforeParse = tempPro.substr(i , sProgram.length());//命令内容
             stTempcmd.m_lineNumber = base_line + getLineNumBer(i , tempPro);//命令所在行号
			 stTempcmd.m_fileName = fileName;//所在文件名
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
		if (cmd_kind != SET_CMD)//对于非集合命令序列  检查是否存在非法换行符
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
						if (nQuote == 0)//第一次碰到引号 表明进入字符串
						{
							nQuote = 1;
						}
						else if(nQuote == 1)//表明出字符串
						{
							if (false == isChangeMean(i , sProgram))//在字符串内且引号非转义字符
							{
								nQuote = 0;
							}
						}
					}
					if (tempStr[i] == '['  &&  nQuote ==0)//开括号并且非字符串内
					{
						++nBlock;
					}
					if (tempStr[i] == ']' &&  nQuote ==0)////闭括号并且非字符串内
					{
						--nBlock;
					}
					if (nBlock == 0 &&tempStr[i] == '\n')//在方括号外 且有换行符
					{
						pFileName(fileName);
						int _line = getLineNumBer(i , tempStr);
						error_out_line("can not change line outside blocks", (*it).m_lineNumber + _line);
					}
					++i;
			}
		}

        i =0;
        if ((*it).m_cmdName == "repeat")//repeat 命令
        {
			string tempCmd = (*it).m_beforeParse;
			i = tempCmd.find("repeat");
			tempCmd.erase(i, 6 );
			i =0 ;
			string tempPara;
			while(i < tempCmd.length() && tempCmd[i] != '[' )//获取参数
			{  
				 tempPara.push_back(tempCmd[i]);
				 ++i;
			 }
			if (i == tempCmd.length())
			{
			    pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//参数错误，解析下一个命令
			   continue;
			}
			 tempCmd.erase(0 , i);
			delSpace(tempPara);
			if (tempPara.empty())//循环次数不能为空
			{
				pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//参数错误，解析下一个命令
				continue;
			}
			(*it).m_argvs.push_back(tempPara);//获得参数
			delSpace(tempCmd);
			j = tempCmd.rfind(']');
			if (string::npos == j)
			{
				pFileName(fileName);
				error_out_line("params wrong of repeat", (*it).m_lineNumber);//参数错误，解析下一个命令
				continue;
			}
			int nBracePair = blockPairs(tempCmd);
			if (nBracePair != 1)//括号匹配错误
			{
			   pFileName(fileName);
				error_out_line("params wrong of repeat ", (*it).m_lineNumber);//参数错误，解析下一个命令
				continue;
			}
			(*it).m_argvs.push_back(tempCmd.substr(1 , j-1));
			(*it).m_argc = 2;
          }
        
		else  if ((*it).m_cmdName == "if")//if 命令
		 {
			 string tempCmd = (*it).m_beforeParse;
			 i = tempCmd.find("if");
			 tempCmd.erase(i, 2 );
			 i =0 ;
			 string tempPara;
			 while(i < tempCmd.length() && tempCmd[i] != '[' )//获取参数
			 {  
				 tempPara.push_back(tempCmd[i]);
				 ++i;
			 }
			 if (i == tempCmd.length())
			 {
				 pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//参数错误，解析下一个命令
				 continue;
			 }
			 tempCmd.erase(0 , i);
			 delSpace(tempPara);
			 if (tempPara.empty())//条件表达式不能为空
			 {
				 pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//参数错误，解析下一个命令
				 continue;
			 }
			 (*it).m_argvs.push_back(tempPara);//获得参数
			 delSpace(tempCmd);
			 j = tempCmd.rfind(']');
			 if (string::npos == j)
			 {
				  pFileName(fileName);
				 error_out_line("params wrong of if", (*it).m_lineNumber);//参数错误，解析下一个命令
				 continue;
			 }
			 int nBracePair = blockPairs(tempCmd);
			 if (nBracePair != 1)//括号匹配错误
			 { 
				 pFileName(fileName);
				 error_out_line("params wrong of if ", (*it).m_lineNumber);//参数错误，解析下一个命令
				 continue;
			 }

			 (*it).m_argvs.push_back(tempCmd.substr(1 , j-1));
			 (*it).m_argc = 2;
         }
         else  if ((*it).m_cmdName == "ifelse")//ifelse 命令
		  {
			  string tempCmd = (*it).m_beforeParse;
			  i = tempCmd.find("ifelse");
			  tempCmd.erase(i, 6);
			  i =0 ;
			  string tempPara;
            
			  delSpace(tempCmd);
              //获取条件表达式
			  while(i < tempCmd.length() && tempCmd[i] != '[' )//以【为分解符
			  {  
				  tempPara.push_back(tempCmd[i]);
				  ++i;
			  }
			  if (i == tempCmd.length())//找不到分界符号
			  {
			  	  pFileName(fileName);
				  error_out_line("params wrong of ifelse", (*it).m_lineNumber);//参数错误，解析下一个命令
				  continue;
			  }
			  tempCmd.erase(0 , i);
			  delSpace(tempPara);
			  if (tempPara.empty())//条件表达式不能为空
			  {
				   pFileName(fileName);
				  error_out_line("params wrong of ifelse", (*it).m_lineNumber);//参数错误，解析下一个命令
				  continue;
			  }
			  (*it).m_argvs.push_back(tempPara);//获得参数
			  delSpace(tempCmd);
              
			  int nBracePair = blockPairs(tempCmd);
			  if (nBracePair != 2)//括号匹配错误
			  {
				  pFileName(fileName);
				  error_out_line("params wrong of ifelse  ", (*it).m_lineNumber);//参数错误，解析下一个命令
				  continue;
			  }
			  
			  i =0;
			  int nBrace = 0;
			  int nQuote = 0;
			  while(i < tempCmd.length())  //获取参数
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
				  }
				  if (tempCmd[i] == ']' &&  nQuote ==0)////闭括号并且非字符串内
				  {
					  --nBrace;
				  }
                  if(nBrace == 0 && nQuote == 0)//一个括号匹配序列结束
				  {  
                      (*it).m_argvs.push_back(tempCmd.substr(1 , i - 1));//表示一个括号匹配对结束
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
             splitExpression(tempCmd , tempResults);//分割参数表达式
             (*it).m_argc = tempResults.size();
			 for(vector<string>::iterator it_ = tempResults.begin() ; it_ != tempResults.end() ; ++it_)
			 {
				  (*it).m_argvs.push_back((*it_));//将参数添加到参数表中
			 }
			 continue;//下一命令
		 }
        
	}
}
