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
Text Label 1900 1875 2    50   ~ 0
MCU_KAM_ON_2
Text Label 1900 1375 2    50   ~ 0
MCU_KAM_ON_1
Text Label 1900 1975 2    50   ~ 0
MCU_KAM_START_2
Text Label 1900 1475 2    50   ~ 0
MCU_KAM_START_1
Text Label 1900 1575 2    50   ~ 0
MCU_KAM_OK_1
Text Label 1900 2075 2    50   ~ 0
MCU_KAM_OK_2
$Comp
L Borta-Dators-rescue:Screw_Terminal_01x06-Connector J1
U 1 1 5F877230
P 2325 4875
F 0 "J1" H 2243 4350 50  0000 C CNN
F 1 "ST_LINK" H 2243 4441 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 2325 4875 50  0001 C CNN
F 3 "~" H 2325 4875 50  0001 C CNN
	1    2325 4875
	-1   0    0    1   
$EndComp
Wire Wire Line
	2525 5075 2625 5075
Text Label 2675 4975 0    50   ~ 0
SWCLK
Wire Wire Line
	2675 4975 2525 4975
Wire Wire Line
	2675 4875 2525 4875
Text Label 2675 4775 0    50   ~ 0
SWDIO
Text Label 2675 4675 0    50   ~ 0
NRST
Wire Wire Line
	2675 4675 2525 4675
Wire Wire Line
	2675 4775 2525 4775
NoConn ~ 2525 4575
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR02
U 1 1 5FDD4504
P 2625 5075
F 0 "#PWR02" H 2625 4925 50  0001 C CNN
F 1 "+3.3V" V 2640 5203 50  0000 L CNN
F 2 "" H 2625 5075 50  0001 C CNN
F 3 "" H 2625 5075 50  0001 C CNN
	1    2625 5075
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR0107
U 1 1 6158D9D9
P 2675 4875
F 0 "#PWR0107" H 2675 4625 50  0001 C CNN
F 1 "GND" V 2680 4747 50  0000 R CNN
F 2 "" H 2675 4875 50  0001 C CNN
F 3 "" H 2675 4875 50  0001 C CNN
	1    2675 4875
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1900 1775 2050 1775
Wire Wire Line
	2550 1975 2700 1975
Wire Wire Line
	2700 1775 2550 1775
Text Label 1900 1675 2    50   ~ 0
TX_KOP
Text Label 1900 1775 2    50   ~ 0
RX_KOP
Wire Wire Line
	2050 1675 1900 1675
$Comp
L Borta-Dators-rescue:GND-power #PWR050
U 1 1 60098A79
P 1900 2275
F 0 "#PWR050" H 1900 2025 50  0001 C CNN
F 1 "GND" V 1905 2147 50  0000 R CNN
F 2 "" H 1900 2275 50  0001 C CNN
F 3 "" H 1900 2275 50  0001 C CNN
	1    1900 2275
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 1675 2550 1675
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR0108
U 1 1 615E13A9
P 1900 2175
F 0 "#PWR0108" H 1900 2025 50  0001 C CNN
F 1 "+3.3V" V 1900 2400 50  0000 C CNN
F 2 "" H 1900 2175 50  0001 C CNN
F 3 "" H 1900 2175 50  0001 C CNN
	1    1900 2175
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:+4V-power #PWR0109
U 1 1 615E2E5F
P 1900 1275
F 0 "#PWR0109" H 1900 1125 50  0001 C CNN
F 1 "+4V" V 1900 1425 50  0000 L CNN
F 2 "" H 1900 1275 50  0001 C CNN
F 3 "" H 1900 1275 50  0001 C CNN
	1    1900 1275
	0    -1   -1   0   
$EndComp
Text Label 2700 1975 0    50   ~ 0
SCL1_KOP
Text Label 2700 1775 0    50   ~ 0
SDA1_KOP
$Comp
L Borta-Dators-rescue:GND-power #PWR049
U 1 1 600253F6
P 1900 1175
F 0 "#PWR049" H 1900 925 50  0001 C CNN
F 1 "GND" V 1905 1047 50  0000 R CNN
F 2 "" H 1900 1175 50  0001 C CNN
F 3 "" H 1900 1175 50  0001 C CNN
	1    1900 1175
	0    1    1    0   
$EndComp
NoConn ~ 5800 1650
NoConn ~ 5800 2350
Wire Wire Line
	7500 2550 7500 2700
$Comp
L Borta-Dators-rescue:Micro_SD_Card-Connector J2
U 1 1 5F7727AD
P 6700 1950
F 0 "J2" H 6650 2667 50  0000 C CNN
F 1 "Micro_SD_Card" H 6650 2576 50  0000 C CNN
F 2 "Borta_Dators:Micro_SD" H 7850 2250 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 6700 1950 50  0001 C CNN
	1    6700 1950
	1    0    0    -1  
