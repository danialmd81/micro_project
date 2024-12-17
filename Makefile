MCU = atmega64
F_CPU = 8000000UL
BAUD = 9600

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -gdwarf-2 -fsigned-char -MD -MP -mmcu=$(MCU) -DF_CPU=$(F_CPU) -O1
		 
TARGET = main

# Source files
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET).hex clean_intermediate

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex $< $(TARGET).eep || exit 0

clean_intermediate:
	rm -f src/*.o src/*.d 

clean:
	rm -f *.elf *.eep $(TARGET).hex 
	rm -f src/*.o src/*.d 

.PHONY: all clean clean_intermediate