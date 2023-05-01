#include "PID.h"		//completed
#include "motor_control.h"
#include "move.h"


void stop()
{
	target_motor_speed = 0;
	target_motor_speed_1 = 0;
	target_motor_speed_2 = 0;
	target_motor_speed_3 = 0;
}
void backward(float voltage)
{
	target_motor_speed = -voltage;
	target_motor_speed_1 = voltage;
	target_motor_speed_2 = -voltage;
	target_motor_speed_3 = voltage;	
}
void backward_right(float voltage,float a)
{
	target_motor_speed = -voltage;
	target_motor_speed_1 = voltage;
	target_motor_speed_2 = -a*voltage;
	target_motor_speed_3 = (2-a)*voltage;	
}

void backward_left(float voltage,float a)
{
	target_motor_speed = -voltage;
	target_motor_speed_1 = voltage;
	target_motor_speed_2 = -(2-a)*voltage;
	target_motor_speed_3 = a*voltage;
}

void backward_tr(float voltage,float a)
{
	target_motor_speed = -(2-a)*voltage;
	target_motor_speed_1 = a*voltage;
	target_motor_speed_2 = -a*voltage;
	target_motor_speed_3 = (2-a)*voltage;	
}

void backward_tl(float voltage,float a)
{
	target_motor_speed = -a*voltage;
	target_motor_speed_1 = (2-a)*voltage;
	target_motor_speed_2 = -(2-a)*voltage;
	target_motor_speed_3 = a*voltage;
}

void forward(float voltage)
{
	target_motor_speed = voltage;
	target_motor_speed_1 = -voltage;
	target_motor_speed_2 = voltage;
	target_motor_speed_3 = -voltage;	
}

void forward_right(float voltage,float a)
{
	target_motor_speed = (2-a)*voltage;
	target_motor_speed_1 = -a*voltage;
	target_motor_speed_2 = voltage;
	target_motor_speed_3 = -voltage;	
}

void forward_left(float voltage,float a)
{
	target_motor_speed = a*voltage;
	target_motor_speed_1 = -(2-a)*voltage;
	target_motor_speed_2 = voltage;
	target_motor_speed_3 = -voltage;	
}

void forward_tr(float voltage,float a)
{
	target_motor_speed = (2-a)*voltage;
	target_motor_speed_1 = -a*voltage;
	target_motor_speed_2 = a*voltage;
	target_motor_speed_3 = -(2-a)*voltage;	
}

void forward_tl(float voltage,float a)
{
	target_motor_speed = a*voltage;
	target_motor_speed_1 = -(2-a)*voltage;
	target_motor_speed_2 = (2-a)*voltage;
	target_motor_speed_3 = -a*voltage;	
}

void right(float voltage)
{
	target_motor_speed = voltage;
	target_motor_speed_1 = voltage;
	target_motor_speed_2 = -voltage;
	target_motor_speed_3 = -voltage;	
}

void right_left(float voltage, float a)
{
	target_motor_speed = voltage;
	target_motor_speed_1 = a*voltage;
	target_motor_speed_2 = -voltage;
	target_motor_speed_3 = -(2-a)*voltage;	
}

void right_right(float voltage, float a)
{
	target_motor_speed = voltage;
	target_motor_speed_1 = (2-a)*voltage;
	target_motor_speed_2 = -voltage;
	target_motor_speed_3 = -a*voltage;	
}

void right_tr(float voltage, float a)
{
	target_motor_speed = a*voltage;
	target_motor_speed_1 = (2-a)*voltage;
	target_motor_speed_2 = -(2-a)*voltage;
	target_motor_speed_3 = -a*voltage;	
}
void right_tl(float voltage, float a)
{
	target_motor_speed = (2-a)*voltage;
	target_motor_speed_1 = a*voltage;
	target_motor_speed_2 = -a*voltage;
	target_motor_speed_3 = -(2-a)*voltage;	
}


void left(float voltage)
{
	target_motor_speed = -voltage;
	target_motor_speed_1 = -voltage;
	target_motor_speed_2 = voltage;
	target_motor_speed_3 = voltage;	
}

void left_left(float voltage, float a)
{
	target_motor_speed = -(2-a)*voltage;
	target_motor_speed_1 = -voltage;
	target_motor_speed_2 = a*voltage;
	target_motor_speed_3 = voltage;	
}

void left_right(float voltage, float a)
{
	target_motor_speed = -a*voltage;
	target_motor_speed_1 = -voltage;
	target_motor_speed_2 = (2-a)*voltage;
	target_motor_speed_3 = voltage;	
}

void left_tl(float voltage, float a)
{
	target_motor_speed = -(2-a)*voltage;
	target_motor_speed_1 = -a*voltage;
	target_motor_speed_2 = a*voltage;
	target_motor_speed_3 = (2-a)*voltage;	
}

void left_tr(float voltage, float a)
{
	target_motor_speed = -a*voltage;
	target_motor_speed_1 = -(2-a)*voltage;
	target_motor_speed_2 = (2-a)*voltage;
	target_motor_speed_3 = a*voltage;	
}

void turn_right(float voltage)
{
	target_motor_speed = voltage;
	target_motor_speed_1 = voltage;
	target_motor_speed_2 = voltage;
	target_motor_speed_3 = voltage;	
}

void turn_left(float voltage)
{
	target_motor_speed = -voltage;
	target_motor_speed_1 = -voltage;
	target_motor_speed_2 = -voltage;
	target_motor_speed_3 = -voltage;	
}
