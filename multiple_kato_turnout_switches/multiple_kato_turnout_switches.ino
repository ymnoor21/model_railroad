// Assign switch label for Switch 1.
String switch1_label = "SWITCH1";

// Assign switch label for Switch 2.
// Comment out the line below if you are not using Switch 2.
String switch2_label = "SWITCH2";

// Declare different switch states (i.e ST_OFF, ST_STRAIGHT1, ST_TURN1, ST_STRAIGHT2, ST_TURN2) with Enum type
enum SWITCHSTATES {
  ST_OFF,
  ST_STRAIGHT1,
  ST_TURN1,
  ST_STRAIGHT2,
  ST_TURN2,
};

// Declare a variable of enum type SWITCHSTATES and initiate with OFF position for Switch 1.
SWITCHSTATES switch1_state = ST_OFF;

// Declare a variable of enum type SWITCHSTATES and initiate with OFF position for Switch 2.
// Comment out the line below if you are not using Switch 2.
SWITCHSTATES switch2_state = ST_OFF;

// Assign 2 digital pins from the Arduino board for pull-up/pull-down Switch 1.
// This is for my Switch 1.
const int switch1_ard_pin1 = 2;
const int switch1_ard_pin2 = 3;

// Assign 2 digital pins from the Arduino board for pull-up/pull-down Switch 2.
// This is for my Switch 2. 
// Comment out these two lines below if you are not using Switch 2.
const int switch2_ard_pin1 = 4;
const int switch2_ard_pin2 = 5;

// Now assign an analog pin A0 from Arduino board to receive pull up/pull down switch button press/release action.
// Make sure to use a 1K - 10K Ohm resistor in series with the switch.
const int switch1 = A0;

// Now assign an analog pin A1 from Arduino board to receive pull up/pull down switch button press/release action.
// Make sure to use a 1K - 10K Ohm resistor in series with the switch.
// Comment out the line below if you are not using Switch 2.
const int switch2 = A1;

// Declare a variable for receiving Switch 1 value, but don't assign any initial value.
int switch1_val;

// Declare a variable for receiving Switch 2 value, but don't assign any initial value.
// Comment out the line below if you are not using Switch 2.
int switch2_val;

// Define Kato turnout switch states (i.e, Straight: 0, Turn: 1) for Switch 1 and initiate it.
int State1 = 0;

// Define Kato turnout switch states (i.e, Straight: 0, Turn: 1) for Switch 2 and initiate it.
// Comment out the line below if you are not using Switch 2.
int State2 = 0;

// Set turnout delay to 0.5 seconds
int turnout_delay = 500;

// Loop read delay to 0 seconds, but you can try increasing this value to 200 (i.e, 0.2 seconds)
// But this value is directly proportional to the response time of Kato switches. 
// So increasing this value will certainly increase the response time of switching.
int read_delay = 0;

// Minimum analog switch value to register a switch press
int minimum_switch_value = 200;

void setup() {
  // Enable serial monitor with 9600 baud rate
  Serial.begin(9600);

  // Declare pinmodes for Switch 1 as OUTPUT since we will be sending digital signals to these pins
  pinMode(switch1_ard_pin1, OUTPUT);
  pinMode(switch1_ard_pin2, OUTPUT);
  
  // Declare pinmodes for Switch 2 as OUTPUT since we will be sending digital signals to these pins
  // Comment out these two lines below if you are not using Switch 2.
  pinMode(switch2_ard_pin1, OUTPUT);
  pinMode(switch2_ard_pin2, OUTPUT);
}

void loop() {
  // Print State 1 value
  Serial.print("State 1: ");
  Serial.print(State1);

  // Print State 2 value
  // Comment out these two lines below if you are not using Switch 2.
  Serial.print(", State 2: ");
  Serial.print(State2);

  // Print new line
  Serial.println("");

  // Read analog pin Switch 1 value
  switch1_val = analogRead(switch1);

  // Read analog pin Switch 2 value
  // Comment out the line below if you are not using Switch 2.
  switch2_val = analogRead(switch2);

  // Print Switch 1's value
  Serial.print("Switch 1: ");
  Serial.print(switch1_val);

  // Print Switch 2's value
  // Comment out these two lines below if you are not using Switch 2.
  Serial.print(", Switch 2: ");
  Serial.print(switch2_val);

  // Print new line
  Serial.println("");
  
  // If switch1_val value is less than minimum_switch_value, then we know the Switch 1 has been pressed
  if (switch1_val < minimum_switch_value) {
    switch(switch1_state) {
      case ST_OFF: 
        switchoff(switch1_label); 
        break;
      case ST_STRAIGHT1: 
        switchstraight(switch1_label); 
        break;
      case ST_TURN1: 
        switchturn(switch1_label);
        break;
    }
  }

  // If switch2_val value is less than minimum_switch_value, then we know the Switch 2 has been pressed
  // Comment out the if block if you are not using Switch 2.
  if (switch2_val < minimum_switch_value) {
    switch(switch2_state) {
      case ST_OFF: 
        switchoff(switch2_label); 
        break;
      case ST_STRAIGHT2: 
        switchstraight(switch2_label); 
        break;
      case ST_TURN2: 
        switchturn(switch2_label);
        break;
    }
  }

  // Set 0.2 seconds of delay between reads since it's a loop
  delay(read_delay);
}