$EndComp
Text Label 5525 1850 2    50   ~ 0
MOSI
Text Label 5525 2050 2    50   ~ 0
CLK
Text Label 5525 2250 2    50   ~ 0
MISO
Text Label 4350 3325 2    50   ~ 0
SWDIO
Text Label 4350 3225 2    50   ~ 0
SWCLK
Text Label 5950 3725 0    50   ~ 0
MCU_KAM_ON_1
Text Label 5950 3625 0    50   ~ 0
MCU_KAM_ON_2
Wire Wire Line
	5950 3425 5800 3425
Wire Wire Line
	5800 3325 5950 3325
Wire Wire Line
	5950 3525 5800 3525
Wire Wire Line
	5800 3625 5950 3625
Wire Wire Line
	4350 3325 4500 3325
Wire Wire Line
	4500 3225 4350 3225
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR011
U 1 1 5FDC4839
P 5800 1950
F 0 "#PWR011" H 5800 1800 50  0001 C CNN
F 1 "+3.3V" V 5815 2078 50  0000 L CNN
F 2 "" H 5800 1950 50  0001 C CNN
F 3 "" H 5800 1950 50  0001 C CNN
	1    5800 1950
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR0110
U 1 1 6158F026
P 7500 2700
F 0 "#PWR0110" H 7500 2450 50  0001 C CNN
F 1 "GND" V 7505 2572 50  0000 R CNN
F 2 "" H 7500 2700 50  0001 C CNN
F 3 "" H 7500 2700 50  0001 C CNN
	1    7500 2700
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR0111
U 1 1 6158F96D
P 5800 2150
F 0 "#PWR0111" H 5800 1900 50  0001 C CNN
F 1 "GND" V 5805 2022 50  0000 R CNN
F 2 "" H 5800 2150 50  0001 C CNN
F 3 "" H 5800 2150 50  0001 C CNN
	1    5800 2150
	0    1    1    0   
$EndComp
Text Label 5950 4125 0    50   ~ 0
MCU_KAM_START_1
Text Label 5950 4025 0    50   ~ 0
MCU_KAM_START_2
Text Label 5950 4425 0    50   ~ 0
MCU_KAM_OK_1
Text Label 5950 4325 0    50   ~ 0
MCU_KAM_OK_2
Wire Wire Line
	5800 3125 5950 3125
$Comp
L Borta-Dators-rescue:STM32F401CEUx-MCU_ST_STM32F4 U3
U 1 1 61740DA2
P 5100 4525
F 0 "U3" H 5500 2925 50  0000 C CNN
F 1 "STM32F401CEUx" H 4525 2925 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-48-1EP_7x7mm_P0.5mm_EP5.6x5.6mm" H 4500 3025 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00102166.pdf" H 5100 4525 50  0001 C CNN
	1    5100 4525
	-1   0    0    1   
$EndComp
$Comp
L Borta-Dators-rescue:C-Device C4
U 1 1 5F8F88FC
P 6450 6125
F 0 "C4" V 6575 6225 50  0000 C CNN
F 1 "100nF" V 6575 6025 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6488 5975 50  0001 C CNN
F 3 "~" H 6450 6125 50  0001 C CNN
	1    6450 6125
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:SW_Push-Switch SW3
U 1 1 5F8B0397
P 6450 5925
F 0 "SW3" H 6475 6175 50  0000 C CNN
F 1 "SW_Push" H 6500 6100 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_EVQQ2" H 6450 6125 50  0001 C CNN
F 3 "~" H 6450 6125 50  0001 C CNN
	1    6450 5925
	1    0    0    -1  
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR0112
U 1 1 617504DF
P 6675 6000
F 0 "#PWR0112" H 6675 5750 50  0001 C CNN
F 1 "GND" V 6680 5872 50  0000 R CNN
F 2 "" H 6675 6000 50  0001 C CNN
F 3 "" H 6675 6000 50  0001 C CNN
	1    6675 6000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 5925 6025 5925
Wire Wire Line
	6025 5925 6250 5925
Connection ~ 6025 5925
$Comp
L Borta-Dators-rescue:GND-power #PWR0113
U 1 1 617575A4
P 5100 2875
F 0 "#PWR0113" H 5100 2625 50  0001 C CNN
F 1 "GND" V 5105 2747 50  0000 R CNN
F 2 "" H 5100 2875 50  0001 C CNN
F 3 "" H 5100 2875 50  0001 C CNN
	1    5100 2875
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 2925 4900 2875
Wire Wire Line
	4900 2875 5000 2875
Wire Wire Line
	5300 2875 5300 2925
Wire Wire Line
	5000 2925 5000 2875
Connection ~ 5000 2875
Wire Wire Line
	5000 2875 5100 2875
Wire Wire Line
	5100 2925 5100 2875
Connection ~ 5100 2875
Wire Wire Line
	5100 2875 5200 2875
Connection ~ 5200 2875
Wire Wire Line
	5200 2875 5300 2875
Wire Wire Line
	5000 6125 5000 6200
Wire Wire Line
	5000 6200 5100 6200
Wire Wire Line
	5300 6200 5300 6125
Wire Wire Line
	5200 6125 5200 6200
Connection ~ 5200 6200
Wire Wire Line
	5200 6200 5300 6200
Wire Wire Line
	5100 6125 5100 6200
