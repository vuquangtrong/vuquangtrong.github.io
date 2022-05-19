g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  
  /* External Interrupts */
  .word  WWDG_IRQHandler                /* Window WatchDog              */
  ...
  .word  TIM1_UP_TIM10_IRQHandler       /* TIM1 Update and TIM10        */
  ...
  .word  USART2_IRQHandler              /* USART2                       */
  .word  0               			    /* Reserved                     */
  .word  EXTI15_10_IRQHandler           /* External Line[15:10]         */
