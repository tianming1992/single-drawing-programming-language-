/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file sys_execu.cpp
/*@author  邹天明
/*@date    2011.11.11
/*@brief   程序运行模块
/*
/*********************************************************************************************************************/

#include "sys_execu.h"


/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 邹天明
/*@param[in]  vector<string> & inputcmds  用户输入命令
/*@param[out]  stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void	initSys(stSysInfo * pSy ,vector<string> & inputcmds )//初始化
{  
	

   pSy->currTurtle.margin = -1;
   pSy->currTurtle.type = PNG;
   pSy->currTurtle.filename.clear();
   pSy->m_pic_fileName.clear();
    for(vector<string>::iterator it = inputcmds.begin()  ; it != inputcmds.end() ; )
   {
	   if ( (*it) ==  "-m" ||  (*it) == "-M" )//-m参数
	   {  
		   ++it;
		   if ( it !=  inputcmds.end())
		   {  
			   int margin = atoi((*it).c_str());
			   if (margin < 0)//边距不可小于0
			   {
				   perror("margin can not less than 0");
				   exit(0);
			   }
			   pSy->currTurtle.margin = margin;
			   inputcmds.erase(it -1  , it +1);
			   it = inputcmds.begin();
			   continue;
		   }
		   else
		   {
			   perror("-m should have a paramater");
			   exit(0);
		   }
	   }
        
	   if ((*it) == "-t" || (*it) == "-T")//-T参数
	   {
		   ++it;
		   if (it != inputcmds.end())
		   {  
			  string type = *it;//获取文件类型
			  if(type == "png" || type == "PNG")
			  {
				  pSy->currTurtle.type = PNG;
			  }
			  else if (type == "pdf" || type == "PDF")
			  {
				  pSy->currTurtle.type = PDF;
			  }
			  else
			  {
				  perror("unknow file type");
				  exit(0);
			  }
			   inputcmds.erase(it -1 , it +1);
			   it = inputcmds.begin();
			   continue;
		   }
		   else
		   {
			   perror("-T should have a paramater");
			   exit(0);
		   }
	   }
  
	   if ( (*it) == "-name" || (*it) == "-NAME" )//生成文件名
	   {
		   ++it;
		   if (it != inputcmds.end())
		   {  
			   pSy->m_pic_fileName = *it;//获取文件名
			   inputcmds.erase(it -1 , it +1);
			   it = inputcmds.begin();
			   continue;
		   }
		   else
		   {
			   perror("-name should have a paramater");
			   exit(0);
		   }
	   }
	   ++it;
   }

   if (inputcmds.size() ==0)
   {
	   perror("can not get the program file name");
	   exit(0);
   }
   if (inputcmds.size() > 1)
   {
	   perror("too mamy paramaters  to exe");
	   exit(0);
   }
   pSy->m_programFile = inputcmds[0];//获取程序文件名
   pSy->m_execuCmdLists.clear();
   pSy->m_rootFucCallerLine = -1;
   pSy->m_funcTable.clear();
   pSy->reTurnToFunc = -1;//返回函数栈地址
  
   /////////////////////////////////////////////////////初始化乌龟
   initpaint(pSy->currTurtle);
}


/********************************************************************************************************************
/*@brief 执行命令
/*@author 邹天明
/*@param[in]  list<stCommand> & stCommdQueue  命令队列
/*@param[out]  stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void execu_cmds( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue)
{  
	
	int funStackSize ;
	while(!stCommdQueue.empty())
	{   
         funStackSize = pstSys->m_funcStack.size();//如果执行过stop命令 且在要返回的函数上层  退出该命令序列
		if (pstSys->reTurnToFunc > -1 && funStackSize > pstSys->reTurnToFunc) 
		{
			stCommdQueue.clear();
			return;
		}
		if (pstSys->reTurnToFunc > -1 && funStackSize == pstSys->reTurnToFunc)
		{
			pstSys->reTurnToFunc = -1;
		}
		exeu(pstSys , stCommdQueue); //执行命令
		if (!stCommdQueue.empty())
		{
			stCommdQueue.pop_front();//删除已经执行的命令
		}
		
		if (pstSys->m_funcStack.size() >   MAX_FUNCTION_STACK )//栈溢出错误  无限递归
		{
			perror("function stack overflow \n");
			exit(0);
		}
     }
}

/********************************************************************************************************************
/*@brief 执行命令
/*@author 邹天明
/*@param[in]  list<stCommand> & stCommdQueue  命令队列
/*@param[out]  stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void exeu( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue)
{
    stCommand currCmd = stCommdQueue.front();

	if (currCmd.m_cmdName == "ifelse")//ifelse命令
	{
		 cmd_ifelse(currCmd , pstSys);
		 return;
	}
	if (currCmd.m_cmdName == "if")//if命令
	{
		  cmd_if(currCmd , pstSys);
		   return;
	}
	if (currCmd.m_cmdName == "make")//if命令
	{
       cmd_make(currCmd , pstSys);
		return;
	}
	if (currCmd.m_cmdName == "dmake")//if命令
	{
		cmd_dmake(currCmd , pstSys);
		return;
	}
	if (currCmd.m_cmdName == "repeat")//repeat命令
	{
		cmd_repeat(currCmd , pstSys);
         return;
	}
	if (currCmd.m_cmdName == "print")//print命令
	{
		cmd_print(currCmd , pstSys);
         return;
	}
    
	if (currCmd.m_cmdName == "stop")//stop命令
	{
		cmd_stop(currCmd , pstSys ,stCommdQueue);
         return;
	}

	if (currCmd.m_cmdName == "import")//stop命令
	{
		return;
	}
	if (true == isFunc(currCmd.m_cmdName ,pstSys->m_funcTable))//是函数
	{
		cmd_func(currCmd , pstSys);
		 return;
	}

	if (currCmd.m_cmdName == "fd")
	{
		cmd_draw_fd(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "bk")
	{
		cmd_draw_bk(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "rt")
	{
		cmd_draw_rt(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "lt")
	{
		cmd_draw_lt(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "pu")
	{
		cmd_draw_pu(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "pd")
	{
		cmd_draw_pd(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "cs")
	{
		cmd_draw_cs(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "home")
	{
		cmd_draw_home(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "setx")
	{
		cmd_draw_setx(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "sety")
	{
		cmd_draw_sety(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "setxy")
	{
		cmd_draw_setxy(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "seth")
	{
		cmd_draw_seth(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "dc")//画圆
	{
		cmd_draw_dc(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "setc")//设置前景色
	{
		cmd_set_color(currCmd ,pstSys);
		return;
	}
   
	pFileName(currCmd.m_fileName);
    error_out_line("can not define this symbol \" " + currCmd.m_cmdName + " \"" + " there", currCmd.m_lineNumber);
}

/********************************************************************************************************************
/*@brief 获取变量值
/*对于任意变量  首先在函数栈中查找  然后在全局变量中查找
/*@author 邹天明
/*@param[in] string valName 变量名     stSysInfo * pSy 系统信息结构体
/*@param[out] 
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
stVal get_val_value(string valName , stSysInfo * pstSys)
{
      stVal  stTempVal ;
	  if(!pstSys->m_funcStack.empty())//函数栈非空 查找局部变量
	  {
		  for (list<stVal>::iterator it = pstSys->m_funcStack.top().m_parmTable.begin() ;
			      it != pstSys->m_funcStack.top().m_parmTable.end(); ++it)
		  {
			  if((*it).m_valName == valName)//找到局部变量  返回其值
			  {
				  return (*it);
			  }
		  }
	  }
	  for (list<stVal>::iterator it = pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end() ; ++it)
	  {
		  if((*it).m_valName == valName)//找到全局变量  返回其值
		  {
			  return (*it);
		  }
	  }
	  stTempVal.m_valKind = UNDEFINED;//找不到该变量  返回未知定义
	  return stTempVal;
}

//寻找某个表达式内部变量  并且将该变量使用真值替换
bool replaceVeri(string &srcEpre , stSysInfo * pstSys)
{
    long int  i =0;
	while(i < srcEpre.length())
	{
		if (srcEpre[i] == ':')//变量的开始符号
		{
			int j =i;
           ++i;//跳到下一个符号
		   string tempValname;
		   while(i<srcEpre.length())
		   {
                 tempValname.push_back(srcEpre[i]);
				 if (true == isIllIdentifer(tempValname))//是合法标志符号 继续下一个字符
				 {
					 ++i;
				 }
				 else break;
		   }
		   //退出循环 释放最后一个非法标识符
		   if (true == tempValname.empty())
		   {
			   return false;
		   }
		   if (false == isIllIdentifer(tempValname))
		   {
			     tempValname.erase(tempValname.length()-1 , 1);
		   }
		
		   stVal tempVal = get_val_value(tempValname , pstSys);
		   if (UNDEFINED == tempVal.m_valKind )//未定义变量
		   {
			   return false;
		   }
           srcEpre.replace(j , tempValname.length() +1 , tempVal.m_str_value);
		   i = j + tempVal.m_str_value.length();
		   continue;
       }
		++i;
	}
	return true;
}

/********************************************************************************************************************
/*@brief 获取一个普通表达式值
/*一个普通表达式指的是  一个数值表达式   或者  一个字符串 其中可能包含变量
/*@author 邹天明
/*@param[in]  string &srcEpre  表达式   stSysInfo * pSy 系统信息结构体
/*@param[out] 
/*@return  stval  变量结构体
/*@pre
/*@exception  若变量结构体类型为undefine 说明解析表达式错误
/********************************************************************************************************************/
stVal  getNormalExpressionVal(string &srcEpre , stSysInfo * pstSys)
{  
	  stVal tempVal;
      if(true == isConstStr(srcEpre))//是一个字符串常量
	  {
           tempVal.m_str_value = srcEpre;
		   tempVal.m_valKind = VAL_STRING;
		   return tempVal;
	  }
	  replaceVeri(srcEpre,pstSys);//替换表达式变量
	  if(true == isConstStr(srcEpre))//是一个字符串常量
	  {
		  tempVal.m_str_value = srcEpre;
		  tempVal.m_valKind = VAL_STRING;
		  return tempVal;
	  }
	  float value;
	  if (true == ValueExpression(srcEpre , value))//是一个表达式
	  {
		  tempVal.m_f_value = value;
		  char ctemp[200];
		  sprintf(ctemp , "%f" , tempVal.m_f_value);
		  tempVal.m_str_value = ctemp;
		  tempVal.m_valKind = VAL_FLOAT;
		  return tempVal;
	  }
	  else
	  {
		  perror("wrong");
	  }
      tempVal.m_valKind = UNDEFINED;//无效的表达式
	  return tempVal;
}

