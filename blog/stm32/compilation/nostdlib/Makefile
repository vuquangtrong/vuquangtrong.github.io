CPU=-mcpu=cortex-m4 -mthumb -mfloat-abi=soft

SPECS=-nostdlib

LINKE_FILE=linker.ld

CLAGS= $(CPU) -std=gnu11 -Wall
LDFLAGS= $(CPU) -T $(LINKE_FILE) -Wl,-Map=$@.map
DBFLAGS= -g

CC=arm-none-eabi-gcc
OD=arm-none-eabi-objdump
OC=arm-none-eabi-objcopy
SYM=arm-none-eabi-nm

all: clean main.elf main-debug.elf main.tmp vector.tmp main.bin

main.elf: main.o delay.o vector.o startup.o
	$(CC) $(LDFLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h
	$(OD) -S $@ > $@.s
	$(SYM) $@ > $@.sym

main.o: main.c
	$(CC) -c $(CLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h

delay.o: delay.c
	$(CC) -c $(CLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h

vector.o: vector.c
	$(CC) -c $(CLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h

startup.o: startup.c
	$(CC) -c $(CLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h

main-debug.elf: main.c delay.c vector.c startup.c
	$(CC) $(CLAGS) $(LDFLAGS) $(SPECS) $(DBFLAGS) $^ -o $@

main.bin: main.elf
	$(OC) -O binary $^ $@	

vector.tmp: main.o delay.o vector.o
	$(CC) $(LDFLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h
	$(SYM) $@ > $@.sym

main.tmp: main.o delay.o
	$(CC) $(LDFLAGS) $(SPECS) $^ -o $@
	$(OD) -h $@ > $@.obj_h
	$(SYM) $@ > $@.sym

# ignore error when do cleaning
clean:
	-rm *.elf *.o *.s *.sym *.tmp *.map *.bin *.obj_h
