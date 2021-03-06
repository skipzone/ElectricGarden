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
$Comp
L Device:Laserdiode_1A3C LD1
U 1 1 5E3E4766
P 2690 3080
F 0 "LD1" H 2640 3365 50  0000 C CNN
F 1 "Laserdiode_1A3C" H 2640 3274 50  0000 C CNN
F 2 "" H 2590 3055 50  0001 C CNN
F 3 "~" H 2720 2880 50  0001 C CNN
	1    2690 3080
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J1
U 1 1 5E3E5EEE
P 5060 2200
F 0 "J1" H 4730 2204 50  0000 R CNN
F 1 "RJ45" H 4730 2295 50  0000 R CNN
F 2 "" V 5060 2225 50  0001 C CNN
F 3 "~" V 5060 2225 50  0001 C CNN
	1    5060 2200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5E3E9A8A
P 2150 3080
F 0 "R1" V 1943 3080 50  0000 C CNN
F 1 "47" V 2034 3080 50  0000 C CNN
F 2 "" V 2080 3080 50  0001 C CNN
F 3 "~" H 2150 3080 50  0001 C CNN
	1    2150 3080
	0    1    1    0   
$EndComp
Wire Wire Line
	4660 2000 3230 2000
Wire Wire Line
	3230 2000 3230 2050
Wire Wire Line
	3230 2050 2590 2050
Text Label 3960 2000 0    50   ~ 0
orange_5v_unreg
Text Label 3880 1900 0    50   ~ 0
orange&white_GND
$Comp
L LIBRARY1:XL53L0X_POLOLU A1
U 1 1 5E3E38FE
P 2320 1850
F 0 "A1" H 2253 1975 50  0000 C CNN
F 1 "XL53L0X_POLOLU" H 2253 1884 50  0000 C CNN
F 2 "" H 2320 1850 50  0001 C CNN
F 3 "" H 2320 1850 50  0001 C CNN
	1    2320 1850
	1    0    0    -1  
$EndComp
Text Label 3930 2100 0    50   ~ 0
green&white_GND
Text Label 4180 2400 0    50   ~ 0
green_SDA
Wire Wire Line
	4660 2400 3170 2400
Wire Wire Line
	3170 2400 3170 2250
Wire Wire Line
	3170 2250 2520 2250
Wire Wire Line
	4660 2200 3320 2200
Wire Wire Line
	3320 2200 3320 2350
Wire Wire Line
	3320 2350 2520 2350
Text Label 4260 2200 0    50   ~ 0
blue_SCL
Wire Wire Line
	4660 2600 3080 2600
Wire Wire Line
	3080 2600 3080 2450
Wire Wire Line
	3080 2450 2520 2450
Text Label 4090 2600 0    50   ~ 0
brown_XSHUT
Text Label 3990 2300 0    50   ~ 0
blue&white_GND
Text Label 3930 2500 0    50   ~ 0
brown&white_GND
$Comp
L power:GND #PWR?
U 1 1 5E3F2EF4
P 1770 3080
F 0 "#PWR?" H 1770 2830 50  0001 C CNN
F 1 "GND" H 1775 2907 50  0000 C CNN
F 2 "" H 1770 3080 50  0001 C CNN
F 3 "" H 1770 3080 50  0001 C CNN
	1    1770 3080
	1    0    0    -1  
$EndComp
Wire Wire Line
	3030 3080 3030 2700
Wire Wire Line
	3030 2700 2590 2700
Wire Wire Line
	2590 2700 2590 2050
Connection ~ 2590 2050
Wire Wire Line
	2590 2050 2520 2050
Wire Wire Line
	2520 2150 2790 2150
$Comp
L power:GND #PWR?
U 1 1 5E3F4592
P 2790 2150
F 0 "#PWR?" H 2790 1900 50  0001 C CNN
F 1 "GND" V 2795 2022 50  0000 R CNN
F 2 "" H 2790 2150 50  0001 C CNN
F 3 "" H 2790 2150 50  0001 C CNN
	1    2790 2150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E3F56F3
P 3830 1900
F 0 "#PWR?" H 3830 1650 50  0001 C CNN
F 1 "GND" V 3835 1772 50  0000 R CNN
F 2 "" H 3830 1900 50  0001 C CNN
F 3 "" H 3830 1900 50  0001 C CNN
	1    3830 1900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E3F7418
P 3830 2100
F 0 "#PWR?" H 3830 1850 50  0001 C CNN
F 1 "GND" V 3835 1972 50  0000 R CNN
F 2 "" H 3830 2100 50  0001 C CNN
F 3 "" H 3830 2100 50  0001 C CNN
	1    3830 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E3F79BA
P 3840 2300
F 0 "#PWR?" H 3840 2050 50  0001 C CNN
F 1 "GND" V 3845 2172 50  0000 R CNN
F 2 "" H 3840 2300 50  0001 C CNN
F 3 "" H 3840 2300 50  0001 C CNN
	1    3840 2300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E3F80C8
P 3850 2500
F 0 "#PWR?" H 3850 2250 50  0001 C CNN
F 1 "GND" V 3855 2372 50  0000 R CNN
F 2 "" H 3850 2500 50  0001 C CNN
F 3 "" H 3850 2500 50  0001 C CNN
	1    3850 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	4660 1900 3830 1900
Wire Wire Line
	4660 2100 3830 2100
Wire Wire Line
	4660 2300 3840 2300
Wire Wire Line
	4660 2500 3850 2500
Wire Notes Line
	5140 1490 5140 3350
Wire Notes Line
	5140 3350 1490 3350
Wire Notes Line
	1490 3350 1490 1490
Wire Notes Line
	1490 1490 5140 1490
Text Label 7490 7510 0    79   ~ 0
TOF_Sensor_Module_with_Laser&RJ45
Text Label 8050 7310 0    79   ~ 0
dwgno._CFS-2-7-2020-A
Text Label 8270 7630 0    55   ~ 0
2-7-2020
Wire Wire Line
	2000 3080 1770 3080
Text Label 2270 3160 0    31   ~ 0
blue_wire_neg
Text Label 2780 3160 0    31   ~ 0
red_wire_pos
Wire Wire Line
	3030 3080 2890 3080
Wire Wire Line
	2390 3080 2300 3080
Text Label 10640 7630 0    55   ~ 0
1
Text Label 4520 7750 0    55   ~ 0
Rev._1_2-8-2020
Text Label 5360 7750 0    55   ~ 0
changed_resistor_location_&_size
$EndSCHEMATC
