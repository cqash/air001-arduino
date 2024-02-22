  #define Button PB_6
 static uint8_t state=0;/* 进入待机模式的标志 */
void onChange() {
 
    if (digitalRead(Button) == LOW)
    {
  printf("SLEEP MODE!\n\n");

  /* systick中断关闭，防止systick中断唤醒 */
  HAL_SuspendTick();       

  state=!state;

  /* systick中断开启 */
  HAL_ResumeTick();    

  printf("WAKEUP OK!\n\n");

    }
}

void setup() {
  
  Serial.begin(115200);      //打开串口
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
  //HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE);
    }
}

