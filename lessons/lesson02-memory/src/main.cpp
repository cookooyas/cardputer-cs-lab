
#include <Arduino.h>
#include <M5Cardputer.h>
#include <stdlib.h>

void setup()
{
  // ========================================
  // 1. Cardputer 초기화
  // ========================================
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);

  auto &lcd = M5Cardputer.Display;

  lcd.setRotation(1);
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);
  lcd.setCursor(5, 5);

  lcd.println("=== POINTER LAB ===");
  lcd.println();

  // ========================================
  // 2. 일반 변수와 포인터
  // ========================================

  int number = 100;

  // number의 주소를 ptr에 저장
  int *ptr = &number;

  lcd.printf("number : %d\n", number);
  lcd.printf("&number: %p\n", (void *)&number);
  lcd.printf("ptr    : %p\n", (void *)ptr);
  lcd.printf("*ptr   : %d\n", *ptr);

  // 포인터를 통해 원본 값 변경
  *ptr = 200;

  lcd.printf("changed: %d\n", number);
  lcd.println();

  // ========================================
  // 3. 동적 메모리 할당
  // ========================================

  // 각각 1024바이트(1KB)를 요청
  uint8_t *first = (uint8_t *)malloc(1024);
  uint8_t *second = (uint8_t *)malloc(1024);

  // 할당 성공 여부 확인
  if (first == nullptr || second == nullptr)
  {
    lcd.println("Allocation FAILED!");

    free(first);
    free(second);
    return;
  }

  lcd.println("[HEAP MEMORY]");

  lcd.printf("first : %p\n", (void *)first);
  lcd.printf("second: %p\n", (void *)second);

  // ========================================
  // 4. 메모리 반환 및 재할당
  // ========================================

  // first가 사용하던 주소를 기록
  void *oldAddress = (void *)first;

  // first 메모리 반환
  free(first);
  first = nullptr;

  // 다시 1024바이트 할당
  uint8_t *third = (uint8_t *)malloc(1024);

  lcd.println();
  lcd.printf("old   : %p\n", oldAddress);
  lcd.printf("third : %p\n", (void *)third);

  lcd.println();

  // 주소가 재사용되었는지 비교
  if (third != nullptr && (void *)third == oldAddress)
  {
    lcd.println("Address reused!");
  }
  else if (third != nullptr)
  {
    lcd.println("Different address!");
  }
  else
  {
    lcd.println("Reallocation FAILED!");
  }

  // ========================================
  // 5. 메모리 정리
  // ========================================

  free(second);
  free(third);

  lcd.println("Experiment complete!");
}

void loop()
{
  M5Cardputer.update();
  delay(100);
}
