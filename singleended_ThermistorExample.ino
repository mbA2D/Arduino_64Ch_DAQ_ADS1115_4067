//FLASH IS NOT GOING TO WORK FOR STORING (TOO COMPLICATED, LIBRARIES DON'T WORK, so we'll plot in matplotlib and use a polynomial.

#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "Channel_Definitions.h"
#include "NTC_10K_NXRT15XH103FA1B_RT_MAP.h"
#include "NTC_10K_NXRT15XV103FA1B_RT_MAP.h"

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */


int16_t adc0, adc1, adc2, adc3;
double channel_readings[NUM_CHANNELS] = {0};

void setupPins(){
  pinMode(MAIN_CHANNEL_S0, OUTPUT);
  pinMode(MAIN_CHANNEL_S1, OUTPUT);
  pinMode(MAIN_CHANNEL_S2, OUTPUT);
  pinMode(MAIN_CHANNEL_S3, OUTPUT);
  pinMode(AUX_CHANNEL_S0, OUTPUT);
  pinMode(AUX_CHANNEL_S1, OUTPUT);
  pinMode(AUX_CHANNEL_S2, OUTPUT);
  pinMode(AUX_CHANNEL_S3, OUTPUT);

  digitalWrite(MAIN_CHANNEL_S0, LOW);
  digitalWrite(MAIN_CHANNEL_S1, LOW);
  digitalWrite(MAIN_CHANNEL_S2, LOW);
  digitalWrite(MAIN_CHANNEL_S3, LOW);
  digitalWrite(AUX_CHANNEL_S0, LOW);
  digitalWrite(AUX_CHANNEL_S1, LOW);
  digitalWrite(AUX_CHANNEL_S2, LOW);
  digitalWrite(AUX_CHANNEL_S3, LOW);
}

void set_channel_input(bool channel, uint8_t num){
  int s0=0, s1=0, s2=0, s3=0;
  s0 = num % 2;
  num = num >> 1;
  s1 = num % 2;
  num = num >> 1;
  s2 = num % 2;
  num = num >> 1;
  s3 = num % 2;

  /*
  Serial.print(s3);
  Serial.print(s2);
  Serial.print(s1);
  Serial.println(s0);
  */

  if(channel == MAIN_CHANNEL){
    digitalWrite(MAIN_CHANNEL_S0, s0);
    digitalWrite(MAIN_CHANNEL_S1, s1);
    digitalWrite(MAIN_CHANNEL_S2, s2);
    digitalWrite(MAIN_CHANNEL_S3, s3);
  }
  else if (channel == AUX_CHANNEL){
    digitalWrite(AUX_CHANNEL_S0, s0);
    digitalWrite(AUX_CHANNEL_S1, s1);
    digitalWrite(AUX_CHANNEL_S2, s2);
    digitalWrite(AUX_CHANNEL_S3, s3);
  }
}

double mV_to_R_divider(double mV, double upper_resistor_ohms, double excitation_voltage){
  //return upper_resistor_ohms / ((excitation_voltage / (mV / 1000)) - 1);

  double current = (excitation_voltage - (mV/1000)) / upper_resistor_ohms;
  return (mV/1000) / current;
}

void update_ADC_readings(){
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
}

void update_channel_readings(){
  for(int i = 0; i < 16; i++){
    set_channel_input(MAIN_CHANNEL, i);
    set_channel_input(AUX_CHANNEL, i);
    delayMicroseconds(10);
    update_ADC_readings();
    channel_readings[0 + 4 * i] = adc0;
    channel_readings[1 + 4 * i] = adc1;
    channel_readings[2 + 4 * i] = adc2;
    channel_readings[3 + 4 * i] = adc3;
  }
}

void print_channel_readings(){
  for(int i = 0; i < NUM_CHANNELS; i++)
  {
    Serial.print(channel_readings[i]);
    Serial.print(",");
  }
  Serial.println("");
}

