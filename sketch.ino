#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/wdt.h>

void Dodger();
void memory_game();
void guess_the_number(struct Random_Range *r1);
void choose_game();


struct Random_Range {
  int upper = 100;
  int lower = 0;
} r1;

struct led_memory {
    int* generated_sequence;
    int* inputted_sequence;
} led_memory;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

int line(int pos, int x);
void drawCircleAt(int pos, bool erase);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello, World!"));
  display.display();
  display.clearDisplay();
  delay(500);

  void (*chooser_pointer)() = &choose_game;
  (*chooser_pointer)();
}

void loop() {
  
}

void choose_game() {
  display.clearDisplay();
  display.display();

  display.print("Choose The Game \n");
  display.print("\n 1. Dodger \n");
  display.print("\n 2. Memory Game \n");
  display.print("\n 3. Guess The Number \n");
  display.display();
  while (true) {
    int a = digitalRead(11);
    int b = digitalRead(10);
    int c = digitalRead(9);

    if (a == HIGH) {
      display.clearDisplay();
      display.display();
      void (*dodger_pointer)() = &Dodger;
      (*dodger_pointer)();
      break;
    } else if (b == HIGH) {
      display.clearDisplay();
      display.display();
      void (*memory_pointer)() = &memory_game;
      (*memory_pointer)();
      break;
    } else if (c == HIGH) {
      display.clearDisplay();
      display.display();
      void (guess_pointer)(struct Random_Range) = &guess_the_number;
      (*guess_pointer)(&r1);
      break;
    }
  }
}

void Dodger() {
  delay(1000);
  tone(8, 152, 70);
  display.drawLine(63, 1, 63, 63, SSD1306_WHITE);
  display.drawCircle(31, 55, 5, SSD1306_WHITE);
  display.display();

  while (true) {

  delay(100);
    static int pos = 31;
    pos = line(pos, 31);
    delay(10);
    pos = line(pos, 94);
  }
}

int line(int pos, int x) {
  int circle_position = pos;

  for (int i = 1; i < 51; i += 3) {
    int n = digitalRead(11);
    if (n == HIGH) {
      drawCircleAt(circle_position, true);
      circle_position = (circle_position == 31) ? 94 : 31;
      pos = circle_position;
      drawCircleAt(circle_position, false);
      display.display();
    }

    display.drawLine(x - 20, i, x - 20, i + 3, SSD1306_WHITE);
    display.drawLine(x, i, x, i + 3, SSD1306_WHITE);
    display.drawLine(x + 20, i, x + 20, i + 3, SSD1306_WHITE);
    display.display();
    delay(60);
    display.drawLine(x - 20, i, x - 20, i + 3, SSD1306_BLACK);
    display.drawLine(x, i, x, i + 3, SSD1306_BLACK);
    display.drawLine(x + 20, i, x + 20, i + 3, SSD1306_BLACK);

    if (i >= 46 && circle_position == x) {
      display.clearDisplay();
      while (true) {
        n = digitalRead(11);
        if (n == HIGH) {
          restartCode();
          
        }
        display.setCursor(32, 18);
        display.print("Game Over ! \n");
        display.print("Press switch 1 to go back");
        tone(8, 262, 250);
        display.display();
      }
    }
  }
  return pos;
}

void drawCircleAt(int pos, bool erase) {
  tone(8, 152, 70);
  display.drawCircle(pos, 55, 5, erase ? SSD1306_BLACK : SSD1306_WHITE);
}

void memory_game() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(11, INPUT);
  led_memory.generated_sequence = (int*)malloc(3 * sizeof(int));
 led_memory.inputted_sequence = (int*)malloc(3 * sizeof(int));

  tone(8, 152, 70);
  int arr[3];
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("Observe the Lights \n");
  display.print("\n Press Switch 1");
  display.display();
  while (true) {
    int n = digitalRead(11);
    if (n == HIGH) {
      delay(100);
      break;
    }
  }
 tone(8, 152, 70);
  srand(analogRead(0));

  for (int i = 0; i < 3; i++) {
    int r = rand() % (3) + 1;
    led_memory.generated_sequence[i] = r;

    switch (r) {
      case (1):
        digitalWrite(7, HIGH);
        delay(1000);
        digitalWrite(7, LOW);
        break;

      case (2):
        digitalWrite(6, HIGH);
        delay(1000);
        digitalWrite(6, LOW);
        break;

      case (3):
        digitalWrite(5, HIGH);
        delay(1000);
        digitalWrite(5, LOW);
        break;
    }
    delay(1000);
  }

  display.clearDisplay();
  display.setCursor(32,32);
  display.print("\n Guess Your Memory : ");
  display.display();
  tone(8, 152, 70);
  int c = 0;
  while (c < 3) {
    if (digitalRead(11) == HIGH) {
      tone(8, 152, 70);
      Serial.println(1);
      led_memory.inputted_sequence[c] = 1;
          c++;
      delay(500);
    } else if (digitalRead(10) == HIGH) {
      tone(8, 152, 70);
      Serial.println(2);
       led_memory.inputted_sequence[c] = 2;
           c++;
      delay(500);
    } else if (digitalRead(9) == HIGH) {
      tone(8, 152, 70);
      Serial.println(3);
       led_memory.inputted_sequence[c] = 3;
           c++;
      delay(500);
    }
  }
  struct led_memory *memory_struct_pointer = &led_memory;
  int is_correct = 1;
  for(int i =0 ; i<3;i++){
    if (memory_struct_pointer->generated_sequence[i]!=memory_struct_pointer->inputted_sequence[i]){
      is_correct = 0;
    }
  }
  display.clearDisplay();
  display.setCursor(10,10);
  if(is_correct == 1){
     display.print("You are Correct");
  } else {
    display.print("You are Wrong");
  }
  tone(8, 152, 70);
  display.print("\nPress Switch 1 to Go back");
  display.display();

  while(true){
    if(digitalRead(11) == HIGH){
      restartCode();
      break;
    }
  }
    free(led_memory.generated_sequence);
   free(led_memory.inputted_sequence);

}

void guess_the_number(struct Random_Range *r1) {
  int upper = r1->upper;
  int lower = r1->lower;
  tone(8, 152, 70);
  srand(analogRead(0));

  int random_number = rand() % (upper - lower + 1) + lower;
  // Serial.println(random_number);
  display.clearDisplay();
  display.setCursor(10, 20);
  display.print("Guess the Number");
  display.display();

  int n = 0;

  while (1) {
    while (Serial.available() == 0) {
      ;
    }
    n = Serial.parseInt();
    display.clearDisplay();
    display.setCursor(10, 20);
    display.display();
    delay(100);

    if (n == random_number) {
      while(true){
        display.setCursor(0, 20);
      display.print("You Guessed it right, Press switch 1 to go back");
      tone(8, 152, 70);
      display.display();      
        int n = digitalRead(11);

        if(n == HIGH){
          restartCode();
          break;
        }
      }
    } else if (n > random_number) {
      display.print("Your Guess is High");
      tone(8, 152, 70);
    } else {
      tone(8, 152, 70);
      display.print("Your Guess is Low");
    }
    Serial.println(n);
    display.setCursor(10, 20);
    display.display();

    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}

void restartCode() {
  wdt_enable(WDTO_15MS); 
  while (1) {
  }
}