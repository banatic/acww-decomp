/* The table of Native functions, empty: the runtime built without the Native objects (a
 * Reference run; tools/run.py without --native). native_run.c then finds nothing to run. */
#include "native_table.h"

const NativeFunction native_functions[1];
const uint32_t native_function_count = 0;
const NativePrivate native_private[1];
const uint32_t native_private_count = 0;
const char *const native_module_names[1];
const uint32_t native_module_count = 0;
