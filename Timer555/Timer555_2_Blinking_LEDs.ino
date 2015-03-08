/*
1. Pin1 to ground
2. Pin2(trigger) to pin6(Threshold)
3. Pin8(Vcc) to pin4(Reset)
4. Pin7(Discharge) to pin8(Vcc) using 22k Ohm resistor
5. Connect 47uF Capacitor negative pin to ground and positive pin to pin6 (threshold)
6. Connect 47uF Capacitor positive pin to pin6 (threshold)
7. Connect 47uF Capacitor positive pin to pin7(Discharge) using 10k Ohm resistor
8. Connectpin3(Output) to Empty Row
	8.1 Empty row -> 200Ohm Resistor -> -LED1 -> LED1+ -> Vcc
	8.1 Empty row -> 200Ohm Resistor -> +LED2 -> LED2-> Ground
9. Connect Pin8(Vcc) to Power
*/