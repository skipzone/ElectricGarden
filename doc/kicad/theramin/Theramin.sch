EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 7500 7510 0    79   ~ 0
THERAMIN
Text Label 8320 7510 0    79   ~ 0
JUMP-ELECTRIC_GARDEN
Text Label 8220 7650 0    71   ~ 0
1-21-2020
Text Label 10330 7510 0    71   ~ 0
by:_C.Spindler
$Comp
L LIBRARY1:XL53L0X_POLOLU A?
U 1 1 5E276D26
P 2060 1640
F 0 "A?" H 1993 1765 50  0000 C CNN
F 1 "XL53L0X_POLOLU" H 1993 1674 50  0000 C CNN
F 2 "" H 2060 1640 50  0001 C CNN
F 3 "" H 2060 1640 50  0001 C CNN
	1    2060 1640
	1    0    0    -1  
$EndComp
$Comp
L LIBRARY1:XL53L0X_POLOLU A?
U 1 1 5E278013
P 2080 2920
F 0 "A?" H 2013 3045 50  0000 C CNN
F 1 "XL53L0X_POLOLU" H 2013 2954 50  0000 C CNN
F 2 "" H 2080 2920 50  0001 C CNN
F 3 "" H 2080 2920 50  0001 C CNN
	1    2080 2920
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5E27AF5A
P 4950 3410
F 0 "A1" H 4950 2321 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 4410 4380 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4950 3410 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4950 3410 50  0001 C CNN
	1    4950 3410
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E27D115
P 2960 1940
F 0 "#PWR?" H 2960 1690 50  0001 C CNN
F 1 "GND" H 2970 1790 50  0000 C CNN
F 2 "" H 2960 1940 50  0001 C CNN
F 3 "" H 2960 1940 50  0001 C CNN
	1    2960 1940
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E27DC62
P 2960 3210
F 0 "#PWR?" H 2960 2960 50  0001 C CNN
F 1 "GND" H 2965 3037 50  0000 C CNN
F 2 "" H 2960 3210 50  0001 C CNN
F 3 "" H 2960 3210 50  0001 C CNN
	1    2960 3210
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E27E658
P 5050 4500
F 0 "#PWR?" H 5050 4250 50  0001 C CNN
F 1 "GND" H 5055 4327 50  0000 C CNN
F 2 "" H 5050 4500 50  0001 C CNN
F 3 "" H 5050 4500 50  0001 C CNN
	1    5050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2260 1940 2960 1940
Wire Wire Line
	2280 3220 2960 3220
Wire Wire Line
	2960 3220 2960 3210
Wire Wire Line
	5150 2410 5150 1840
Wire Wire Line
	2280 3120 3200 3120
Wire Wire Line
	3200 3120 3200 1840
Connection ~ 3200 1840
Wire Wire Line
	3200 1840 2260 1840
Wire Wire Line
	5450 3810 6010 3810
Wire Wire Line
	6010 3810 6010 2230
Wire Wire Line
	2740 2230 2740 2040
Wire Wire Line
	2740 2040 2260 2040
Wire Wire Line
	2280 3320 2740 3320
Wire Wire Line
	2740 3320 2740 2230
Connection ~ 2740 2230
Wire Wire Line
	5460 3910 6110 3910
Wire Wire Line
	6110 3910 6110 2140
Wire Wire Line
	2630 3420 2280 3420
Wire Wire Line
	2630 2140 2630 3420
Connection ~ 2630 2140
Wire Wire Line
	2630 2140 2260 2140
Wire Wire Line
	4450 3110 4100 3110
Wire Wire Line
	4100 3110 4100 2900
Wire Wire Line
	4100 2900 2530 2900
Wire Wire Line
	2530 2900 2530 2240
Wire Wire Line
	2530 2240 2260 2240
