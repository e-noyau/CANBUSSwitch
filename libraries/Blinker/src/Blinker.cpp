#include "Arduino.h"
#include "Blinker.h"

Blinker::Blinker(int pin) : _pin(pin) {
  pinMode(_pin, OUTPUT);
  stop();
}

void Blinker::start(std::vector<int> pattern) {
  _intervals = pattern;
  _currentInterval = 0;
  _isStopped = false;
  _state = HIGH;
  digitalWrite(_pin, _state);
  _previousMillis = millis();
}

void Blinker::stop() {
  _isStopped = true;
  _state = LOW;
  digitalWrite(_pin, _state);
}

bool Blinker::isStopped() {
  return _isStopped;
}

void Blinker::loop() {
  if (_isStopped)
    return;
  
  unsigned long currentMillis = millis();
  
  if ((currentMillis - _previousMillis) > _intervals[_currentInterval]) {
    _previousMillis = currentMillis;
    _currentInterval = (_currentInterval + 1) % _intervals.size();
    
    _state = (_state == LOW) ? HIGH : LOW;
    digitalWrite(_pin, _state);  // Update the actual LED
  }
}
