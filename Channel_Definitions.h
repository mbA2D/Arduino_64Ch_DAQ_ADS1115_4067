//39XXK (XV) is brown wires on positive end
//33XXK (XH) is red wires on negative end
#include "NTC_10K_NXRT15XH103FA1B_RT_MAP.h"
#include "NTC_10K_NXRT15XV103FA1B_RT_MAP.h"

#define HIGHER_CABLE_TEMP
#ifdef HIGHER_CABLE_TEMP
  #define CABLE_TEMP_CHANNEL_NUM 16
#endif

//PIN CONNECTION DEFINITIONS

#define SPEAKER_PIN 11

#define MAIN_CHANNEL 0
#define AUX_CHANNEL 1

#define NUM_CHANNELS 64

#define MAIN_CHANNEL_S0 6
#define MAIN_CHANNEL_S1 5
#define MAIN_CHANNEL_S2 4
#define MAIN_CHANNEL_S3 3

#define AUX_CHANNEL_S0 7
#define AUX_CHANNEL_S1 8
#define AUX_CHANNEL_S2 9
#define AUX_CHANNEL_S3 10

enum{
  NTC_NXRT15XH,
  NTC_NXRT15XV,
  V_DIV_2,
  V_DIV_4,
  VOLTAGE
};

enum{
  AUX_SIG,
  MAIN0_SIG,
  MAIN1_SIG,
  MAIN2_SIG
};

//VOLTAGE DIVIDER DEFINITIONS

#define UPPER_RESISTOR_VALUE_OHMS 10000
#define EXCITATION_VOLTAGE_VALUE_VOLTS 5


uint8_t channel_connected_device[NUM_CHANNELS] = 
{
  VOLTAGE, //AUX 0
  NTC_NXRT15XV, //MAIN0 0 //3-2-T-P
  NTC_NXRT15XV, //MAIN1 0 //6-3-B-P
  NTC_NXRT15XV, //MAIN2 0 //8-1-B-P
  VOLTAGE, //AUX 1
  NTC_NXRT15XH, //MAIN0 1 //3-2-B-N
  NTC_NXRT15XH,//MAIN1 1 //6-3-T-N
  NTC_NXRT15XH,//MAIN2 1 //8-1-T-N
  V_DIV_2, //AUX 2 //V_CELL_1
  NTC_NXRT15XV,//MAIN0 2 //3-3-T-P
  NTC_NXRT15XV,//MAIN1 2 //5-1-B-P
  NTC_NXRT15XV,//MAIN2 2 //8-2-B-P
  V_DIV_4, //AUX 3 //V_MODULE
  NTC_NXRT15XH,//MAIN0 3 //3-3-B-N
  NTC_NXRT15XH,//MAIN1 3 //5-1-T-N
  NTC_NXRT15XH,//MAIN2 3 //8-2-T-N
  NTC_NXRT15XV, //AUX 4
  NTC_NXRT15XV,//MAIN0 4 //2-1-T-P
  NTC_NXRT15XV,//MAIN1 4 //5-2-B-P
  NTC_NXRT15XV, //MAIN2 4 //8-3-B-P
  NTC_NXRT15XV, //AUX 5
  NTC_NXRT15XH,//MAIN0 5 //2-1-B-N
  NTC_NXRT15XH,//MAIN1 5 //5-2-T-N
  NTC_NXRT15XH,//MAIN2 5 //8-3-T-N
  NTC_NXRT15XV, //AUX 6
  NTC_NXRT15XV,//MAIN0 6 //2-2-T-P
  NTC_NXRT15XV,//MAIN1 6 //5-3-T-N
  NTC_NXRT15XV,//MAIN2 6 //7-1-B-P
  NTC_NXRT15XV, //AUX 7
  NTC_NXRT15XH,//MAIN0 7 //2-2-B-N
  NTC_NXRT15XH,//MAIN1 7 //5-3-T-N
  NTC_NXRT15XH,//MAIN2 7 //7-1-T-N
  NTC_NXRT15XV, //AUX 8
  NTC_NXRT15XV,//MAIN0 8 //2-3-T-P
  NTC_NXRT15XV,//MAIN1 8 //4-1-T-P
  NTC_NXRT15XV,//MAIN2 8 //7-2-B-P
  NTC_NXRT15XV, //AUX 9
  NTC_NXRT15XH,//MAIN0 9 //2-3-B-N
  NTC_NXRT15XH,//MAIN1 9 //4-1-B-N
  NTC_NXRT15XH,//MAIN2 9 //7-2-T-N
  NTC_NXRT15XV, //AUX 10
  NTC_NXRT15XV,//MAIN0 10 //1-1-T-P
  NTC_NXRT15XV,//MAIN1 10 //4-2-T-P
  NTC_NXRT15XV,//MAIN2 10 //7-3-B-P
  NTC_NXRT15XV,//AUX 11
  NTC_NXRT15XH,//MAIN0 11 //1-1-B-N
  NTC_NXRT15XH,//MAIN1 11 //4-2-B-N
  NTC_NXRT15XH,//MAIN2 11 //7-3-T-N
  NTC_NXRT15XV,//AUX 12
  NTC_NXRT15XV,//MAIN0 12 //1-2-T-P
  NTC_NXRT15XV,//MAIN1 12 //4-3-T-P
  NTC_NXRT15XV,//MAIN2 12 //6-1-B-P
  NTC_NXRT15XV,//AUX 13
  NTC_NXRT15XH,//MAIN0 13 //1-2-B-N
  NTC_NXRT15XH,//MAIN1 13 //4-3-B-N
  NTC_NXRT15XH,//MAIN2 13 //6-1-T-N
  NTC_NXRT15XV,//AUX 14
  NTC_NXRT15XV,//MAIN0 14 //1-3-T-P
  NTC_NXRT15XV,//MAIN1 14 //3-1-T-P
  NTC_NXRT15XV,//MAIN2 14 //6-2-B-P
  NTC_NXRT15XV,//AUX 15
  NTC_NXRT15XH,//MAIN0 15 //1-3-B-N
  NTC_NXRT15XH,//MAIN1 15 //3-1-B-N
  NTC_NXRT15XH//MAIN2 15 //6-2-T-N
};
