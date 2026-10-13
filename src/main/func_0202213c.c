/* func_0202213c @ 0x0202213c, 0x1a0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02137550(void *, int);
extern u32 func_0208150c(u32);
extern u32 func_0207cc94(void *, u32 *, int);
extern u32 func_0207cf14(void *, u32);
extern s8 func_020036c0(u32);
extern void func_02094fd4(void *);
extern void func_02094fbc(void *);
extern void func_020a8c1c(void *);
extern void func_02003618(u32, void *);
extern void func_02068404(u32, int, void *);
extern int func_0207bb84(void *, u32, u32);
extern u32 func_020036e8(u32);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct UnkStruct_0202213c {
    u32 x, y;
} UnkStruct_0202213c;
extern UnkStruct_0202213c data_020d9158;
extern u8 data_020d8d20[2];
extern UnkStruct_0202213c data_020d91f0;
extern struct {
    u32 a;
    u8 b;
} data_020c8c98;
extern u32 data_021e5a2c;

struct UnkStruct_0202213c_2 {
    u8 pad_00[0x830];
    u32 val;
};

struct UnkStruct_0202213c_3 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0x100 - 0x44];
    struct UnkStruct_0202213c_2 *sub;
    u8 unk_104[0x122 - 0x104];
    u8 unk_122[1];
};

int func_0202213c(struct UnkStruct_0202213c_3 *self)
{
    int flag1;
    int flag2;
    u32 *p;
    s8 buf[2];
    u32 arr[2];
    u32 copy1[2];
    u32 other[2];
    u32 copy2[2];
    u8 temp[0x20];
    int i;
    int r6;

    func_02137550(arr, 8);
    *(UnkStruct_0202213c *) copy1 = data_020d9158;
    buf[0] = data_020d8d20[0];
    buf[1] = data_020d8d20[1];
    func_02137550(other, 8);
    flag1 = 0;
    flag2 = 0;
    other[0] = func_0208150c(self->sub->val);

    r6 = 1;
    i = 0;
    do {
        p = &arr[i];
        arr[i] = func_0207cc94(&data_021e5a2c, other, r6);
        if (arr[i] != 0) {
            copy1[i] = func_0207cf14(&data_021e5a2c, func_0208150c(arr[i]));
            buf[i] = func_020036c0(func_0208150c(arr[i]));
        }
        if (r6 < 2 && *p != 0) {
            other[r6] = func_0208150c(*p);
            r6++;
        }
        i++;
    } while (i < 2);

    func_02094fd4(temp);
    *(UnkStruct_0202213c *) copy2 = data_020d91f0;
    r6 = buf[1];
    if (r6 == 0) {
        copy2[0] = 1;
        copy2[1] = 0;
    }

    i = 0;
    do {
        func_020a8c1c(temp);
        func_02003618(func_0208150c(arr[copy2[i]]), temp);
        func_02068404(self->unk_40, i + 7, temp);
        i++;
    } while (i < 2);
    func_02094fbc(temp);

    if (copy1[0] != 0xFFFFFFFF && copy1[1] != 0xFFFFFFFF) {
        int r = func_0207bb84(&data_021e5a2c, copy1[0], copy1[1]);
        if (r == 2) {
            flag1 = 1;
        } else if (r > 2) {
            flag1 = 2;
        }
        if (buf[0] == r6) {
            if (buf[0] == 0) {
                flag2 = 1;
            } else {
                flag2 = 2;
            }
        }
    }

    {
        int a5 = func_020036e8(func_0208150c(self->sub->val));
        int a6 = data_020c8c98.a;
        int a7 = data_020c8c98.b;
        int a8;
        flag2 = flag2 * 3;
        a8 = flag1 + flag2;
        func_0202da38(self, &self->unk_104, &self->unk_122, 0x1e, a5, a6, a7, a8, 0);
    }
    return 1;
}