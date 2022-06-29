#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hardware/invcase.h>

int main() {

    int err;
    struct invcase_module_t *module = NULL;
    struct invcase_device_t *device = NULL;
    char buffer[INVCASE_BUFFER_MAX_SIZE];

    printf("InvCase Conventional HAL Test App\n");

    err =  hw_get_module(
        INVCASE_HARDWARE_MODULE_ID, 
        (struct hw_module_t const**) &module
    );

    if (err != 0) {
		printf("hw_get_module() failed: (%s)\n", strerror(-err));
        return -1;
	} else {
        printf("hw_get_module() OK\n");
		if (module->common.methods->open(
                    (struct hw_module_t *) module, 
                    INVCASE_HARDWARE_MODULE_ID, 
                    (struct hw_device_t **) &device
                ) != 0) {
			printf("HAL failed to open! (%s)\n",strerror(-err));
			return -1;
		} else {
            printf("hw_get_module() Open: OK\n");
        }
	}

    printf("Input a string: ");
    scanf("%s", buffer);

    err = device->write(buffer, strlen(buffer));
    if (err != 0) {
        printf("HAL failed to write! (%s)\n", strerror(-err));
    }

    err = device->read(buffer, INVCASE_BUFFER_MAX_SIZE);
    if (err != 0) {
        printf("HAL failed to read! (%s)\n", strerror(-err));
    }

    printf("Converted string: ");
    printf("%s\n", buffer);

    return 0;
}
