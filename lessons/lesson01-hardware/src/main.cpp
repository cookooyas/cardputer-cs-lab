
#include <Arduino.h>
#include <M5Cardputer.h>
#include <stdlib.h>

void setup()
{

  // 1. Cardputer 및 LCD 초기화
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);

  auto &lcd = M5Cardputer.Display;
  lcd.setRotation(1);
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);
  lcd.setCursor(5, 5);

  lcd.println("=== MEMORY LAB ===");
  lcd.println();

  // 2. 메모리 할당 전
  uint32_t before = ESP.getFreeHeap();

  // 3. RAM 32KB 할당
  const size_t SIZE = 32 * 1024;
  uint8_t *data = (uint8_t *)malloc(SIZE);

  // 4. 할당 성공 여부 확인
  if (data == nullptr)
  {
    lcd.println("Allocation FAILED!");
    return;
  }

  // 실제 할당된 영역에 값 기록
  data[0] = 10;
  data[SIZE - 1] = 20;

  // 5. 메모리 할당 후
  uint32_t after = ESP.getFreeHeap();

  // 6. 메모리 반환
  free(data);
  data = nullptr;

  // 7. 반환 후 여유 메모리 측정
  uint32_t restored = ESP.getFreeHeap();

  // 8. LCD에 결과 표시
  lcd.printf("Before : %lu KB\n",
             (unsigned long)(before / 1024));

  lcd.printf("After  : %lu KB\n",
             (unsigned long)(after / 1024));

  lcd.printf("Freed  : %lu KB\n",
             (unsigned long)(restored / 1024));

  lcd.println();

  lcd.printf("Allocated: %u KB\n",
             (unsigned)(SIZE / 1024));

  lcd.println("Experiment complete!");
}

void loop()
{
  M5Cardputer.update();
  delay(100);
}
