/*********************************************************************************************************************
/*Copyright  ֥����С�� All right reserved @2011 
/*@file turtle.cpp
/*@author  ��Ǳ
/*@date    2011.11.11
/*@brief   ��ͼ����ִ��ģ��
/*
/*********************************************************************************************************************/
#include "turtle.h"

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void initpaint(stTurtle &stCurrTurtle)
{
	if (stCurrTurtle.margin >=0)
	{
		stCurrTurtle.record = true; //�����-m ���� ���¼��ǰ��������
	}
	else
	{
		stCurrTurtle.record = false; 
	}
	//��ʼ������ṹ�����
	stCurrTurtle.m_currX=0;
	stCurrTurtle.m_currY=0;
	stCurrTurtle.m_last_currX=0;
	stCurrTurtle.m_last_currY=0;
	stCurrTurtle.m_max_positive_x=0;  
	stCurrTurtle.m_max_negtive_x=0;  
	stCurrTurtle.m_max_positive_y=0;  
	stCurrTurtle.m_max_negtive_y=0;
	stCurrTurtle.m_currAngle=0;
	stCurrTurtle.m_write=true;
	if (stCurrTurtle.type == PNG)
	{
		stCurrTurtle.filename = "~temp~~.png";//�м��ļ���
	}
	else
	{
        stCurrTurtle.filename = "~temp~~.pdf";//�м��ļ���
	}
	
	stCurrTurtle.initfilename=stCurrTurtle.filename;
	stCurrTurtle.flag_max_isset=false;
	string gg=stCurrTurtle.filename;
	int mm=stCurrTurtle.filename.length();
	if (stCurrTurtle.type==PNG)           //���Ҫ����png
	{		
		if (stCurrTurtle.filename.length()==0)
		{
			stCurrTurtle.filename="slogo.png";
	    }
		stCurrTurtle.initfilename = stCurrTurtle.filename;
	     
		if (stCurrTurtle.margin<0)                        //�б߾�����
		{
			stCurrTurtle.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 1000);
			stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
			cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);  
			cairo_select_font_face ( stCurrTurtle.cr, "Adobe Heiti Std" ,
				CAIRO_FONT_SLANT_NORMAL,
				CAIRO_FONT_WEIGHT_NORMAL) ;
			cairo_set_font_size ( stCurrTurtle.cr, 24.0 ) ;
			cairo_set_line_width(stCurrTurtle.cr,1);
			cairo_set_source_rgb(stCurrTurtle.cr , 255,255,255);
			cairo_rectangle(stCurrTurtle.cr , 0 , 0, 1010,1010);
			cairo_fill(stCurrTurtle.cr);
			cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);
		} 
		else                                  //û�б߾�����
		{
			if (stCurrTurtle.record==true)
			{
				stCurrTurtle.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 2000, 2000);
				stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
				cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);  
				cairo_select_font_face ( stCurrTurtle.cr, "Adobe Heiti Std" ,
					CAIRO_FONT_SLANT_NORMAL,
					CAIRO_FONT_WEIGHT_NORMAL) ;
				cairo_set_font_size ( stCurrTurtle.cr, 24.0 ) ;
				cairo_set_line_width(stCurrTurtle.cr,1);
				stCurrTurtle.filename=stCurrTurtle.initfilename + "1";
			}
		}
	} 
	else                  //���Ҫ����pdf
	{
		if (stCurrTurtle.filename.length()==0)
		{
			stCurrTurtle.filename="slogo.pdf";
	    }
		  stCurrTurtle.initfilename = stCurrTurtle.filename;

		if (stCurrTurtle.margin<0)               //û�б߾�����
		{
			stCurrTurtle.surface = cairo_pdf_surface_create(stCurrTurtle.filename.c_str(), 1000, 1000);
			stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
			cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);  
			cairo_select_font_face ( stCurrTurtle.cr, "Adobe Heiti Std" ,
				CAIRO_FONT_SLANT_NORMAL,
				CAIRO_FONT_WEIGHT_NORMAL) ;
			cairo_set_font_size ( stCurrTurtle.cr, 24.0 ) ;
			cairo_set_line_width(stCurrTurtle.cr,1);
		} 
		else                   //�б߾�����
		{
			if (stCurrTurtle.record==true)
			{
				stCurrTurtle.filename= stCurrTurtle.initfilename + "1";
				stCurrTurtle.surface = cairo_pdf_surface_create(stCurrTurtle.filename.c_str(), 2000, 2000);
				stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
				cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);  
				cairo_select_font_face ( stCurrTurtle.cr, "Adobe Heiti Std" ,
					CAIRO_FONT_SLANT_NORMAL,
					CAIRO_FONT_WEIGHT_NORMAL) ;
				cairo_set_font_size ( stCurrTurtle.cr, 24.0 ) ;
				cairo_set_line_width(stCurrTurtle.cr,1);

			}
		}
	}
}

