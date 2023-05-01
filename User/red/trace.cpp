#include "trace.h"
#include "main.h"
#include "Chassis.hpp"
#include "Motor.hpp"
#include "DR16.hpp"

extern Class_Chassis Chassis;
struct SpeedTypeDef v_front={0, 10000, 0};//向前
struct SpeedTypeDef v_frontlow={0, -4000, 0};//慢速向前
struct SpeedTypeDef v_back={0, -10000, 0};//向后
struct SpeedTypeDef v_backlow={0, -4000, 0};//慢速向后
struct SpeedTypeDef v_left={10000, 0 ,0};//向左
struct SpeedTypeDef v_leftlow={4000, 0 ,0};//慢速向左
struct SpeedTypeDef v_right={-10000, 0 ,0};//向右
struct SpeedTypeDef v_rightlow={-4000, 0 ,0};//慢速向右
struct SpeedTypeDef v_rotate={0, 0, 4000};//正转
struct SpeedTypeDef v_crotate={0, 0, -4000};//逆转
struct SpeedTypeDef v_leftfront={10000, 10000, 0};//左前
struct SpeedTypeDef v_leftback={10000, -10000, 0};//左后	  
struct SpeedTypeDef v_rightfront={-10000, 10000, 0};//右前
struct SpeedTypeDef v_rightback={-10000, -10000, 0};//右后
struct SpeedTypeDef v_stop={0, 0 ,0};//停下
struct SpeedTypeDef v_correct_turnleft={5000,0,0};//trace里面调用的微调值，测试后修改
struct SpeedTypeDef v_correct_turnright={-5000,0,0};//
struct SpeedTypeDef v_rotatelow={0, 0, 4000};//正转

int front[5];//5个是因为我用的是front[1-4]没用front[0] 
int back[5];
int right[5];
int left[5];
 

int state=0;//state=0时表示向前走也就是方向是front，state=1表示back，state=2表示right，state=3表示left


float v=20;//参考季军代码蜜汁变量，为什么要是v我也不知道，设置转速用的 

//trace
//每边4个传感器
//默认爪子在正前方 
//front1-4, back1-4, left1-4, right1-4表示前后左右4个电机


//规定检测到黑线是1，没有检测到是0 
void read_redsense(){
	//这边全部是读取数据，按照7.31号的检测，传感器传输1表示黑，0表示白 
	//16行全部读取 
	front[2]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);
	front[1]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
	front[3]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
	front[4]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
	back[2]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);	
	back[1]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
	back[3]=1-HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);	
	back[4]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0);	
	right[2]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1);
	right[1]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2);		
	right[3]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3);	
	right[4]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_4);	
	left[2]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_5);		
	left[1]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6);
	left[3]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7);	
	left[4]=1-HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8);					
}


//只需要用到右边巡线和左边巡线
//右边巡线
void right_track(){
	read_redsense();
	if(right[1]==1 && right[4]==1){
		Chassis.Changhu_velocity(v_right);
		HAL_Delay(10);
	}
	else if(right[1]==0 && right[4]==0){
		Chassis.Changhu_velocity(v_right);
		HAL_Delay(10);
	}
	else if(right[1]==1 && right[4]==0){
		Chassis.Changhu_velocity(v_rightfront);	
		HAL_Delay(10);
	}
	else if(right[1]==0 && right[4]==1){
		Chassis.Changhu_velocity(v_rightback);
		HAL_Delay(10);
	}	
}

//左边巡线
void left_track(){
	read_redsense();
	if(left[1]==1 && left[4]==1){
		Chassis.Changhu_velocity(v_left);
		HAL_Delay(10);
	} 
	else if(left[1]==0 && left[4]==0){
		Chassis.Changhu_velocity(v_left);
		HAL_Delay(10);
	}
	else if(left[1]==1 && left[4]==0){
		Chassis.Changhu_velocity(v_leftback);	
		HAL_Delay(10);
	}
	else if(left[1]==0 && left[4]==1){
		Chassis.Changhu_velocity(v_leftfront);
		HAL_Delay(10);
	}	
}

//最终版了，这个没有问题
int trace_check_two(){
	read_redsense();
	while((right[1]+right[2]+right[3]+right[4])>1){
			right_track();
	}
	return 1;
}

//穿过巡线区之后的校准
double check_line(){
	int check1=1;
	int check2=1;
	//后面先找到黑线
	read_redsense();
	while((back[1]+back[2]+back[3]+back[4])<=1){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(10);
		read_redsense();
	}
	//再走一会直到有一边接触了
	while(check1 || check2){
		read_redsense();
		if((right[1]+right[2]+right[3]+right[4])>2){
			check1=0;
			break;
		}
		else if((left[1]+left[2]+left[3]+left[4])>2){
			check2=0;
			break;
		}
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(10);
	}
	//有接触之后要调整一下
	if(check1==0){
		while((left[1]+left[2]+left[3]+left[4])<=1){	
			Chassis.Changhu_velocity(v_crotate);
//		Chassis.Changhu_velocity(v_rotateright);
			HAL_Delay(20);
			read_redsense();
		}
	}
	if(check2==0){
		while((right[1]+right[2]+right[3]+right[4])<=1){
			Chassis.Changhu_velocity(v_rotate);
//		Chassis.Changhu_velocity(v_rotateleft);
			HAL_Delay(20);
			read_redsense();
		}
	}
	//下面两行是测试
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(1000);
	
	return 1;
}

//从出发点开始运行，直到走到取壶区黑线上调整机身完毕
void modified_trace_pre(int time_2)//time_1表示第一步时间，time_2表示跨越巡线区时间，
{
	int i=0;
	
	//第一步直行+第二步拐弯
	trace_check_two();
	
  Chassis.Changhu_velocity(v_crotate);
	HAL_Delay(650);
	//第三步：校准后直走
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(time_2);
	

	//第四步和黑线接轨
	check_line();
	
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(100);
	Chassis.Changhu_velocity(v_stop);
}

//如果到了十字位置返回1，没到返回0
	void trace_check_crossroad()
{	
	int check=1;
	read_redsense();
	while(check==1){
		Chassis.Changhu_velocity(v_rotatelow);
		HAL_Delay(20);
		if(left[1]==0 && left[4]==0 && left[2]==1 && left[3]==1){
			check=0;
		}
		read_redsense();
	}
	Chassis.Changhu_velocity(v_stop);
}
	/*int check_1=1,check_2=1;
	int left_sum;
	int right_sum;
	while(check_1 || check_2){
		read_redsense();
		if(back[1]==1 && back[4]==1){
			check_1=0;
		}
		else if(back[1]==0 && back[4]==0){
			if(back[2]==1 && back[3]==0){
				Chassis.Changhu_velocity(v_rightlow);
			}
			else if(back[2]==0 && back[3]==1){
				Chassis.Changhu_velocity(v_leftlow);
			}
			else {
				check_1=0;	
			}
		}
		else if(back[1]==1 && back[4]==0){
			Chassis.Changhu_velocity(v_rightlow);
			HAL_Delay(10);
			check_1=1;
		}
		else if(back[1]==0 && back[4]==1){
			Chassis.Changhu_velocity(v_leftlow);
			HAL_Delay(10);
			check_1=1;
		}
		
		read_redsense();
		if(right[1]==1 && right[4]==1){
			check_2=0;
		}
		else if(right[1]==0 && right[4]==0){
			if(right[2]==1 && right[3]==0){
				Chassis.Changhu_velocity(v_crotate);
			}
			else if(right[2]==0 && right[3]==1){
				Chassis.Changhu_velocity(v_rotate);
			}
			else {
				check_2=0;	
			}
		}
		else if(right[1]==1 && right[4]==0){
//			Chassis.Changhu_velocity(v_rotateright);
			Chassis.Changhu_velocity(v_crotate);
			HAL_Delay(10);
			check_2=1;
		}
		else if(right[1]==0 && right[4]==1){
//			Chassis.Changhu_velocity(v_rotateleft);
			Chassis.Changhu_velocity(v_rotate);
			HAL_Delay(10);
			check_2=1;
		}	
		
	}
	

	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(2000);
	*/
/*	//先锁死前面
	while(check_1){
		read_redsense();
		if(front[1]==1
			&& front[4]==1){
			check_1=0;
		}
		else if(front[1]==0 && front[4]==0){
			check_1=0;
		}
		else if(front[1]==1 && front[4]==0){
			Chassis.Changhu_velocity(v_leftlow);
		}
		else if(front[1]==0 && front[4]==1){
			Chassis.Changhu_velocity(v_rightlow);
		}
		HAL_Delay(10);						
	}*/
/*	while(check_2)
	{	//再锁死两边
		read_redsense();
		left_sum=left[1]+left[2]+left[3]+left[4];
		right_sum=right[1]+right[2]+right[3]+right[4];
		//先通过转动对直，然后再通过平移完全对准
		
		if(left_sum==2 || left_sum==3){
			if(right_sum!=1 || right_sum!=0){
				check_2=0;
			}
			else if(right[1]==1){
				Chassis.Changhu_velocity(v_rotateright);
			}
			else if(right[4]==1){
				Chassis.Changhu_velocity(v_rotateleft);
			}
		}
		if(right_sum==2 || right_sum==3){
			if(left_sum!=1 || left_sum!=0){
				check_2=0;
			}
			else if(left[1]==1){
				Chassis.Changhu_velocity(v_rotateleft);
			}
			else if(left[4]==1){
				Chassis.Changhu_velocity(v_rotateright);
			}
		}
		else {
			Chassis.Changhu_velocity(v_rotateright);
		}
		HAL_Delay(10);	
	}*/
	//可能前后有一点区别可以再动一下，这里加这个只是为了明天节省时间

void trace_xuanzhuan(){
	read_redsense();
	while((front[1]+front[2]+front[3]+front[4])<=1 && (right[1]+right[2]+right[3]+right[4])<=1){
		Chassis.Changhu_velocity(v_rotate);
		HAL_Delay(10);
		read_redsense();
	}
	Chassis.Changhu_velocity(v_stop);
}




