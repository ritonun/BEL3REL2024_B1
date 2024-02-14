default: build

build:
	avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p main.c -o main
	# DF_CPU: indique la frequence de la cloc arduino pour la fonction _delay_ms()
	# mmcu: indique le microcontrolleur utilise

burn: build
	avr-objcopy -O ihex -R .eeprom main main.hex
	# .hex: format de programme develope par intel pour certain microcontrolleur

	avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex
	# /dev/ttyACM0: port USB ou l'arduino est conecte (linux)
	# 115200: baud rate de la liaison serial usb arduino-pc