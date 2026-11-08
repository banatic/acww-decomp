/* The extension never changes the original record prefix or a game object's layout. */
#include "localized_names.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NameBuffer {
    struct NameBuffer *next;
    void *owner;
    uint8_t text[LOCALIZED_NAME_CAPACITY];
} NameBuffer;

static NameBuffer *buffers;

int localized_names_enabled(void)
{
    const char *flag = getenv("ACWW_NAMES");
    return flag != NULL && strcmp(flag, "1") == 0;
}

int localized_name_stride(int original)
{
    return original + (localized_names_enabled() ? LOCALIZED_NAME_EXTENSION : 0);
}

static const uint8_t *name_extension(const void *record, size_t prefix)
{
    if (!localized_names_enabled() || record == NULL) {
        return NULL;
    }
    const uint8_t *extension = (const uint8_t *) record + prefix;
    if (memcmp(extension, "LTXT", 4) != 0) {
        return NULL;
    }
    for (size_t at = 8; at + 1 < LOCALIZED_NAME_EXTENSION; at += 2) {
        if (extension[at] == 0 && extension[at + 1] == 0) {
            return extension;
        }
    }
    return NULL;
}

const char *localized_name_text(const void *record, size_t prefix)
{
    const uint8_t *extension = name_extension(record, prefix);
    return extension != NULL ? (const char *) extension + 8 : NULL;
}

int localized_name_attribute(const void *record, size_t prefix, unsigned index)
{
    const uint8_t *extension = name_extension(record, prefix);
    if (extension == NULL || index > 2) {
        return -1;
    }
    unsigned value = extension[4 + index];
    return value == 255 || (index == 2 && value > 2) ? -1 : (int) value;
}

/* Each live name text gets its own buffer, also when the object itself is on a guest stack.
 * The virtual buffer/capacity slots use it; each class releases it from both destructors. */
void *localized_name_buffer(void *owner, void *original)
{
    if (!localized_names_enabled()) {
        return original;
    }
    for (NameBuffer *buffer = buffers; buffer != NULL; buffer = buffer->next) {
        if (buffer->owner == owner) {
            return buffer->text;
        }
    }
    NameBuffer *buffer = calloc(1, sizeof(*buffer));
    if (buffer == NULL) {
        fputs("localized names: cannot allocate text buffer\n", stderr);
        exit(1);
    }
    buffer->owner = owner;
    buffer->next = buffers;
    buffers = buffer;
    return buffer->text;
}

void localized_name_release(void *owner)
{
    for (NameBuffer **link = &buffers; *link != NULL; link = &(*link)->next) {
        if ((*link)->owner == owner) {
            NameBuffer *buffer = *link;
            *link = buffer->next;
            free(buffer);
            return;
        }
    }
}