$Comp
L power:+5V #PWR?
U 1 1 5E28912B
P 4850 2410
F 0 "#PWR?" H 4850 2260 50  0001 C CNN
F 1 "+5V" H 4720 2490 50  0000 C CNN
F 2 "" H 4850 2410 50  0001 C CNN
F 3 "" H 4850 2410 50  0001 C CNN
	1    4850 2410
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4410 5050 4500
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 5E28C5E6
P 1390 4690
F 0 "J?" H 1308 4365 50  0000 C CNN
F 1 "Screw_Terminal" H 1308 4456 50  0000 C CNN
F 2 "" H 1390 4690 50  0001 C CNN
F 3 "~" H 1390 4690 50  0001 C CNN
	1    1390 4690
	-1   0    0    1   
$EndComp
Text Label 1280 4140 0    71   ~ 0
local
Text Label 1280 4270 0    71   ~ 0
speaker
$Comp
L Device:R R?
U 1 1 5E291B8C
P 5950 6260
F 0 "R?" V 5743 6260 50  0000 C CNN
F 1 "2k" V 5834 6260 50  0000 C CNN
F 2 "" V 5880 6260 50  0001 C CNN
F 3 "~" H 5950 6260 50  0001 C CNN
	1    5950 6260
	0    1    1    0   
$EndComp
$Comp
L Potentiometer_Digital:MCP42010 U?
U 1 1 5E295A97
P 5070 5960
F 0 "U?" H 5260 5490 50  0000 C CNN
F 1 "MCP4231_10k" H 4710 6450 50  0000 C CNN
F 2 "" H 5070 6060 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/11195c.pdf" H 5070 6060 50  0001 C CNN
	1    5070 5960
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1840 3400 1840
Wire Wire Line
	2740 2230 4000 2230
Wire Wire Line
	2630 2140 3400 2140
$Comp
L Device:R R?
U 1 1 5E27A478
P 3400 1990
F 0 "R?" H 3470 2036 50  0000 L CNN
F 1 "4k7" H 3470 1945 50  0000 L CNN
F 2 "" V 3330 1990 50  0001 C CNN
F 3 "~" H 3400 1990 50  0001 C CNN
	1    3400 1990
	1    0    0    -1  
$EndComp
Connection ~ 3400 1840
Wire Wire Line
	3400 1840 3700 1840
Connection ~ 3400 2140
Wire Wire Line
	3400 2140 6110 2140
$Comp
L Device:R R?
U 1 1 5E27A94F
P 3850 2000
F 0 "R?" V 3940 2020 50  0000 C CNN
F 1 "4k7" V 3734 2000 50  0000 C CNN
F 2 "" V 3780 2000 50  0001 C CNN
F 3 "~" H 3850 2000 50  0001 C CNN
	1    3850 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 2000 3700 1840
Connection ~ 3700 1840
Wire Wire Line
	3700 1840 5150 1840
Wire Wire Line
	4000 2000 4000 2230
Connection ~ 4000 2230
Wire Wire Line
	4000 2230 6010 2230
$Comp
L power:GND #PWR?
U 1 1 5E27983B
P 5070 6460
F 0 "#PWR?" H 5070 6210 50  0001 C CNN
F 1 "GND" H 5075 6287 50  0000 C CNN
F 2 "" H 5070 6460 50  0001 C CNN
F 3 "" H 5070 6460 50  0001 C CNN
	1    5070 6460
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Audio:PAM8302AAD U?
U 1 1 5E27B9DC
P 2670 5600
F 0 "U?" H 2860 5210 50  0000 C CNN
F 1 "PAM8302A" H 2380 5970 50  0000 C CNN
F 2 "" H 2670 5600 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/PAM8302A.pdf" H 2670 5600 50  0001 C CNN
	1    2670 5600
	1    0    0    -1  
$EndComp
Text Label 2100 6750 0    39   ~ 0
PAM8302A_inputs_have
Text Label 2100 6830 0    39   ~ 0
1.0uF_capacitors_inline.
Wire Wire Line
	6290 4860 6290 6260
