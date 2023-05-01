#ifndef MOTOR_CONTROL_H		//completed
#define MOTOR_CONTROL_H

#include "PID.h"

#define VOLTAGE_MAXIMUM 1000

extern int encoder_num;
extern int encoder_num_1;
extern int encoder_num_2;
extern int encoder_num_3;
extern float measured_motor_speed;
extern float measured_motor_speed_1;
extern float measured_motor_speed_2;
extern float measured_motor_speed_3;
extern float target_motor_speed;
extern float target_motor_speed_1;
extern float target_motor_speed_2;
extern float target_motor_speed_3;
extern float target_motor_speed_4;
extern pid_t pid_motor_speed;
extern pid_t pid_motor_speed_1;
extern pid_t pid_motor_speed_2;
extern pid_t pid_motor_speed_3;

void set_motor_voltage(float voltage);
void set_motor_voltage_1(float voltage);
void set_motor_voltage_2(float voltage);
void set_motor_voltage_3(float voltage);
void set_motor_voltage_4(float voltage);
void motor_control(void);
void motor_control_1(void);
void motor_control_2(void);
void motor_control_3(void);
void motor_control_4(void);

#endif
