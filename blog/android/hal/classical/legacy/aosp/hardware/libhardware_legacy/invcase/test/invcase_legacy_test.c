#include <stdio.h>
#include <string.h>
#include "hardware_legacy/invcase.h"

int main()
{
    char buffer[INVCASE_BUFFER_MAX_SIZE];
    printf("InvCase Legacy HAL Test App\n");
    printf("Input a string: ");
    scanf("%s", buffer);
    invcase_write(buffer, strlen(buffer));
    invcase_read(buffer, INVCASE_BUFFER_MAX_SIZE);
    printf("Converted string: ");
    printf("%s\n", buffer);
    return 0;
}
