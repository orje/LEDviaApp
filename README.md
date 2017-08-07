# LEDviaApp
![picture](doc/stuff/LEDviaApp.jpg)  
Demo video: https://www.youtube.com/watch?v=NQhEtg-nRmY
### 1  Introduction
For the beginning, a short introduction of myself.  
I'm from Germany and professionally I work as an industrial electronics since many years. I put production machines into operation, optimize and repair them and do the troubleshooting. To do this, one task is to look into the programmings of the controls. And from time to time I do some changes in the programs. Most of the PLC controls are from the Siemens Simatic line or simular PLC.  
With Arduino and the C language as a hobby I started in my free time about 3 years ago.  
I bought the Arduino starter Kit and tried a few things.   
It was a little bit overwhelming, because compared to the PLC controls, programming an embedded system in C is pretty less structured. You have the setup, the loop, many libraries, examples in the internet and than: Good luck!  
First I tried to find some German lessons and books in the Internet to learn from. Finally I landed with Kernighan & Ritchie - C Programming Language 2 and Steven Prata - C Primer Plus Sixth Edition. With these books I learned competently something about the C language but not very much about structuring a program for an embedded system.  
In the Internet I stumbled over terms like finite state machine and conceptions from Moore and Mealy. That was the additionally piece to C that I was looking for. And right on the Arduino homepage I found the framework plus the modeling tool of Miro Samek http://playground.arduino.cc/Code/QP that integrates different concepts.  
As an interesting and advanced project for me I decided to start with the controlling of a LED stripe with a handy.  
But as a newbie and a hobbiest it took me a longer time to understand Miro's framework and model to end up this project. Puh!  
So please don't mind if I'm sometimes a little bit euphoric about my success. And don't mind if maybe you as a professionell C and/or embedded programmer would come to other solutions. I would really like to learn from your reviews.  
Within the Issues I list tasks that should or could still be done to improve the project.  
### 2  Control of a LED stripe
But first I had to learn how to program the WS2812B 5050 RGB stripe with the WS2811 Controller.  
I found the libraries from Adafruit https://github.com/adafruit/Adafruit_NeoPixel and the alternative FastLED https://github.com/FastLED/FastLED which is mentioned in the Internet to be faster. Both libraries come with very nice examples.  
But I ended up with the small library of Nick Gammon https://github.com/nickgammon/NeoPixels_SPI , because it is lightwise and shows me the "bare metal" way to control the stripe so that I could integrate it in my sketch. My intention was to get smaller code.
### 3  Starting with the Bluetooth module for the Arduino
The next step was to get the communication between my handy and the Arduino with the Bluetooth module HC-06 to run. For that purpose I found very helpful information from Martyn Currey http://www.martyncurrey.com/arduino-and-hc-06-zs-040/ .
### 4  Programming of the handy app
The third challenge was to find something to program a handy app.  
Fortunately I didn't had to learn Java as I suspected, because according to my information from the internet this is the most common language for apps. Presumably this would have cost me some additional time.  
So I was glad to find the MIT App Inventor 2 http://appinventor.mit.edu/explore/get-started.html . Martyn Currey did already work with it to connect a bluetooth module and the Arduino http://www.martyncurrey.com/arduinobtcontrol/ .  
Additional useful help in the Internet about the use of the App Inventor can be found from Abraham Getzler https://groups.google.com/forum/#!category-topic/mitappinventortest/2cd6Uz__xA0  and Taifun  https://puravidaapps.com/snippets.php#2enableBT .  
The App Inventor is completely graphical. And it is also event driven like Miro Samek's framework and that was the second challenge. I had to get used to it, because in the beginning this was irritating. But with all the good informations in the internet about using the App Inventor I succeded quiete soon.
### 5  First Arduino sketch and handy app attempt
With I was able to realize a first sketch and an app – but got right away into trouble or let's say had to enter the next level in embedded programming: Dealing with the hardware. I simply transmitted the colour values that I generated with the sliders in my app and soon the Arduino and the app got stuck.  
Through this thread of Robin2 http://forum.arduino.cc/index.php?topic=288234.0 and that from Nick Gammon http://www.gammon.com.au/serial I learned something about the function of the USART Serial communication and that there are interrupts involved. But I learned also that during the control of the LED stripe interrupts are not alowed. So the need of the interrupt for the USART Serial communication and the strictly interdict of using interrupts while controlling the LED stripe doesn't go together. If the interrupts are off, the Serial  communication can lose data and if the interrupts are on, the control of the stripe gets corrupted, because of the strict timing that is necessary.  
Furthermore I learned that the Serial communication is asynchronous and I'm supposed to use a kind of a handshake and a frame around my communication data like a start and a stop sign for a tougher communication. For the app I came out with this solution:  

