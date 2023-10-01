CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -o0 -Wall -D USING_SEMI_HOST

LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T linker_stm32f407xx.ld -Wl,-Map=memory.map
LDFLAGS_SEMIHOST= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T linker_stm32f407xx.ld -Wl,-Map=memory_semi.map

OBJS+= 	./main.o \
		./startup_stm32f407xx.o \
		./led.o
SYSCALLS_OBJ=syscalls.o

all: final.elf final_semihost.elf
	@echo "BUild final executable file done."

final.elf: $(OBJS) $(SYSCALLS_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

final_semihost.elf: $(OBJS)
	$(CC) $(LDFLAGS_SEMIHOST) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf

flash:
	# Run openocd server, connect via GDB client or Telnet Client.
	openocd -f board/stm32f4discovery.cfg