Connection ~ 5100 6200
Wire Wire Line
	5100 6200 5200 6200
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR0114
U 1 1 61776E09
P 5200 6200
F 0 "#PWR0114" H 5200 6050 50  0001 C CNN
F 1 "+3.3V" H 5215 6373 50  0000 C CNN
F 2 "" H 5200 6200 50  0001 C CNN
F 3 "" H 5200 6200 50  0001 C CNN
	1    5200 6200
	-1   0    0    1   
$EndComp
$Comp
L Borta-Dators-rescue:C-Device C1
U 1 1 6177818F
P 4725 6200
F 0 "C1" V 4975 6200 50  0000 C CNN
F 1 "100nF" V 4875 6150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4763 6050 50  0001 C CNN
F 3 "~" H 4725 6200 50  0001 C CNN
	1    4725 6200
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR0115
U 1 1 61778C5D
P 4450 6200
F 0 "#PWR0115" H 4450 5950 50  0001 C CNN
F 1 "GND" V 4455 6072 50  0000 R CNN
F 2 "" H 4450 6200 50  0001 C CNN
F 3 "" H 4450 6200 50  0001 C CNN
	1    4450 6200
	0    1    1    0   
$EndComp
Wire Wire Line
	4875 6200 5000 6200
Connection ~ 5000 6200
Wire Wire Line
	4450 6200 4575 6200
Text Label 2625 5700 0    50   ~ 0
RX_BLUETOOTH
Text Label 2625 5600 0    50   ~ 0
TX_BLUETOOTH
$Comp
L Borta-Dators-rescue:GND-power #PWR0116
U 1 1 615DFE2F
P 2525 5500
F 0 "#PWR0116" H 2525 5250 50  0001 C CNN
F 1 "GND" V 2525 5350 50  0000 R CNN
F 2 "" H 2525 5500 50  0001 C CNN
F 3 "" H 2525 5500 50  0001 C CNN
	1    2525 5500
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:+4V-power #PWR0117
U 1 1 615E3DC2
P 2850 5400
F 0 "#PWR0117" H 2850 5250 50  0001 C CNN
F 1 "+4V" V 2850 5600 50  0000 C CNN
F 2 "" H 2850 5400 50  0001 C CNN
F 3 "" H 2850 5400 50  0001 C CNN
	1    2850 5400
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:Screw_Terminal_01x04-Connector J6
U 1 1 61732713
P 2325 5600
F 0 "J6" H 2243 5175 50  0000 C CNN
F 1 "bluetooth" H 2243 5266 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 2325 5600 50  0001 C CNN
F 3 "~" H 2325 5600 50  0001 C CNN
	1    2325 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2525 5600 2625 5600
Wire Wire Line
	2525 5700 2625 5700
Text Label 4350 3725 2    50   ~ 0
TX_BLUETOOTH
Text Label 4350 3625 2    50   ~ 0
RX_BLUETOOTH
Wire Wire Line
	6025 6125 6300 6125
Wire Wire Line
	6025 5925 6025 6125
Wire Wire Line
	6600 6125 6675 6125
Wire Wire Line
	6675 6125 6675 6000
Wire Wire Line
	6675 5925 6650 5925
Connection ~ 6675 6000
Wire Wire Line
	6675 6000 6675 5925
$Comp
L Borta-Dators-rescue:R_Small-Device R1
U 1 1 6180732A
P 6025 6300
F 0 "R1" H 6084 6346 50  0000 L CNN
F 1 "10k" H 6084 6255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6025 6300 50  0001 C CNN
F 3 "~" H 6025 6300 50  0001 C CNN
	1    6025 6300
	1    0    0    -1  
$EndComp
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR0118
U 1 1 61807BDD
P 6025 6450
F 0 "#PWR0118" H 6025 6300 50  0001 C CNN
F 1 "+3.3V" H 6040 6623 50  0000 C CNN
F 2 "" H 6025 6450 50  0001 C CNN
F 3 "" H 6025 6450 50  0001 C CNN
	1    6025 6450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6025 6125 6025 6200
Connection ~ 6025 6125
Wire Wire Line
	6025 6400 6025 6450
Text Label 4350 4425 2    50   ~ 0
TX_KOP
Text Label 4350 4325 2    50   ~ 0
RX_KOP
Text Label 5950 3925 0    50   ~ 0
SCL1_KOP
Text Label 5950 3825 0    50   ~ 0
SDA1_KOP
Text Label 6025 6050 2    50   ~ 0
NRST
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR04
U 1 1 6170BFE6
P 5800 5425
F 0 "#PWR04" H 5800 5275 50  0001 C CNN
F 1 "+3.3V" V 5825 5625 50  0000 C CNN
F 2 "" H 5800 5425 50  0001 C CNN
F 3 "" H 5800 5425 50  0001 C CNN
	1    5800 5425
	0    1    1    0   
$EndComp
Text Label 2700 1875 0    50   ~ 0
SDA2_KOP
Text Label 2700 2075 0    50   ~ 0
SCL2_KOP
Wire Wire Line
	2700 2075 2550 2075
Wire Wire Line
	2700 1875 2550 1875
