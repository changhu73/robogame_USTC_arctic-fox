#ifndef __CHASIS_H
#define __CHASIS_H
#include "chasis.h"
#include "trace.h"
//6个动作 
void move_front(float a,float b);
void move_left(float a,float b);
void move_right(float a,float b);
void move_back(float a,float b);
void rotation_clockwise(float a, float b);//顺时针转动
void rotation_anticlockwise(float a,float b);//逆时针转动

#endif
