//This code was written to get thermistor readings from Midnight Sun's prototype battery module
//It was also me just playing around with multiple files in an arduino sketch, enums, and other good coding practices (which I likely did not follow).

#define ENABLE_SPEAKER
#define ENABLE_ADC

#ifdef ENABLE_ADC
  #include "ADC.h"
#endif

#ifdef ENABLE_SPEAKER
  #include "Speaker.h"
#endif

long current_millis = 0;
bool warning = false;

void setup(void) 
{
  Serial.begin(115200);

  #ifdef ENABLE ADC
    setup_ADC();
  #endif

  #ifdef ENABLE_SPEAKER
    setup_beep();
    enable_beep();
  #endif
}

void loop(void) 
{
  current_millis = millis();

  #ifdef ENABLE_ADC
  if(current_millis - last_adc_update_millis > ADC_UPDATE_INTERVAL_MILLIS)
  {
    update_channel_readings();
    channel_readings_to_proper_value();
    print_channel_readings();
    warning = check_ADC_thresholds();
  }
  #endif

  #ifdef ENABLE_SPEAKER
  speaker_enabled = warning;
  if(speaker_enabled)
    if(current_millis - last_speaker_change_millis > BEEP_INTERVAL_AND_LENGTH_MILLIS)
      update_speaker();
  #endif
}