/* 
  Purpose: To turn off switches
  Description: 
    Takes in a switch label, sends a LOW signal to its corresponding pins, and finally saves the switch state.
  Param: Switch label
*/
void switchoff(String switch_label) {
  // Handle Switch 1 turn off
  if (switch_label == switch1_label) {
    digitalWrite(switch1_ard_pin1, LOW);
    digitalWrite(switch1_ard_pin2, LOW);

    if (State1 == 1) {
      // Save the last state of Switch 1, i.e., Straight
      switch1_state = ST_STRAIGHT1;
    }
    
    if (State1 == 0) {
      // Save the last state of Switch 1, i.e., Turn
      switch1_state = ST_TURN1;
    }
  }

  // Handle Switch 2 turn off
  if (switch_label == switch2_label) {
    digitalWrite(switch2_ard_pin1, LOW);
    digitalWrite(switch2_ard_pin2, LOW);

    if (State2 == 1) {
      // Save the last state of Switch 2, i.e., Straight
      switch2_state = ST_STRAIGHT2;
    }
    
    if (State2 == 0) {
      // Save the last state of Switch 2, i.e., Turn
      switch2_state = ST_TURN2;
    }
  }
}

/* 
  Purpose: To turn the switch to a straight position
  Description: 
    Takes in a switch label, sends HIGH and LOW signals to its 
    corresponding pin 1 and pin 2, respectively. Finally saves 
    the STRAIGHT position in its state variable.
  Param: Switch label
*/
void switchstraight(String switch_label) {
  if (switch_label == switch1_label) {
    digitalWrite(switch1_ard_pin1, HIGH); // -> Must set State1 to 0
    digitalWrite(switch1_ard_pin2, LOW);

    // keep power to the turnout for 0.5 seconds
    delay(turnout_delay); 
    // Save the straight state of Switch 1. State values are: [Straight = 0, Turn = 1]
    State1 = 0;
    // Reset switch state to OFF position again
    switch1_state = ST_OFF;
  }

  if (switch_label == switch2_label) {
    digitalWrite(switch2_ard_pin1, HIGH); // -> Must set State2 to 0
    digitalWrite(switch2_ard_pin2, LOW);

    // keep power to the turnout for 0.5 seconds
    delay(turnout_delay); 
    // Save the straight state of Switch 2. State values are: [Straight = 0, Turn = 1]
    State2 = 0;
    // Reset switch state to OFF position again
    switch2_state = ST_OFF;
  }
}

/* 
  Purpose: To turn the switch to the turn position
  Description: 
    Takes in a switch label, sends LOW and HIGH signals to its corresponding pin 1 and pin 2, respectively. Finally saves the TURN position in its state variable.
  Param: Switch label
*/
void switchturn(String switch_label) {
  if (switch_label == switch1_label) {
    digitalWrite(switch1_ard_pin1, LOW);
    digitalWrite(switch1_ard_pin2, HIGH); // -> Must set State1 to 1

    // keep power to the turnout for 0.5 seconds
    delay(turnout_delay); 
    // Save the turn state of Switch 1. State values are: [Straight = 0, Turn = 1]
    State1 = 1;
    // Reset switch state to OFF position again
    switch1_state = ST_OFF;
  }

  if (switch_label == switch2_label) {
    digitalWrite(switch2_ard_pin1, LOW);
    digitalWrite(switch2_ard_pin2, HIGH); // -> Must set State2 to 1

    // keep power to the turnout for 0.5 seconds
    delay(turnout_delay); 
    // Save the turn state of Switch 2. State values are: [Straight = 0, Turn = 1]
    State2 = 1;
    // Reset switch state to OFF position again
    switch2_state = ST_OFF;
  }
}