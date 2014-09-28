/*
 * Basic_Distance_Measuring.ino
 *
 *
 * Copyright 2014 The Arobito Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * Author: Jürgen Edelbluth
 */

#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250

void setup()
{
	// Serial monitoring
	Serial.begin(9600);
	
	// Initializing Trigger Output and Echo Input
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	
	// Reset the trigger pin and wait a half a second
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(500);
}

long singleMeasurement()
{
	long duration = 0;
	
	// Measure: Put up Trigger...
	digitalWrite(TRIGGER_PIN, HIGH);
	// ... wait for 11 µs ...
	delayMicroseconds(11);
	// ... put the trigger down ...
	digitalWrite(TRIGGER_PIN, LOW);
	// ... and wait for the echo ...
	duration = pulseIn(ECHO_PIN, HIGH);
	return (long) (((float) duration / USONIC_DIV) * 10.0);
}

long measure()
{
	long measureSum = 0;
	for (int i = 0; i < MEASURE_SAMPLES; i++)
	{
		delay(MEASURE_SAMPLE_DELAY);
		measureSum += singleMeasurement();
	}
	return measureSum / MEASURE_SAMPLES;
}

void loop()
{
	delay(MEASURE_DELAY);
	long distance = measure();
	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" mm");
}
