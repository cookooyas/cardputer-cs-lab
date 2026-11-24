
#include <Arduino.h>
#include <M5Cardputer.h>

void setup()
{
  // 1. Cardputer 하드웨어 초기화
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);

  // 2. 디스플레이 초기화
  auto &lcd = M5Cardputer.Display;

  lcd.setRotation(1);
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.setCursor(5, 5);

  // 3. 제목 출력
  lcd.println("CARDPUTER LAB");
  lcd.println();

  // 4. 하드웨어 정보 조회
  uint32_t cpu = ESP.getCpuFreqMHz();
  uint32_t heap = ESP.getFreeHeap();
  uint32_t flash = ESP.getFlashChipSize();

  // 5. 결과를 Cardputer 화면에 출력
  lcd.setTextSize(1);

  lcd.printf("CPU: %lu MHz\n",
             (unsigned long)cpu);

  lcd.printf("Free Heap: %lu KB\n",
             (unsigned long)(heap / 1024));

  lcd.printf("Flash: %lu MB\n",
             (unsigned long)(flash / 1024 / 1024));

  lcd.println();
  lcd.println("Program is running!");
}

void loop()
{
  M5Cardputer.update();
  delay(100);
}
