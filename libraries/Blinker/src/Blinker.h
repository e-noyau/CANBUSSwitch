#pragma once

#define CLASSIC_BLINK_PATTERN { 250 }
#define DUAL_BLINK_PATTERN { 250, 250, 250, 250, 250, 250, 125, 125, 125, 125 }
#define MOSTLY_ON_BLINK_PATTERN { 250, 125 }

class Blinker {
public:
  Blinker(int pin);
  
  // Start the blinker. More complex patterns are possible, just pass a list of intervals, and the
  // code will loop through these.
  // * A simple pattern of { 250 } will cause the pin to turn on, then off every 250ms.
  // * A dual pattern {500, 250 } will cause the pin to turn on for half a second and then turn off
  //   for 1/4 of a second.
  // * More complex pattern are possible.
  void start(std::vector<int> pattern = CLASSIC_BLINK_PATTERN);

  void stop();
  bool isStopped();
  
  void loop();

private:
  std::vector<int> _intervals;
  int _currentInterval;
  bool _isStopped;
  int _pin; 
  int _state;
  unsigned long _previousMillis;
};
