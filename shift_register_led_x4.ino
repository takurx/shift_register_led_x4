int latchPin_100ms = 3;  // 74HC595_100msのST_CPへ
int clockPin_100ms = 4;  // 74HC595_100msのSH_CPへ
int dataPin_100ms = 2;   // 74HC595_100msのDSへ

int latchPin_1ms = 6;  // 74HC595_1msのST_CPへ
int clockPin_1ms = 7;  // 74HC595_1msのSH_CPへ
int dataPin_1ms = 5;   // 74HC595_1msのDSへ

int latchPin_10ms = 9;  // 74HC595_10msのST_CPへ
int clockPin_10ms = 10; // 74HC595_10msのSH_CPへ
int dataPin_10ms = 8;   // 74HC595_10msのDSへ

int latchPin_1000ms = 12;  // 74HC595_1000msのST_CPへ
int clockPin_1000ms = 13;  // 74HC595_1000msのSH_CPへ
int dataPin_1000ms = 11;   // 74HC595_1000msのDSへ

unsigned int val;
unsigned int j;
unsigned int k;

unsigned int c_100ms;
unsigned int c_1ms;
unsigned int c_10ms;
unsigned int c_1000ms;

void setup() 
{
  pinMode(latchPin_100ms, OUTPUT);
  pinMode(clockPin_100ms, OUTPUT);
  pinMode(dataPin_100ms, OUTPUT);

  pinMode(latchPin_1ms, OUTPUT);
  pinMode(clockPin_1ms, OUTPUT);
  pinMode(dataPin_1ms, OUTPUT);

  pinMode(latchPin_10ms, OUTPUT);
  pinMode(clockPin_10ms, OUTPUT);
  pinMode(dataPin_10ms, OUTPUT);

  pinMode(latchPin_1000ms, OUTPUT);
  pinMode(clockPin_1000ms, OUTPUT);
  pinMode(dataPin_1000ms, OUTPUT);

  c_100ms = 0;
  c_1ms = 0;
  c_10ms = 0;
  c_1000ms = 0;
}

void loop() {
  // LED1からLED10までを順に光らせます
  for (int i = 0; i < 10000; i++) 
  {
    // 送信中のlatchPinはグランド(LOW)レベル
    digitalWrite(latchPin_1ms, LOW);
    // シフト演算を使って点灯するLEDを選択しています
    val = 1 << c_1ms;
  
    //MSBFIRST, 74HC595_0_QA-QH->74HC595_1_QA-QB
    j = val;
    k = val>>8;
    shiftOut(dataPin_1ms, clockPin_1ms, MSBFIRST, k);//上位バイトを送信
    shiftOut(dataPin_1ms, clockPin_1ms, MSBFIRST, j);//2バイトの下位を送信
    
    //LSBFIRST, 74HC595_1_QB-QA->74HC595_0_QH-QA
    /*
    j = val<<6;
    k = val<<6>>8;
    shiftOut(dataPin_1ms, clockPin_1ms, LSBFIRST, j);//2バイトの下位を送信
    shiftOut(dataPin_1ms, clockPin_1ms, LSBFIRST, k);//上位バイトを送信
    */
    
    // 送信終了後latchPinをHIGHにする
    digitalWrite(latchPin_1ms, HIGH);

    c_1ms = c_1ms + 1;
    
    if(c_1ms > 10)    //10ms経過
    {
      // 送信中のlatchPinはグランド(LOW)レベル
      digitalWrite(latchPin_10ms, LOW);
      // シフト演算を使って点灯するLEDを選択しています
      val = 1 << c_10ms;
    
      //MSBFIRST, 74HC595_0_QA-QH->74HC595_1_QA-QB
      j = val;
      k = val>>8;
      shiftOut(dataPin_10ms, clockPin_10ms, MSBFIRST, k);//上位バイトを送信
      shiftOut(dataPin_10ms, clockPin_10ms, MSBFIRST, j);//2バイトの下位を送信
      
      // 送信終了後latchPinをHIGHにする
      digitalWrite(latchPin_10ms, HIGH);
    
      c_10ms = c_10ms + 1;
      c_1ms = 0;
    }
    
    if(c_10ms > 10)   //100ms経過
    {
      // 送信中のlatchPinはグランド(LOW)レベル
      digitalWrite(latchPin_100ms, LOW);
      // シフト演算を使って点灯するLEDを選択しています
      val = 1 << c_100ms;
    
      //MSBFIRST, 74HC595_0_QA-QH->74HC595_1_QA-QB
      j = val;
      k = val>>8;
      shiftOut(dataPin_100ms, clockPin_100ms, MSBFIRST, k);//上位バイトを送信
      shiftOut(dataPin_100ms, clockPin_100ms, MSBFIRST, j);//2バイトの下位を送信
      
      // 送信終了後latchPinをHIGHにする
      digitalWrite(latchPin_100ms, HIGH);
      
      c_100ms = c_100ms + 1;
      c_10ms = 0;
    }

    if(c_100ms > 10)  //1000ms経過
    {
      // 送信中のlatchPinはグランド(LOW)レベル
      digitalWrite(latchPin_1000ms, LOW);
      // シフト演算を使って点灯するLEDを選択しています
      val = 1 << c_1000ms;
    
      //MSBFIRST, 74HC595_0_QA-QH->74HC595_1_QA-QB
      j = val;
      k = val>>8;
      shiftOut(dataPin_1000ms, clockPin_1000ms, MSBFIRST, k);//上位バイトを送信
      shiftOut(dataPin_1000ms, clockPin_1000ms, MSBFIRST, j);//2バイトの下位を送信
      
      // 送信終了後latchPinをHIGHにする
      digitalWrite(latchPin_1000ms, HIGH);
      
      c_1000ms = c_1000ms + 1;
      c_100ms = 0;
    }

    if(c_1000ms > 10)  //10000ms経過
    {
      c_1000ms = 0;
    }

    delay(1);
  }
}