Wire Wire Line
	6290 6260 6100 6260
Wire Wire Line
	5800 6260 5570 6260
Wire Wire Line
	5770 6160 5770 5000
Wire Wire Line
	5770 5000 2120 5000
Wire Wire Line
	2120 5000 2120 5400
Wire Wire Line
	2120 5400 2270 5400
$Comp
L power:GND #PWR?
U 1 1 5E283D06
P 2000 5600
F 0 "#PWR?" H 2000 5350 50  0001 C CNN
F 1 "GND" H 2005 5427 50  0000 C CNN
F 2 "" H 2000 5600 50  0001 C CNN
F 3 "" H 2000 5600 50  0001 C CNN
	1    2000 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E2868DF
P 2670 6000
F 0 "#PWR?" H 2670 5750 50  0001 C CNN
F 1 "GND" H 2675 5827 50  0000 C CNN
F 2 "" H 2670 6000 50  0001 C CNN
F 3 "" H 2670 6000 50  0001 C CNN
	1    2670 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E2874BA
P 2670 5200
F 0 "#PWR?" H 2670 5050 50  0001 C CNN
F 1 "+5V" H 2770 5320 50  0000 C CNN
F 2 "" H 2670 5200 50  0001 C CNN
F 3 "" H 2670 5200 50  0001 C CNN
	1    2670 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2270 5600 2000 5600
Wire Wire Line
	1590 4590 1890 4590
Wire Wire Line
	1890 4590 1890 6300
Wire Wire Line
	1890 6300 3320 6300
Wire Wire Line
	3320 6300 3320 5600
Wire Wire Line
	3320 5600 3070 5600
Wire Wire Line
	3070 5400 3430 5400
Wire Wire Line
	3430 5400 3430 6390
Wire Wire Line
	3430 6390 1800 6390
Wire Wire Line
	1800 6390 1800 4690
Wire Wire Line
	1800 4690 1590 4690
Wire Wire Line
	4450 3210 3100 3210
Wire Wire Line
	3100 3210 3100 3520
Wire Wire Line
	3100 3520 2280 3520
Wire Wire Line
	4450 3710 3690 3710
Wire Wire Line
	3690 3710 3690 4860
Wire Wire Line
	3690 4860 6290 4860
Wire Wire Line
	3550 3510 3550 5960
Wire Wire Line
	3550 3510 4450 3510
Wire Wire Line
	3550 5960 4230 5960
Wire Wire Line
	4450 3910 3800 3910
Wire Wire Line
	3800 3910 3800 5760
Wire Wire Line
	3800 5760 4570 5760
Wire Wire Line
	3940 4010 3940 5860
Wire Wire Line
	3940 5860 4570 5860
Wire Wire Line
	4450 4110 4080 4110
Wire Wire Line
	4080 4110 4080 5660
Wire Wire Line
	4080 5660 4570 5660
Wire Wire Line
	4450 4010 3940 4010
$Comp
L Device:R R?
U 1 1 5E29C82A
P 4230 6110
F 0 "R?" H 4300 6156 50  0000 L CNN
F 1 "5k1" H 4300 6065 50  0000 L CNN
F 2 "" V 4160 6110 50  0001 C CNN
F 3 "~" H 4230 6110 50  0001 C CNN
	1    4230 6110
	1    0    0    -1  
$EndComp
Connection ~ 4230 5960
Wire Wire Line
	4230 5960 4570 5960
$Comp
L Device:R R?
U 1 1 5E29E0AC
P 4440 6410
F 0 "R?" H 4510 6456 50  0000 L CNN
F 1 "5k1" H 4510 6365 50  0000 L CNN
F 2 "" V 4370 6410 50  0001 C CNN
F 3 "~" H 4440 6410 50  0001 C CNN
	1    4440 6410
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5E29EEC0
P 3900 6550
F 0 "#PWR?" H 3900 6400 50  0001 C CNN
F 1 "+5V" H 3915 6723 50  0000 C CNN
F 2 "" H 3900 6550 50  0001 C CNN
F 3 "" H 3900 6550 50  0001 C CNN
	1    3900 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 6560 3900 6550