void channel_readings_to_mV(){
  for(int i = 0; i < NUM_CHANNELS; i++)
  {
    //1 bit  = 0.1875mV
    //    bit * mV per bit = mV
    channel_readings[i] *= 0.1875;
  }
}

void channel_readings_mV_to_R(){
  for(int i = 0; i < NUM_CHANNELS; i++)
  {
    //vin = EXCITATION_VOLTAGE_VALUE_VOLTS
    //vout = channel_reading
    //R1 = UPPER_RESISTOR_VALUE_OHMS
    //R2: vin/vout = r2 / r1+r2
    channel_readings[i] = mV_to_R_divider(channel_readings[i], UPPER_RESISTOR_VALUE_OHMS, EXCITATION_VOLTAGE_VALUE_VOLTS);
  }
}


double mV_to_proper_value(uint8_t ch, double mV){
  //channels go 0 to 63
  int device = channel_connected_device[ch];

  if(device == VOLTAGE)
    return mV;
  else if (device == V_DIV_2)
    return mV*2;
  else if (device == V_DIV_4)
    return mV*4;
  else if(device == NTC_NXRT15XH){
    double r = mV_to_R_divider(mV, UPPER_RESISTOR_VALUE_OHMS, EXCITATION_VOLTAGE_VALUE_VOLTS);
    return NXRT15XH103FA1B_get_temp(r);
  }
  else if(device == NTC_NXRT15XV){
    double r = mV_to_R_divider(mV, UPPER_RESISTOR_VALUE_OHMS, EXCITATION_VOLTAGE_VALUE_VOLTS);
    return NXRT15XV103FA1B_get_temp(r);
  }
}


void channel_readings_to_proper_value(){
  for(int i = 0; i < NUM_CHANNELS; i++)
    channel_readings[i] = mV_to_proper_value(i, channel_readings[i]);
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.print(F("AUX_0, MAIN0_0, MAIN1_0, MAIN2_0, "));
  Serial.print(F("AUX_1, MAIN0_1, MAIN1_1, MAIN2_1, "));
  Serial.print(F("AUX_2, MAIN0_2, MAIN1_2, MAIN2_2, "));
  Serial.print(F("AUX_3, MAIN0_3, MAIN1_3, MAIN2_3, "));
  Serial.print(F("AUX_4, MAIN0_4, MAIN1_4, MAIN2_4, "));
  Serial.print(F("AUX_5, MAIN0_5, MAIN1_5, MAIN2_5, "));
  Serial.print(F("AUX_6, MAIN0_6, MAIN1_6, MAIN2_6, "));
  Serial.print(F("AUX_7, MAIN0_7, MAIN1_7, MAIN2_7, "));
  Serial.print(F("AUX_8, MAIN0_8, MAIN1_8, MAIN2_8, "));
  Serial.print(F("AUX_9, MAIN0_9, MAIN1_9, MAIN2_9, "));
  Serial.print(F("AUX_10, MAIN0_10, MAIN1_10, MAIN2_10, "));
  Serial.print(F("AUX_11, MAIN0_11, MAIN1_11, MAIN2_11, "));
  Serial.print(F("AUX_12, MAIN0_12, MAIN1_12, MAIN2_12, "));
  Serial.print(F("AUX_13, MAIN0_13, MAIN1_13, MAIN2_13, "));
  Serial.print(F("AUX_14, MAIN0_14, MAIN1_14, MAIN2_14, "));
  Serial.println(F("AUX_15, MAIN0_15, MAIN1_15, MAIN2_15"));
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  

  setupPins();

  set_channel_input(MAIN_CHANNEL, 0);
  set_channel_input(AUX_CHANNEL, 0);
  
  ads.begin();
}

void loop(void) 
{
  update_channel_readings();
  channel_readings_to_mV();
  channel_readings_to_proper_value();
  //channel_readings_mV_to_R();
  print_channel_readings();
  
  delay(100);
}
