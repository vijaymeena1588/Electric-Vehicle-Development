// -------------------------
// E-Car Startup Alert Sound
// -------------------------

const int buzzerPin = 2;   // Buzzer pin
const int ledPin = 7;      // LED for startup indication

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Startup Sound (EV ignition alert)
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000);
  delay(500);
  noTone(buzzerPin);
  digitalWrite(ledPin, LOW);

  delay(200);
  tone(buzzerPin, 1500);
  delay(300);
  noTone(buzzerPin);

  Serial.begin(9600);
  Serial.println("E-Car Powered ON 🚗⚡");
}

void loop() {
  // Nothing to do in loop (only plays on startup)
}
