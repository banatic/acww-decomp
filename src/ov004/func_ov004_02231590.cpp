/* func_ov004_02231590 @ 0x02231590, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02231590 {
    int a;
    ~UnkStruct_02231590() {}
};

extern "C" {
extern void func_02068bc4(void *, int);
extern void func_02068bb8(void *, int);
}
extern "C" void func_ov004_02231590(char *self)
{
    UnkStruct_02231590 t;
    char *p = *(char **) (self + 0x2d0);
    switch (*(u8 *) (self + 0x2ae)) {
        case 0xe:
            func_02068bc4(p + 0x1a2c, 0);
            break;
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_02068bb8(p + 0x1a2c, 0);
            break;
    }
}
