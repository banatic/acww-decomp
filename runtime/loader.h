/* Loading the ARM9 modules into memory at their addresses. */
#ifndef RUNTIME_LOADER_H
#define RUNTIME_LOADER_H

/* Reads the manifest tools/diffcheck.py writes (one "<module> <base> <path>" line per module)
 * and loads every resident module: main, the autoloads and the TCMs. 0 on success. */
int loader_init(const char *manifest);

/* Loads an overlay ("ov004") over its region, or does nothing for a resident module. */
int loader_load(const char *module);

#endif
