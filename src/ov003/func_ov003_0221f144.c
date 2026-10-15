/* func_ov003_0221f144 @ 0x0221f144, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;
typedef struct {
    fx32 m[12];
} Mtx43;

extern void *data_021c67a4; // 0x021c67a4
extern Vec data_021c67d0;   // 0x021c67d0
extern Mtx43 data_021fbe48; // 0x021fbe48
extern fx32 data_020ca0e4;
extern void func_020e96c8(Mtx43 *, fx32, fx32, fx32);
extern int func_0203c590(void *);
extern void func_020e9774(Mtx43 *, int);

typedef struct {
    char pad_00[0x64];
    Mtx43 m;
} UnkStruct_0221f144;

int func_ov003_0221f144(UnkStruct_0221f144 *self)
{
    void *x = data_021c67a4;
    volatile fx32 coordinates[3];
    if (x != 0) {
        coordinates[0] = data_021c67d0.x;
        coordinates[1] = data_021c67d0.y;
        coordinates[2] = data_021c67d0.z;
        func_020e96c8(&data_021fbe48, data_021c67d0.x - data_020ca0e4, 0, 0);
        func_020e9774(&data_021fbe48, func_0203c590(x));
        self->m = data_021fbe48;
        return 1;
    }
    return 0;
}
