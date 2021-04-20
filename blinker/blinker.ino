#include <vector>

#include <Button2.h>
#include <Blinker.h>

#define BUTTON_PIN  15
#define LED_BUILTIN 2
#define RELAY 32

Button2 button = Button2(BUTTON_PIN);

std::vector<Blinker> blinkers({
  Blinker(LED_BUILTIN),
  Blinker(RELAY)
});

void setup() {
  Serial.begin(115200);
  delay(50);
  
  button.setLongClickTime(500); // Long click is half a second.
  
  button.setClickHandler(handler);
  button.setLongClickHandler(handler);
  button.setDoubleClickHandler(handler);
}

void loop() {
  button.loop();
  for (Blinker& blinker : blinkers)
    blinker.loop();
}

void handler(Button2& btn) {
    switch (btn.getClickType()) {
      case SINGLE_CLICK:
        for (Blinker& blinker : blinkers) {
          if (blinker.isStopped()) {
            blinker.start();
          } else {
            blinker.stop();
          }
        }
        break;
      case DOUBLE_CLICK:
        Serial.print("double ");
        for (Blinker& blinker : blinkers) {
          blinker.start(DUAL_BLINK_PATTERN);
        }
        break;
      case LONG_CLICK:
        Serial.print("long");
        for (Blinker& blinker : blinkers) {
          blinker.start(MOSTLY_ON_BLINK_PATTERN);
        }
        break;
    }
    Serial.print("click");
    Serial.print(" (");
    Serial.print(btn.getNumberOfClicks());    
    Serial.println(")");
}
