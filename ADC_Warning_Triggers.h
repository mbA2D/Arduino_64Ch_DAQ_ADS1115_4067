//each device - from channel_definitions.h - will have high and low thresholds.
//if either of those thresholds are crossed, then make warning true
//right now this is hacky, and defined based on what is connected to the channel, not what that connected device represents - air vs cell temperature

bool check_thresholds(int channel, uint8_t device)
{
  bool threshold_passed = false;
  
  if(device == NTC_NXRT15XH){
    if((channel_readings[channel] > 60) || (channel_readings[channel] < 15)){
      threshold_passed = true;
    }
  }
  else if (device == NTC_NXRT15XV){
    #ifdef HIGHER_CABLE_TEMP
      if(channel == CABLE_TEMP_CHANNEL_NUM){
        if((channel_readings[channel] > 90) || (channel_readings[channel] < 15)){
          threshold_passed = true;
        }
      }
      else if((channel_readings[channel] > 60) || (channel_readings[channel] < 15)){
        threshold_passed = true;
      }
    #else
      if((channel_readings[channel] > 60) || (channel_readings[channel] < 15)){
        threshold_passed = true;
      }
    #endif
  }

  //Li-ion undervotlage faults
  else if (device == V_DIV_2){
    if((channel_readings[channel] > 4202) || (channel_readings[channel] < 2500))
      threshold_passed = true;
  }

  //THIS PART IS VERY MUCH HACKING IT TOGETHER - I should make something to compare channels to each other.
  //Channel 8 is the V_DIV_2 channel, measuring the low cell.
  else if (device == V_DIV_4){
    if(((channel_readings[channel] - channel_readings[8]) > 4202) || ((channel_readings[channel] - channel_readings[8]) < 2500))
      threshold_passed = true;
  }
  
  return threshold_passed;
}


bool check_ADC_thresholds()
{
  bool warning_found = false;
  for(int i = 0; i < NUM_CHANNELS; i++){
    warning_found = check_thresholds(i, channel_connected_device[i]);
    if(warning_found) //return early if a warning is found
      return true;
  }
  return warning_found;
}
