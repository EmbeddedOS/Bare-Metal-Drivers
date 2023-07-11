CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -o0 -Wall
LDFLAGS= --specs=nano.specs -T linker_stm32f407xx.ld -Wl,-Map=memory.map
OBJS+= 	./main.o \
		./startup_stm32f407xx.o \
		./syscalls.o

all: final.elf
	@echo "BUild final executable file done."

final.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf

flash:
	# Run openocd server, connect via GDB client or Telnet Client.
	openocd -f board/stm32f4discovery.cfg