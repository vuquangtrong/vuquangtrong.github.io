#ifndef INVCASE_LEGACY_H
#define INVCASE_LEGACY_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INVCASE_BUFFER_MAX_SIZE 1024

int invcase_read(char *buf, size_t count);
int invcase_write(char *buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* INVCASE_LEGACY_H */
