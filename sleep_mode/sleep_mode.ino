  #define Button PB_6
 static uint8_t state=0;/* 进入待机模式的标志 */
void onChange() {
 
    if (digitalRead(Button) == LOW)
    {
 // printf("SLEEP MODE!\n\n");

  /* systick中断关闭，防止systick中断唤醒 */
  HAL_SuspendTick();       

  state=!state;

  /* systick中断开启 */
  HAL_ResumeTick();    

  //printf("WAKEUP OK!\n\n");

    }
}

WEAK void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;

    /* 振荡器配置 */
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* 开启HSI */
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1分频 */
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz; /* 配置HSI时钟24MHz */
    RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* 关闭HSE */
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                      /* 开启PLL */
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;              /*选择时钟源HSI*/
    /* 配置振荡器 */
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* 时钟源配置 */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* 选择配置时钟 HCLK,SYSCLK,PCLK1 */
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;                                      /* 选择PLL作为系统时钟 */
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* AHB时钟 1分频 */
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                              /* APB时钟 2分频 */
    /* 配置时钟源 */
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
}


void setup() {
  //Serial.begin(9600);      //打开串口
  pinMode(Button, INPUT_PULLDOWN);  //设置管脚为输入
  attachInterrupt(digitalPinToInterrupt(Button), onChange, CHANGE);
  /*
   LOW 当引脚为低电平时，触发中断
   CHANGE 当引脚电平发生改变时，触发中断
   RISING 当引脚由低电平变为高电平时，触发中断
   FALLING 当引脚由高电平变为低电平时，触发中断
   */
  pinMode(PB_0, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  HAL_Init;
  digitalWrite(PB_0, HIGH);
  delay(500);
  Serial.println("run OK!\n\n");
  digitalWrite(PB_0, LOW);
  delay(500);
  if(state==1) {
    HAL_SuspendTick();   /* systick中断关闭，防止systick中断唤醒 */
    //HAL_Init;  
     /* 进入SLEEP模式 */
  HAL_PWR_EnterSLEEPMode(PWR_SLEEPENTRY_WFE);  
  //HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE);  /* 停止模式，目前无法唤醒，需要断电才能恢复 */
    }
}

