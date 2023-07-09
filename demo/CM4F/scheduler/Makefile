CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -o0 -Wall

OBJS+= 	./main.o \
		./stm32_startup.o

all: final.elf
	@echo "Building final executable file."

final.elf: $(OBJS)
	@echo "Do not thing."

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf