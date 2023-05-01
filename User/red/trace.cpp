#include "trace.h"
#include "main.h"
#include "Chassis.hpp"
#include "Motor.hpp"
#include "DR16.hpp"

extern Class_Chassis Chassis;
struct SpeedTypeDef v_front={0, 10000, 0};//��ǰ
struct SpeedTypeDef v_frontlow={0, -4000, 0};//������ǰ
struct SpeedTypeDef v_back={0, -10000, 0};//���
struct SpeedTypeDef v_backlow={0, -4000, 0};//�������
struct SpeedTypeDef v_left={10000, 0 ,0};//����
struct SpeedTypeDef v_leftlow={4000, 0 ,0};//��������
struct SpeedTypeDef v_right={-10000, 0 ,0};//����
struct SpeedTypeDef v_rightlow={-4000, 0 ,0};//��������
struct SpeedTypeDef v_rotate={0, 0, 4000};//��ת
struct SpeedTypeDef v_crotate={0, 0, -4000};//��ת
struct SpeedTypeDef v_leftfront={10000, 10000, 0};//��ǰ
struct SpeedTypeDef v_leftback={10000, -10000, 0};//���	  
struct SpeedTypeDef v_rightfront={-10000, 10000, 0};//��ǰ
struct SpeedTypeDef v_rightback={-10000, -10000, 0};//�Һ�
struct SpeedTypeDef v_stop={0, 0 ,0};//ͣ��
struct SpeedTypeDef v_correct_turnleft={5000,0,0};//trace������õ�΢��ֵ�����Ժ��޸�
struct SpeedTypeDef v_correct_turnright={-5000,0,0};//
struct SpeedTypeDef v_rotatelow={0, 0, 4000};//��ת

int front[5];//5������Ϊ���õ���front[1-4]û��front[0] 
int back[5];
int right[5];
int left[5];
 

int state=0;//state=0ʱ��ʾ��ǰ��Ҳ���Ƿ�����front��state=1��ʾback��state=2��ʾright��state=3��ʾleft


float v=20;//�ο�����������֭������ΪʲôҪ��v��Ҳ��֪��������ת���õ� 

//trace
//ÿ��4��������
//Ĭ��צ������ǰ�� 
//front1-4, back1-4, left1-4, right1-4��ʾǰ������4�����


//�涨��⵽������1��û�м�⵽��0 
void read_redsense(){
	//���ȫ���Ƕ�ȡ���ݣ�����7.31�ŵļ�⣬����������1��ʾ�ڣ�0��ʾ�� 
	//16��ȫ����ȡ 
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


//ֻ��Ҫ�õ��ұ�Ѳ�ߺ����Ѳ��
//�ұ�Ѳ��
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

//���Ѳ��
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

//���հ��ˣ����û������
int trace_check_two(){
	read_redsense();
	while((right[1]+right[2]+right[3]+right[4])>1){
			right_track();
	}
	return 1;
}

//����Ѳ����֮���У׼
double check_line(){
	int check1=1;
	int check2=1;
	//�������ҵ�����
	read_redsense();
	while((back[1]+back[2]+back[3]+back[4])<=1){
		Chassis.Changhu_velocity(v_backlow);
		HAL_Delay(10);
		read_redsense();
	}
	//����һ��ֱ����һ�߽Ӵ���
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
	//�нӴ�֮��Ҫ����һ��
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
	//���������ǲ���
	Chassis.Changhu_velocity(v_stop);
	HAL_Delay(1000);
	
	return 1;
}

//�ӳ����㿪ʼ���У�ֱ���ߵ�ȡ���������ϵ����������
void modified_trace_pre(int time_2)//time_1��ʾ��һ��ʱ�䣬time_2��ʾ��ԽѲ����ʱ�䣬
{
	int i=0;
	
	//��һ��ֱ��+�ڶ�������
	trace_check_two();
	
  Chassis.Changhu_velocity(v_crotate);
	HAL_Delay(650);
	//��������У׼��ֱ��
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(time_2);
	

	//���Ĳ��ͺ��߽ӹ�
	check_line();
	
	Chassis.Changhu_velocity(v_back);
	HAL_Delay(100);
	Chassis.Changhu_velocity(v_stop);
}

//�������ʮ��λ�÷���1��û������0
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
/*	//������ǰ��
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
	{	//����������
		read_redsense();
		left_sum=left[1]+left[2]+left[3]+left[4];
		right_sum=right[1]+right[2]+right[3]+right[4];
		//��ͨ��ת����ֱ��Ȼ����ͨ��ƽ����ȫ��׼
		
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
	//����ǰ����һ����������ٶ�һ�£���������ֻ��Ϊ�������ʡʱ��

void trace_xuanzhuan(){
	read_redsense();
	while((front[1]+front[2]+front[3]+front[4])<=1 && (right[1]+right[2]+right[3]+right[4])<=1){
		Chassis.Changhu_velocity(v_rotate);
		HAL_Delay(10);
		read_redsense();
	}
	Chassis.Changhu_velocity(v_stop);
}