/********************************************************************************************************************
/*@brief make 命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_make(stCommand & currCmd ,stSysInfo * pstSys)
{
    if(currCmd.m_argc != 2)
	{
	   	pFileName(currCmd.m_fileName);
		error_out_line("wrong parameters of make ", currCmd.m_lineNumber);
		return;
	}
	stVal tempVal ;
	stVal valToAdd;
	tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//获取第一个参数值
	if (VAL_STRING == tempVal.m_valKind )//是字符串类型的
	{
		delSpace(tempVal.m_str_value);
		tempVal.m_str_value.erase(0 , 1);
		tempVal.m_str_value.erase(tempVal.m_str_value.length()-1 ,1);//去除双引号
        delSpace(tempVal.m_str_value);
		if (false == isIllIdentifer(tempVal.m_str_value))//是否合法标识符
		{
			pFileName(currCmd.m_fileName);
			error_out_line("wrong identifer name" , currCmd.m_lineNumber);
			return ;
		}
		//获取变量名
		valToAdd.m_valName = tempVal.m_str_value;
		toLower_(valToAdd.m_valName);
    }
	else 
	{
		pFileName(currCmd.m_fileName);
		error_out_line("name should be a string"  , currCmd.m_lineNumber);
		return ;
	}
   
	tempVal = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//获取第二个参数值
	 if (tempVal.m_valKind == UNDEFINED)//无效表达式
		{
			pFileName(currCmd.m_fileName);
			error_out_line("wrong value "  , currCmd.m_lineNumber);
			return ;
		}
        valToAdd.m_str_value = tempVal.m_str_value;
		valToAdd.m_valKind = tempVal.m_valKind;
		if (tempVal.m_valKind == VAL_FLOAT)
		{
			valToAdd.m_f_value = tempVal.m_f_value;
		}
        //是否覆盖
		list<stVal>::iterator it;
		for( it=pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end();++it)
	   {
           if ((*it).m_valName == valToAdd.m_valName)
           {
			   (*it) = valToAdd;
			   break;
           }
	    }
		if (it == pstSys->m_globalValTable.end())//无同名变量  添加
		{
			pstSys->m_globalValTable.push_back(valToAdd);
		}
       return ;
} 

/********************************************************************************************************************
/*@brief  执行函数 
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  无限递归会导致栈溢出 ，程序将自动退出
/********************************************************************************************************************/
void cmd_func(stCommand & currCmd ,stSysInfo * pstSys)
{
    stFunc currFunction ;
	list<stFunc>::iterator it;
	for ( it = pstSys->m_funcTable.begin() ; it != pstSys->m_funcTable.end() ; ++it)
	{
		if ((*it).m_funcName == currCmd.m_cmdName)//寻找该函数定义
		{
			currFunction = *it;
			break;
		}
	}
	if (it == pstSys->m_funcTable.end())
	{
		return ;
	}
	
    if (currCmd.m_argc > currFunction.m_argc)
    {
		pFileName(currCmd.m_fileName);
		error_out_line("too many paramaters  " , currCmd.m_lineNumber);
		return ;
    }
	if (currCmd.m_argc < currFunction.m_argc)//传给参数太少
	{
		pFileName(currCmd.m_fileName);
		error_out_line("too less paramaters  " , currCmd.m_lineNumber);
		return ;
	}
	list<stVal>::iterator false_it = currFunction.m_parmTable.begin();//形参表
	vector<string>::iterator true_it = currCmd.m_argvs.begin();//实参表
    while(false_it != currFunction.m_parmTable.end() && true_it != currCmd.m_argvs.end())//给函数形参赋值
	{
         stVal tempVal = getNormalExpressionVal((*true_it) , pstSys);//获取实参的值
		 if (UNDEFINED == tempVal.m_valKind)//实参定义错误
		 {
		 	pFileName(currCmd.m_fileName);
			 error_out_line("wrong expression or undefined symbol \" "+(*true_it) +" \"" , currCmd.m_lineNumber);
			 return ;
		 }
		 //toLower_((*false_it).m_valName);
		 tempVal.m_valName = (*false_it).m_valName ;
         (*false_it) = tempVal ;
		 ++false_it ;  ++true_it;
	}
	if (true == pstSys->m_funcStack.empty())
	{
		pstSys->m_rootFucCallerLine = currCmd.m_lineNumber; //函数栈第一个函数获取其初始调用者行号 
	}                                                                                          //用于判断该函数是否有效定义
     //小于函数所在地址  未定义错误
	if((pstSys->m_rootFucCallerLine < currFunction.m_lineNumber) && (pstSys->m_programFile == currFunction.m_fileName))
	{
		pFileName(currCmd.m_fileName);
		error_out_line("undefined symbol  \" " + currFunction.m_funcName  + " \"" , currCmd.m_lineNumber);
		return ;
	}

	if (currFunction.m_conntext.empty())
	{
		return ;//函数为空 返回
	}
    pstSys->m_funcStack.push(currFunction);//将当前函数入函数栈
    list<stCommand> currFunCmds;
	 //解析该函数内容
	parase(currFunCmds , currFunction.m_conntext , pstSys->m_funcTable,FUNC_CMD ,currFunction.m_lineNumber ,currFunction.m_fileName);
	execu_cmds(pstSys , currFunCmds);//执行该函数内容
	//函数执行完毕 函数出栈
	pstSys->m_funcStack.pop();
	return ;
}

