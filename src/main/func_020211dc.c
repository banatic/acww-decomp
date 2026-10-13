/* func_020211dc @ 0x020211dc, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020211dc {
    u8 pad_00[0x100];
    void *unk_100;
    u8 arr[0x1e];
    u8 unk_122;
    u8 pad_123[0x49];
    u32 unk_16C;
    u32 unk_170;
    u32 unk_174;
    u32 unk_178;
} UnkStruct_020211dc;
extern int func_020984e8(void);
extern int func_020991c8(int);
extern void func_020991a0(int);
extern int func_02073d90(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0200368c(void *, int, int, int);
extern int data_020ccf94;
extern int data_020c8c20;
extern u32 data_020d9078[2];
extern u32 data_020d9498[2];
int func_020211dc(UnkStruct_020211dc *self)
{
    int r4;
    int ret1;
    int ret2;
    UnkStruct_020211dc *ptr;
    r4 = func_020991c8(func_020984e8());
    if (func_02073d90(data_020ccf94) != 0) {
        r4 = 10;
    }
    ptr = self;
    if (r4 < 10) {
        if (1) {
            int v = *((int *) (((char *) self->unk_100) + 0x830));
            ret1 = func_0208150c(v);
            ret2 = func_020036e8(ret1);
            func_0200368c(ptr->arr, 30, data_020c8c20, ret2);
            self->unk_122 = r4;
            func_020991a0(func_020984e8());
        }
        {
            volatile u32 *srcA = (volatile u32 *) data_020d9078;
            u32 a0;
            u32 a1;
            volatile u32 *srcB;
            u32 b0;
            u32 b1;
            a0 = srcA[0];
            a1 = srcA[1];
            self->unk_16C = a0;
            self->unk_170 = a1;
            srcB = (volatile u32 *) data_020d9498;
            b0 = srcB[0];
            b1 = srcB[1];
            self->unk_174 = b0;
            self->unk_178 = b1;
        }
        return 1;
    } else {
        return 0;
    }
}
