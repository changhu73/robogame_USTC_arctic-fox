#ifndef __MOVE_H		//completed
#define __MOVE_H

#include "PID.h"
#include "motor_control.h"

void stop(void);
void forward(float voltage);
void backward(float voltage);
void left(float voltage);
void right(float voltage);
void forward_right(float voltage,float a);
void forward_left(float voltage,float a);
void backward_right(float voltage,float a);
void backward_left(float voltage,float a);
void left_left(float voltage, float a);
void left_right(float voltage, float a);
void right_left(float voltage, float a);
void right_right(float voltage, float a);
void turn_right(float voltage);
void turn_left(float voltage);
void right_tl(float voltage, float a);
void right_tr(float voltage, float a);
void left_tr(float voltage, float a);
void left_tl(float voltage, float a);
void backward_tl(float voltage,float a);
void backward_tr(float voltage,float a);
void forward_tl(float voltage,float a);
void forward_tr(float voltage,float a);


#endif
