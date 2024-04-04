https://github.com/23cs02014/PDS_Project_HomeAutomation/assets/164471213/f60d2929-d0d7-438a-8f4f-f9bdb35237f3

# Motivation: Why did we choose the project?
+   In today's fast-paced world, convenience and efficiency are paramount. The ability to control and monitor our homes remotely offers not just convenience but also significant energy savings and enhanced security. Arduino, with its user-friendly interface and versatile capabilities, provides an excellent platform for developing home automation systems.
+   By choosing to make a project on home automation using Arduino, we embark on a journey that combines creativity, technology, and practicality. We have the opportunity to design and implement solutions that cater to our specific needs, whether it's controlling lights, temperature, or security systems.
+   Furthermore, the skills and knowledge gained from working on this project are highly transferable and relevant in today's IoT-driven world. It offers a hands-on experience in programming, electronics, and system integration, which are invaluable in various fields such as engineering, technology, and even entrepreneurship.
+   In conclusion, a project on home automation using Arduino not only offers practical benefits but also serves as an exciting and enriching learning experience. It allows us to innovate, automate, and enhance our living spaces, making it a compelling choice for our project.

# Important highlights of the project:-
### 1. Light sensor:- 
+ It is called Light Dependent Resistor (LDR). We are using 10 bit ADC. The ADC on the Arduino is a 10-bit ADC meaning it has the ability to detect 1,024 (2^10) discrete analog levels. Some microcontrollers have 8-bit ADCs (2^8 = 256 discrete levels) and some have 16-bit ADCs (2^16 = 65,536 discrete levels). The LDR outputs certain voltage which is read by the Arduino's 10 bit ADC(It gives a value between 0 and 1023).
+ We are using the light sensor to detect external light and taking the input to adjust the brightness of the lights inside the room.
### 2. Temperature sensor:-
+ The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air and spits out a digital signal on the data pin (no analog input pins needed). It's fairly simple to use but requires careful timing to grab data. It has library <DHT>.
+ We're using the temperature sensor to detect the ambient temperature of the room, if the temperature exceeds a certain threshold, the windows open automatically.
### 3. Smoke  sensor:- 
+ We are using a Generic MQ2 Mq-2 Gas Sensor Module Smoke Methane Butane Detection. It can be used in homes and factories of gas leakage monitoring device, suitable for liquefied petroleum gas, butane, propane, methane, smoke detection. The sensor also gives values to the 10 bit ADC.
+ If the smoke sensor detects smoke above a certain threshold, a buzzer will be activated.
### 4. Automatic door:- 
+ We are using a servo motor. It uses an encoder or speed sensor to provide speed feedback and position. This feedback signal is compared with the input command position (desired position of the motor corresponding to a load) and produces the error signal (if there exists a difference between them).
+ The entrance of the room is being secured by the app which we created. We can open the door by clickling the "Open" button on our phone after the bluetooth connection is established.
### 5. MIT app inventor:-
+ In this project, we have used the “MIT app inventor” to create the app which runs on Bluetooth to communicate with our Arduino Nano.
+ ***The app does not run on C***
+ MIT App Inventor is based on visual programming, specifically using a blocks-based programming interface. It is mainly used to make apps on android devices.

![Screenshot 2024-04-04 160355](https://github.com/23cs02014/PDS_Project_HomeAutomation/assets/164471213/a9546544-4cd7-4239-b205-f36bfda7114f)

# Functionalities:-
+ The app is password protected.

![Password](https://github.com/23cs02014/PDS_Project_HomeAutomation/assets/164471213/069a45b5-2cb7-40cc-b637-c2ecb2dfbb4a)


## Buttons in the app:-
![Homescreen](https://github.com/23cs02014/PDS_Project_HomeAutomation/assets/164471213/1217e638-5fe0-4ffd-8ac3-192f351ac261)
+ First two buttons are for opening and closing the door.
+ The percentages indicate the brightness of the lights.
+ Turn on the "Automatic Lights" switch to operate the lights automatically. Whenever its dark outside, the lights inside turn on automatically and when its bright enough outside, the lights turn off automatically.
+ The last two buttons are for opening and closing the windows.
+ When the "Automatic Blinds" switch is turned on, temperature sensor takes the value of the ambient temperature and if the value crosses a certain threshold, the windows open automatically.

# What we learnt?
## Arduino:-
+ Arduino is an open-source electronics platform based on easy-to-use hardware and software. The platform consists of an easy-to-use hardware development board and an integrated development environment (IDE) for writing and uploading code to the board.

![PDS circuit](https://github.com/23cs02014/PDS_Project_HomeAutomation/assets/164471213/bf31a1e6-e60f-4e08-bace-7a6bd19f7200)


### Key Components of Arduino:-
### 1. Micro controller:-
+ The brain of the Arduino board, responsible for executing the code and controlling the hardware. The most common microcontroller used in Arduino boards is the Atmel AVR series.
### 2. Input and Output Pins:-
+ These pins allow the Arduino board to interact with external components such as sensors, LEDs, and motors. The number of pins varies depending on the Arduino board model.
### 3. Power supply:-
+ Arduino boards can be powered through a USB connection, a battery, or an external power supply. They typically operate at 5 volts.
### 4. Integrated Development Environment (IDE):-
+ The Arduino IDE is a software tool used to write, compile, and upload code to the Arduino board. It's based on the Processing programming language and is simple and easy to use.

# General  structure of Arduino code:-
### 1. Setup Function:-
+ The setup() function is where you initialize variables, pin modes, and any other initial setup required by your program. This function runs once when the Arduino is powered on or reset.
### 2. Loop Function:-
+ The loop() function is the heart of your Arduino code. It contains the main logic of your program and runs repeatedly after the setup() function has completed.
### 3. Control Structures:-
+ Control structures allow you to control the flow of your program based on certain conditions. Arduino supports common control structures like if, else, while, and for.
### 4. Data Structures:-
+ We're using the data structure "Struct" to hold our values.
+ The struct contains a character variable for the incoming value and three booleans of which, two of them are used for Automatic Lights and Automatic Blinds
+ The third one is a flag variable to detect the current state of the lights.
+ It contains a byte variable to hold the current brightness value for the lights.
### 5. Libraries:-
+ Libraries are collections of pre-written code that provide additional functionality to your Arduino projects. You can include libraries in your code using the #include directive.


