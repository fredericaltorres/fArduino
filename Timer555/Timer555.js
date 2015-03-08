/*

LED Blinker:	
timer 

Timer 555, 1 LEDs Blinking Schematic:
=====================================

1. Pin1 to ground
2. Connect a 0.01uF capacitor between pins 5 and 1.
3. Connect a 0.47uF capacitor between pins 1 and 6.
	Negative lead of the capacitor to pin 1. 
4. Connect a 22k Ohm resistor between pin 6 and 7.
5. Connect a 22kOhm pins 7 and 8.  
6. Connect a pins 4 and 8 to each other (red) and pins 
7. Connect a 2 and 6 to each other (yellow).
8. Connect an LED+ to pin3 LED- to ground 
8. Connect Pin8(Vcc) to Power

Timer 555, 2 LEDs Blinking Schematic:
=====================================

2. Pin2(trigger) to pin6(Threshold)
3. Pin8(Vcc) to pin4(Reset)
4. Pin7(Discharge) to pin8(Vcc) using 22k Ohm resistor
5. Connect 47uF Capacitor negative pin to ground
6. Connect 47uF Capacitor positive pin to pin6 (threshold)
7. Connect 47uF Capacitor positive pin to pin7(Discharge) using 10k Ohm resistor
8. Connectpin3(Output) to Empty Row
	8.1 Empty row -> 200Ohm Resistor -> -LED1 -> LED1+ -> Vcc
	8.1 Empty row -> 200Ohm Resistor -> +LED2 -> LED2-> Ground
9. Connect Pin8(Vcc) to Power

http://en.wikipedia.org/wiki/555_timer_IC
Goog explainaintion: http://www.instructables.com/id/555-Timer/step5/555-Timer-Astable-Mode/
http://www.instructables.com/id/Know-Your-IC-555-Timers/step3/Project-555-timer-Light-Blinker/
http://www.instructables.com/id/ThrobbingFading-LED-w555ith-555-Timer/?utm_source=pm&utm_medium=related-instructables&utm_campaign=related_test

1.1RC => where t is in seconds, R is in ohms (resistance) and C is in farads (capacitance).
Frequency of Output = 1/[0.7*(RA+2*RB)*C]

555 Timer: explainaintion

Legend:
- C: Capacitor 0.47uF
- vC: Voltage Across Capacitor
- Vcc: 5v
- 1/3Vcc = 1.67
- 2/3Vcc = 3.33
- Ra resistor 100kOmh
- Rb resistor 10kOmh

FrequencyOfOutput = 1 /( 0.7*( 100000 + 2 * 10000) * 47/1000/1000/1000) == 253.2928 ==  25Hz
FrequencyOfOutput = 1 /( 0.7*( ra:100,000 + 2 * Rb:10,000) * 0.00000047)

1. Initial State
	C has no changer vC == 0
	vC = THRESHOLD + TRIGGER == LOW (Connected)
	=> v OUTPUT HIGH == Vcc

2. Since TRIGGER == LOW -> C is charging and vC is increasing
	vC = (Vcc - V0) * (1- e-t / [(RA+RB)*C])

3. vC == 2/3 Vcc
	=> THRESHOLD = HIGH => OUTPUT = LOW
	timeToAccumlate = 1.1*(RA+RB)*C seconds

4.	C is discharging via Rb into DISCHARGE. 

	vC = 2/3*Vcc* ( e-t /(RB*C))
	timeToDischarge = 0.7*RB*C seconds

5. When vC == TRIGGER ==1/3Vcc => TRIGGER = LOW => OUTPUT = HIGH
   Goto step 2
*/


function print(s) {
	console.log(s)
}

// Calculator
// http://houseofjeff.com/555-timer-oscillator-frequency-calculator/#comment-8887

// http://www.learningaboutelectronics.com/Articles/LED-flasher-circuit.php
// Flashing 2 leds

var capacitor = 47/1000/1000/1000 // 0.47uF
var capacitor = 47/1000/1000/1000*10 // 4.7uF
var capacitor = 47/1000/1000/1000*100 // 47uF
//var capacitor = 47/1000/1000/1000*1000 // 470uF
//var capacitor = 10/1000/1000/1000*100 // 10uF

// http://www.talkingelectronics.com/projects/50%20-%20555%20Circuits/50%20-%20555%20Circuits.htm

var vcc = 5
var vcc13 = 1/3 * vcc
var vcc23 = 2/3 * vcc
var Ra = 8.2 * 1000 // kOmh
var Rb = 68  * 1000 // kOmh
var Ra = 22 * 1000 // kOmh
var Rb = 22  * 1000 // kOmh

var frequencyOfOutput 	= (1 / ( 0.7 * ( Ra + 2 * Rb) * capacitor)) / 10
var dutyCycle 			= (0.7 * (Ra + Rb) * capacitor) / (0.7 * ( Ra + 2*Rb ) * capacitor)
var dutyCycleSimplified = (Ra+ Rb) / (Ra + 2*Rb)

print("frequencyOfOutput:"+frequencyOfOutput+" per seconds")
print("dutyCycle:"+dutyCycle)
print("dutyCycleSimplified:"+dutyCycleSimplified)



//FrequencyOfOutput = 1 /( 0.7*( 100000 + 2 * 10000) * 47/1000/1000/1000) == 253.2928 ==  25Hz
//FrequencyOfOutput = 1 /( 0.7*( ra:100,000 + 2 * Rb:10,000) * 0.00000047)
