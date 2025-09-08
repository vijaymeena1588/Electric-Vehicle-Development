#include <LiquidCrystal.h>
#include <DHT.h>

// ---------------------- Pin Definitions ----------------------
#define DHTPIN 2
#define DHTTYPE DHT11
#define VOLTAGE_PIN A0     // Voltage divider pin
#define CURRENT_PIN A1     // ACS712 pin
#define AUX_VOLT_PIN A2    // Extra DC voltage measurement pin

// ---------------------- LCD Setup ----------------------
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// ---------------------- Sensor Objects ----------------------
DHT dht(DHTPIN, DHTTYPE);

// ---------------------- Constants ----------------------
// ADC reference
const float ARDUINO_VCC = 5.0;
const int ADC_RES = 1023;

// Voltage divider (for pack voltage)
const float R1 = 5100.0;
const float R2 = 47000.0;

// ACS712 Current Sensor
const float ACS_SENSITIVITY = 185.0; // mV per A for ACS712-05B
const float ACS_OFFSET = 2.5;        // V at 0A

// Battery Voltage Limits
const float MAX_VOLTAGE = 58.0;
const float MIN_VOLTAGE = 39.0;

// ---------------------- Global Variables ----------------------
float batteryVoltage = 0;
float currentReading = 0;
float temperature = 0;
int SOC = 0;
float auxVoltage = 0;

// ---------------------- Setup ----------------------
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();

  lcd.print("EV BMS Monitor");
  delay(2000);
  lcd.clear();
}

// ---------------------- Main Loop ----------------------
void loop() {
  // Read sensors
  batteryVoltage = getPackVoltage();
  currentReading = getCurrent();
  auxVoltage = getAuxVoltage();
  temperature = dht.readTemperature();
  SOC = calculateSOC(batteryVoltage);

  // Display on LCD
  updateLCD();

  // Print detailed report
  printSerialReport();

  delay(1000);
}

// ---------------------- Helper Functions ----------------------

// Average Pack Voltage
float getPackVoltage() {
  float sum = 0;
  for (int i = 0; i < 200; i++) {
    int raw = analogRead(VOLTAGE_PIN);
    float vSensed = raw * (ARDUINO_VCC / ADC_RES);
    float vActual = vSensed * ((R1 + R2) / R1);
    sum += vActual * 1.05; // Calibration factor
  }
  return sum / 200.0;
}

// Current Measurement using ACS712
float getCurrent() {
  long sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += analogRead(CURRENT_PIN);
  }
  float adcValue = sum / 1000.0;
  float voltage = (adcValue / ADC_RES) * ARDUINO_VCC;
  float current = (voltage - ACS_OFFSET) * 1000 / ACS_SENSITIVITY;
  return current;
}

// Extra Auxiliary DC Voltage (Optional sensor)
float getAuxVoltage() {
  int raw = analogRead(AUX_VOLT_PIN);
  float analogVoltage = (float)raw * (ARDUINO_VCC / ADC_RES);
  float inputVoltage = analogVoltage * 5.0; // scale factor
  return inputVoltage;
}

// SOC Calculation
int calculateSOC(float Vin) {
  if (Vin >= 58) return 100;
  else if (Vin >= 55) return 85;
  else if (Vin >= 52) return 65;
  else if (Vin >= 50) return 50;
  else if (Vin >= 48) return 35;
  else if (Vin >= 45) return 15;
  else return 0;
}

// Update LCD Dashboard
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(batteryVoltage, 1);
  lcd.print(" SOC:");
  lcd.print(SOC);

  lcd.setCursor(0, 1);
  lcd.print("I:");
  lcd.print(currentReading, 1);
  lcd.print("A T:");
  lcd.print(temperature, 0);
  lcd.print("C");
}

// Serial Detailed Report
void printSerialReport() {
  Serial.println("--------------- EV BMS REPORT ---------------");
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");

  Serial.print("Current: ");
  Serial.print(currentReading, 3);
  Serial.println(" A");

  Serial.print("State of Charge: ");
  Serial.print(SOC);
  Serial.println(" %");

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("Aux Voltage: ");
  Serial.print(auxVoltage, 2);
  Serial.println(" V");

  // Estimated Power (Wattage)
  float power = batteryVoltage * currentReading;
  Serial.print("Estimated Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  // Health estimation (dummy example)
  String health = (temperature > 50 || SOC < 15) ? "CRITICAL" : "NORMAL";
  Serial.print("Battery Health: ");
  Serial.println(health);

  Serial.println("---------------------------------------------");
  Serial.println();
}
