/*
 * Basic_Keypad_Usage.ino
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

/************************************************************************
  Connection keypad <-> Arduino
                                          
  Keypad Pin | Assignment | Arduino Pin     
  -----------+------------+------------
           1 | Column 4   |  4
		   2 | Column 3   |  5
		   3 | Column 2   |  6
		   4 | Column 1   |  7
		   5 | Row 4      |  8
		   6 | Row 3      |  9
		   7 | Row 2      | 10
		   8 | Row 1      | 11
    
 ************************************************************************/
#define COL_0_PIN  7
#define COL_1_PIN  6
#define COL_2_PIN  5
#define COL_3_PIN  4
#define ROW_0_PIN 11
#define ROW_1_PIN 10
#define ROW_2_PIN  9
#define ROW_3_PIN  8

#define KEY_READ_SAMPLES 99

int cols[4] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN };
int rows[4] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN };
	
char key_names[4][4] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' }
};

boolean key_state[4][4] = {
	{ false, false, false, false },
	{ false, false, false, false },
	{ false, false, false, false },
	{ false, false, false, false }
};

void setup()
{
	// Serial communication
	Serial.begin(9600);
	// Assign the pins
	for (int i = 0; i < (sizeof(cols) / sizeof(int)); i++)
	{
		int pin = cols[i];
		Serial.print("Setting up PIN ");
		Serial.print(pin);
		Serial.println(" as INPUT");
		pinMode(pin, INPUT);
		digitalWrite(pin, LOW);
	}
	for (int i = 0; i < (sizeof(rows) / sizeof(int)); i++)
	{
		int pin = rows[i];
		Serial.print("Setting up PIN ");
		Serial.print(pin);
		Serial.println(" as OUTPUT");
		pinMode(pin, OUTPUT);
		// Reset the pin
		digitalWrite(pin, LOW);
	}
}

boolean readKey(int key_pin) 
{
	int trueCount = 0;
	int falseCount = 0;
	for (int i = 0; i < KEY_READ_SAMPLES; i++)
	{
		delayMicroseconds(50);
		if (digitalRead(key_pin) == HIGH)
		{
			trueCount++;
		}
		else
		{
			falseCount++;
		}
	}
	return (trueCount > falseCount);
}

void loop()
{
	for (int r = 0; r < (sizeof(rows) / sizeof(int)); r++)
	{
		int row_pin = rows[r];
		digitalWrite(row_pin, HIGH);
		for (int c = 0; c < (sizeof(cols) / sizeof(int)); c++)
		{
			int col_pin = cols[c];
			boolean current_state = key_state[r][c];
			char key_name = key_names[r][c];
			boolean new_state = readKey(col_pin);
			if (new_state != current_state)
			{
				key_state[r][c] = new_state;
				Serial.print("Key state change for key '");
				Serial.print(key_name);
				Serial.print("' to state '");
				Serial.print(new_state);
				Serial.println("'");
			}
		}
	}
}
