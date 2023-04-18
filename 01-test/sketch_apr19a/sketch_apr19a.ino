#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Rows 4
#define Cols 4

char keys[Rows][Cols] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

#define MAX_CHAR 16
#define MAX_LINE 2

LiquidCrystal_I2C lcd(0x27, MAX_CHAR, MAX_LINE);

const int RowPinTbl[Rows] = { 5, 4, 3, 2 };
const int ColPinTbl[Cols] = { 6, 7, 8, 9 };

// 직전 키
char previousKey;
bool pressed;

void setup() {
  // 디스플레이 초가화
  lcd.begin();
  // 디스플레이 백라이트 활성화
  lcd.backlight();
  // input 초기화
  lcd.setCursor(0, 0);
  lcd.print("13 + 15 = 28");

  Serial.begin(9600);
  for (int i = 0; i < Rows; i++) {
    pinMode(RowPinTbl[i], INPUT_PULLUP);
  }

  for (int j = 0; j < Cols; j++) {
    pinMode(ColPinTbl[j], OUTPUT);
    digitalWrite(ColPinTbl[j], HIGH);
  }
}

void loop() {
  char key;
  bool pressed = false;

  for (int j = 0; j < Cols; j++) {
    digitalWrite(ColPinTbl[j], LOW);
    for (int i = 0; i < Rows; i++) {
      if (digitalRead(RowPinTbl[i]) == LOW) {
        key = keys[i][j];
      }
    }
    digitalWrite(ColPinTbl[j], HIGH);
  }

  if (key == NULL) {
    return;
  }

  Serial.print("pressed: ");
  Serial.print(key);
}
