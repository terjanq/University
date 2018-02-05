# Lista 7 (nieobowiązkowa)


1.  Zaprojektuj płytkę drukowaną jedno- lub dwustronną (PCB) dla kostki elektronicznej opartej o układ CMOS 4060 ([schemat](http://www.learningelectronics.net/circuits/dicing-with-leds.html)) przy użyciu programu Eagle lub KiCad. Zadbaj o układ diod przypominający kostkę (zgodnie z rysunkiem), wygodne położenie przycisku oraz piny do podpięcia zasilania. **[3]**
2.  Zrealizuj termostat wzorem zadania 3 z listy 3, jednak zamiast histerezy zastosuj kontroler PID. Prawidłowo działający kontroler może ustawić temperaturę czujnika na zadaną bez wahań charakterystycznych dla histerezy. **[3]**
3.  Wykorzystaj system FreeRTOS, aby mikrokontroler wykonywał jednocześnie efekt z zadania 1 i 2 z listy 1 (przewijanie LED i zapamiętywanie przycisku). Obsługa obu efektów powinna być w dwóch osobnych procesach FreeRTOS. **[2]**
4.  Zlutuj (na płytce stykowej perfboard/stripboard lub samodzielnie wykonanej płytce PCB) układ programatora [USBasp](http://www.fischl.de/usbasp/). Zaprogramuj mikrokontroler programatora, np. [używając Arduino](https://www.arduino.cc/en/Tutorial/ArduinoISP). **[3]**[](http://www.fischl.de/usbasp/)