Text Label 2700 1375 0    50   ~ 0
BUS_CONTROL1
Text Label 2700 1475 0    50   ~ 0
BUS_CONTROL2
Text Label 4350 3925 2    50   ~ 0
MOSI
Text Label 4350 4025 2    50   ~ 0
MISO
Text Label 4350 4125 2    50   ~ 0
CLK
Text Label 5525 1750 2    50   ~ 0
NSS
Text Label 4350 4225 2    50   ~ 0
NSS
Text Label 5950 4225 0    50   ~ 0
SDA2_KOP
Text Label 5950 3525 0    50   ~ 0
SCL2_KOP
Wire Wire Line
	5950 3725 5800 3725
$Comp
L Borta-Dators-rescue:LED_Small-Device D4
U 1 1 6174C705
P 6725 3125
F 0 "D4" H 6625 3075 50  0000 C CNN
F 1 "LED_Small" H 6950 3075 50  0000 C CNN
F 2 "Diode_SMD:D_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6725 3125 50  0001 C CNN
F 3 "~" V 6725 3125 50  0001 C CNN
	1    6725 3125
	-1   0    0    1   
$EndComp
$Comp
L Borta-Dators-rescue:LED_Small-Device D3
U 1 1 6174A8C6
P 6725 3425
F 0 "D3" H 6625 3375 50  0000 C CNN
F 1 "LED_Small" H 6950 3375 50  0000 C CNN
F 2 "Diode_SMD:D_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6725 3425 50  0001 C CNN
F 3 "~" V 6725 3425 50  0001 C CNN
	1    6725 3425
	-1   0    0    1   
$EndComp
$Comp
L Borta-Dators-rescue:LED_Small-Device D5
U 1 1 6174AFA2
P 6725 3325
F 0 "D5" H 6625 3275 50  0000 C CNN
F 1 "LED_Small" H 6950 3275 50  0000 C CNN
F 2 "Diode_SMD:D_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6725 3325 50  0001 C CNN
F 3 "~" V 6725 3325 50  0001 C CNN
	1    6725 3325
	-1   0    0    1   
$EndComp
$Comp
L Borta-Dators-rescue:R_Small-Device R3
U 1 1 61762865
P 6050 3125
F 0 "R3" V 6100 3250 50  0000 C CNN
F 1 "150" V 6100 2975 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6050 3125 50  0001 C CNN
F 3 "~" H 6050 3125 50  0001 C CNN
	1    6050 3125
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:R_Small-Device R5
U 1 1 61764589
P 6050 3325
F 0 "R5" V 6100 3450 50  0000 C CNN
F 1 "150" V 6100 3175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6050 3325 50  0001 C CNN
F 3 "~" H 6050 3325 50  0001 C CNN
	1    6050 3325
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:R_Small-Device R6
U 1 1 6176490C
P 6050 3425
F 0 "R6" V 6100 3550 50  0000 C CNN
F 1 "150" V 6100 3275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6050 3425 50  0001 C CNN
F 3 "~" H 6050 3425 50  0001 C CNN
	1    6050 3425
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:C_Small-Device C2
U 1 1 6178A15F
P 6425 5525
F 0 "C2" V 6325 5450 50  0000 C CNN
F 1 "4.7uF" V 6325 5650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6425 5525 50  0001 C CNN
F 3 "~" H 6425 5525 50  0001 C CNN
	1    6425 5525
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:R_Small-Device R2
U 1 1 6178B646
P 5975 5725
F 0 "R2" V 6050 5800 50  0000 C CNN
F 1 "1k" V 6050 5650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 5975 5725 50  0001 C CNN
F 3 "~" H 5975 5725 50  0001 C CNN
	1    5975 5725
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR06
U 1 1 61793A34
P 6575 5525
F 0 "#PWR06" H 6575 5275 50  0001 C CNN
F 1 "GND" V 6580 5397 50  0000 R CNN
F 2 "" H 6575 5525 50  0001 C CNN
F 3 "" H 6575 5525 50  0001 C CNN
	1    6575 5525
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR05
U 1 1 6179401F
P 6125 5725
F 0 "#PWR05" H 6125 5475 50  0001 C CNN
F 1 "GND" V 6175 5625 50  0000 R CNN
F 2 "" H 6125 5725 50  0001 C CNN
F 3 "" H 6125 5725 50  0001 C CNN
	1    6125 5725
	0    -1   -1   0   
$EndComp
NoConn ~ 5800 5125
NoConn ~ 5800 5225
Wire Wire Line
	5800 1750 5525 1750
Wire Wire Line
	5800 1850 5525 1850
Wire Wire Line
	5800 2050 5525 2050
Wire Wire Line
	5800 2250 5525 2250
Wire Wire Line
	4350 3625 4500 3625
Wire Wire Line
	4350 3725 4500 3725
Wire Wire Line
	4500 4025 4350 4025
Wire Wire Line
	4500 3925 4350 3925
Wire Wire Line
	4350 4525 4500 4525
Wire Wire Line
	4350 4425 4500 4425
Wire Wire Line
	4350 4325 4500 4325
Wire Wire Line
	4350 4225 4500 4225
Wire Wire Line
	4350 4125 4500 4125
Wire Wire Line
	5950 3925 5800 3925
