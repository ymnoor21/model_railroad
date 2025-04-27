int l293D_input_pin1 = 2;
int l293d_input_pin2 = 4;
int l293d_enable_1_2 = 8;
int switch1_pin = A0;
int switch1_val;

int solenoid_state = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(l293d_enable_1_2, OUTPUT);
  pinMode(l293D_input_pin1, OUTPUT);
  pinMode(l293d_input_pin2, OUTPUT);  
  pinMode(switch1_pin, INPUT);
}

void loop()
{
  switch1_val = analogRead(switch1_pin);
  Serial.print("Switch 1: ");
  Serial.print(switch1_val);
  
  if (switch1_val < 200) {
    if (solenoid_state == 0) {
      //solenoid Turn
      Serial.println(", Direction: Turn");
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, HIGH);
      digitalWrite(l293d_input_pin2, LOW);
      delay(500);

      solenoid_state = 1; //Turn
      
      digitalWrite(l293d_enable_1_2, LOW);
      digitalWrite(l293D_input_pin1, LOW);
      digitalWrite(l293d_input_pin2, LOW);
      delay(500); // solenoid stop

    } else if (solenoid_state == 1) {
      //solenoid Straight
      Serial.println(", Direction: Straight");
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, LOW);
      digitalWrite(l293d_input_pin2, HIGH);
      delay(500);

      solenoid_state = 0;
      
      digitalWrite(l293d_enable_1_2, HIGH);
      digitalWrite(l293D_input_pin1, HIGH);
      digitalWrite(l293d_input_pin2, HIGH);
      delay(500); // solenoid stop
    }
  }

  Serial.println("");
}