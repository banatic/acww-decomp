/* func_020f70b4 @ 0x020f70b4, 0x1c bytes, ARM, module autoload_2
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

extern void func_020eed48(ENVResource *resSet);

extern void func_020f70b4(ENVResource *resSet);

extern void func_020f6f3c(void *resSet);

void func_020f70b4(ENVResource *resSet)
{
    func_020f6f3c(resSet);
    func_020eed48(resSet);
}
