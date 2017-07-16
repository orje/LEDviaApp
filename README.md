# LEDviaApp

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

Letztendlich habe ich mich dafür entschieden, 
1. die Datenübertragung klein zu halten. Es wird immer nur ein Zeichen für die über das Handy gewählte Farbe oder das gewählte Anzeige-Programm plus dem Farb- oder Programmwert übertragen.
2. dass das Handy zuerst nur ein Zeichen als Anfrage überträgt.
3. der Sketch / das model zeitgetriggert im Empfangsbuffer nachschaut, ob ein Anfrage-Zeichen vorliegt und dann von der LED-Ansteuerung zur Kommunikation umschaltet.
4. dass die Daten von einem Start- und einem Endzeichen eingerahmt werden, um den Beginn der Datenübernahme zu starten und das Ende der Kommunikation zu erkennen und zu quittieren.