/********************************************************************************************************************
/*@brief 获取条件表达式值
/*@author 邹天明
/*@param[in]   string sExpr 条件表达式     stSysInfo * pSy 系统信息结构体
/*@param[out] 
/*@return  返回值 0 假  1 真 -1 出错  
/*@pre
/*@exception  
/********************************************************************************************************************/
int  getConditionExVal(string sExpr , stSysInfo * pstSys)
{  
	int i =0;
	int nQuote =0;
	int pos =0;
	char op;
	while(i < sExpr.length())
	{
		if (sExpr[i] == '\"')
		{ 
			if (nQuote == 0)//第一次碰到引号 表明进入字符串
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sExpr))//在字符串内且引号非转义字符
				{
					nQuote = 0;
				}
			}
		}
        if (nQuote ==0 && (sExpr[i] == '<' || sExpr[i] == '>' || sExpr[i] == '='))//寻找条件符号
        {
           pos = i;
		   op = sExpr[i];
        }
		++i;
	}

	string left = sExpr.substr(0 , pos);
	string right = sExpr.erase(0 , pos +1);//获取左右表达式
	delSpace(left);
	delSpace(right);
	if (left.empty() || right.empty())
	{
		return -1;
	}
	stVal leftVal = getNormalExpressionVal(left,pstSys);
	stVal rightVal = getNormalExpressionVal(right,pstSys);
	if (leftVal.m_valKind == UNDEFINED || rightVal.m_valKind == UNDEFINED)//表达式是错误
	{
		return -1;
	}
   if (leftVal.m_valKind != leftVal.m_valKind)
   { 
	   return -1;//类型匹配错误
   }
   if(rightVal.m_valKind == VAL_FLOAT)//数值比较
   {
       switch(op)
	   {
	   case  '>':  return leftVal.m_f_value > rightVal.m_f_value;
	   case  '<':  return leftVal.m_f_value < rightVal.m_f_value;
	   case  '=':  return leftVal.m_f_value == rightVal.m_f_value; 
	   }
   }
   if (rightVal.m_valKind == VAL_STRING)//字符串比较
   {
	   switch(op)
	   {
	   case  '>':  return leftVal.m_str_value > rightVal.m_str_value;
	   case  '<':  return leftVal.m_str_value < rightVal.m_str_value;
	   case  '=':  return leftVal.m_str_value == rightVal.m_str_value; 
	   }
   }
}

