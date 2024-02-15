default: build

build:
	# cree le fichier de compilation
	avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p src/*.c -o build/main
	# DF_CPU: indique la frequence de la cloc arduino pour la fonction _delay_ms()
	# mmcu: indique le microcontrolleur utilise
	# src/*.c: inclus tout les fichiers se terminant en .c pour la compialtion
	# -o build/main: compile en un fichier 'main' situe dans le folder build/ 

burn: build
	# convertit puis flash le programme main sur la memoire de l'arduino
	avr-objcopy -O ihex -R .eeprom build/main build/main.hex
	# convertit le fichier main en un fichier main.hex qui vas etre envoyer sur le uC
	# .hex: format de programme develope par intel pour certain microcontrolleur

	avrdude -F -V -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:build/main.hex
	# /dev/ttyACM0: port USB ou l'arduino est connecte (linux)
	# 115200: baud rate de la liaison serial usb arduino-pc