Wire Wire Line
	5950 3825 5800 3825
Wire Wire Line
	5800 4225 5950 4225
Wire Wire Line
	6125 5725 6075 5725
Wire Wire Line
	5875 5725 5800 5725
NoConn ~ 4500 4625
NoConn ~ 5800 4925
NoConn ~ 5800 4825
NoConn ~ 5800 4725
$Comp
L Borta-Dators-rescue:PWR_FLAG-power #FLG0101
U 1 1 6188FF1D
P 5300 6200
F 0 "#FLG0101" H 5300 6275 50  0001 C CNN
F 1 "PWR_FLAG" V 5300 6328 50  0000 L CNN
F 2 "" H 5300 6200 50  0001 C CNN
F 3 "~" H 5300 6200 50  0001 C CNN
	1    5300 6200
	0    1    1    0   
$EndComp
Connection ~ 5300 6200
$Comp
L Borta-Dators-rescue:PWR_FLAG-power #FLG0102
U 1 1 6189791E
P 6675 6125
F 0 "#FLG0102" H 6675 6200 50  0001 C CNN
F 1 "PWR_FLAG" V 6675 6253 50  0000 L CNN
F 2 "" H 6675 6125 50  0001 C CNN
F 3 "~" H 6675 6125 50  0001 C CNN
	1    6675 6125
	0    1    1    0   
$EndComp
Connection ~ 6675 6125
$Comp
L Borta-Dators-rescue:PWR_FLAG-power #FLG0103
U 1 1 61898776
P 2775 5400
F 0 "#FLG0103" H 2775 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 2775 5573 50  0000 C CNN
F 2 "" H 2775 5400 50  0001 C CNN
F 3 "~" H 2775 5400 50  0001 C CNN
	1    2775 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2525 5400 2775 5400
Connection ~ 2775 5400
Wire Wire Line
	2775 5400 2850 5400
$Comp
L Borta-Dators-rescue:PWR_FLAG-power #FLG0104
U 1 1 618A00E0
P 6225 5525
F 0 "#FLG0104" H 6225 5600 50  0001 C CNN
F 1 "PWR_FLAG" H 6225 5698 50  0000 C CNN
F 2 "" H 6225 5525 50  0001 C CNN
F 3 "~" H 6225 5525 50  0001 C CNN
	1    6225 5525
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2875 5200 2925
Wire Wire Line
	5800 5525 6225 5525
Connection ~ 6225 5525
Wire Wire Line
	6225 5525 6325 5525
Wire Wire Line
	6525 5525 6575 5525
Text Label 4350 3525 2    50   ~ 0
BUS_CONTROL1
Text Label 4350 3425 2    50   ~ 0
BUS_CONTROL2
Wire Wire Line
	4500 3425 4350 3425
Wire Wire Line
	4500 3525 4350 3525
Wire Wire Line
	6150 3125 6625 3125
Wire Wire Line
	6825 3125 6925 3125
Wire Wire Line
	6925 3125 6925 3225
Wire Wire Line
	6150 3425 6625 3425
Wire Wire Line
	6150 3325 6625 3325
Wire Wire Line
	6825 3325 6925 3325
Wire Wire Line
	6825 3425 6925 3425
Wire Wire Line
	6925 3325 6925 3425
