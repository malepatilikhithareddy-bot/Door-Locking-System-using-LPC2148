# Door-Locking-System-using-LPC2148
Password-based door locking system using LPC2148 with keypad authentication, password change feature, and door access counter.
# Password Based Door Locking System using LPC2148

## Project Overview

This project implements a **secure password-based door locking system using the LPC2148 ARM7 microcontroller**. The system allows authorized users to unlock a door by entering a password through a **4×4 matrix keypad**. A **16×2 LCD display (4-bit mode)** is used to guide the user and display system status messages such as password entry, access granted, or access denied.

In addition to basic authentication, the system includes **advanced features such as password modification and door access counting**, which improves flexibility and enhances system security.

The project was developed using **Embedded C in Keil µVision**, and the circuit was designed and tested using **Proteus Professional**.

---

## Features

* Password-based door authentication
* **Change password functionality** for improved security
* **Door access counter** to track how many times the door is opened
* **4×4 matrix keypad** for user input
* **16×2 LCD display** for user interaction and system messages
* Displays **Access Granted** or **Access Denied** based on password verification
* Implemented using **LPC2148 ARM7 microcontroller**

---

## Hardware Components

* LPC2148 ARM7 Microcontroller
* 4×4 Matrix Keypad
* 16×2 LCD Display (4-bit mode)
* Door Lock / Relay mechanism
* Power Supply

---

## Software Tools

* **Keil µVision** – Used for writing and compiling Embedded C code
* **Proteus Professional** – Used for circuit design and simulation

---

## Working Principle

1. The system initializes the **LCD display and keypad interface**.
2. The user enters a password using the **4×4 keypad**.
3. The microcontroller reads the keypad input and compares it with the stored password.
4. If the password is correct:

   * The door unlocks.
   * The **door access counter increases**.
   * LCD displays **Access Granted**.
5. If the password is incorrect:

   * LCD displays **Access Denied**.
   * The system waits for another password attempt.
6. The system also allows the user to **change the password**, which increases the flexibility and security of the system.

---

## Project Structure

```
LPC2148-Door-Locking-System
│
├── code
│   ├── main.c
│   ├── lcd.c
│   ├── lcd.h
│   ├── keypad.c
│   └── keypad.h
│
├── proteus
│   └── door_lock_simulation.pdsprj
│
├── images
│   └── circuit_diagram.png
│
└── README.md
```

---

## Applications

* Smart home security systems
* Office access control systems
* Digital locker systems
* Embedded security applications

---

## Future Improvements

* Fingerprint or biometric authentication
* IoT-based remote door monitoring
* Mobile app-based access control
* Alarm system for multiple incorrect attempts

---

## Author

**Likhitha Reddy**
Electronics and Communication Engineering
Interested in Embedded Systems, VLSI Design, and Digital Systems
