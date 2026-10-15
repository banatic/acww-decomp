/* ENV_SetResourceSet @ 0x020f70b4, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef u16 ENVType;

typedef struct ENVResource ENVResource;

struct ENVResource {
    char *name;
    u16 len;
    ENVType type;
    void *ptr;
};

extern void ENV_AppendResourceSet(ENVResource *resSet);

extern void ENV_SetResourceSet(ENVResource *resSet);

extern void func_020f6f3c(void *resSet);

void ENV_SetResourceSet(ENVResource *resSet)
{
    func_020f6f3c(resSet);
    ENV_AppendResourceSet(resSet);
}