Wire Wire Line
	6925 3425 6925 3525
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP1
U 1 1 617BD080
P 7875 3150
F 0 "TP1" V 7829 3338 50  0000 L CNN
F 1 "+4V" V 7920 3338 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 3150 50  0001 C CNN
F 3 "~" H 8075 3150 50  0001 C CNN
	1    7875 3150
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP2
U 1 1 617BF0DF
P 7875 3325
F 0 "TP2" V 7829 3513 50  0000 L CNN
F 1 "+3.3V" V 7920 3513 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 3325 50  0001 C CNN
F 3 "~" H 8075 3325 50  0001 C CNN
	1    7875 3325
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP3
U 1 1 617BF3CE
P 7875 3500
F 0 "TP3" V 7829 3688 50  0000 L CNN
F 1 "BUS_CONTROL1" V 7920 3688 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 3500 50  0001 C CNN
F 3 "~" H 8075 3500 50  0001 C CNN
	1    7875 3500
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP4
U 1 1 617BF705
P 7875 3675
F 0 "TP4" V 7829 3863 50  0000 L CNN
F 1 "BUS_CONTROL2" V 7920 3863 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 3675 50  0001 C CNN
F 3 "~" H 8075 3675 50  0001 C CNN
	1    7875 3675
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP16
U 1 1 617BF9A0
P 7875 5775
F 0 "TP16" V 7829 5963 50  0000 L CNN
F 1 "GND" V 7920 5963 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5775 50  0001 C CNN
F 3 "~" H 8075 5775 50  0001 C CNN
	1    7875 5775
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP5
U 1 1 617BFD19
P 7875 3850
F 0 "TP5" V 7829 4038 50  0000 L CNN
F 1 "SDA1_I2C" V 7920 4038 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 3850 50  0001 C CNN
F 3 "~" H 8075 3850 50  0001 C CNN
	1    7875 3850
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP6
U 1 1 617C0045
P 7875 4025
F 0 "TP6" V 7829 4213 50  0000 L CNN
F 1 "SCL1_I2C" V 7920 4213 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4025 50  0001 C CNN
F 3 "~" H 8075 4025 50  0001 C CNN
	1    7875 4025
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP7
U 1 1 617C05CA
P 7875 4200
F 0 "TP7" V 7829 4388 50  0000 L CNN
F 1 "RX_UART" V 7920 4388 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4200 50  0001 C CNN
F 3 "~" H 8075 4200 50  0001 C CNN
	1    7875 4200
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP8
U 1 1 617C0A7A
P 7875 4375
F 0 "TP8" V 7829 4563 50  0000 L CNN
F 1 "TX_UART" V 7920 4563 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4375 50  0001 C CNN
F 3 "~" H 8075 4375 50  0001 C CNN
	1    7875 4375
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP9
U 1 1 617C0CBF
P 7875 4550
F 0 "TP9" V 7829 4738 50  0000 L CNN
F 1 "CUT_CONTROL" V 7920 4738 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4550 50  0001 C CNN
F 3 "~" H 8075 4550 50  0001 C CNN
	1    7875 4550
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP10
U 1 1 617C1062
P 7875 4725
F 0 "TP10" V 7829 4913 50  0000 L CNN
F 1 "SDA2_I2C" V 7920 4913 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4725 50  0001 C CNN
F 3 "~" H 8075 4725 50  0001 C CNN
	1    7875 4725
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP11
U 1 1 617C1326
P 7875 4900
F 0 "TP11" V 7829 5088 50  0000 L CNN
F 1 "SCL2_I2C" V 7920 5088 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 4900 50  0001 C CNN
F 3 "~" H 8075 4900 50  0001 C CNN
	1    7875 4900
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP12
U 1 1 617C2DC9
P 7875 5075
F 0 "TP12" V 7829 5263 50  0000 L CNN
F 1 "NSS_SPI" V 7920 5263 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5075 50  0001 C CNN
F 3 "~" H 8075 5075 50  0001 C CNN
	1    7875 5075
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP13
U 1 1 617C3050
P 7875 5250
F 0 "TP13" V 7829 5438 50  0000 L CNN
F 1 "MOSI_SPI" V 7920 5438 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5250 50  0001 C CNN
F 3 "~" H 8075 5250 50  0001 C CNN
	1    7875 5250
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP14
U 1 1 617C33AE
P 7875 5425
F 0 "TP14" V 7829 5613 50  0000 L CNN
F 1 "CLK_SPI" V 7920 5613 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5425 50  0001 C CNN
F 3 "~" H 8075 5425 50  0001 C CNN
	1    7875 5425
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:+4V-power #PWR08
U 1 1 617C3B18
P 7875 3150
F 0 "#PWR08" H 7875 3000 50  0001 C CNN
F 1 "+4V" V 7875 3300 50  0000 L CNN
F 2 "" H 7875 3150 50  0001 C CNN
F 3 "" H 7875 3150 50  0001 C CNN
	1    7875 3150
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR09
U 1 1 617C5753
P 7875 3325
F 0 "#PWR09" H 7875 3175 50  0001 C CNN
F 1 "+3.3V" V 7875 3550 50  0000 C CNN
F 2 "" H 7875 3325 50  0001 C CNN
F 3 "" H 7875 3325 50  0001 C CNN
	1    7875 3325
	0    -1   -1   0   
$EndComp
Text Label 7875 3500 2    50   ~ 0
BUS_CONTROL1
Text Label 7875 3675 2    50   ~ 0
BUS_CONTROL2
$Comp
L Borta-Dators-rescue:GND-power #PWR010
U 1 1 617C695A
P 7875 5775
F 0 "#PWR010" H 7875 5525 50  0001 C CNN
F 1 "GND" V 7880 5647 50  0000 R CNN
F 2 "" H 7875 5775 50  0001 C CNN
F 3 "" H 7875 5775 50  0001 C CNN
	1    7875 5775
	0    1    1    0   
$EndComp
Text Label 7875 3850 2    50   ~ 0
SDA1_KOP
Text Label 7875 4025 2    50   ~ 0
SCL1_KOP
Text Label 7875 4200 2    50   ~ 0
RX_KOP
Text Label 7875 4375 2    50   ~ 0
TX_KOP
Text Label 7875 4725 2    50   ~ 0
SDA2_KOP
Text Label 7875 4900 2    50   ~ 0
SCL2_KOP
Text Label 7875 5075 2    50   ~ 0
NSS
Text Label 7875 5250 2    50   ~ 0
MOSI
Text Label 7875 5425 2    50   ~ 0
CLK
Text Label 7875 5600 2    50   ~ 0
MISO
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP17
U 1 1 617E09C0
P 7875 5950
F 0 "TP17" V 7829 6138 50  0000 L CNN
F 1 "GND" V 7920 6138 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5950 50  0001 C CNN
F 3 "~" H 8075 5950 50  0001 C CNN
	1    7875 5950
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP18
U 1 1 617E0E3C
P 7875 6125
F 0 "TP18" V 7829 6313 50  0000 L CNN
F 1 "GND" V 7920 6313 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 6125 50  0001 C CNN
F 3 "~" H 8075 6125 50  0001 C CNN
	1    7875 6125
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR012
U 1 1 617E1C96
P 7875 5950
F 0 "#PWR012" H 7875 5700 50  0001 C CNN
F 1 "GND" V 7880 5822 50  0000 R CNN
F 2 "" H 7875 5950 50  0001 C CNN
F 3 "" H 7875 5950 50  0001 C CNN
	1    7875 5950
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR013
U 1 1 617E203D
P 7875 6125
F 0 "#PWR013" H 7875 5875 50  0001 C CNN
F 1 "GND" V 7880 5997 50  0000 R CNN
F 2 "" H 7875 6125 50  0001 C CNN
F 3 "" H 7875 6125 50  0001 C CNN
	1    7875 6125
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 1175 2050 1175
Wire Wire Line
	2050 1275 1900 1275
