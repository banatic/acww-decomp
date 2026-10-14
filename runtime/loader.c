#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

#define MAX_MODULES 160

static struct {
    char name[16];
    unsigned base;
    char path[512];
} modules[MAX_MODULES];
static int module_count;

static int load_file(const char *path, unsigned base)
{
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *dst = memory_host(base, (uint32_t) size);
    int ok = size == 0 || (dst != NULL && fread(dst, 1, (size_t) size, f) == (size_t) size);
    fclose(f);
    return ok ? 0 : -1;
}

int loader_init(const char *manifest)
{
    FILE *f = fopen(manifest, "r");
    if (f == NULL) {
        return -1;
    }
    char line[640];
    while (module_count < MAX_MODULES && fgets(line, sizeof(line), f) != NULL) {
        if (sscanf(line, "%15s %x %511[^\r\n]", modules[module_count].name, &modules[module_count].base,
                   modules[module_count].path) == 3) {
            module_count++;
        }
    }
    fclose(f);
    for (int i = 0; i < module_count; i++) {
        if (strncmp(modules[i].name, "ov", 2) != 0 && load_file(modules[i].path, modules[i].base) != 0) {
            fprintf(stderr, "cannot load %s from %s\n", modules[i].name, modules[i].path);
            return -1;
        }
    }
    return 0;
}

int loader_load(const char *module)
{
    for (int i = 0; i < module_count; i++) {
        if (strcmp(modules[i].name, module) == 0) {
            if (strncmp(module, "ov", 2) != 0) {
                return 0;
            }
            return load_file(modules[i].path, modules[i].base);
        }
    }
    return -1;
}
