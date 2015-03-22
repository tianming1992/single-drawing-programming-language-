/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file sys_execu.cpp
/*@author  ������
/*@date    2011.11.11
/*@brief   ��������ģ��
/*
/*********************************************************************************************************************/

#include "sys_execu.h"


/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ������
/*@param[in]  vector<string> & inputcmds  �û���������
/*@param[out]  stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void	initSys(stSysInfo * pSy ,vector<string> & inputcmds )//��ʼ��
{  
	

   pSy->currTurtle.margin = -1;
   pSy->currTurtle.type = PNG;
   pSy->currTurtle.filename.clear();
   pSy->m_pic_fileName.clear();
    for(vector<string>::iterator it = inputcmds.begin()  ; it != inputcmds.end() ; )
   {
	   if ( (*it) ==  "-m" ||  (*it) == "-M" )//-m����
	   {  
		   ++it;
		   if ( it !=  inputcmds.end())
		   {  
			   int margin = atoi((*it).c_str());
			   if (margin < 0)//�߾಻��С��0
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
        
	   if ((*it) == "-t" || (*it) == "-T")//-T����
	   {
		   ++it;
		   if (it != inputcmds.end())
		   {  
			  string type = *it;//��ȡ�ļ�����
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
  
	   if ( (*it) == "-name" || (*it) == "-NAME" )//�����ļ���
	   {
		   ++it;
		   if (it != inputcmds.end())
		   {  
			   pSy->m_pic_fileName = *it;//��ȡ�ļ���
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
   pSy->m_programFile = inputcmds[0];//��ȡ�����ļ���
   pSy->m_execuCmdLists.clear();
   pSy->m_rootFucCallerLine = -1;
   pSy->m_funcTable.clear();
   pSy->reTurnToFunc = -1;//���غ���ջ��ַ
  
   /////////////////////////////////////////////////////��ʼ���ڹ�
   initpaint(pSy->currTurtle);
}


/********************************************************************************************************************
/*@brief ִ������
/*@author ������
/*@param[in]  list<stCommand> & stCommdQueue  �������
/*@param[out]  stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void execu_cmds( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue)
{  
	
	int funStackSize ;
	while(!stCommdQueue.empty())
	{   
         funStackSize = pstSys->m_funcStack.size();//���ִ�й�stop���� ����Ҫ���صĺ����ϲ�  �˳�����������
		if (pstSys->reTurnToFunc > -1 && funStackSize > pstSys->reTurnToFunc) 
		{
			stCommdQueue.clear();
			return;
		}
		if (pstSys->reTurnToFunc > -1 && funStackSize == pstSys->reTurnToFunc)
		{
			pstSys->reTurnToFunc = -1;
		}
		exeu(pstSys , stCommdQueue); //ִ������
		if (!stCommdQueue.empty())
		{
			stCommdQueue.pop_front();//ɾ���Ѿ�ִ�е�����
		}
		
		if (pstSys->m_funcStack.size() >   MAX_FUNCTION_STACK )//ջ�������  ���޵ݹ�
		{
			perror("function stack overflow \n");
			exit(0);
		}
     }
}

/********************************************************************************************************************
/*@brief ִ������
/*@author ������
/*@param[in]  list<stCommand> & stCommdQueue  �������
/*@param[out]  stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void exeu( struct stSysInfo * pstSys , list<stCommand> & stCommdQueue)
{
    stCommand currCmd = stCommdQueue.front();

	if (currCmd.m_cmdName == "ifelse")//ifelse����
	{
		 cmd_ifelse(currCmd , pstSys);
		 return;
	}
	if (currCmd.m_cmdName == "if")//if����
	{
		  cmd_if(currCmd , pstSys);
		   return;
	}
	if (currCmd.m_cmdName == "make")//if����
	{
       cmd_make(currCmd , pstSys);
		return;
	}
	if (currCmd.m_cmdName == "dmake")//if����
	{
		cmd_dmake(currCmd , pstSys);
		return;
	}
	if (currCmd.m_cmdName == "repeat")//repeat����
	{
		cmd_repeat(currCmd , pstSys);
         return;
	}
	if (currCmd.m_cmdName == "print")//print����
	{
		cmd_print(currCmd , pstSys);
         return;
	}
    
	if (currCmd.m_cmdName == "stop")//stop����
	{
		cmd_stop(currCmd , pstSys ,stCommdQueue);
         return;
	}

	if (currCmd.m_cmdName == "import")//stop����
	{
		return;
	}
	if (true == isFunc(currCmd.m_cmdName ,pstSys->m_funcTable))//�Ǻ���
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
	if (currCmd.m_cmdName == "dc")//��Բ
	{
		cmd_draw_dc(currCmd ,pstSys);
		return;
	}
	if (currCmd.m_cmdName == "setc")//����ǰ��ɫ
	{
		cmd_set_color(currCmd ,pstSys);
		return;
	}
   
	pFileName(currCmd.m_fileName);
    error_out_line("can not define this symbol \" " + currCmd.m_cmdName + " \"" + " there", currCmd.m_lineNumber);
}

/********************************************************************************************************************
/*@brief ��ȡ����ֵ
/*�����������  �����ں���ջ�в���  Ȼ����ȫ�ֱ����в���
/*@author ������
/*@param[in] string valName ������     stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@param[out] 
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
stVal get_val_value(string valName , stSysInfo * pstSys)
{
      stVal  stTempVal ;
	  if(!pstSys->m_funcStack.empty())//����ջ�ǿ� ���Ҿֲ�����
	  {
		  for (list<stVal>::iterator it = pstSys->m_funcStack.top().m_parmTable.begin() ;
			      it != pstSys->m_funcStack.top().m_parmTable.end(); ++it)
		  {
			  if((*it).m_valName == valName)//�ҵ��ֲ�����  ������ֵ
			  {
				  return (*it);
			  }
		  }
	  }
	  for (list<stVal>::iterator it = pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end() ; ++it)
	  {
		  if((*it).m_valName == valName)//�ҵ�ȫ�ֱ���  ������ֵ
		  {
			  return (*it);
		  }
	  }
	  stTempVal.m_valKind = UNDEFINED;//�Ҳ����ñ���  ����δ֪����
	  return stTempVal;
}

//Ѱ��ĳ�����ʽ�ڲ�����  ���ҽ��ñ���ʹ����ֵ�滻
bool replaceVeri(string &srcEpre , stSysInfo * pstSys)
{
    long int  i =0;
	while(i < srcEpre.length())
	{
		if (srcEpre[i] == ':')//�����Ŀ�ʼ����
		{
			int j =i;
           ++i;//������һ������
		   string tempValname;
		   while(i<srcEpre.length())
		   {
                 tempValname.push_back(srcEpre[i]);
				 if (true == isIllIdentifer(tempValname))//�ǺϷ���־���� ������һ���ַ�
				 {
					 ++i;
				 }
				 else break;
		   }
		   //�˳�ѭ�� �ͷ����һ���Ƿ���ʶ��
		   if (true == tempValname.empty())
		   {
			   return false;
		   }
		   if (false == isIllIdentifer(tempValname))
		   {
			     tempValname.erase(tempValname.length()-1 , 1);
		   }
		
		   stVal tempVal = get_val_value(tempValname , pstSys);
		   if (UNDEFINED == tempVal.m_valKind )//δ�������
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
/*@brief ��ȡһ����ͨ���ʽֵ
/*һ����ͨ���ʽָ����  һ����ֵ���ʽ   ����  һ���ַ��� ���п��ܰ�������
/*@author ������
/*@param[in]  string &srcEpre  ���ʽ   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@param[out] 
/*@return  stval  �����ṹ��
/*@pre
/*@exception  �������ṹ������Ϊundefine ˵���������ʽ����
/********************************************************************************************************************/
stVal  getNormalExpressionVal(string &srcEpre , stSysInfo * pstSys)
{  
	  stVal tempVal;
      if(true == isConstStr(srcEpre))//��һ���ַ�������
	  {
           tempVal.m_str_value = srcEpre;
		   tempVal.m_valKind = VAL_STRING;
		   return tempVal;
	  }
	  replaceVeri(srcEpre,pstSys);//�滻���ʽ����
	  if(true == isConstStr(srcEpre))//��һ���ַ�������
	  {
		  tempVal.m_str_value = srcEpre;
		  tempVal.m_valKind = VAL_STRING;
		  return tempVal;
	  }
	  float value;
	  if (true == ValueExpression(srcEpre , value))//��һ�����ʽ
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
      tempVal.m_valKind = UNDEFINED;//��Ч�ı��ʽ
	  return tempVal;
}

