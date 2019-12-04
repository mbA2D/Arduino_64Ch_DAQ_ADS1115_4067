//each device - from channel_definitions.h - will have high and low thresholds.
//if either of those thresholds are crossed, then make warning true
//right now this is hacky, and defined based on what is connected to the channel, not what that connected device represents - air vs cell temperature


bool check_thresholds(int channel, int device)
{
  if(device == NTC_NXRT15XH)
    if(channel_readings[channel] > 60 || channel_readings[channel] < 15)
      return true;
  else if (device == NTC_NXRT15XV)
  {
    if(channel_readings[channel] > 60 || channel_readings[channel] < 15)
      return true;
  }

  //Li-ion undervotlage faults
  else if (device == V_DIV_2)
  {
    if(channel_readings[channel] > 4202 || channel_readings[channel] < 2500)
      return true;
  }

  //THIS PART IS VERY MUCH HACKING IT TOGETHER - I should make something to compare channels to each other.
  //Channel 8 is the V_DIV_2 channel, measuring the low cell.
  else if (device == V_DIV_4)
  {
    if((channel_readings[channel] - channel_readings[8] > 4202) || (channel_readings[channel] - channel_readings[8] < 2500))
      return true;
  }
  return false;
}


bool check_ADC_thresholds()
{
  bool warning_found = false;
  for(int i = 0; i < NUM_CHANNELS; i++){
    warning_found = check_thresholds(i, channel_connected_device[i]);
    if(warning_found) //return early if a warning is found
      return true;
  }
  return false;
}



