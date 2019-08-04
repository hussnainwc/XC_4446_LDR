#include "Arduino.h"
#include "XC-4446_LDR.h"

/**
 * Constructor
 * @param  {int} pin The pin to read from
 * @return null
 */
XC_4446::XC_4446(int pin) {
  _pin = pin;
}

/**
 * Calculate current lux so as to remove anomalies
 * @param  null
 * @return null
 */
void XC_4446::begin(){
  Serial.println("Calculating lux for better precision in 3 seconds please make sure environment is in its usual state");
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  AVG_LUX = XC_4446::CalcRoomLux();
  Serial.println("Room lux is " + String(AVG_LUX));
}

/**
 * Read lux, according to sample size specified,
 * get the average and print to serial if user states
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::ReadLux(bool print = true){
  PRINT_TO_SERIAL = print;
  if(PRINT_TO_SERIAL){
    Serial.println("lux : " + String(XC_4446::AvgReading()));
  }
}

/**
 * Read lux, according to sample size specified,
 * get the average and conver it to Foot Candles.
 * Then print to serial if user states
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::ReadInFC(bool print = true){
  PRINT_TO_SERIAL = print;
  if(PRINT_TO_SERIAL){
    Serial.println("fc : " + String(XC_4446::AvgReading()/LUX_FC));
  }
}

/**
 * Read lux and print to serial if user states
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::ReadNoAvgLux(bool print = true){
  PRINT_TO_SERIAL = print;
  if(PRINT_TO_SERIAL){
    Serial.println("lux : " + String(analogRead(_pin)));
  }
}

/**
 * Read lux and convert to Foot Candles.
 * Then print to serial if user states
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::ReadNoAvgFC(bool print = true){
  PRINT_TO_SERIAL = print;
  if(PRINT_TO_SERIAL){
    Serial.println("fc : " + String(analogRead(_pin)/LUX_FC));
  }
}

/**
 * Read lux, according to sample size specified,
 * get the average and check if it falls under range specified.
 * Then print to serial if user states.
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::SafeReadLux(bool print = true){
  PRINT_TO_SERIAL = print;
  if(AVG_LUX == 0){
    XC_4446::CalcRoomLux();
  }
  if(XC_4446::CheckAnomaly(XC_4446::AvgReading())){
    if(PRINT_TO_SERIAL){
      Serial.println("lux : " + String(TOTAL/SAMPLE_SIZE));
    }
  }
  else{
    XC_4446::SafeReadLux();
  }
}

/**
 * Read lux, according to sample size specified,
 * get the average and check if it falls under range specified.
 * Convert to Foot Candles and print to serial if user states.
 * @param {bool} print to serial
 * @return null
 */
void XC_4446::SafeReadInFC(bool print = true){
  PRINT_TO_SERIAL = print;
  if(AVG_LUX == 0){
    XC_4446::CalcRoomLux();
  }
  if(XC_4446::CheckAnomaly(XC_4446::AvgReading())){
    if(PRINT_TO_SERIAL){
      Serial.println("fc : " + String((TOTAL/SAMPLE_SIZE)/LUX_FC));
    }
  }
  else{
    XC_4446::SafeReadInFC();
  }
};

/**
 * Read lux and get an average to initilaize room average.
 * @param null
 * @return {float} initial Average Reading
 */
float XC_4446::CalcRoomLux(){
  return XC_4446::AvgReading();
};

/**
* Sets sample size
* @param {int) size
* @return null
*/
void XC_4446::SetSampleSize(int size){
  SAMPLE_SIZE = size;
}

/**
* Sets sample interval
* @param {int) interval
* @return null
*/
void XC_4446::SetSampleInterval(int interval){
  SAMPLE_INTERVAL = interval;
}

/**
 * Get an average of the readings according to sample size.
 * @param null
 * @return {float} Average Reading
 */
float XC_4446::AvgReading(){
  return XC_4446::ReadLDR()/SAMPLE_SIZE;
};

/**
 * Read lux as specified sample size
 * and delay by sample interval between each reading
 * @param null
 * @return {float} TOTAL of the readings
 */
float XC_4446::ReadLDR(){
  TOTAL = 0;
  for(int i=0;i<SAMPLE_SIZE;i++){
    READING = analogRead(_pin);
    delay(SAMPLE_INTERVAL);
    TOTAL += READING;
  }
  return TOTAL;
};

/**
* Sets range for radings.
* @param {float} range
* @return null
*/
void XC_4446::SetRange(float range){
  RANGE = range/100;
}

/**
 * Checks if reading falls under specified range.
 * @param {float} Average reading
 * @return {bool} if reading falls under range
 */
bool XC_4446::CheckAnomaly(float reading){
  if(RANGE != 0){
  if(reading >= ((1 + RANGE) * AVG_LUX) || reading <= ((1 - RANGE) * AVG_LUX)){
    return false;
  }
  return true;
  }
  else{
    SetRange(10);
    XC_4446::CheckAnomaly(reading);
  }
};
