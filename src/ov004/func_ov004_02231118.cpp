/* func_ov004_02231118 @ 0x02231118, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02231118 {
    int a, b;
    ~UnkStruct_02231118() {}
};
extern "C" {
extern void func_0203ee14(void *, void *);
extern void func_020a8164(void *, void *);
extern int func_02073d90(void *);
extern void *data_ov004_022557b8;
extern void *data_020ccf94;
}

extern "C" void func_ov004_02231118(char *self)
{
    UnkStruct_02231118 t;
    char *b = self;
    if (self != 0) {
        b = self + 0x290;
    }
    func_0203ee14(self, b);
    func_020a8164(self + 0x290, data_ov004_022557b8);
    if (func_02073d90(data_020ccf94) != 0) {
        *(u8 *) (self + 0x2ae) = 0x1d;
    } else {
        *(u8 *) (self + 0x2ae) = 0xe;
    }
    *(int *) (*(char **) (self + 0x2d0) + 8) = 1;
}
