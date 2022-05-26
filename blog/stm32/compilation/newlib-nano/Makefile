CPU=-mcpu=cortex-m4 -mthumb -mfloat-abi=soft

SPECS_NANO=--specs=nano.specs --specs=nosys.specs
SPECS_SEMI=--specs=rdimon.specs

LINKE_FILE=linker.ld

LIKER_NANO=
LIKER_SEMI=-lrdimon

DEFINE_NANO=
DEFINE_SEMI=-DUSE_SEMIHOSTING

CLAGS= $(CPU) -std=gnu11 -Wall
LDFLAGS= $(CPU) -T $(LINKE_FILE) -Wl,-Map=$@.map
DBFLAGS= -g

CC=arm-none-eabi-gcc
OD=arm-none-eabi-objdump
OC=arm-none-eabi-objcopy
SYM=arm-none-eabi-nm

all: clean main.elf main-debug.elf main-semi.elf 

main.elf: main.c delay.c vector.c startup.c
	$(CC) $(CLAGS) $(DEFINE_NANO) $(LDFLAGS) $(SPECS_NANO) $(LIKER_NANO) $^ -o $@

main-debug.elf: main.c delay.c vector.c startup.c
	$(CC) $(CLAGS) $(DEFINE_NANO) $(LDFLAGS) $(SPECS_NANO) $(LIKER_NANO) $(DBFLAGS) $^ -o $@

main-semi.elf: main.c delay.c vector.c startup.c
	$(CC) $(CLAGS) $(DEFINE_SEMI) $(LDFLAGS) $(SPECS_SEMI) $(LIKER_SEMI) $^ -o $@

# ignore error when do cleaning
clean:
	-rm *.elf *.o *.s *.sym *.tmp *.map *.bin *.obj_h
