void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  Serial2.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  while (Serial2.available()) {
    String a = Serial2.readString();
    if (a.substring(0, 4) == "P1=0") {
      switch_point(0,0);
      Serial.println("OK");
    }
    if (a.substring(0, 4) == "P1=1") {
      switch_point(0,1);
      Serial.println("OK");
    }
    if (a.substring(0, 4) == "P2=0") {
      switch_point(1,0);
      Serial.println("OK");
    }
    if (a.substring(0, 4) == "P2=1") {
      switch_point(1,1);
      Serial.println("OK");
    }
  }

}

void switch_point(int point, int dir) {
  switch (point) {
    case 0:
      if (dir == 0) {
        digitalWrite(8, HIGH);
        delay(250);
      } else {
        digitalWrite(9, HIGH);
        delay(250);
      }
      break;
    case 1:
      if (dir == 0) {
        digitalWrite(10, HIGH);
        delay(250);
      } else {
        digitalWrite(11, HIGH);
        delay(250);
      }
      break;
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