/********************************************************************************************************************
/*@brief make ����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
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
	tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//��ȡ��һ������ֵ
	if (VAL_STRING == tempVal.m_valKind )//���ַ������͵�
	{
		delSpace(tempVal.m_str_value);
		tempVal.m_str_value.erase(0 , 1);
		tempVal.m_str_value.erase(tempVal.m_str_value.length()-1 ,1);//ȥ��˫����
        delSpace(tempVal.m_str_value);
		if (false == isIllIdentifer(tempVal.m_str_value))//�Ƿ�Ϸ���ʶ��
		{
			pFileName(currCmd.m_fileName);
			error_out_line("wrong identifer name" , currCmd.m_lineNumber);
			return ;
		}
		//��ȡ������
		valToAdd.m_valName = tempVal.m_str_value;
		toLower_(valToAdd.m_valName);
    }
	else 
	{
		pFileName(currCmd.m_fileName);
		error_out_line("name should be a string"  , currCmd.m_lineNumber);
		return ;
	}
   
	tempVal = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//��ȡ�ڶ�������ֵ
	 if (tempVal.m_valKind == UNDEFINED)//��Ч���ʽ
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
        //�Ƿ񸲸�
		list<stVal>::iterator it;
		for( it=pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end();++it)
	   {
           if ((*it).m_valName == valToAdd.m_valName)
           {
			   (*it) = valToAdd;
			   break;
           }
	    }
		if (it == pstSys->m_globalValTable.end())//��ͬ������  ���
		{
			pstSys->m_globalValTable.push_back(valToAdd);
		}
       return ;
} 

/********************************************************************************************************************
/*@brief  ִ�к��� 
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  ���޵ݹ�ᵼ��ջ��� �������Զ��˳�
/********************************************************************************************************************/
void cmd_func(stCommand & currCmd ,stSysInfo * pstSys)
{
    stFunc currFunction ;
	list<stFunc>::iterator it;
	for ( it = pstSys->m_funcTable.begin() ; it != pstSys->m_funcTable.end() ; ++it)
	{
		if ((*it).m_funcName == currCmd.m_cmdName)//Ѱ�Ҹú�������
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
	if (currCmd.m_argc < currFunction.m_argc)//��������̫��
	{
		pFileName(currCmd.m_fileName);
		error_out_line("too less paramaters  " , currCmd.m_lineNumber);
		return ;
	}
	list<stVal>::iterator false_it = currFunction.m_parmTable.begin();//�βα�
	vector<string>::iterator true_it = currCmd.m_argvs.begin();//ʵ�α�
    while(false_it != currFunction.m_parmTable.end() && true_it != currCmd.m_argvs.end())//�������βθ�ֵ
	{
         stVal tempVal = getNormalExpressionVal((*true_it) , pstSys);//��ȡʵ�ε�ֵ
		 if (UNDEFINED == tempVal.m_valKind)//ʵ�ζ������
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
		pstSys->m_rootFucCallerLine = currCmd.m_lineNumber; //����ջ��һ��������ȡ���ʼ�������к� 
	}                                                                                          //�����жϸú����Ƿ���Ч����
     //С�ں������ڵ�ַ  δ�������
	if((pstSys->m_rootFucCallerLine < currFunction.m_lineNumber) && (pstSys->m_programFile == currFunction.m_fileName))
	{
		pFileName(currCmd.m_fileName);
		error_out_line("undefined symbol  \" " + currFunction.m_funcName  + " \"" , currCmd.m_lineNumber);
		return ;
	}

	if (currFunction.m_conntext.empty())
	{
		return ;//����Ϊ�� ����
	}
    pstSys->m_funcStack.push(currFunction);//����ǰ�����뺯��ջ
    list<stCommand> currFunCmds;
	 //�����ú�������
	parase(currFunCmds , currFunction.m_conntext , pstSys->m_funcTable,FUNC_CMD ,currFunction.m_lineNumber ,currFunction.m_fileName);
	execu_cmds(pstSys , currFunCmds);//ִ�иú�������
	//����ִ����� ������ջ
	pstSys->m_funcStack.pop();
	return ;
}

/********************************************************************************************************************
/*@brief ��ȡ�������ʽֵ
/*@author ������
/*@param[in]   string sExpr �������ʽ     stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@param[out] 
/*@return  ����ֵ 0 ��  1 �� -1 ����  
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
			if (nQuote == 0)//��һ���������� ���������ַ���
			{
				nQuote = 1;
			}
			else if(nQuote == 1)
			{
				if (false == isChangeMean(i , sExpr))//���ַ����������ŷ�ת���ַ�
				{
					nQuote = 0;
				}
			}
		}
        if (nQuote ==0 && (sExpr[i] == '<' || sExpr[i] == '>' || sExpr[i] == '='))//Ѱ����������
        {
           pos = i;
		   op = sExpr[i];
        }
		++i;
	}

	string left = sExpr.substr(0 , pos);
	string right = sExpr.erase(0 , pos +1);//��ȡ���ұ��ʽ
	delSpace(left);
	delSpace(right);
	if (left.empty() || right.empty())
	{
		return -1;
	}
	stVal leftVal = getNormalExpressionVal(left,pstSys);
	stVal rightVal = getNormalExpressionVal(right,pstSys);
	if (leftVal.m_valKind == UNDEFINED || rightVal.m_valKind == UNDEFINED)//���ʽ�Ǵ���
	{
		return -1;
	}
   if (leftVal.m_valKind != leftVal.m_valKind)
   { 
	   return -1;//����ƥ�����
   }
   if(rightVal.m_valKind == VAL_FLOAT)//��ֵ�Ƚ�
   {
       switch(op)
	   {
	   case  '>':  return leftVal.m_f_value > rightVal.m_f_value;
	   case  '<':  return leftVal.m_f_value < rightVal.m_f_value;
	   case  '=':  return leftVal.m_f_value == rightVal.m_f_value; 
	   }
   }
   if (rightVal.m_valKind == VAL_STRING)//�ַ����Ƚ�
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
/*@brief  if����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_if(stCommand & currCmd ,stSysInfo * pstSys)
{
    string condition = currCmd.m_argvs[0]; //��ȡ�������ʽ
	if(condition.empty())
	{
		pFileName(currCmd.m_fileName);
		error_out_line("condition can not be empty of if" , currCmd.m_lineNumber);
		return;
	}
	int value = getConditionExVal(condition , pstSys);//��ȡ�������ʽֵ
	if(-1 == value)//�������ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong condition expression of if \" "+ condition + " \"" , currCmd.m_lineNumber);
		return;
	}
	if (value)//����ֵΪ��
	{
        delSpace(currCmd.m_argvs[1]);
		if (currCmd.m_argvs[1].empty())
		{
			return;//ִ�����Ϊ��
		}
		list<stCommand> currIfCmds;
		//������if����
		parase(currIfCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfCmds);//ִ�и�if����
		return;
	}
	return;
}

/********************************************************************************************************************
/*@brief  ifelse����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_ifelse(stCommand & currCmd ,stSysInfo * pstSys)
{
	string condition = currCmd.m_argvs[0]; //��ȡ�������ʽ
	if(condition.empty())
	{
		pFileName(currCmd.m_fileName);
		error_out_line("condition can not be empty of ifelse" , currCmd.m_lineNumber);
		return;
	}
	int value = getConditionExVal(condition , pstSys);//��ȡ�������ʽֵ
	if(-1 == value)//�������ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong condition expression of ifelse \" "+condition +" \"" , currCmd.m_lineNumber);
		return;
	}

	if (value)//����ֵΪ��
	{
		delSpace(currCmd.m_argvs[1]);
		if (currCmd.m_argvs[1].empty())
		{
			return;//ִ�����Ϊ��
		}
		list<stCommand> currIfelseCmds;
		//������if����
		parase(currIfelseCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfelseCmds);//ִ�и�if����
		return;
	}
	else
	{ 
		delSpace(currCmd.m_argvs[2]);
		if (currCmd.m_argvs[2].empty())
		{
			return;//ִ�����Ϊ��
		}
		list<stCommand> currIfelseCmds;
		//������ifelse����
		parase(currIfelseCmds ,currCmd.m_argvs[2] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		execu_cmds(pstSys , currIfelseCmds);//ִ�и�if����
		return;
	}
}

/********************************************************************************************************************
/*@brief  repeat����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_repeat(stCommand & currCmd ,stSysInfo * pstSys)
{
     string times = currCmd.m_argvs[0];//ѭ����������
	 delSpace( times);
	 stVal timeVal = getNormalExpressionVal(times , pstSys);//��ȡѭ���������ʽֵ
	 if(timeVal.m_valKind != VAL_FLOAT)
	 {
		 pFileName(currCmd.m_fileName);
		 error_out_line("error expression of repeat" , currCmd.m_lineNumber);//�������ʹ���
		 return ;
	 }

	 if (false == isInt(timeVal.m_f_value))
	 {  
		 	pFileName(currCmd.m_fileName);
		 error_out_line("circle times should be a integer" , currCmd.m_lineNumber);//����Ϊ����
		 return ;
	 }

	 if (currCmd.m_argvs[1].empty())
	 {
		 return ;//ѭ�����Ϊ��
	 }
	 list<stCommand> currRepeatCmds;
	 for (int i = 0 ; i < timeVal.m_f_value ; ++ i)
	 {  
		 //������repeat����
		 parase(currRepeatCmds ,currCmd.m_argvs[1] , pstSys->m_funcTable,SET_CMD ,currCmd.m_lineNumber ,currCmd.m_fileName);
		 execu_cmds(pstSys , currRepeatCmds);//ѭ��ִ�и�repeat����
	 }
       return;
}

/********************************************************************************************************************
/*@brief  stop����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_stop(stCommand & currCmd ,stSysInfo * pstSys, list<stCommand> & stCommdQueue)
{  
	if (currCmd.m_argc >0) //��������
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many paraters of stop" , currCmd.m_lineNumber);
		return ;
	}
    if (true == pstSys->m_funcStack.empty())//����ջΪ�� ������ǰ�������������� �˳�����
    {
		destroy_psy(pstSys);//����ϵͳ��Ϣ
		exit(0);
    }
	else//����ջ�ǿ� �����ں�����  �˻ص���һ�㺯��
	{
         pstSys->reTurnToFunc = pstSys->m_funcStack.size() -1 ;
         stCommdQueue.clear();//��յ�ǰ�������
		 return ;
	}
}

/********************************************************************************************************************
/*@brief  print����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
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
   if (UNDEFINED == tempVal.m_valKind)//���ʽ����
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
   if (tempVal.m_valKind == VAL_STRING)//��ȡ�ַ���ֵ�����Ҵ����ڲ�ת���ַ�
   {
	   toPrint = tempVal.m_str_value;
	   toPrint.erase(0 ,1);
	   toPrint.erase(toPrint.length()-1 ,1);
	   toPrint = toChangeMean(toPrint);
   }

   //////////////////////////////////////////////////////////////////////////////////////////�͸��ڹ��ӡ
   print(pstSys->currTurtle , toPrint);
   return;
}

/********************************************************************************************************************
/*@brief  import ���� ����ģ��
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_import(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() != 1)//������Ŀ��ƥ��
	{
		pFileName(currCmd.m_fileName);
		error_out_line("paramater wrong of import" , currCmd.m_lineNumber);
		return;
	}
	stVal stFileName = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);
	if (stFileName.m_valKind != VAL_STRING)//��������Ϊ�ַ�������
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
	if (false == getString(fileName , program))//�ļ��򿪴���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("can not open file" + fileName , currCmd.m_lineNumber);
		return;
	}
	getFuncTable(pstSys->m_funcTable , program , fileName);//����ģ��
	return;
}

/********************************************************************************************************************
/*@brief //��ͼfd����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_fd(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
    if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	FD(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief //��ͼbk����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_bk(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	BK(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief //��ͼrt����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_rt(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	RT(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief //��ͼlt����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_lt(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	LT(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief //��ͼPU����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_pu(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//������Ŀ�Ƿ�ƥ��
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of pu" , currCmd.m_lineNumber);
		return ;
	}

	PU(pstSys->currTurtle );//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief //��ͼPD����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_pd(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//������Ŀ�Ƿ�ƥ��
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of pd" , currCmd.m_lineNumber);
		return ;
	}

	PD(pstSys->currTurtle );//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief//��ͼcs����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_cs(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//������Ŀ�Ƿ�ƥ��
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of cs" , currCmd.m_lineNumber);
		return ;
	}

	CS(pstSys->currTurtle );//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief//��ͼhome����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_home(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() > 0)//������Ŀ�Ƿ�ƥ��
	{
		pFileName(currCmd.m_fileName);
		error_out_line(" too many parameters of home" , currCmd.m_lineNumber);
		return ;
	}

	HOME(pstSys->currTurtle );//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief//��ͼsetx����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_setx(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETX(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief//��ͼsety����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_sety(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETY(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief//��ͼsetxy����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_setxy(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() < 2)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal1 = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�����һ������ֵ
	if (UNDEFINED == tempVal1.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal1.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
   
	stVal tempVal2 = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//����ڶ�������ֵ
	if (UNDEFINED == tempVal2.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[1] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal2.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}

	SETXY(pstSys->currTurtle , tempVal1.m_f_value , tempVal2.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief ��ͼseth����
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_seth(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	SETH(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief ��ͼ��ǰrgbֵ
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_set_color(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() < 3)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal1 = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�����һ������ֵ
	if (UNDEFINED == tempVal1.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal1.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	if (tempVal1.m_f_value > 255 || tempVal1.m_f_value < 0)//rgbȡֵ��ΧΪ[0 , 255]
	{
		pFileName(currCmd.m_fileName);
		error_out_line("param 1 of setc can not bigger than 255 or less than 0" , currCmd.m_lineNumber);
		return ;
	}

	stVal tempVal2 = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//����ڶ�������ֵ
	if (UNDEFINED == tempVal2.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[1] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal2.m_valKind)//�������ʹ���
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
	stVal tempVal3 = getNormalExpressionVal(currCmd.m_argvs[2] , pstSys);//�������������ֵ
	if (UNDEFINED == tempVal3.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[2] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal3.m_valKind)//�������ʹ���
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
    setcolor(pstSys->currTurtle,tempVal1.m_f_value , tempVal2.m_f_value , tempVal3.m_f_value);//���ú���
	return;
}

/********************************************************************************************************************
/*@brief �ڵ�ǰλ�û�һ��Բ
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void cmd_draw_dc(stCommand & currCmd ,stSysInfo * pstSys)
{
	if (currCmd.m_argvs.size() == 0)//������Ŀ�Ƿ�ƥ��
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
	stVal tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//�������ֵ
	if (UNDEFINED == tempVal.m_valKind)//���ʽ����
	{
		pFileName(currCmd.m_fileName);
		error_out_line("wrong expression or undefined symbol \" "+currCmd.m_argvs[0] +" \"" , currCmd.m_lineNumber);
		return ;
	}
	if(VAL_STRING == tempVal.m_valKind)//�������ʹ���
	{
		pFileName(currCmd.m_fileName);
		error_out_line("parameters should be a number" , currCmd.m_lineNumber);
		return ;
	}
	drawcircle(pstSys->currTurtle , tempVal.m_f_value);//�����ڹ��ͼ
	return;
}

/********************************************************************************************************************
/*@brief dmake �ֲ�������ֵ���� ��������������������ʱ���൱��dmake���� �����Զ�������У������ڶ�����߸ı�
/*                       ȫ�ֱ�����ֵ
/*@author ������
/*@param[in]  stCommand & currCmd ��ǰ����
/*@param[out]   stSysInfo * pSy ϵͳ��Ϣ�ṹ��
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
	tempVal = getNormalExpressionVal(currCmd.m_argvs[0] , pstSys);//��ȡ��һ������ֵ
	if (VAL_STRING == tempVal.m_valKind )//���ַ������͵�
	{
		delSpace(tempVal.m_str_value);
		tempVal.m_str_value.erase(0 , 1);
		tempVal.m_str_value.erase(tempVal.m_str_value.length()-1 ,1);//ȥ��˫����
		delSpace(tempVal.m_str_value);
		if (false == isIllIdentifer(tempVal.m_str_value))//�Ƿ�Ϸ���ʶ��
		{
			pFileName(currCmd.m_fileName);
			error_out_line("wrong identifer name" , currCmd.m_lineNumber);
			return ;
		}
		//��ȡ������
		valToAdd.m_valName = tempVal.m_str_value;
		toLower_(valToAdd.m_valName);
	}
	else 
	{
		pFileName(currCmd.m_fileName);
		error_out_line("name should be a string"  , currCmd.m_lineNumber);
		return ;
	}

	tempVal = getNormalExpressionVal(currCmd.m_argvs[1] , pstSys);//��ȡ�ڶ�������ֵ
	if (tempVal.m_valKind == UNDEFINED)//��Ч���ʽ
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

	if (!pstSys->m_funcStack.empty())//����ջ�ǿ� ������Ǿֲ�����
	{
		for (it = pstSys->m_funcStack.top().m_parmTable.begin() ; it != pstSys->m_funcStack.top().m_parmTable.end();++it)
		{
			if ((*it).m_valName == valToAdd.m_valName)
			{
				(*it) = valToAdd;
				return;//Ϊ�Ѿ�����ľֲ��������򸲸�ԭ��ֵ
			}
		}
		//����Ϊ�ú����½�һ���ֲ�����
	    pstSys->m_funcStack.top().m_parmTable.push_back(valToAdd);
		return;
	}
  else//������ں�����,����ȫ�ֱ���
  {
	  for( it=pstSys->m_globalValTable.begin() ; it != pstSys->m_globalValTable.end();++it)
	   {
		   if ((*it).m_valName == valToAdd.m_valName)
		   {
			  (*it) = valToAdd;
			  return;
		    }
	   }
	  if (it == pstSys->m_globalValTable.end())//��ͬ������  ���
	  {
		  pstSys->m_globalValTable.push_back(valToAdd);
	  }
	}
	return ;
}
/********************************************************************************************************************
/*@brief ����ϵͳ��Ϣ
/*@author ������
/*@param[in] stSysInfo*psy
/*@param[out]   
/*@return  void
/*@pre
/*@exception  
/********************************************************************************************************************/
void  destroy_psy(stSysInfo*psy)
{
       destroy_turtle(psy->currTurtle);//���ٻ�ͼ��Ϣ
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
		if ( !psy->m_pic_fileName.empty())//�����ָ���ļ��� �����ָ���ļ�
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
                cout.write (buffer,length);//�����������׼���
		}
	    delete[] buffer;
		remove(psy->currTurtle.initfilename.c_str());//ɾ���м��ļ�
	   delete psy;
	   return;
}

