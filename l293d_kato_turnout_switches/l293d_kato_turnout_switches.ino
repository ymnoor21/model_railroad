int l293D_input_pin1 = 2;
int l293d_input_pin2 = 4;

int l293D_input_pin3 = 5;
int l293d_input_pin4 = 6;

int l293d_enable_1_2 = 8;
int l293d_enable_3_4 = 12;

int switch1_pin = A0;
int switch1_val;

int switch2_pin = A1;
int switch2_val;

int solenoid1_state = 0;
int solenoid2_state = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(l293d_enable_1_2, OUTPUT);
  pinMode(l293D_input_pin1, OUTPUT);
  pinMode(l293d_input_pin2, OUTPUT);  
  pinMode(switch1_pin, INPUT);

  pinMode(l293d_enable_3_4, OUTPUT);
  pinMode(l293D_input_pin3, OUTPUT);
  pinMode(l293d_input_pin4, OUTPUT);  
  pinMode(switch2_pin, INPUT);
}

void loop()
{
  switch1_val = analogRead(switch1_pin);
  switch2_val = analogRead(switch2_pin);
  Serial.print("Switch 1: ");
  Serial.print(switch1_val);
  
  if (switch1_val < 200) {
    if (solenoid1_state == 0) {
      //solenoid Turn
      Serial.print(", Direction: Turn");
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, HIGH);
      digitalWrite(l293d_input_pin2, LOW);
      delay(500);

      solenoid1_state = 1; //Turn
      
      digitalWrite(l293d_enable_1_2, LOW);
      digitalWrite(l293D_input_pin1, LOW);
      digitalWrite(l293d_input_pin2, LOW);
      delay(500); // solenoid stop

    } else if (solenoid1_state == 1) {
      //solenoid Straight
      Serial.print(", Direction: Straight");
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, LOW);
      digitalWrite(l293d_input_pin2, HIGH);
      delay(500);

      solenoid1_state = 0;
      
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, HIGH);
      digitalWrite(l293d_input_pin2, HIGH);
      delay(500); // solenoid stop
    }
  }

  Serial.print(", Switch 2: ");
  Serial.print(switch2_val);

  if (switch2_val < 200) {
    if (solenoid2_state == 0) {
      //solenoid Turn
      Serial.print(", Direction: Turn");
      digitalWrite(l293d_enable_3_4, HIGH);
      digitalWrite(l293D_input_pin3, HIGH);
      digitalWrite(l293d_input_pin4, LOW);
      delay(500);

      solenoid2_state = 1; //Turn
      
      digitalWrite(l293d_enable_3_4, LOW);
      digitalWrite(l293D_input_pin3, LOW);
      digitalWrite(l293d_input_pin4, LOW);
      delay(500); // solenoid stop

    } else if (solenoid2_state == 1) {
      //solenoid Straight
      Serial.print(", Direction: Straight");
      digitalWrite(l293d_enable_3_4, HIGH);
      digitalWrite(l293D_input_pin3, LOW);
      digitalWrite(l293d_input_pin4, HIGH);
      delay(500);

      solenoid2_state = 0;
      
      digitalWrite(l293d_enable_3_4, HIGH);
      digitalWrite(l293D_input_pin3, HIGH);
      digitalWrite(l293d_input_pin4, HIGH);
      delay(500); // solenoid stop
    }
  }

  Serial.println("");
}
