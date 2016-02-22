/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
uint32_t EXTI_Line;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


int main(void)
{  
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
  
  /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC *************************************************/

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, ENABLE);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOG, &GPIO_InitStructure);  

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | 
                         RCC_APB2Periph_GPIOG, DISABLE);  
  
  /* Global initialization ends above.*/
  /* -------------------------------------------------------------------------- */

  /* Task 1: Configure your output LED on Port F */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);




  
  /* Task 2: Configure PA.0 and PB.11 as input 
     Please note the Mode referring to the connection */

  


  /* Task 2a: Configure Button pin as input PA.0 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /* Task 2b: Configure Button pin as input PB.11 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
  /* Task 3:  Configure EXTI Line to Button GPIO Pin */


  /* Task 3a: Configure Button EXTI Line 0 to PA.0 */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  

  /* Task 3b: Enable EXTI Interrupt  */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Clear all the LEDs */
  GPIOF->ODR = 0;

  while (1)
  {

  /* Task 4: Generate a fastest square wave on LED4, i.e. PF.9 */
  /*         Notice the difference of Square Wave for Different Optimizations */
  /* Remember to comment Task 6 when doing Task 4 */
    /*GPIOF->BSRR = GPIO_Pin_9;
    GPIOF->BRR = GPIO_Pin_9;*/
    
    GPIOF->ODR ^= 1 << 9;

  /* Task 5: Modify the file stm32f10x_it.c to toggle LED5 (i.e. PF.8) when */
  /*          KEY1 (i.e. PA.0) is pressed.                                   */          

  

  /* Task 6: Check if there is key press on Joystick select input (i.e. PB.11) */
  /*         If the key is pressed,                                            */
  /*           light up LED7 (i.e. PF.6) 	  		               */
  /*            else                                                           */
  /*           turn off LED7 (i.e. PF.6)                                       */

  /*  uint8_t key = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    if (key == 0){
      GPIOF->BSRR = GPIO_Pin_6;
    }
    else{
      GPIOF->BRR = GPIO_Pin_6;
    }*/
  }
}


