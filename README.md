# LEDviaApp

Der Weg zur Umsetzung dieses Projekts war/ist für einen newbie in der embedded world schon ganz schön anspruchsvoll. Deshalb will ich dazu ein paar Bemerkungen posten.

Zu aller erst musste ich die Ansteuerung des WS2812B 5050 RGB Stripe mit WS2811 Controller bewältigen. Dazu gibt es überlicherweise die libary des Distributors Adafruit Industries https://github.com/adafruit/Adafruit_NeoPixel oder als Alternative die libary von FastLED https://github.com/FastLED/FastLED , welche als schneller gilt. Beide liefern tolle Sketche mit verschiedenen Effekten mit. Ich habe mich nach einigen Versuchen für eine weitere alternative libary von Nick Gammon https://github.com/nickgammon/NeoPixels_SPI entschieden, da sie mir die "bare metal" Ansteuerung des LED-Streifens zur Verfügung stellt. Damit konnte ich schon einige Variationen für die direkte Ansteuerung des RGB Stripe mit der Arduino IDE realisieren.

Die nächste Herausforderung war die Kommunikationserweiterung des UNO durch das Bluetooth-Modul HC-06 mit einem Handy. Dazu fand ich sehr hilfreiche Informationen von Martyn Currey. http://www.martyncurrey.com/arduino-and-hc-06-zs-040/ und http://www.martyncurrey.com/arduinobtcontrol/

Jetzt fehlte nur noch die Programmierung einer App für das Handy. Glücklicherweise mußte ich dazu nicht erst Java lernen, sondern stieß u.a. durch Martyn Currey auf den MIT App Inventor 2. http://appinventor.mit.edu/explore/get-started.html Auch dazu hatte Martyn Currey schon gearbeitet. http://www.martyncurrey.com/arduinobtcontrol/
Weitere wertvolle Hilfe zum MIT App Inventor 2 im Allgemeinen und zur Bluetooth Kommmunikation im Speziellen findet man von Abraham Getzler https://groups.google.com/forum/#!category-topic/mitappinventortest/2cd6Uz__xA0 und Taifun https://puravidaapps.com/snippets.php#2enableBT

Mit all diesen Informationen konnte ich einen ersten ino-Sketch und eine erste App ersellen.

Als Problem stellte sich heraus, dass sich die Kommunikation mit dem Handy und die Ansteuerung des LED-Streifens gegenseitig stören, was zu Hängern und undefiniertem Verhalten führt.
Insbesondere, wenn ich die Werte der Farb Slider in der App so programmiere, dass sie permanent die Änderung der Werte übertragen.
Zum Verständnis der seriellen Kommunikation halfen mir die Forum-Diskussionen von Robin2  http://forum.arduino.cc/index.php?topic=288234.0 und wiederum Nick Gammon. http://www.gammon.com.au/serial

Dadurch wurde mir klar, dass ich die Kommunikation zwischen UNO und Handy und die Ansteuerung des LED Stripes durch den UNO prinzipiell trennen muss.
Und das ich eine Art von Handshake für die Kommuniukation zwischen dem UNO und dem Handy benötigte, da diese asynchron verläuft. D.h. keiner wartet per se auf den anderen, sondern man muss die Kommunikation regeln.