/********************************************************************************************************************
/*@brief Ѱ�����߽�
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void findmax(stTurtle &stCurrTurtle)                 // ��ú���ı߼�����
{

	if (stCurrTurtle.m_write==true)
	{

		if (stCurrTurtle.flag_max_isset==true)               //����ı߼������Ѿ�����
		{

			if (stCurrTurtle.m_currX>stCurrTurtle.m_max_positive_x)          //��ǰx��������������x����
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currX<stCurrTurtle.m_max_negtive_x)       //��ǰx����С�������x����
			{
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currY>stCurrTurtle.m_max_positive_y)     //��ǰy��������������y����
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY;
			}
			if (stCurrTurtle.m_currY<stCurrTurtle.m_max_negtive_y)        //��ǰy����С���������y����
			{
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY;
			}

			if (stCurrTurtle.m_last_currX>stCurrTurtle.m_max_positive_x)          //��ǰx��������������x����
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_last_currX;
			}
			if (stCurrTurtle.m_last_currX<stCurrTurtle.m_max_negtive_x)       //��ǰx����С�������x����
			{
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_last_currX;
			}
			if (stCurrTurtle.m_last_currY>stCurrTurtle.m_max_positive_y)     //��ǰy��������������y����
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_last_currY;
			}
			if (stCurrTurtle.m_last_currY<stCurrTurtle.m_max_negtive_y)        //��ǰy����С���������y����
			{
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_last_currY;
			}
		}
		else                   //����ı߼����껹û����
		{
			if (stCurrTurtle.m_currX>stCurrTurtle.m_last_currX)                //��ǰx���������һ��x����
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX;
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_last_currX;
			} 
			else
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_last_currX;
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currY>stCurrTurtle.m_last_currY)                //��ǰy���������һ��y����
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY;
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_last_currY;
			} 
			 //��ǰy����С���������y����
			else
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_last_currY;
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY;
			}
			stCurrTurtle.flag_max_isset=true;
		}
	}
}

/********************************************************************************************************************
/*@brief FD����
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ�� float length
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void FD(stTurtle &stCurrTurtle,float length)
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //�����������      
	{
		hisCmd temp;
		temp.m_name = "FD";
		temp.params.push_back(length);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��

	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		cairo_rel_line_to(stCurrTurtle.cr,length*sin(stCurrTurtle.m_currAngle*PI/180),-length*cos(stCurrTurtle.m_currAngle*PI/180));
	}
	else                              //�������ʣ��������켣
	{
		cairo_rel_move_to(stCurrTurtle.cr,length*sin
			(stCurrTurtle.m_currAngle*PI/180),-length*cos(stCurrTurtle.m_currAngle*PI/180));
	}

	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);             //�õ���ǰ�����ʵ������
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)                                        //ҳ�߾�û�У���ѵ�ǰʵ������ת��Ϊ���������
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);                            //��ú�����ĸ��߼�����
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
	//cairo_destroy(cr);
}

/********************************************************************************************************************
/*@brief BK ����
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��  float length
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void BK(stTurtle &stCurrTurtle,float length)          
{
	FD(stCurrTurtle,-length);
}

/********************************************************************************************************************
/*@brief RT����
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle,float angle
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void RT(stTurtle &stCurrTurtle,float angle)         //������ת
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)        //�����������      
	{
		hisCmd temp;
		temp.m_name = "RT";
		temp.params.push_back(angle);
		stCurrTurtle.cmds.push_back(temp);
	}

	stCurrTurtle.m_currAngle+=angle;
}

/********************************************************************************************************************
/*@brief    //������ת
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle,float angle
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void LT(stTurtle &stCurrTurtle,float angle)       //������ת
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)    //�����������      
	{
		hisCmd temp;
		temp.m_name = "LT";
		temp.params.push_back(angle);
		stCurrTurtle.cmds.push_back(temp);
	}

	stCurrTurtle.m_currAngle-=angle;
}

/********************************************************************************************************************
/*@brief //̧��
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void PU(stTurtle &stCurrTurtle)  //̧��
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)     //�����������     
	{
		hisCmd temp;
		temp.m_name = "PU";
		stCurrTurtle.cmds.push_back(temp);
	}
	stCurrTurtle.m_write=false;
}

/********************************************************************************************************************
/*@brief //���
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void PD(stTurtle &stCurrTurtle)  //���
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)     //�����������     
	{
		hisCmd temp;
		temp.m_name = "PD";
		stCurrTurtle.cmds.push_back(temp);
	}
	stCurrTurtle.m_write=true;
}

/********************************************************************************************************************
/*@brief   //�������ͼ�Σ�����ص�ԭ�㣬����0��
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void CS(stTurtle &stCurrTurtle)                //�������ͼ�Σ�����ص�ԭ�㣬����0��
{

	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)      //�����������     
	{
		hisCmd temp;
		temp.m_name = "CS";
		stCurrTurtle.cmds.push_back(temp);
	}
	    //�������ͼ��
	if (stCurrTurtle.type==PNG)                 
	{
		cairo_save(stCurrTurtle.cr);
		cairo_rectangle(stCurrTurtle.cr,0,0,2000,2000);
		cairo_set_source_rgb(stCurrTurtle.cr,255,255,255);
		cairo_fill(stCurrTurtle.cr);
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
		cairo_restore(stCurrTurtle.cr);
		stCurrTurtle.flag_max_isset=false;
	} 
	else
	{
		cairo_rectangle(stCurrTurtle.cr,0,0,2000,2000);
		cairo_set_source_rgb(stCurrTurtle.cr,255,255,255);
		cairo_fill(stCurrTurtle.cr);
		cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);
		stCurrTurtle.flag_max_isset=false;
	}
    stCurrTurtle.m_currAngle = 0;
	bool tempWrite = stCurrTurtle.m_write;
	stCurrTurtle.m_write = false;
	HOME(stCurrTurtle);
	stCurrTurtle.m_write = tempWrite;
}

/********************************************************************************************************************
/*@brief  //����ص�ԭ�㣬����0��
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void HOME(stTurtle &stCurrTurtle)           //����ص�ԭ�㣬����0��
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)         //�����������     
	{
		hisCmd temp;
		temp.m_name = "HOME";
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		cairo_rel_line_to(stCurrTurtle.cr,-stCurrTurtle.m_currX,stCurrTurtle.m_currY);
	}
	else                              //�������ʣ��������켣
	{
		cairo_rel_move_to(stCurrTurtle.cr,-stCurrTurtle.m_currX,stCurrTurtle.m_currY);
	}
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);          //�õ���ǰ�����ʵ������
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
	stCurrTurtle.m_currAngle=0;
}

/********************************************************************************************************************
/*@brief SETX����
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle,float fx_axis
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void SETX(stTurtle &stCurrTurtle,float fx_axis)
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)
	{
		hisCmd temp;
		temp.m_name = "SETX";
		temp.params.push_back(fx_axis);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	float true_x=fx_axis-stCurrTurtle.m_currX;    //ת��Ϊ������ڵ�������

	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		cairo_rel_line_to(stCurrTurtle.cr,true_x,0);
	}
	else                              //�������ʣ��������켣
	{
		cairo_rel_move_to(stCurrTurtle.cr,true_x,0);
	}
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void SETY(stTurtle &stCurrTurtle,float fy_axis)
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)
	{
		hisCmd temp;
		temp.m_name = "SETY";
		temp.params.push_back(fy_axis);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	float true_y=fy_axis-stCurrTurtle.m_currY;    //ת��Ϊ������ڵ�������

	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		cairo_rel_line_to(stCurrTurtle.cr,0,-true_y);
	}
	else                              //�������ʣ��������켣
	{
		cairo_rel_move_to(stCurrTurtle.cr,0,-true_y);
	}
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void SETXY(stTurtle &stCurrTurtle,float fx_axis,float fy_axis)
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)
	{
		hisCmd temp;
		temp.m_name = "SETXY";
		temp.params.push_back(fx_axis);
		temp.params.push_back(fy_axis);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	float true_x=fx_axis-stCurrTurtle.m_currX;    //ת��Ϊ������ڵ�������
	float true_y=fy_axis-stCurrTurtle.m_currY;    //ת��Ϊ������ڵ�������

	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		cairo_rel_line_to(stCurrTurtle.cr,true_x,-true_y);
	}
	else                              //�������ʣ��������켣
	{
		cairo_rel_move_to(stCurrTurtle.cr,true_x,-true_y);
	}
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void SETH(stTurtle &stCurrTurtle,float angle)
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)
	{
		hisCmd temp;
		temp.m_name = "SETH";
		temp.params.push_back(angle);
		stCurrTurtle.cmds.push_back(temp);
	}
	stCurrTurtle.m_currAngle=angle;
}
void print(stTurtle &stCurrTurtle,string txt)
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)
	{
		hisCmd temp;
		temp.m_name = "print";
		temp.txtname=txt;
		stCurrTurtle.cmds.push_back(temp);
	}
	double thenewx,thenewy;
	cairo_move_to(stCurrTurtle.cr,499,500);       //�ƶ���ԭ��
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	cairo_save(stCurrTurtle.cr);
	cairo_rotate(stCurrTurtle.cr,stCurrTurtle.m_currAngle*PI/180);
	cairo_text_path(stCurrTurtle.cr,txt.c_str());
	cairo_rotate(stCurrTurtle.cr,-stCurrTurtle.m_currAngle*PI/180);
	cairo_restore(stCurrTurtle.cr);
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)                //ҳ�߾�û�У���ѵ�ǰʵ������ת��Ϊ���������
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);
	stCurrTurtle.m_currX=stCurrTurtle.m_last_currX;
	stCurrTurtle.m_currY=stCurrTurtle.m_last_currY;
	if (cos(stCurrTurtle.m_currAngle)>0)         //�����������������yƫ��
	{
		stCurrTurtle.m_max_positive_y+=1;
	} 
	else
	{
		stCurrTurtle.m_max_negtive_y-=1;
	}
	if (sin(stCurrTurtle.m_currAngle)>0)         //�����������������xƫ��
	{
		stCurrTurtle.m_max_positive_x+=0;
	} 
	else
	{
		stCurrTurtle.m_max_negtive_x-=0;
	}

	cairo_stroke(stCurrTurtle.cr);
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
}

/********************************************************************************************************************
/*@brief ��ʼ��ϵͳ��Ϣ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void  destroy_turtle(stTurtle &stCurrTurtle)       //�ڶ��������������ʼ������ṹ��
{
	float  width,height;                            

	width=stCurrTurtle.m_max_positive_x-stCurrTurtle.m_max_negtive_x+2;               //��õ�ǰͼ����ʵ�ʿ��
	height=stCurrTurtle.m_max_positive_y-stCurrTurtle.m_max_negtive_y+2;               //��õ�ǰͼ����ʵ�ʸ߶�

	float truex=999+stCurrTurtle.m_max_negtive_x-stCurrTurtle.margin-1;                  //��õ�ǰͼ����ʵ�����϶����x����
	float truey=1000-stCurrTurtle.m_max_positive_y-stCurrTurtle.margin-1;              //��õ�ǰͼ����ʵ�����϶����y����
	if (stCurrTurtle.margin < 0)//���û��-m���� ֱ�����ٷ���
	{
		if (stCurrTurtle.type == PDF)
		{
			cairo_show_page(stCurrTurtle.cr);
		}
		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//�ͷ�cr surface�Ȳ���
		return;
	}
	if (stCurrTurtle.record == true)
	{  
		if (stCurrTurtle.type == PDF)
		{
			cairo_show_page(stCurrTurtle.cr);
		}
		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//�ͷ�cr surface�Ȳ���
	}


	if (stCurrTurtle.record==true)                   //������ǰ�ǵ�һ��ִ������
	{
		stCurrTurtle.m_currX=0;                                                        
		stCurrTurtle.m_currY=0;
		stCurrTurtle.m_last_currX=0;
		stCurrTurtle.m_last_currY=0;
		stCurrTurtle.m_max_positive_x=0;  
		stCurrTurtle.m_max_negtive_x=0;  
		stCurrTurtle.m_max_positive_y=0;  
		stCurrTurtle.m_max_negtive_y=0;
		stCurrTurtle.m_currAngle=0;
		stCurrTurtle.m_write=true;
		stCurrTurtle.flag_max_isset=false;
		stCurrTurtle.record=false;	//��ʼ������  ��record =false
		stCurrTurtle.filename=stCurrTurtle.initfilename;
		if (stCurrTurtle.type==PNG)   //��� margin>=0���������µĴ�Сsurface  
		{
			stCurrTurtle.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,width+2*stCurrTurtle.margin, height+2*stCurrTurtle.margin);
			stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
			cairo_rectangle(stCurrTurtle.cr,0,0,width+2*stCurrTurtle.margin+20,height+2*stCurrTurtle.margin+20);
			cairo_set_source_rgb(stCurrTurtle.cr,255,255,255);
			cairo_fill(stCurrTurtle.cr);
		     cairo_set_source_rgb(stCurrTurtle.cr , 0 ,0,0);
		} 
		else
		{
			stCurrTurtle.surface = cairo_pdf_surface_create (stCurrTurtle.filename.c_str() ,width+2*stCurrTurtle.margin, height+2*stCurrTurtle.margin) ;
			stCurrTurtle.cr = cairo_create(stCurrTurtle.surface);
		}
		cairo_set_source_rgb(stCurrTurtle.cr,0,0,0);  
		cairo_select_font_face ( stCurrTurtle.cr, "Adobe Heiti Std" ,
			CAIRO_FONT_SLANT_NORMAL,
			CAIRO_FONT_WEIGHT_NORMAL) ;
		cairo_set_font_size ( stCurrTurtle.cr, 24.0 ) ;
		cairo_set_line_width(stCurrTurtle.cr,1);
		list<hisCmd>::iterator iter;
		cairo_translate(stCurrTurtle.cr,-truex,-truey);
		for (iter=stCurrTurtle.cmds.begin();iter!=stCurrTurtle.cmds.end();iter++)      //����������������ȡ�����ִ��
		{
			if (iter->m_name=="FD")
			{
				FD(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="BK")
			{
				BK(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="RT")
			{
				RT(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="LT")
			{
				LT(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="PU")
			{
				PU(stCurrTurtle);
			}
			if (iter->m_name=="PD")
			{
				PD(stCurrTurtle);
			}
			if (iter->m_name=="CS")
			{
				CS(stCurrTurtle);
			}
			if (iter->m_name=="HOME")
			{
				HOME(stCurrTurtle);
			}
			if (iter->m_name=="SETX")
			{
				SETX(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="SETY")
			{
				SETY(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="SETXY")
			{
				SETXY(stCurrTurtle,iter->params[0],iter->params[1]);
			}
			if (iter->m_name=="SETH")
			{
				SETH(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="print")
			{
				print(stCurrTurtle,iter->txtname);
			}
			if (iter->m_name=="drawcircle")
			{
				drawcircle(stCurrTurtle,iter->params[0]);
			}
			if (iter->m_name=="setcolor")
			{
				setcolor(stCurrTurtle,iter->params[0],iter->params[1],iter->params[2]);
			}
		}
		if (stCurrTurtle.type==PDF)              //����pdf�ļ�
		{
			cairo_show_page(stCurrTurtle.cr);

		}

		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//�ͷ�cr surface�Ȳ���
		remove((stCurrTurtle.initfilename + "1").c_str());  //ɾ���м��ļ�
        return;
	}
}

/********************************************************************************************************************
/*@brief �ڵ�ǰλ�û�һ��Բ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void drawcircle(stTurtle &stCurrTurtle,float radius)
{

	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //�����������      
	{
		hisCmd temp;
		temp.m_name = "drawcircle";
		temp.params.push_back(radius);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //�ƶ���ԭ��
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //�ƶ���ԭ��

	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//�ƶ�����ǰλ��
	if (stCurrTurtle.m_write==true)       //�������ʣ������켣
	{
		if (stCurrTurtle.margin<0)                                        //ҳ�߾�û�У���ѵ�ǰʵ������ת��Ϊ���������
		{
			cairo_new_sub_path(stCurrTurtle.cr);
			cairo_arc(stCurrTurtle.cr,stCurrTurtle.m_currX+499,500-stCurrTurtle.m_currY,radius,0,2*PI);
		} 
		else
		{
			cairo_new_sub_path(stCurrTurtle.cr);
			cairo_arc(stCurrTurtle.cr,stCurrTurtle.m_currX+999,1000-stCurrTurtle.m_currY,radius,0,2*PI);
		}
	}
	else                              //�������ʣ��������켣
	{
		return;
	}	
	if (stCurrTurtle.flag_max_isset==true)               //����ı߼������Ѿ�����
	{

		if (stCurrTurtle.m_currX+radius>stCurrTurtle.m_max_positive_x)          //��ǰx��������������x����
		{
			stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX+radius;
		}
		if (stCurrTurtle.m_currX-radius<stCurrTurtle.m_max_negtive_x)       //��ǰx����С�������x����
		{
			stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX-radius;
		}
		if (stCurrTurtle.m_currY+radius>stCurrTurtle.m_max_positive_y)          //��ǰx��������������x����
		{
			stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY+radius;
		}
		if (stCurrTurtle.m_currY-radius<stCurrTurtle.m_max_negtive_y)       //��ǰx����С�������x����
		{
			stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY-radius;
		}
	}
	else                   //����ı߼����껹û����
	{
		stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX+radius;
		stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX-radius;
		stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY+radius;
		stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY-radius;
		stCurrTurtle.flag_max_isset=true;
	}
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
}

/********************************************************************************************************************
/*@brief ����ǰ��ɫ ����Ϊrgbֵ
/*@author ��Ǳ
/*@param[in]  stTurtle &stCurrTurtle  ����ṹ��
/*@param[out]  stTurtle &stCurrTurtle  ����ṹ��
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void setcolor(stTurtle &stCurrTurtle,float red,float green, float blue)
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //�����������      
	{
		hisCmd temp;
		temp.m_name = "setcolor";
		temp.params.push_back(red);
		temp.params.push_back(green);
		temp.params.push_back(blue);
		stCurrTurtle.cmds.push_back(temp);
	}
	cairo_set_source_rgb(stCurrTurtle.cr , red/255,green/255,blue/255);  
	return;
}

