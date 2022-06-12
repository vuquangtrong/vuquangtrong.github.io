BINARY := invcase
BUILD := /lib/modules/$(shell uname -r)/build
obj-m := $(BINARY).o

all:
	make -C $(BUILD) M=$(PWD) modules

install:
	echo 'KERNEL=="invcase", SUBSYSTEM=="invcase", MODE="0777"' | sudo tee /etc/udev/rules.d/99-invcase.rules
	sudo insmod $(BINARY).ko
	
remove:
	sudo rmmod $(BINARY)

clean:
	make -C $(BUILD) M=$(PWD) clean