Wire Wire Line
	1900 2175 2050 2175
Wire Wire Line
	1900 2275 2050 2275
$Comp
L Borta-Dators-rescue:TestPoint-Connector TP15
U 1 1 617C36D3
P 7875 5600
F 0 "TP15" V 7829 5788 50  0000 L CNN
F 1 "MISO_SPI" V 7920 5788 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8075 5600 50  0001 C CNN
F 3 "~" H 8075 5600 50  0001 C CNN
	1    7875 5600
	0    1    1    0   
$EndComp
Text Label 7875 4550 2    50   ~ 0
CUT_CONTROL
Text Label 4350 4525 2    50   ~ 0
CUT_CONTROL
Text Label 2700 1675 0    50   ~ 0
CUT_CONTROL
$Comp
L Borta-Dators-rescue:Conn_02x12_Top_Bottom-Connector_Generic J3
U 1 1 61847CC9
P 2250 1675
F 0 "J3" H 2300 2392 50  0000 C CNN
F 1 "Conn_02x12_Top_Bottom" H 2300 2301 50  0000 C CNN
F 2 "Borta_Dators:SAMTEC-SSW-112-02-X-D-RA" H 2250 1675 50  0001 C CNN
F 3 "~" H 2250 1675 50  0001 C CNN
	1    2250 1675
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1375 2050 1375
Wire Wire Line
	1900 1475 2050 1475
Wire Wire Line
	2050 1575 1900 1575
Wire Wire Line
	2050 1875 1900 1875
Wire Wire Line
	1900 1975 2050 1975
Wire Wire Line
	1900 2075 2050 2075
$Comp
L Borta-Dators-rescue:GND-power #PWR01
U 1 1 618A8BBF
P 2700 1175
F 0 "#PWR01" H 2700 925 50  0001 C CNN
F 1 "GND" V 2705 1047 50  0000 R CNN
F 2 "" H 2700 1175 50  0001 C CNN
F 3 "" H 2700 1175 50  0001 C CNN
	1    2700 1175
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:+3.3V-power #PWR03
U 1 1 618A970B
P 2700 1275
F 0 "#PWR03" H 2700 1125 50  0001 C CNN
F 1 "+3.3V" V 2700 1500 50  0000 C CNN
F 2 "" H 2700 1275 50  0001 C CNN
F 3 "" H 2700 1275 50  0001 C CNN
	1    2700 1275
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:+4V-power #PWR014
U 1 1 618D7426
P 2700 2175
F 0 "#PWR014" H 2700 2025 50  0001 C CNN
F 1 "+4V" V 2700 2325 50  0000 L CNN
F 2 "" H 2700 2175 50  0001 C CNN
F 3 "" H 2700 2175 50  0001 C CNN
	1    2700 2175
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR015
U 1 1 618D875D
P 2700 2275
F 0 "#PWR015" H 2700 2025 50  0001 C CNN
F 1 "GND" V 2705 2147 50  0000 R CNN
F 2 "" H 2700 2275 50  0001 C CNN
F 3 "" H 2700 2275 50  0001 C CNN
	1    2700 2275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 1175 2550 1175
Wire Wire Line
	2700 1475 2550 1475
Wire Wire Line
	2550 1375 2700 1375
Wire Wire Line
	2700 1275 2550 1275
Wire Wire Line
	2700 2175 2550 2175
Wire Wire Line
	2700 2275 2550 2275
NoConn ~ 2550 1575
$Comp
L Borta-Dators-rescue:R_Small-Device R8
U 1 1 61A50A90
P 8650 2260
F 0 "R8" V 8454 2260 50  0000 C CNN
F 1 "R_Small" V 8545 2260 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 8650 2260 50  0001 C CNN
F 3 "~" H 8650 2260 50  0001 C CNN
	1    8650 2260
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:Buzzer-Device BZ1
U 1 1 61A5490D
P 9410 1810
F 0 "BZ1" H 9562 1839 50  0000 L CNN
F 1 "Buzzer" H 9562 1748 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" V 9385 1910 50  0001 C CNN
F 3 "~" V 9385 1910 50  0001 C CNN
	1    9410 1810
	1    0    0    -1  
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR017
U 1 1 61A564A9
P 9200 2580
F 0 "#PWR017" H 9200 2330 50  0001 C CNN
F 1 "GND" V 9205 2452 50  0000 R CNN
F 2 "" H 9200 2580 50  0001 C CNN
F 3 "" H 9200 2580 50  0001 C CNN
	1    9200 2580
	1    0    0    -1  
