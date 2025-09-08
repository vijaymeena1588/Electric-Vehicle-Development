// -------------------------
// Ultrasonic Reverse Assist for E-Car
// -------------------------

// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pin for dashboard LED indicator
const int ledPin = 7;

// Safe distance threshold in cm
const int safeDistance = 30;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("E-Car Reverse Assist System Activated");
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure time taken for echo
  long duration = pulseIn(echoPin, HIGH);

  // Convert time to distance (cm)
  long distance = (duration * 0.0343) / 2;

  // Print distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if object is within safe distance
  if (distance > 0 && distance <= safeDistance) {
    // Blink LED to alert driver
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  } else {
    // Keep LED off
    digitalWrite(ledPin, LOW);
  }

  delay(200); // Small delay before next measurement
}