Wire Wire Line
	4230 6260 4230 6560
Connection ~ 4230 6560
Wire Wire Line
	4230 6560 3900 6560
Wire Wire Line
	4440 6560 4230 6560
Wire Wire Line
	4570 6260 4440 6260
$Comp
L Amplifier_Operational:OPA333xxD U?
U 1 1 5E28DD28
P 8080 4020
F 0 "U?" H 8140 3860 50  0000 L CNN
F 1 "OPA333_?" H 8110 4180 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7980 3820 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa333.pdf" H 8230 4170 50  0001 C CNN
	1    8080 4020
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:OPA333xxD U?
U 1 1 5E291B8C
P 9350 4030
F 0 "U?" H 9460 3900 50  0000 L CNN
F 1 "OPA333_?" H 9380 4200 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9250 3830 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/opa333.pdf" H 9500 4180 50  0001 C CNN
	1    9350 4030
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E2935D3
P 7100 3850
F 0 "R?" H 7170 3896 50  0000 L CNN
F 1 "100k" H 6850 3850 50  0000 L CNN
F 2 "" V 7030 3850 50  0001 C CNN
F 3 "~" H 7100 3850 50  0001 C CNN
	1    7100 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E294ECF
P 7100 4150
F 0 "R?" H 7170 4196 50  0000 L CNN
F 1 "100k" H 6860 4160 50  0000 L CNN
F 2 "" V 7030 4150 50  0001 C CNN
F 3 "~" H 7100 4150 50  0001 C CNN
	1    7100 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E295DA8
P 8790 4840
F 0 "R?" H 8860 4886 50  0000 L CNN
F 1 "B" H 8860 4795 50  0000 L CNN
F 2 "" V 8720 4840 50  0001 C CNN
F 3 "~" H 8790 4840 50  0001 C CNN
	1    8790 4840
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E29670B
P 9390 4650
F 0 "R?" V 9490 4670 50  0000 C CNN
F 1 "A" V 9290 4650 50  0000 C CNN
F 2 "" V 9320 4650 50  0001 C CNN
F 3 "~" H 9390 4650 50  0001 C CNN
	1    9390 4650
	0    1    1    0   
$EndComp
$Comp
L Device:CP1 C?
U 1 1 5E2973F2
P 7400 4150
F 0 "C?" H 7515 4196 50  0000 L CNN
F 1 "100nF" H 7515 4105 50  0000 L CNN
F 2 "" H 7400 4150 50  0001 C CNN
F 3 "~" H 7400 4150 50  0001 C CNN
	1    7400 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 5E298E9A
P 10360 4030
F 0 "J?" H 10320 3760 50  0000 L CNN
F 1 "Screw_Terminal" H 10130 4220 50  0000 L CNN
F 2 "" H 10360 4030 50  0001 C CNN
F 3 "~" H 10360 4030 50  0001 C CNN
	1    10360 4030
	1    0    0    -1  
$EndComp
Text Label 10540 4050 0    50   ~ 0
out_to
Text Label 10540 4150 0    50   ~ 0
house_amplifier
$Comp
L power:+5V #PWR?
U 1 1 5E29AFCE
P 6810 3700
F 0 "#PWR?" H 6810 3550 50  0001 C CNN
F 1 "+5V" H 6825 3873 50  0000 C CNN
F 2 "" H 6810 3700 50  0001 C CNN
F 3 "" H 6810 3700 50  0001 C CNN
	1    6810 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E29BEA4
P 6790 4300
F 0 "#PWR?" H 6790 4050 50  0001 C CNN
F 1 "GND" H 6795 4127 50  0000 C CNN
F 2 "" H 6790 4300 50  0001 C CNN
F 3 "" H 6790 4300 50  0001 C CNN
	1    6790 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E29CC1F
