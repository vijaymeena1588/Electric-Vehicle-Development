# Electric-Vehicle-Development
Revived and successfully completed VIT’s first off-road electric vehicle project, which had been on hold for 5 years. As the Lead Electrical Head, I was responsible for designing and implementing the EV circuitry, managing a 60V DC system, and ensuring interconnection safety locks in compliance with SAE eBAJA rulebook standards. Additionally, I coordinated electrical subsystem integration, safety checks, and testing. Represented the team at BAJA SAEINDIA 2025 (eBAJA) and led technical discussions with judges, successfully clearing the on-site vehicle inspection for approval. The project outcome was a fully functional and competition-ready off-road EV prototype.

# My E-Car Project

This repository contains the design and technical documentation for our electric car project.

## Project Documents

* [**6kW Powertrain Design**](6kW%20Powertrain%20Design.pdf): Detailed specifications and design of the 6kW powertrain system.  
* [**E-Car Design Presentation**](E-Car%20Design%20Presentation.pdf): A presentation outlining the overall design and features of the electric car.  
* [**Electrical System Sheet**](Electrical_System_Sheet.pdf): A document detailing the electrical system components and layout.  

---

## Technical Resources

* [**BMS Parameters**](BMS%20Parameters.pdf): A document detailing the key parameters for the Battery Management System.  
* [**BMS Questions**](BMS%20Questions.pdf): A collection of questions and answers related to BMS design and functionality.  
* [**Battery Types Selection**](Battery%20Types%20Selection.pdf): A guide to selecting different battery types for an electric vehicle.  
* [**EV Technology & Issues**](EV%20Technology%20&%20Issues.pdf): A document covering EV technology and its common real-time issues.  
* [**Power Converters in EV 1**](Power%20Converters%20in%20EV%201.pdf): An overview of various power converters used in electric vehicles.  
* [**Power Converters in EV**](Power%20Converters%20in%20EV.pdf): A presentation on power converters and their use in electric and hybrid vehicles.  


# 🚗 EV Battery Management System (BMS) Dashboard using Arduino

This project implements a **mini BMS dashboard** for Electric Vehicles (EVs) using Arduino.  
It measures and displays **battery voltage, current, SOC (State of Charge), temperature, and auxiliary DC voltage** on an **LCD screen** and logs detailed information to the **Serial Monitor**.  

The project is designed to simulate a real-world **EV BMS monitoring system** with fault detection and estimated battery health.

---

## 📌 Features

✅ **Battery Voltage Monitoring** – Reads pack voltage via voltage divider.  
✅ **Current Monitoring** – Uses ACS712 sensor for accurate current measurement.  
✅ **SOC (State of Charge)** – Calculates percentage based on battery voltage mapping.  
✅ **Temperature Monitoring** – DHT11 sensor provides battery pack temperature.  
✅ **Auxiliary Voltage Input** – Extra DC voltage channel for expansion.  
✅ **LCD Dashboard** – Real-time display of Voltage, Current, SOC, and Temperature.  
✅ **Serial Monitor Report** – Detailed log with Voltage, Current, SOC, Temperature, Power, Health Status.  
✅ **Battery Health Estimation** – Simple logic for fault detection (Overheating, Low SOC, etc.).  
✅ **Modular & Scalable Code** – Easy to add more sensors or modify SOC mapping.  

---

## ⚙️ Hardware Components

- **Arduino UNO / Mega / Nano**  
- **16x2 LCD Display** (Parallel connection, can be replaced with I2C LCD)  
- **DHT11 Temperature Sensor**  
- **ACS712 Current Sensor (05B / 20A / 30A)**  
- **Voltage Divider Circuit** (using resistors R1 = 51kΩ, R2 = 4.7kΩ)  
- **Wires & Breadboard**  
- **Battery Pack (36V–60V)** (⚠️ Use safely – for testing you can simulate with a DC power supply)  

---

## 🔌 Circuit Diagram Explanation

**1. Voltage Measurement (Battery Pack Voltage):**  
- Battery → Voltage Divider (R1 = 51kΩ, R2 = 4.7kΩ) → Arduino A0  
- Reduces high battery voltage (up to 60V) into safe 0–5V range.  

**2. Current Measurement (ACS712):**  
- Battery → Load passes through ACS712 sensor.  
- ACS712 output → Arduino A1.  
- Provides 2.5V at 0A, shifts with load current.  

**3. Auxiliary DC Voltage Measurement:**  
- Any extra DC source (like 12V line) → Arduino A2 (scaled by divider if needed).  

**4. Temperature Measurement (DHT11):**  
- DHT11 → Arduino pin D2.  
- Provides °C temperature.  

**5. LCD Display (16x2 Parallel):**  
- RS → Pin 7  
- E  → Pin 8  
- D4 → Pin 9  
- D5 → Pin 10  
- D6 → Pin 11  
- D7 → Pin 12  
- VCC → 5V, GND → GND  

---

## 🖥️ Software Requirements

- **Arduino IDE**  
- **DHT Library** (`DHT.h`)  
- **LiquidCrystal Library** (built-in with Arduino IDE)  

---

## 🔧 How to Build the Circuit

1. Connect the **voltage divider** to A0 for pack voltage.  
2. Wire up the **ACS712 current sensor** in series with the load, connect output to A1.  
3. Connect **DHT11 sensor** to pin D2.  
4. Connect **LCD (16x2)** as per pin definitions.  
5. Power the Arduino via USB or regulated 5V supply.  
6. Ensure your battery source is within safe range for the divider setup.  

---

## 🧑‍💻 How the Code Works

1. **Voltage Reading** – Reads analog value at A0, converts to actual pack voltage using scaling & calibration factor.  
2. **Current Reading** – Reads ACS712 output at A1, removes 2.5V offset, converts to Amps.  
3. **Temperature** – Reads DHT11 in °C.  
4. **SOC Calculation** – Uses simple voltage-based mapping:  
   - 58V → 100%  
   - 55V → 85%  
   - 52V → 65%  
   - 50V → 50%  
   - 48V → 35%  
   - 45V → 15%  
   - Below 45V → 0%  
5. **LCD Update** – Refreshes every second with Voltage, SOC, Current, Temperature.  
6. **Serial Monitor** – Prints a full BMS-style report including power (V × I) and battery health.  

---

## 📊 Output Example

### LCD Output:
```
V:52.4 SOC:65
I:3.2A T:28C
```

### Serial Monitor:
```
--------------- EV BMS REPORT ---------------
Battery Voltage: 52.40 V
Current: 3.215 A
State of Charge: 65 %
Temperature: 28.0 °C
Aux Voltage: 12.10 V
Estimated Power: 168.4 W
Battery Health: NORMAL
---------------------------------------------
```

---

## 🚀 Future Improvements

- Add **cell-level monitoring** for balancing.  
- Implement **SD card logging** for trip history.  
- Add **Bluetooth / WiFi** to send BMS data to mobile app.  
- Improve SOC calculation using **Coulomb counting** instead of voltage mapping.  
- Add **fault detection** (overvoltage, undervoltage, overcurrent, thermal runaway).  

---

⚠️ **Disclaimer:**  
This project is for educational purposes. When working with **high-voltage EV batteries**, ensure you use proper **safety precautions, insulation, and isolation circuits**.  

