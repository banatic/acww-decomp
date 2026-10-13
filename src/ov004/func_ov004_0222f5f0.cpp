/* func_ov004_0222f5f0 @ 0x0222f5f0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222f5f0 {
    int a, b;
    ~UnkStruct_0222f5f0() {}
};
extern "C" {
extern void func_0203ee14(void *, void *);
extern void func_020a8164(void *, void *);
extern void *data_ov004_02255304;
}

extern "C" int func_ov004_0222f5f0(char *self)
{
    UnkStruct_0222f5f0 t;
    char *b = self;
    if (self != 0) {
        b = self + 0x290;
    }
    func_0203ee14(self, b);
    func_020a8164(self + 0x290, data_ov004_02255304);
    *(u8 *) (self + 0x2ae) = 0;
    *(int *) (*(char **) (self + 0x2d0) + 8) = 1;
    return 1;
}
