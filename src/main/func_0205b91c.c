/* func_0205b91c @ 0x0205b91c, 0x144 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0204df30(int);
extern void func_0205a370(void *self, void *p1, void *p2, void *p3, void *obj);
extern void func_0205a6f0(void *self, void *obj, u8 *b0, u8 *b1);
extern void func_0205ad00(void *self, void *obj);
extern int func_0205affc(void *self, void *obj, unsigned int *p);
extern int func_0205aec0(void *self, void *obj);
extern int func_0205adc0(void *self, void *obj);
extern void *func_02060ee0(void *addr, int param);
extern u16 *func_02061204(void *addr, int param);
extern u16 *func_020611e8(void *addr, int param);
extern void MI_CpuFill8(void *dst, int value, int size);

extern u32 data_021c997c[74];
extern char data_021c9854[0x128];

typedef struct {
    char pad_00[0x28];
    u32 unk_28;
} G2Struct;
extern G2Struct data_021c9a7c;

extern unsigned char data_021ebcd4[];

int func_0205b91c(void *self, int *out)
{
    void *obj;
    int count;
    int flags;
    int result1, result2, result3;
    void *ptr;
    u8 b0, b1;
    unsigned int local_int;
    unsigned int i;

    obj = func_0204df30(0);
    count = 3;
    flags = 0;

    if (obj != 0) {
        for (i = 0; i < 0x4A; i++) {
            data_021c997c[i] = flags;
        }
        data_021c9a7c.unk_28 = flags;
        MI_CpuFill8(data_021c9854, flags, 0x128);

        func_0205a370(self, (char *) self + 8, (char *) self + 4, (char *) self + 12, obj);

        *(u16 *) ((char *) self + 0x10) = 0x1100;
        *(u16 *) ((char *) self + 0x12) = 0x1144;

        ptr = func_02060ee0((void *) data_021ebcd4, 0);
        if (ptr != 0) {
            *(u16 *) ((char *) self + 0x10) = *func_02061204(ptr, 0);
            *(u16 *) ((char *) self + 0x12) = *func_020611e8(ptr, 0);
        }

        b0 = 0;
        b1 = 0;
        func_0205a6f0(self, obj, &b0, &b1);

        func_0205ad00(self, obj);

        local_int = 0;
        result1 = func_0205affc(self, obj, &local_int);
        result2 = func_0205aec0(self, obj);
        result3 = func_0205adc0(self, obj);

        if (b1 != 0) {
            count--;
            flags |= 1;
        }
        if (b0 != 0) {
            count--;
            flags |= 2;
        }

        if ((data_021c9a7c.unk_28 & 0xf) == 0xf) {
            count++;
            flags |= 4;
        }

        if (result2 != 0 || result3 != 0) {
            flags |= 8;
            count++;
        }
        if (result2 == 0 || result3 == 0) {
            flags |= 0x40;
        }

        if (result1 != 0x4A) {
            count += 2;
            flags |= 0x10;
        } else if (local_int >= 5) {
            flags |= 0x20;
        }
    }

    if (out != 0) {
        *out = count;
    }
    return flags;
}
