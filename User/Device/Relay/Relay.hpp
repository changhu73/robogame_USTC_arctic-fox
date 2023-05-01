#ifndef RELAY_HPP
#define RELAY_HPP
#include"main.h"
//void set_r=Relay_output_situation(int relay_num,int open_or_close);
class Class_Relay
{
    public:
    void Init(GPIO_TypeDef *__Output_GPIOx,uint16_t __Output_GPIO_Pin);
    void set_Relay_output_situation(uint16_t open_or_close);
    protected:
        //继电器
        uint16_t Output_GPIO_Pin;
        GPIO_TypeDef *Output_GPIOx;
};
#endif
