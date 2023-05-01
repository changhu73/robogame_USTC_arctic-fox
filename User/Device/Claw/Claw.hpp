#ifndef CLAW_HPP
#define CLAW_HPP

#include "Motor.hpp"
#include "DR16.hpp"
class Class_Claw
{
    public:
	  Class_Motor Motor[2];
	  void Init();
	  void Changhu_velocity(SpeedTypeDef velo);
      void Set_Velocity(SpeedTypeDef __Velocity);
	  SpeedTypeDef Get_Velocity();
	protected:
        TIM_HandleTypeDef Driver_PWM_TIM; 	//PWM?????
		SpeedTypeDef Velocity = 
        {
            1,
            0,
            0
        };
		  
};
#endif
