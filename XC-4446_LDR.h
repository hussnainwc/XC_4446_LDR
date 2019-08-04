#ifndef XC_4446_h
#define XC_4446_h
#include "Arduino.h"
#endif

class XC_4446{
  public:
    XC_4446 (int pin);
    void begin();
    void ReadLux(bool);
    void ReadInFC(bool);
    void ReadNoAvgLux(bool);
    void ReadNoAvgFC(bool);
    void SafeReadLux(bool);
    void SafeReadInFC(bool);
    void SetRange(float);
    void SetSampleSize(int);
    void SetSampleInterval(int);

  private:
    int _pin;
    int SAMPLE_SIZE = 3;
    int SAMPLE_INTERVAL = 50;
    float AVG_LUX = 0;
    int SECONDS_MICROSECONDS = 1000;
    float LUX_FC = 10.764;
    float TOTAL = 0;
    float READING = 0;
    bool PRINT_TO_SERIAL = true;
    float RANGE = 0;

    float ReadLDR();
    float AvgReading();
    float CalcRoomLux();
    bool CheckAnomaly(float);
};
