/*
 * PN: NXRT15XH103FA1B
 * R at 25C          10  k ohm +/- 1%
 * B(25/50)      3380 K     +/- 1%
 */


//Thermistor Constants Steinhart_hart
#define NXRT15XH103FA1B_A 0.8983467387e-3
#define NXRT15XH103FA1B_B 2.495328425e-4
#define NXRT15XH103FA1B_C 2.014385543e-7

double NXRT15XH103FA1B_get_temp(double resistance){
  return ((1/(NXRT15XH103FA1B_A + (NXRT15XH103FA1B_B * log(resistance)) + (NXRT15XH103FA1B_C * (pow(log(resistance),3))))) - 273.15);
}



/*
#define NXRT15XH103FA1B_NUM_POINTS 166
#define NXRT15XH103FA1B_R_INDEX 1
#define NXRT15XH103FA1B_T_INDEX 0


const double NXRT15XH103FA1B_Resistance_Temperature_R_C[][2] =
 {
{-40, 195652},
{-39, 184917.1},
{-38, 174845.2},
{-37, 165391},
{-36, 156512.5},
{-35, 148171},
{-34, 140330.4},
{-33, 132957.6},
{-32, 126021.5},
{-31, 119493.6},
{-30, 113347.1},
{-29, 107564.9},
{-28, 102115.5},
{-27, 96977.6},
{-26, 92131.5},
{-25, 87558.8},
{-24, 83242.4},
{-23, 79166.3},
{-22, 75315.7},
{-21, 71676.8},
{-20, 68236.7},
{-19, 64990.7},
{-18, 61919},
{-17, 59011.3},
{-16, 56257.9},
{-15, 53649.6},
{-14, 51177.9},
{-13, 48834.9},
{-12, 46613.2},
{-11, 44505.8},
{-10, 42506.2},
{-9, 40599.7},
{-8, 38790.5},
{-7, 37072.9},
{-6, 35441.7},
{-5, 33892.2},
{-4, 32419.7},
{-3, 31020},
{-2, 29689},
{-1, 28423.1},
{0, 27218.6},
{1, 26076},
{2, 24987.7},
{3, 23950.9},
{4, 22962.9},
{5, 22021.1},
{6, 21123},
{7, 20266.6},
{8, 19449.5},
{9, 18669.8},
{10, 17925.5},
{11, 17213.9},
{12, 16534.4},
{13, 15885.6},
{14, 15265.8},
{15, 14673.5},
{16, 14107.5},
{17, 13566.4},
{18, 13048.9},
{19, 12554},
{20, 12080.5},
{21, 11628.1},
{22, 11194.7},
{23, 10779.5},
{24, 10381.5},
{25, 10000},
{26, 9634.2},
{27, 9283.5},
{28, 8947},
{29, 8624.2},
{30, 8314.5},
{31, 8018.1},
{32, 7733.7},
{33, 7460.9},
{34, 7199.1},
{35, 6947.9},
{36, 6706.7},
{37, 6475.1},
{38, 6252.6},
{39, 6039},
{40, 5833.6},
{41, 5635.7},
{42, 5445.4},
{43, 5262.3},
{44, 5086.3},
{45, 4916.9},
{46, 4753.9},
{47, 4597.1},
{48, 4446.1},
{49, 4300.8},
{50, 4160.9},
{51, 4026.2},
{52, 3896.4},
{53, 3771.4},
{54, 3651},
{55, 3535},
{56, 3423.1},
{57, 3315.2},
{58, 3211.3},
{59, 3111},
{60, 3014.3},
{61, 2922.4},
{62, 2833.7},
{63, 2748.2},
{64, 2665.7},
{65, 2586.1},
{66, 2509.3},
{67, 2435.1},
{68, 2363.5},
{69, 2294.3},
{70, 2227.5},
{71, 2162.7},
{72, 2100.1},
{73, 2039.6},
{74, 1981.1},
{75, 1924.5},
{76, 1869.8},
{77, 1817},
{78, 1765.8},
{79, 1716.4},
{80, 1668.5},
{81, 1622.4},
{82, 1577.7},
{83, 1534.5},
{84, 1492.7},
{85, 1452.1},
{86, 1412.9},
{87, 1374.9},
{88, 1338.1},
{89, 1302.5},
{90, 1268},
{91, 1234.3},
{92, 1201.6},
{93, 1170},
{94, 1139.3},
{95, 1109.6},
{96, 1080.7},
{97, 1052.8},
{98, 1025.6},
{99, 999.3},
{100, 973.8},
{101, 949.2},
{102, 925.4},
{103, 902.2},
{104, 879.8},
{105, 858},
{106, 836.8},
{107, 816.2},
{108, 796.3},
{109, 776.9},
{110, 758},
{111, 739.7},
{112, 721.9},
{113, 704.6},
{114, 687.8},
{115, 671.5},
{116, 655.6},
{117, 640.2},
{118, 625.2},
{119, 610.6},
{120, 596.4},
{121, 582.6},
{122, 569.2},
{123, 556.2},
{124, 543.5},
{125, 531.1}
 };


double NXRT15XH103FA1B_get_temp(double resistance){
  //given resistance, use the table to find the temperature.
  double temp = 0;
  
  //find the first resistance value that is higher
  int i = 0;
  for(i = 0; i < NXRT15XH103FA1B_NUM_POINTS; i++)
  {
    if(NXRT15XH103FA1B_Resistance_Temperature_R_C[i][NXRT15XH103FA1B_R_INDEX] > resistance){
      break;
    }
  }

  //assume linear between the two values at [i] and [i-1]
  temp = map(resistance, NXRT15XH103FA1B_Resistance_Temperature_R_C[i][NXRT15XH103FA1B_R_INDEX],
                         NXRT15XH103FA1B_Resistance_Temperature_R_C[i-1][NXRT15XH103FA1B_R_INDEX],
                         NXRT15XH103FA1B_Resistance_Temperature_R_C[i][NXRT15XH103FA1B_T_INDEX],
                         NXRT15XH103FA1B_Resistance_Temperature_R_C[i-1][NXRT15XH103FA1B_T_INDEX]);
  
  return temp;
}

*/