/********************************************************************************************************************
/*@brief  if命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_if(stCommand & currCmd ,stSysInfo * pstSys)
{
    string condition = currCmd.m_argvs[0]; //获取条件表达式
	if(condition.empty())
	{
		pFileName(currCmd.m_fileName);
		error_out_line("condition can not be empty of if" , currCmd.m_lineNumber);
		return;
	}
	int value = getConditionExVal(condition , pstSys);//获取条件表达式值
	if(-1 == value)//条件表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong condition expression of if \" "+ condition + " \"" , currCmd.m_lineNumber);
		return;
	}
	if (value)//返回值为真
	{
        delSpace(currCmd.m_argvs[1]);
		if (currCmd.m_argvs[1].empty())
		{
			return;//执行语句为空
		}
		list<stCommand> currIfCmds;
		//解析该if内容
		parase(currIfCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfCmds);//执行该if内容
		return;
	}
	return;
}

/********************************************************************************************************************
/*@brief  ifelse命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_ifelse(stCommand & currCmd ,stSysInfo * pstSys)
{
	string condition = currCmd.m_argvs[0]; //获取条件表达式
	if(condition.empty())
	{
		pFileName(currCmd.m_fileName);
		error_out_line("condition can not be empty of ifelse" , currCmd.m_lineNumber);
		return;
	}
	int value = getConditionExVal(condition , pstSys);//获取条件表达式值
	if(-1 == value)//条件表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong condition expression of ifelse \" "+condition +" \"" , currCmd.m_lineNumber);
		return;
	}

	if (value)//返回值为真
	{
		delSpace(currCmd.m_argvs[1]);
		if (currCmd.m_argvs[1].empty())
		{
			return;//执行语句为空
		}
		list<stCommand> currIfelseCmds;
		//解析该if内容
		parase(currIfelseCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfelseCmds);//执行该if内容
		return;
	}
	else
	{ 
		delSpace(currCmd.m_argvs[2]);
		if (currCmd.m_argvs[2].empty())
		{
			return;//执行语句为空
		}
		list<stCommand> currIfelseCmds;
		//解析该ifelse内容
		parase(currIfelseCmds ,currCmd.m_argvs[2] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfelseCmds);//执行该if内容
		return;
	}
}

/********************************************************************************************************************
/*@brief  repeat命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_repeat(stCommand & currCmd ,stSysInfo * pstSys)
{
     string times = currCmd.m_argvs[0];//循环次数参数
	 delSpace( times);
	 stVal timeVal = getNormalExpressionVal(times , pstSys);//获取循环次数表达式值
	 if(timeVal.m_valKind != VAL_FLOAT)
	 {
		 pFileName(currCmd.m_fileName);
		 error_out_line("error expression of repeat" , currCmd.m_lineNumber);//参数类型错误
		 return ;
	 }

	 if (false == isInt(timeVal.m_f_value))
	 {  
		 	pFileName(currCmd.m_fileName);
		 error_out_line("circle times should be a integer" , currCmd.m_lineNumber);//必须为整数
		 return ;
	 }

	 if (currCmd.m_argvs[1].empty())
	 {
		 return ;//循环语句为空
	 }
	 list<stCommand> currRepeatCmds;
	 for (int i = 0 ; i < timeVal.m_f_value ; ++ i)
	 {  
		 //解析该repeat内容
		 parase(currRepeatCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		 execu_cmds(pstSys , currRepeatCmds);//循环执行该repeat内容
	 }
       return;
}

/********************************************************************************************************************
/*@brief  stop命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_stop(stCommand & currCmd ,stSysInfo * pstSys, list<stCommand> & stCommdQueue)
{  
	if (currCmd.m_argc >0) //参数错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many paraters of stop" , currCmd.m_lineNumber);
		return ;
	}
    if (true == pstSys->m_funcStack.empty())//函数栈为空 表明当前运行在主程序中 退出程序
    {
		destroy_psy(pstSys);//销毁系统信息
		exit(0);
    }
	else//函数栈非空 运行在函数中  退回到上一层函数
	{
         pstSys->reTurnToFunc = pstSys->m_funcStack.size() -1 ;
         stCommdQueue.clear();//清空当前命令队列
		 return ;
	}
}

/********************************************************************************************************************
/*@brief  print命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_print(stCommand & currCmd ,stSysInfo * pstSys)
{
   if (currCmd.m_argvs.size() == 0)
   {
	   	pFileName(currCmd.m_fileName);
	   error_out_line(" too less parameters of print" , currCmd.m_lineNumber);
	   return ;
   }
   if (currCmd.m_argvs.size() > 1)
   {
	   	pFileName(currCmd.m_fileName);
	   error_out_line(" too many parameters of print" , currCmd.m_lineNumber);
	   return ;
   }
   stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);
   if (UNDEFINED == tempVal.m_valKind)//表达式错误
   {
	   	pFileName(currCmd.m_fileName);
	   error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
	   return ;
   }

   string toPrint;
   if (tempVal.m_valKind == VAL_FLOAT)
   {
	   toPrint = turnFstrTostand(tempVal.m_str_value);
   }
   if (tempVal.m_valKind == VAL_STRING)//获取字符串值，并且处理内部转义字符
   {
	   toPrint = tempVal.m_str_value;
	   toPrint.erase(0 ,1);
	   toPrint.erase(toPrint.length()-1 ,1);
	   toPrint = toChangeMean(toPrint);
   }

   //////////////////////////////////////////////////////////////////////////////////////////送给乌龟打印
   print(pstSys->currTurtle , toPrint);
   return;
}

/********************************************************************************************************************
/*@brief  import 命令 导入模块
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_import(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() != 1)//参数数目不匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line("paramater wrong of import" , currCmd.m_lineNumber);
		return;
	}
	stVal stFileName = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);
	if (stFileName.m_valKind != VAL_STRING)//参数必须为字符串类型
	{
		pFileName(currCmd.m_fileName);
		error_out_line("paramater wrong of import should be a string" , currCmd.m_lineNumber);
		return;
	}

	string fileName = stFileName.m_str_value;
	fileName.erase(0 , 1);
	fileName.erase(fileName.length()-1 , 1);
	delSpace(fileName);
	string program;
	if (false == getString(fileName , program))//文件打开错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("can not open file" + fileName , currCmd.m_lineNumber);
		return;
	}
	getFuncTable(pstSys->m_funcTable , program , fileName);//解析模块
	return;
}

/********************************************************************************************************************
/*@brief //绘图fd命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_fd(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of fd" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of fd" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
    if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	FD(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief //绘图bk命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_bk(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of bk" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of bk" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	BK(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief //绘图rt命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_rt(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of rt" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of rt" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	RT(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief //绘图lt命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_lt(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of lt" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of lt" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	LT(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief //绘图PU命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_pu(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of pu" , currCmd.m_lineNumber);
		return ;
	}

	PU(pstSys->currTurtle );//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief //绘图PD命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_pd(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of pd" , currCmd.m_lineNumber);
		return ;
	}

	PD(pstSys->currTurtle );//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief//绘图cs命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_cs(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of cs" , currCmd.m_lineNumber);
		return ;
	}

	CS(pstSys->currTurtle );//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief//绘图home命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_home(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of home" , currCmd.m_lineNumber);
		return ;
	}

	HOME(pstSys->currTurtle );//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief//绘图setx命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_setx(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of setx" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of setx" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETX(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief//绘图sety命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_sety(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of sety" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of sety" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETY(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief//绘图setxy命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_setxy(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() < 2)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of setxy" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 2)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of setxy" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal1 = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算第一个参数值
	if (UNDEFINED == tempVal1.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal1.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
   
	stVal tempVal2 = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//计算第二个参数值
	if (UNDEFINED == tempVal2.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[1] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal2.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}

	SETXY(pstSys->currTurtle , tempVal1.m_f_value , tempVal2.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief 绘图seth命令
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_seth(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of seth" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of seth" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETH(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief 绘图当前rgb值
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_set_color(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() < 3)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of setc" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 3)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of setc" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal1 = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算第一个参数值
	if (UNDEFINED == tempVal1.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal1.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	if (tempVal1.m_f_value > 255 || tempVal1.m_f_value < 0)//rgb取值范围为[0 , 255]
	{
		pFileName(currCmd.m_fileName);
		error_out_line("param 1 of setc can not bigger than 255 or less than 0" , currCmd.m_lineNumber);
		return ;
	}

	stVal tempVal2 = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//计算第二个参数值
	if (UNDEFINED == tempVal2.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[1] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal2.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	if (tempVal2.m_f_value > 255 || tempVal2.m_f_value < 0)
	{
		pFileName(currCmd.m_fileName);
		error_out_line("param 2 of setc can not bigger than 255 or less than 0" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal3 = getNormalExpressionVal(currCmd.m_argvs[2] , pstSys);//计算第三个参数值
	if (UNDEFINED == tempVal3.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[2] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal3.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	if (tempVal3.m_f_value > 255 || tempVal3.m_f_value < 0)
	{
		pFileName(currCmd.m_fileName);
		error_out_line("param 3 of setc can not bigger than 255 or less than 0" , currCmd.m_lineNumber);
		return ;
	}
    setcolor(pstSys->currTurtle,tempVal1.m_f_value , tempVal2.m_f_value , tempVal3.m_f_value);//调用海龟
	return;
}

/********************************************************************************************************************
/*@brief 在当前位置画一个圆
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_dc(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//参数数目是否匹配
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too less parameters of DC" , currCmd.m_lineNumber);
		return ;
	}
	if (currCmd.m_argvs.size() > 1)
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of DC" , currCmd.m_lineNumber);
		return ;
	}
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//计算参数值
	if (UNDEFINED == tempVal.m_valKind)//表达式错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//参数类型错误
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	drawcircle(pstSys->currTurtle , tempVal.m_f_value);//调用乌龟绘图
	return;
}

/********************************************************************************************************************
/*@brief dmake 局部变量赋值命令 当该命令用于主程序中时，相当于dmake命令 用于自定义过程中，则用于定义或者改变
/*                       全局变量的值
/*@author 邹天明
/*@param[in]  stCommand & currCmd 当前命令
/*@param[out]   stSysInfo * pSy 系统信息结构体
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_dmake(stCommand & currCmd ,stSysInfo * pstSys)
{
	if(currCmd.m_argc != 2)
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong parameters of dmake ", currCmd.m_lineNumber);
		return;
	}
	stVal tempVal ;
	stVal valToAdd;
	tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//获取第一个参数值
	if (VAL_STRING == tempVal.m_valKind )//是字符串类型的
	{
		delSpace(tempVal.m_str_value);
		tempVal.m_str_value.erase(0 , 1);
		tempVal.m_str_value.erase(tempVal.m_str_value.length()-1 ,1);//去除双引号
		delSpace(tempVal.m_str_value);
		if (false == isIllIdentifer(tempVal.m_str_value))//是否合法标识符
		{
			pFileName(currCmd.m_fileName);
			error_out_line("wrong identifer name" , currCmd.m_lineNumber);
			return ;
		}
		//获取变量名
		valToAdd.m_valName = tempVal.m_str_value;
		toLower_(valToAdd.m_valName);
	}
	else 
	{
		pFileName(currCmd.m_fileName);
		error_out_line("name should be a string"  , currCmd.m_lineNumber);
		return ;
	}

	tempVal = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//获取第二个参数值
	if (tempVal.m_valKind == UNDEFINED)//无效表达式
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong value in dmake"  , currCmd.m_lineNumber);
		return ;
	}
	valToAdd.m_str_value = tempVal.m_str_value;
	valToAdd.m_valKind = tempVal.m_valKind;
	if (tempVal.m_valKind == VAL_FLOAT)
	{
		valToAdd.m_f_value = tempVal.m_f_value;
	}
	list<stVal>::iterator it;

	if (!pstSys->m_funcStack.empty())//函数栈非空 定义的是局部变量
	{
		for (it = pstSys->m_funcStack.top().m_parmTable.begin() ; it != pstSys->m_funcStack.top().m_parmTable.end();++it)
		{
			if ((*it).m_valName == valToAdd.m_valName)
			{
				(*it) = valToAdd;
				return;//为已经定义的局部变量，则覆盖原来值
			}
		}
		//否则为该函数新建一个局部变量
	    pstSys->m_funcStack.top().m_parmTable.push_back(valToAdd);
		return;
	}
  else//如果不在函数中,则定义全局变量
  {
	  for( it=pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end();++it)
	   {
		   if ((*it).m_valName == valToAdd.m_valName)
		   {
			  (*it) = valToAdd;
			  return;
		    }
	   }
	  if (it == pstSys->m_globalValTable.end())//无同名变量  添加
	  {
		  pstSys->m_globalValTable.push_back(valToAdd);
	  }
	}
	return ;
}
/********************************************************************************************************************
/*@brief 销毁系统信息
/*@author 邹天明
/*@param[in] stSysInfo*psy
/*@param[out]   
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void  destroy_psy(stSysInfo*psy)
{
       destroy_turtle(psy->currTurtle);//销毁绘图信息
	   long int length;
		char * buffer;

		ifstream is;
		is.open (psy->currTurtle.initfilename.c_str() , ios::binary );
		if (!is)
		{
			return;
		}

		// get length of file:
		is.seekg (0, ios::end);
		length = is.tellg();
		is.seekg (0, ios::beg);

		// allocate memory:
		if (length> 0)
		{
			buffer = new char [length];
		}
		else
		{
			return;
		}
		// read data as a block:
		is.read (buffer,length);
		is.close();
		//
		if ( !psy->m_pic_fileName.empty())//如果有指定文件名 输出到指定文件
		{
             	ofstream outfile(psy->m_pic_fileName.c_str() , ios::binary);
				if (!outfile)
				{
					return;
				}
				outfile.write(buffer,length);
				outfile.close();
		}
		else
		{
                cout.write (buffer,length);//否则输出到标准输出
		}
	    delete[] buffer;
		remove(psy->currTurtle.initfilename.c_str());//删除中间文件
	   delete psy;
	   return;
}