$EndComp
$Comp
L Borta-Dators-rescue:+4V-power #PWR016
U 1 1 61A589AA
P 9180 1550
F 0 "#PWR016" H 9180 1400 50  0001 C CNN
F 1 "+4V" V 9180 1700 50  0000 L CNN
F 2 "" H 9180 1550 50  0001 C CNN
F 3 "" H 9180 1550 50  0001 C CNN
	1    9180 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 2260 8900 2260
Wire Wire Line
	9200 2460 9200 2580
Wire Wire Line
	9200 2060 9200 1910
Wire Wire Line
	9200 1910 9310 1910
Wire Wire Line
	9310 1710 9180 1710
Wire Wire Line
	9180 1710 9180 1550
Text Label 8340 2260 2    50   ~ 0
BUZZER
Wire Wire Line
	8550 2260 8340 2260
Text Label 4350 3125 2    50   ~ 0
BUZZER
Wire Wire Line
	4500 3825 4355 3825
$Comp
L Borta-Dators-rescue:Q_NPN_BCE-Device Q1
U 1 1 61A8C3C4
P 9100 2260
F 0 "Q1" H 9291 2306 50  0000 L CNN
F 1 "BCX54" H 9291 2215 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 9300 2360 50  0001 C CNN
F 3 "~" H 9100 2260 50  0001 C CNN
	1    9100 2260
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3225 5950 3225
Wire Wire Line
	6925 3225 6925 3325
Wire Wire Line
	6825 3225 6925 3225
Wire Wire Line
	6625 3225 6150 3225
$Comp
L Borta-Dators-rescue:R_Small-Device R4
U 1 1 61763ADD
P 6050 3225
F 0 "R4" V 6100 3350 50  0000 C CNN
F 1 "150" V 6100 3075 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 6050 3225 50  0001 C CNN
F 3 "~" H 6050 3225 50  0001 C CNN
	1    6050 3225
	0    -1   -1   0   
$EndComp
$Comp
L Borta-Dators-rescue:LED_Small-Device D2
U 1 1 6174B73A
P 6725 3225
F 0 "D2" H 6625 3175 50  0000 C CNN
F 1 "LED_Small" H 6950 3175 50  0000 C CNN
F 2 "Diode_SMD:D_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6725 3225 50  0001 C CNN
F 3 "~" V 6725 3225 50  0001 C CNN
	1    6725 3225
	-1   0    0    1   
$EndComp
Connection ~ 6925 3225
Connection ~ 6925 3325
Connection ~ 6925 3425
$Comp
L Borta-Dators-rescue:GND-power #PWR0101
U 1 1 61B1B954
P 6925 3525
F 0 "#PWR0101" H 6925 3275 50  0001 C CNN
F 1 "GND" V 6930 3397 50  0000 R CNN
F 2 "" H 6925 3525 50  0001 C CNN
F 3 "" H 6925 3525 50  0001 C CNN
	1    6925 3525
	1    0    0    -1  
$EndComp
$Comp
L Borta-Dators-rescue:GND-power #PWR07
U 1 1 61774732
P 3380 3885
F 0 "#PWR07" H 3380 3635 50  0001 C CNN
F 1 "GND" V 3385 3757 50  0000 R CNN
F 2 "" H 3380 3885 50  0001 C CNN
F 3 "" H 3380 3885 50  0001 C CNN
	1    3380 3885
	1    0    0    -1  
$EndComp
Wire Wire Line
	3480 3825 3380 3825
$Comp
L Borta-Dators-rescue:R_Small-Device R7
U 1 1 61764F62
P 4255 3825
F 0 "R7" V 4215 3955 50  0000 C CNN
F 1 "150" V 4220 3675 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" H 4255 3825 50  0001 C CNN
F 3 "~" H 4255 3825 50  0001 C CNN
	1    4255 3825
	0    1    1    0   
$EndComp
$Comp
L Borta-Dators-rescue:LED_Small-Device D1
U 1 1 61748A59
P 3580 3825
F 0 "D1" H 3480 3775 50  0000 C CNN
F 1 "LED_Small" H 3810 3860 50  0000 C CNN
F 2 "Diode_SMD:D_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3580 3825 50  0001 C CNN
F 3 "~" V 3580 3825 50  0001 C CNN
	1    3580 3825
	1    0    0    -1  
$EndComp
Wire Wire Line
	3680 3825 4155 3825
Wire Wire Line
	3380 3825 3380 3885
Wire Wire Line
	5800 4025 5950 4025
Wire Wire Line
	5800 4125 5950 4125
Wire Wire Line
	5800 4325 5950 4325
Wire Wire Line
	5800 4425 5950 4425
Wire Wire Line
	4500 3125 4350 3125
NoConn ~ 5800 4525
$EndSCHEMATC
