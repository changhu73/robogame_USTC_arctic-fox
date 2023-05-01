#include"Relay.hpp"
/*
void set_Relay_output_situation(uint16_t relay_num,uint16_t open_or_close)
{
   if(relay_num==0)
   {
      if(open_or_close==0) //要求继电器为断路状态
      HAL_GPIO_WritePin(RELAY_0_Pin, RELAY_0_GPIO_Port, GPIO_PIN_RESET); 
      else if(open_or_close==1)//要求继电器为闭合状态
      HAL_GPIO_WritePin(RELAY_0_Pin, RELAY_0_GPIO_Port, GPIO_PIN_SET); 
   }
   else if(relay_num==1)
   {
      if(open_or_close==0) //要求继电器为断路状态
      HAL_GPIO_WritePin(RELAY_1_Pin, RELAY_1_GPIO_Port, GPIO_PIN_RESET); 
      else if(open_or_close==1)
      HAL_GPIO_WritePin(RELAY_1_Pin, RELAY_1_GPIO_Port, GPIO_PIN_SET); 
   }
}
*/

/**
 * @brief 初始化继电器
 * 
 * @param __Output_GPIO_Pin 继电器引脚号
 * @param __Output_GPIOx 继电器引脚组
 */
void Class_Relay::Init(GPIO_TypeDef *__Output_GPIOx,uint16_t __Output_GPIO_Pin)
{
    
    Output_GPIO_Pin = __Output_GPIO_Pin;
    Output_GPIOx = __Output_GPIOx;

}

/**
 * @brief 设置继电器是闭合还是断路
 * 
 * @param open_or_close 继电器闭合(1)还是断路(0)，闭合推出
 */
 void Class_Relay::set_Relay_output_situation(uint16_t open_or_close)
 {
   if(open_or_close==1)
   {
   HAL_GPIO_WritePin(Output_GPIOx,Output_GPIO_Pin,GPIO_PIN_SET);
  
   }
   else if (open_or_close==0)
   {
   HAL_GPIO_WritePin(Output_GPIOx,Output_GPIO_Pin,GPIO_PIN_RESET);

   }
 }
