/* Opt-in Western names carried alongside the original Korean fixed records. */
#ifndef RUNTIME_LOCALIZED_NAMES_H
#define RUNTIME_LOCALIZED_NAMES_H

#include <stddef.h>

#define LOCALIZED_NAME_EXTENSION 64
#define LOCALIZED_NAME_CAPACITY 64

int localized_names_enabled(void);
int localized_name_stride(int original);
const char *localized_name_text(const void *record, size_t prefix);
int localized_name_attribute(const void *record, size_t prefix, unsigned index);
void *localized_name_buffer(void *owner, void *original);
void localized_name_release(void *owner);

#endif