![blocks](doc/blocks.png)  
Note that I don't react to every changes of the sliders right away but only when the sliders are let gone. That way only the final changes of the values will be communicated. This relieves the communication and shortened it to what is really necessary and so frees time for the LED conrol.  
Second the Bluetooth adress of my HC-06 module is integrated for faster connection and has to be changed when using a different one.
### 6  Structured programming  
Even tough I tried to structure my sketch as general supposed like using small functions, using a switch/case structure and avoid blocking functions like delay(), I was not very happy with the overview. I needed a few status variables and was jumping from function to function. And with every change I had to go almost through the whole code.  
This is the same experience I make in my job. As better a program is structured and if the structure is shown in a graphical manner, the better it is to care for.  
For that reason I turned to the long way to learn to use the framework and the modeling tool from Miro Samek (link above). I liked it right away even tough my knowledge doesn't reach into its totally depth. The graphical modeling tool gives me a good overview coupled with the ability of  using code in the states, in the transitions or even in the underlying sketch. Furthermore I can use hierachical states what saves me repetitions. And last but not least the framework does only react on signals and events depending on the current state, so I don't have to lock them in other states manually like in sequential programs. All this together are great benefits.  
With the state machine implementation it is easy and clear to splitt the two functions that should never be active at the same time: the Serial communication and the LED control.  
One important trick with state machines, respectively event driven transitions from state to state is to use a time tick if needed to repeat something or to move on in a program. I use the same time tick for the periodically check of an app request, the handshake controlled communication and the progress in the LED programs. If there are needed more (like in my first attempt) they can simply be created in the ino sketch file within the model. More information about the implementation are within the documentation of the model.  
![state machine](doc/SMofLEDviaApp.png)
### 7  Concluding remarks
So finally I realized my project with the following cornerstones:  
A) I use two self exclusioning states: LED control and Serial communication.  
B) To reduce the communication load I only transfer the changed values and so it is only 4 char long:  
1 char for the selected value together with 1 char of the selected colour or the selected LED program. Ahead of these 2 chars comes 1 char as a start sign. And afterwards comes 1 char as a stop sign.  
C) I don't use the USART Serial interrupt itself, because it could fire at any time and so causes problems with the LED control (explained above). Instead I look activly from time to time into the USART Serial receive buffer.  
D) A once started communication has to be ended before a new one is allowed to keep control over the two basic states.  
E) The handshake is implemented this way (see picture below):  
If a colour or a LED program is changed in the app (4) and there isn't already a communication going on, it first sends only 1 char 'R' as a request to the Arduino and waits for the answer (5).  
The char lands in the receive buffer. The sketch looks time triggered (6) into the receive buffer and when it sees the request (7), it sends a transmit char 'T' to the app (8).  
If the app sees the transmit char (10), also time triggered (9) by a Clock Timer, it sends the 4 char data (11) and waits for the acknowledge of the Arduino. Because the sketch knows at this time that it awaits data it looks time triggered (12) for the start sign (13).
With the start sign '<' the sketch processes the data until the stop sign '>' shows up (14). Then it sends the acknowledge sign 'A' (14) and turns to the LED program (15).  
When the app receives the acknowledge sign it becomes ready for a next transmission (14).  
The sketch looks periodically time triggered (1, 16) into the receive buffer and turns back right away to the LED program if there is no new request (2, 17).  
![handshake](doc/handshake.png)
### 8  Technical specifications
Used hardware:  
Samsung Galaxy S5, HC-06 Bluetooth-Modul, Arduino UNO, 2m 120 LEDs WS2812B 5050 RGB Stripe with WS2811 Controller, AC adapter YU0510 5VDC 10A
### 9  Links
A) To realize my project I used:  
the online app Ide MIT App Inventor 2  
http://appinventor.mit.edu/explore/get-started.html

the Arduino IDE 1.8.x  
https://www.arduino.cc/en/Main/Software  

the QP-nano 5.8.2 for Arduino framework with its QM Graphical Modeling Tool 4.0.1  
http://playground.arduino.cc/Code/QP  

the LED library from Nick Gammon  
https://github.com/nickgammon/NeoPixels_SPI  

the Arduino SPI library from the installation path  
%Arduino installation path%\Arduino\hardware\arduino\avr\libraries\SPI\src  

To generate the sketch with the  QM Graphical Modeling Tool the library from Nick Gammon and the SPI library from Arduino has to be in the sketch path.  
![directory](doc/sketch_directory.PNG)  
B) Again for information because I'm very thankful to them:  
for sketch programming:  
Robin2  
	http://forum.arduino.cc/index.php?topic=288234.0

Nick Gammon  
	http://www.gammon.com.au/forum/?id=10894
	http://www.gammon.com.au/serial
	http://www.gammon.com.au/forum/?id=13357

Martyn Currey  
	http://www.martyncurrey.com/arduino-and-hc-06-zs-040/
	http://www.martyncurrey.com/arduinobtcontrol/

for QM programming:  
	https://state-machine.com/arduino/

for app programming:  
MIT App Inventor 2 Forum  
	https://groups.google.com/forum/#!forum/mitappinventortest/categories

Taifun  
	https://puravidaapps.com/snippets.php#2enableBT

Abraham Getzler  
	https://groups.google.com/forum/#!category-topic/mitappinventortest/2cd6Uz__xA0
