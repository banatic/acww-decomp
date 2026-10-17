/* The table of Native functions, empty: the runtime built without the Native objects (a
 * Reference run; tools/run.py without --native). native_run.c then finds nothing to run. */
#include "native_table.h"
#include "native_guest.h"

/* No Native objects or entry wrappers are linked into the Reference binary. */
void (*native_guest_enter_hook)(uint32_t index, uintptr_t caller, const uint32_t *args);
uintptr_t (*native_guest_return_hook)(uint32_t index);
uint32_t (*native_guest_slot_hook)(uint32_t owner, uint32_t offset, uint32_t size);

const NativeFunction native_functions[1];
const uint32_t native_function_count = 0;
const NativeBody native_bodies[1];
const uint32_t native_body_count = 0;
const NativeBody clean_bodies[1];
const uint32_t clean_body_count = 0;
const NativeFunction clean_functions[1];
const uint32_t clean_function_count = 0;
const NativePrivate native_private[1];
const uint32_t native_private_count = 0;
const char *const native_module_names[1];
const uint32_t native_module_count = 0;
