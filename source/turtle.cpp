/*********************************************************************************************************************
/*Copyright  芝麻球小队 All right reserved @2011 
/*@file turtle.cpp
/*@author  戴潜
/*@date    2011.11.11
/*@brief   绘图命令执行模块
/*
/*********************************************************************************************************************/
#include "turtle.h"

/********************************************************************************************************************
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void initpaint(stTurtle &stCurrTurtle)
{
	if (stCurrTurtle.margin >=0)
	{
		stCurrTurtle.record = true; //如果有-m 参数 则记录当前命令序列
	}
	else
	{
		stCurrTurtle.record = false; 
	}
	//初始化海龟结构体变量
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
		stCurrTurtle.filename = "~temp~~.png";//中间文件名
	}
	else
	{
        stCurrTurtle.filename = "~temp~~.pdf";//中间文件名
	}
	
	stCurrTurtle.initfilename=stCurrTurtle.filename;
	stCurrTurtle.flag_max_isset=false;
	string gg=stCurrTurtle.filename;
	int mm=stCurrTurtle.filename.length();
	if (stCurrTurtle.type==PNG)           //如果要生成png
	{		
		if (stCurrTurtle.filename.length()==0)
		{
			stCurrTurtle.filename="slogo.png";
	    }
		stCurrTurtle.initfilename = stCurrTurtle.filename;
	     
		if (stCurrTurtle.margin<0)                        //有边距的情况
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
		else                                  //没有边距的情况
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
	else                  //如果要生成pdf
	{
		if (stCurrTurtle.filename.length()==0)
		{
			stCurrTurtle.filename="slogo.pdf";
	    }
		  stCurrTurtle.initfilename = stCurrTurtle.filename;

		if (stCurrTurtle.margin<0)               //没有边距的情况
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
		else                   //有边距的情况
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
/*@brief 寻找最大边界
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void findmax(stTurtle &stCurrTurtle)                 // 获得海龟的边际坐标
{

	if (stCurrTurtle.m_write==true)
	{

		if (stCurrTurtle.flag_max_isset==true)               //海龟的边际坐标已经设置
		{

			if (stCurrTurtle.m_currX>stCurrTurtle.m_max_positive_x)          //当前x坐标大于最大正向x坐标
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currX<stCurrTurtle.m_max_negtive_x)       //当前x坐标小于最大负向x坐标
			{
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currY>stCurrTurtle.m_max_positive_y)     //当前y坐标大于最大正向y坐标
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY;
			}
			if (stCurrTurtle.m_currY<stCurrTurtle.m_max_negtive_y)        //当前y坐标小于最大正向y坐标
			{
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY;
			}

			if (stCurrTurtle.m_last_currX>stCurrTurtle.m_max_positive_x)          //当前x坐标大于最大正向x坐标
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_last_currX;
			}
			if (stCurrTurtle.m_last_currX<stCurrTurtle.m_max_negtive_x)       //当前x坐标小于最大负向x坐标
			{
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_last_currX;
			}
			if (stCurrTurtle.m_last_currY>stCurrTurtle.m_max_positive_y)     //当前y坐标大于最大正向y坐标
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_last_currY;
			}
			if (stCurrTurtle.m_last_currY<stCurrTurtle.m_max_negtive_y)        //当前y坐标小于最大正向y坐标
			{
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_last_currY;
			}
		}
		else                   //海龟的边际坐标还没设置
		{
			if (stCurrTurtle.m_currX>stCurrTurtle.m_last_currX)                //当前x坐标大于上一次x坐标
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX;
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_last_currX;
			} 
			else
			{
				stCurrTurtle.m_max_positive_x=stCurrTurtle.m_last_currX;
				stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX;
			}
			if (stCurrTurtle.m_currY>stCurrTurtle.m_last_currY)                //当前y坐标大于上一次y坐标
			{
				stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY;
				stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_last_currY;
			} 
			 //当前y坐标小于最大正向y坐标
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
/*@brief FD命令
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体 float length
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void FD(stTurtle &stCurrTurtle,float length)
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //加入命令队列      
	{
		hisCmd temp;
		temp.m_name = "FD";
		temp.params.push_back(length);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点

	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		cairo_rel_line_to(stCurrTurtle.cr,length*sin(stCurrTurtle.m_currAngle*PI/180),-length*cos(stCurrTurtle.m_currAngle*PI/180));
	}
	else                              //如果是提笔，不产生轨迹
	{
		cairo_rel_move_to(stCurrTurtle.cr,length*sin
			(stCurrTurtle.m_currAngle*PI/180),-length*cos(stCurrTurtle.m_currAngle*PI/180));
	}

	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);             //得到当前海龟的实际坐标
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)                                        //页边距没有，则把当前实际坐标转化为海龟的坐标
	{
		stCurrTurtle.m_currX=float(thenewx)-499;
		stCurrTurtle.m_currY=500-float(thenewy);
	} 
	else
	{
		stCurrTurtle.m_currX=float(thenewx)-999;
		stCurrTurtle.m_currY=1000-float(thenewy);
	}
	findmax(stCurrTurtle);                            //获得海龟的四个边际坐标
	cairo_stroke(stCurrTurtle.cr);  
	if (stCurrTurtle.type == PNG)
	{
		cairo_surface_write_to_png(stCurrTurtle.surface, stCurrTurtle.filename.c_str());
	} 
	//cairo_destroy(cr);
}

/********************************************************************************************************************
/*@brief BK 命令
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体  float length
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void BK(stTurtle &stCurrTurtle,float length)          
{
	FD(stCurrTurtle,-length);
}

/********************************************************************************************************************
/*@brief RT命令
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle,float angle
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void RT(stTurtle &stCurrTurtle,float angle)         //海龟右转
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)        //加入命令队列      
	{
		hisCmd temp;
		temp.m_name = "RT";
		temp.params.push_back(angle);
		stCurrTurtle.cmds.push_back(temp);
	}

	stCurrTurtle.m_currAngle+=angle;
}

/********************************************************************************************************************
/*@brief    //海龟左转
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle,float angle
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void LT(stTurtle &stCurrTurtle,float angle)       //海龟左转
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)    //加入命令队列      
	{
		hisCmd temp;
		temp.m_name = "LT";
		temp.params.push_back(angle);
		stCurrTurtle.cmds.push_back(temp);
	}

	stCurrTurtle.m_currAngle-=angle;
}

/********************************************************************************************************************
/*@brief //抬笔
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void PU(stTurtle &stCurrTurtle)  //抬笔
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)     //加入命令队列     
	{
		hisCmd temp;
		temp.m_name = "PU";
		stCurrTurtle.cmds.push_back(temp);
	}
	stCurrTurtle.m_write=false;
}

/********************************************************************************************************************
/*@brief //落笔
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void PD(stTurtle &stCurrTurtle)  //落笔
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)     //加入命令队列     
	{
		hisCmd temp;
		temp.m_name = "PD";
		stCurrTurtle.cmds.push_back(temp);
	}
	stCurrTurtle.m_write=true;
}

/********************************************************************************************************************
/*@brief   //清除所有图形，海归回到原点，朝向0度
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void CS(stTurtle &stCurrTurtle)                //清除所有图形，海归回到原点，朝向0度
{

	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)      //加入命令队列     
	{
		hisCmd temp;
		temp.m_name = "CS";
		stCurrTurtle.cmds.push_back(temp);
	}
	    //清除所有图形
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
/*@brief  //海归回到原点，朝向0度
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void HOME(stTurtle &stCurrTurtle)           //海归回到原点，朝向0度
{
	double thenewx,thenewy;
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)         //加入命令队列     
	{
		hisCmd temp;
		temp.m_name = "HOME";
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		cairo_rel_line_to(stCurrTurtle.cr,-stCurrTurtle.m_currX,stCurrTurtle.m_currY);
	}
	else                              //如果是提笔，不产生轨迹
	{
		cairo_rel_move_to(stCurrTurtle.cr,-stCurrTurtle.m_currX,stCurrTurtle.m_currY);
	}
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);          //得到当前海龟的实际坐标
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
/*@brief SETX命令
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle,float fx_axis
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
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
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	float true_x=fx_axis-stCurrTurtle.m_currX;    //转化为相对现在点的坐标差

	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		cairo_rel_line_to(stCurrTurtle.cr,true_x,0);
	}
	else                              //如果是提笔，不产生轨迹
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
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
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
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	float true_y=fy_axis-stCurrTurtle.m_currY;    //转化为相对现在点的坐标差

	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		cairo_rel_line_to(stCurrTurtle.cr,0,-true_y);
	}
	else                              //如果是提笔，不产生轨迹
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
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
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
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	float true_x=fx_axis-stCurrTurtle.m_currX;    //转化为相对现在点的坐标差
	float true_y=fy_axis-stCurrTurtle.m_currY;    //转化为相对现在点的坐标差

	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		cairo_rel_line_to(stCurrTurtle.cr,true_x,-true_y);
	}
	else                              //如果是提笔，不产生轨迹
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
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
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
	cairo_move_to(stCurrTurtle.cr,499,500);       //移动到原点
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点
	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	cairo_save(stCurrTurtle.cr);
	cairo_rotate(stCurrTurtle.cr,stCurrTurtle.m_currAngle*PI/180);
	cairo_text_path(stCurrTurtle.cr,txt.c_str());
	cairo_rotate(stCurrTurtle.cr,-stCurrTurtle.m_currAngle*PI/180);
	cairo_restore(stCurrTurtle.cr);
	cairo_get_current_point(stCurrTurtle.cr,&thenewx,&thenewy);
	stCurrTurtle.m_last_currX=stCurrTurtle.m_currX;
	stCurrTurtle.m_last_currY=stCurrTurtle.m_currY;
	if (stCurrTurtle.margin<0)                //页边距没有，则把当前实际坐标转化为海龟的坐标
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
	if (cos(stCurrTurtle.m_currAngle)>0)         //修正由于字体带来的y偏差
	{
		stCurrTurtle.m_max_positive_y+=1;
	} 
	else
	{
		stCurrTurtle.m_max_negtive_y-=1;
	}
	if (sin(stCurrTurtle.m_currAngle)>0)         //修正由于字体带来的x偏差
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
/*@brief 初始化系统信息
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void  destroy_turtle(stTurtle &stCurrTurtle)       //第二遍运行命令，并初始化海龟结构体
{
	float  width,height;                            

	width=stCurrTurtle.m_max_positive_x-stCurrTurtle.m_max_negtive_x+2;               //获得当前图画的实际宽度
	height=stCurrTurtle.m_max_positive_y-stCurrTurtle.m_max_negtive_y+2;               //获得当前图画的实际高度

	float truex=999+stCurrTurtle.m_max_negtive_x-stCurrTurtle.margin-1;                  //获得当前图画的实际左上顶点的x坐标
	float truey=1000-stCurrTurtle.m_max_positive_y-stCurrTurtle.margin-1;              //获得当前图画的实际左上顶点的y坐标
	if (stCurrTurtle.margin < 0)//如果没有-m参数 直接销毁返回
	{
		if (stCurrTurtle.type == PDF)
		{
			cairo_show_page(stCurrTurtle.cr);
		}
		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//释放cr surface等操作
		return;
	}
	if (stCurrTurtle.record == true)
	{  
		if (stCurrTurtle.type == PDF)
		{
			cairo_show_page(stCurrTurtle.cr);
		}
		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//释放cr surface等操作
	}


	if (stCurrTurtle.record==true)                   //若果当前是第一遍执行命令
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
		stCurrTurtle.record=false;	//初始化海龟  且record =false
		stCurrTurtle.filename=stCurrTurtle.initfilename;
		if (stCurrTurtle.type==PNG)   //如果 margin>=0；则生成新的大小surface  
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
		for (iter=stCurrTurtle.cmds.begin();iter!=stCurrTurtle.cmds.end();iter++)      //从命令队列中逐个提取命令，并执行
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
		if (stCurrTurtle.type==PDF)              //生成pdf文件
		{
			cairo_show_page(stCurrTurtle.cr);

		}

		cairo_destroy (stCurrTurtle.cr);
		cairo_surface_destroy ( stCurrTurtle.surface) ;//释放cr surface等操作
		remove((stCurrTurtle.initfilename + "1").c_str());  //删除中间文件
        return;
	}
}

/********************************************************************************************************************
/*@brief 在当前位置画一个圆
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void drawcircle(stTurtle &stCurrTurtle,float radius)
{

	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //加入命令队列      
	{
		hisCmd temp;
		temp.m_name = "drawcircle";
		temp.params.push_back(radius);
		stCurrTurtle.cmds.push_back(temp);
	}
	if (stCurrTurtle.margin<0)
	{
		cairo_move_to(stCurrTurtle.cr,499,500); //移动到原点
	} 
	else
	{
		cairo_move_to(stCurrTurtle.cr,999,1000); //移动到原点

	}
	cairo_rel_move_to(stCurrTurtle.cr, stCurrTurtle.m_currX, -stCurrTurtle.m_currY);//移动到当前位置
	if (stCurrTurtle.m_write==true)       //如果是落笔，产生轨迹
	{
		if (stCurrTurtle.margin<0)                                        //页边距没有，则把当前实际坐标转化为海龟的坐标
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
	else                              //如果是提笔，不产生轨迹
	{
		return;
	}	
	if (stCurrTurtle.flag_max_isset==true)               //海龟的边际坐标已经设置
	{

		if (stCurrTurtle.m_currX+radius>stCurrTurtle.m_max_positive_x)          //当前x坐标大于最大正向x坐标
		{
			stCurrTurtle.m_max_positive_x=stCurrTurtle.m_currX+radius;
		}
		if (stCurrTurtle.m_currX-radius<stCurrTurtle.m_max_negtive_x)       //当前x坐标小于最大负向x坐标
		{
			stCurrTurtle.m_max_negtive_x=stCurrTurtle.m_currX-radius;
		}
		if (stCurrTurtle.m_currY+radius>stCurrTurtle.m_max_positive_y)          //当前x坐标大于最大正向x坐标
		{
			stCurrTurtle.m_max_positive_y=stCurrTurtle.m_currY+radius;
		}
		if (stCurrTurtle.m_currY-radius<stCurrTurtle.m_max_negtive_y)       //当前x坐标小于最大负向x坐标
		{
			stCurrTurtle.m_max_negtive_y=stCurrTurtle.m_currY-radius;
		}
	}
	else                   //海龟的边际坐标还没设置
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
/*@brief 设置前景色 参数为rgb值
/*@author 戴潜
/*@param[in]  stTurtle &stCurrTurtle  海龟结构体
/*@param[out]  stTurtle &stCurrTurtle  海龟结构体
/*@return  void
/*@pre
/*@exception
/********************************************************************************************************************/
void setcolor(stTurtle &stCurrTurtle,float red,float green, float blue)
{
	if ( stCurrTurtle.margin >=0 && stCurrTurtle.record == true)            //加入命令队列      
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

