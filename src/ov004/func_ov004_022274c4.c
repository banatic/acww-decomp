/* func_ov004_022274c4 @ 0x022274c4, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022274c4 {
    u8 pad_00[0x2d0];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
    int room;
};

extern int func_02056f94(void *p);
extern void func_0200f3e8(struct UnkStruct_022274c4 *self);
extern int func_02008258(struct UnkStruct_022274c4 *self, int a);
extern int func_0200d4e8(struct UnkStruct_022274c4 *self, int a, int b, int c);
extern int func_02073908(int a, int b);
extern int func_0203e110(void);
extern int data_020ccf94;

int func_ov004_022274c4(struct UnkStruct_022274c4 *self)
{
    int result = func_02056f94(&self->sub);
    if (result) {
        func_0200f3e8(self);
        self->handle = func_02008258(self, self->src);
        func_0200d4e8(self, 3, 1, -1);
        result = func_02073908(data_020ccf94, self->room);
        if (result) {
            result = func_0203e110();
        }
    }
    return result;
}
