# LEDviaApp

[Bild](doc/SM%20of%20LEDviaApp.png)

Hier ein Demo-Video: https://www.youtube.com/watch?v=ySMSormm9lA

Der Weg zur Umsetzung dieses Projekts war/ist für einen newbie in der embedded world schon ganz schön anspruchsvoll. Deshalb will ich dazu ein paar Bemerkungen posten.

Zu allererst musste ich die Ansteuerung des WS2812B 5050 RGB Stripe mit WS2811 Controller bewältigen. Dazu gibt es überlicherweise die libary des Distributors Adafruit Industries  https://github.com/adafruit/Adafruit_NeoPixel  oder als Alternative die libary von FastLED  https://github.com/FastLED/FastLED  , welche in Internet-Foren als schneller gilt. Beide liefern tolle Sketche mit verschiedenen Effekten aus. Ich habe mich nach einigen Versuchen für eine weitere alternative libary von Nick Gammon  https://github.com/nickgammon/NeoPixels_SPI  entschieden, da sie mir die "bare metal" Ansteuerung des LED-Streifens zur Verfügung stellt. Damit konnte ich schon einige Variationen für die direkte Ansteuerung des RGB Stripe mit der Arduino IDE realisieren.

Die nächste Herausforderung war die Kommunikationserweiterung des UNO durch das Bluetooth-Modul HC-06 mit einem Handy. Dazu fand ich sehr hilfreiche Informationen von Martyn Currey  http://www.martyncurrey.com/arduino-and-hc-06-zs-040/  und  http://www.martyncurrey.com/arduinobtcontrol/

Jetzt fehlte nur noch die Programmierung einer App für das Handy. Glücklicherweise mußte ich dazu nicht erst Java lernen, sondern stieß u.a. durch Martyn Currey auf den MIT App Inventor 2  http://appinventor.mit.edu/explore/get-started.html  Auch dazu hatte Martyn Currey schon gearbeitet  http://www.martyncurrey.com/arduinobtcontrol/
Weitere wertvolle Hilfe zum MIT App Inventor 2 im allgemeinen und zur Bluetooth-Kommmunikation im speziellen findet man von Abraham Getzler  https://groups.google.com/forum/#!category-topic/mitappinventortest/2cd6Uz__xA0  und Taifun  https://puravidaapps.com/snippets.php#2enableBT

Mit all diesen Informationen konnte ich einen ersten ino-Sketch und eine erste App erstellen.

Als Problem stellte sich heraus, dass sich die Kommunikation mit dem Handy und die Ansteuerung des LED-Streifens gegenseitig stören, was zu Hängern und undefiniertem Verhalten führt.
Insbesondere, wenn ich die Werte der Farb-Slider in der App so programmiere, dass sie permanent die Änderung der Werte übertragen.

Zum Verständnis der seriellen Kommunikation halfen mir die Forum-Diskussionen von Robin2  http://forum.arduino.cc/index.php?topic=288234.0  und wiederum Nick Gammon  http://www.gammon.com.au/serial  Dadurch wurde mir klar, dass ich die Kommunikation zwischen UNO und Handy und die Ansteuerung des LED-Stripe durch den UNO prinzipiell trennen muss. Hintergrund ist, dass die LED-Ansteuerung aufgrund von Timing-Anforderungen die Interruptverarbeitung zeitweise abschalten muss, wogegen die serielle Kommunikation Interrupts benötigt. Fehlen ihr diese, können Kommunikationsdaten verloren gehen.  
Ferner benötige ich eine Art von Handshake für die Kommuniukation zwischen dem UNO und dem Handy, da diese asynchron verläuft. D.h. keiner wartet per se auf den anderen, sondern man muss die Kommunikation regeln.

Bei der Umsetzung meines Sketches und meiner App wandte ich die allgemein empfohlene Programmstrukturierung an, Aufgaben in möglichst kleine Funktionen zu gliedern, die Aufrufstruktur möglichst mit switch/case umzusetzen und nicht die blockierende delay()-Funktion zu benutzen.
Da ich mich als newbie parallel zur Umsetzung dieses Projektes, weiterhin mit dem Thema C-Programmierung im allgemeinen und die Frage der Strukturierung von Programmen im besonderen hineinlas, stieß ich auf das framework plus dem modeling tool von Miro Samek  http://playground.arduino.cc/Code/QP  Das framework setzt nicht nur die allgemein postulierten Programmstrukturtechniken um, sondern stellt mit dem modeling tool auch eine Möglichkeit (kein Muss) zur Verfügung, die Struktur graphisch zu kreieren.
Allerdings erfordert es eine intensive Einarbeitung. Als Ergebnis habe ich aber nun ein m.M. nach übersichtliches Programm.

Letztendlich habe ich mich beim Programmdesign dafür entschieden, 
1. die Datenübertragung klein zu halten. Es wird immer nur ein Zeichen für die auf dem Handy gewählte Farbe oder das gewählte Anzeige-Programm plus dem Farb- oder Programmwert übertragen.
2. dass das Handy zuerst nur ein Zeichen als Anfrage überträgt. Denn das landet auf jeden Fall hardwaregesteuert im Empfangsbuffer.
3. dass der Sketch / das model zeitgetriggert im Empfangsbuffer nachschaut, ob ein Anfrage-Zeichen vorliegt und dann von der LED-Ansteuerung zur Kommunikation umschaltet. Dabei nutze ich bei den LED-Animationsprogrammen die Pause zwischen den Animationstakten.
4. dass die Daten von einem Start- und einem Endzeichen eingerahmt werden, um den Beginn der Datenübernahme zu starten und das Ende der Kommunikation zu erkennen und zu quittieren.
