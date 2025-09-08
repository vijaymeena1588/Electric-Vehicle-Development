# Electric-Vehicle-Development

Revived and successfully completed VIT’s first off-road electric vehicle project, which had been on hold for 5 years.  
As the **Lead Electrical Head**, I was responsible for designing and implementing the EV circuitry, managing a 60V DC system, and ensuring interconnection safety locks in compliance with SAE eBAJA rulebook standards. Additionally, I coordinated electrical subsystem integration, safety checks, and testing.  

Represented the team at **BAJA SAEINDIA 2025 (eBAJA)** and led technical discussions with judges, successfully clearing the on-site vehicle inspection for approval. The project outcome was a **fully functional and competition-ready off-road EV Car**.

---

## 📂 Repository Structure

---

## Project Documents

- **[6KW Powertrain](EV_Development/Project_Documents/6KW_POWERTRAIN.pdf)** – Detailed specifications and design of the 6KW drivetrain.  
- **[E-Car Design](EV_Development/Project_Documents/DESIGN_ECAR.pdf)** – Full technical design and presentation of the electric car.  
- **[Electrical System Sheet](EV_Development/Project_Documents/Electrical_System_Sheet.pdf)** – Complete electrical system diagram and component sheet.  

---

## Technical Resources (Resource folder)

- **[2V - Power Train and working](EV_Development/Resource/2V%20-%20Power%20Train%20and%20working.pdf)** – Powertrain fundamentals and working notes.  
- **[BMS_EV](EV_Development/Resource/BMS_EV.pdf)** – BMS-related parameters and architecture for EV packs.  
- **[Battery types selection](EV_Development/Resource/Battery_types_selection.pdf)** – Guidance on choosing battery chemistries for EV use.  
- **[EV technology and real-time issues](EV_Development/Resource/EV%20technology%20and%20real-time%20issues.pdf)** – Common issues and technology considerations in EVs.  
- **[Intro to EV](EV_Development/Resource/Intro_to_EV.pdf)** – Fundamental concepts of electric vehicles.  
- **[Power converters in EV session](EV_Development/Resource/power%20converters%20in%20EV%20session.pdf)** – Notes and slides on power converters used in EV systems.
  
---

## 🔋 1. BMS Dashboard (`BMS_Dashboard.ino`)

Implements a **Battery Management System (BMS) dashboard** to monitor critical parameters of an EV battery pack.  
The system provides **real-time monitoring, health estimation, and diagnostics** via LCD and Serial Monitor.  

### 📌 Technical Features
- **Voltage Measurement** – Voltage divider (R1 = 51kΩ, R2 = 4.7kΩ) scales pack voltage (36–60V) → safe 0–5V input to Arduino.  
- **Current Measurement** – ACS712 Hall-effect sensor (05B/20A/30A variant) provides bidirectional current readings with 185 mV/A sensitivity.  
- **SOC Estimation** – Voltage-to-SOC mapping based on Li-ion pack discharge characteristics.  
- **Temperature Monitoring** – DHT11 sensor provides ambient/battery pack thermal feedback.  
- **Auxiliary Channel** – Supports additional DC bus input (e.g., 12V line).  
- **LCD Dashboard** – Displays V, I, SOC, Temp in real time.  
- **Serial Diagnostics** – Logs full BMS report: Voltage, Current, SOC, Power, Battery Health.  
- **Fault Detection** – Identifies **overtemperature** or **low SOC** states.  

### 🛠️ Hardware Required
- Arduino UNO 
- 16x2 LCD (Parallel or I2C)  
- ACS712 Current Sensor  
- DHT11 Temperature Sensor  
- Voltage Divider Network (51kΩ, 4.7kΩ)  
- EV Battery Pack (36–60V) / Bench DC Supply  

---

## 🔊 2. E-Car Startup Alert (`E_Car_Startup_Alert_Sound.ino`)

Electric cars are nearly silent at low speeds. This subsystem introduces an **acoustic startup alert** to warn pedestrians and nearby vehicles when the EV is powered ON.  

### 📌 Technical Features
- Generates a **2-tone buzzer sequence** at ignition.  
- Optional LED flash synchronized with buzzer.  
- One-time alert → system remains silent post-initialization.  
- Complies with pedestrian safety awareness requirements in EVs.  

---

## 🔄 3. Reverse Assist (`Reverse_Assist_for_E_Car.ino`)

Implements a **low-speed reversing assist system** using ultrasonic sensing to detect obstacles behind the vehicle.  

### 📌 Technical Features
- **Ultrasonic Sensor (HC-SR04)** measures rear obstacle distance.  
- If **d < 30 cm** → LED indicator blinks continuously.  
- If **clear** → LED remains OFF.  
- Can be extended to dual-output (LED + buzzer) for combined visual + auditory alert.  
- Provides driver with **situational awareness** during reversing maneuvers.  

---

## 📡 4. Smart Speedometer (`Smart_Speedometer.ino`)

Digital instrumentation system for **real-time vehicle speed measurement** based on wheel pulse sensing.  

### 📌 Technical Features
- **Pulse Detection** – Hall effect sensor or IR reflective sensor mounted on wheel hub.  
- **Speed Calculation** – RPM → Linear velocity computed using wheel circumference.  
- **Display** – Real-time vehicle speed on LCD dashboard.  
- **Utility** – Useful for driver performance monitoring in track/testing conditions.  