P 10160 4330
F 0 "#PWR?" H 10160 4080 50  0001 C CNN
F 1 "GND" H 10165 4157 50  0000 C CNN
F 2 "" H 10160 4330 50  0001 C CNN
F 3 "" H 10160 4330 50  0001 C CNN
	1    10160 4330
	1    0    0    -1  
$EndComp
Wire Wire Line
	10160 4130 10160 4330
Wire Wire Line
	9650 4030 9860 4030
$Comp
L power:GND #PWR?
U 1 1 5E2A5182
P 9250 4330
F 0 "#PWR?" H 9250 4080 50  0001 C CNN
F 1 "GND" H 9180 4200 50  0000 C CNN
F 2 "" H 9250 4330 50  0001 C CNN
F 3 "" H 9250 4330 50  0001 C CNN
	1    9250 4330
	1    0    0    -1  
$EndComp
Wire Wire Line
	7780 3920 7400 3920
Wire Wire Line
	7400 3920 7400 4000
Wire Wire Line
	7400 4000 7100 4000
Connection ~ 7400 4000
Connection ~ 7100 4000
Wire Wire Line
	6810 3700 7100 3700
Wire Wire Line
	7100 3700 7980 3700
Wire Wire Line
	7980 3700 7980 3720
Connection ~ 7100 3700
Wire Wire Line
	7980 3700 9250 3700
Wire Wire Line
	9250 3700 9250 3730
Connection ~ 7980 3700
Wire Wire Line
	6790 4300 7100 4300
Wire Wire Line
	7100 4300 7400 4300
Connection ~ 7100 4300
Wire Wire Line
	7400 4300 7710 4300
Wire Wire Line
	7710 4300 7710 4320
Wire Wire Line
	7710 4320 7980 4320
Connection ~ 7400 4300
Wire Wire Line
	8380 4020 8440 4020
Wire Wire Line
	8560 4020 8560 4990
Wire Wire Line
	8560 4990 8790 4990
Wire Wire Line
	8790 4690 8790 4650
Wire Wire Line
	8790 4130 9050 4130
Wire Wire Line
	9240 4650 8790 4650
Connection ~ 8790 4650
Wire Wire Line
	8790 4650 8790 4130
Wire Wire Line
	9860 4030 9860 4650
Wire Wire Line
	9860 4650 9540 4650
Connection ~ 9860 4030
Wire Wire Line
	9860 4030 10160 4030
Wire Wire Line
	7780 4120 7780 4480
Wire Wire Line
	7780 4480 8440 4480
Wire Wire Line
	8440 4480 8440 4020
Connection ~ 8440 4020
Wire Wire Line
	8440 4020 8560 4020
Text Label 8580 5180 0    50   ~ 0
gain_equals_one_plus_A_divided_by_B
Wire Wire Line
	9050 3930 9050 3400
Wire Wire Line
	9050 3400 6510 3400
Wire Wire Line
	6510 3400 6510 5000
$Comp
L power:GND #PWR?
U 1 1 5E2C11E6
P 5570 6060
F 0 "#PWR?" H 5570 5810 50  0001 C CNN
F 1 "GND" V 5660 6040 50  0000 R CNN
F 2 "" H 5570 6060 50  0001 C CNN
F 3 "" H 5570 6060 50  0001 C CNN
	1    5570 6060
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5570 6160 5770 6160
Text Label 2730 5180 0    50   ~ 0
unregulated
Text Label 4660 2300 0    50   ~ 0
unregulated
Text Label 9480 7310 0    79   ~ 0
DwgNo_CFS-1-24-2020-A
Wire Wire Line
	5150 1840 6240 1840
Wire Wire Line
	6240 1840 6240 4760
Wire Wire Line
	6240 4760 5070 4760
Wire Wire Line
	5070 4760 5070 5460
Connection ~ 5150 1840
$EndSCHEMATC
