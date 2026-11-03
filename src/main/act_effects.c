/* act_effects: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a794 @ 0x0201a794, 0x2 bytes, Thumb
 * func_0201a790 @ 0x0201a790, 0x2 bytes, Thumb
 * func_0201a74c @ 0x0201a74c, 0x44 bytes, Thumb
 * func_0201a720 @ 0x0201a720, 0x2c bytes, Thumb
 * func_0201a714 @ 0x0201a714, 0xc bytes, Thumb
 * func_0201a6f8 @ 0x0201a6f8, 0x1c bytes, Thumb
 * func_0201a6c8 @ 0x0201a6c8, 0x2e bytes, Thumb
 * func_0201a698 @ 0x0201a698, 0x30 bytes, Thumb
 * func_0201a608 @ 0x0201a608, 0x90 bytes, Thumb
 * func_0201a5d8 @ 0x0201a5d8, 0x2e bytes, Thumb
 * func_0201a5b0 @ 0x0201a5b0, 0x26 bytes, Thumb
 * func_0201a518 @ 0x0201a518, 0x98 bytes, Thumb
 * func_0201a4e4 @ 0x0201a4e4, 0x34 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0201a6c8 {
    char pad_00[0x10];
    char unk_10[0xC];
    unsigned int unk_1C;
};

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u8 unk_08;
    u8 unk_09;
} UnkStruct_0201a698_2;

typedef struct {
    u8 pad_00[0x20];
    u32 unk_20;
} UnkStruct_0201a698;

struct UnkStruct_0201a608 {
    char pad_00[0x18];
    int unk_18;
    char pad_1C[8];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned char unk_26;
};

typedef struct {
    s16 value;
    u8 unk_02;
    u8 unk_03;
} Elem;

typedef struct {
    int slots[4];  // 0x00
    Elem elems[3]; // 0x10
    int unk_1C;    // 0x1c
    int unk_20;    // 0x20
    u8 pad_24;     // 0x24
    u8 unk_25;     // 0x25
    u8 pad_26;     // 0x26
    u8 unk_27;     // 0x27
} UnkStruct_0201a518_2;

typedef struct {
    char data[28];
} UnkStruct_0201a518;

extern void MI_CpuFill8(void *p, int a, int b);
extern void MI_CpuCopy8(int a, int b, int c);
extern unsigned char *func_02018fdc(int);
extern int func_020044b0(int, int, int, int);
extern int func_020044c0(int, int, int, int);
extern void func_0200455c(int);
extern void func_0200456c(int);
extern void func_0200454c(void);
extern int func_020912ac(int p0, short p1, int p2, void *p3);
extern void func_0209129c(int);

void func_0201a720(int unused, int *ptr, int count);
void func_0201a4e4(int *array);

void func_0201a794(void *object) {}

void func_0201a790(void *object) {}

void func_0201a74c(void *p)
{
    MI_CpuFill8(p, 0xff, 0x10);
    func_0201a720((int) p, (int *) ((char *) p + 0x10), 2);
    *(unsigned int *) ((char *) p + 0x1c) = 0x137;
    *(unsigned char *) ((char *) p + 0x24) = 2;
    *(unsigned char *) ((char *) p + 0x25) = 0x3c;
    *(unsigned char *) ((char *) p + 0x27) = 0;
    *(unsigned char *) ((char *) p + 0x26) = 0;
}

void func_0201a720(int unused, int *ptr, int count)
{
    int i;
    unsigned int fill = 0;

    for (i = 0; i < count; i++) {
        MI_CpuFill8(ptr, fill, 4);
        *(short *) ptr = -1;
        ptr++;
    }
}

void func_0201a714(int arg1, int arg2, int arg3, int arg4)
{
    MI_CpuCopy8(arg3, arg2, arg4 << 2);
}

int func_0201a6f8(int *a)
{
    int res = -1;
    int i;

    for (i = 0; i < 4; i++) {
        if (a[i] == -1) {
            res = i;
            break;
        }
    }

    return res;
}

void func_0201a6c8(struct UnkStruct_0201a6c8 *s, unsigned int a, unsigned int b, unsigned int c)
{
    func_0201a720((int) s, (int *) s->unk_10, 2);
    func_0201a714((int) s, (int) s->unk_10, a, b);
    s->unk_1C = c;
}

void func_0201a698(UnkStruct_0201a698 *out, UnkStruct_0201a698_2 *arr, int idx)
{
    UnkStruct_0201a698_2 *elem;

    elem = &arr[idx];

    if (elem->unk_09) {
        func_0201a4e4((int *) out);
    }
    if (elem->unk_04) {
        func_0201a6c8((struct UnkStruct_0201a6c8 *) out, elem->unk_04, (u8) elem->unk_08, elem->unk_00);
        out->unk_20 = idx;
    }
}

void func_0201a608(struct UnkStruct_0201a608 *a, unsigned char *b)
{
    unsigned char *p = func_02018fdc(a->unk_25);
    if (b[3] == 1 || a->unk_24 == 2) {
        a->unk_24 = p[0x19];
        if (a->unk_24 == 1) {
            if (a->unk_26 == 0) {
                func_020044b0(a->unk_18, a->unk_25 + 0x84, 0x7f, 0);
            } else {
                func_0200455c((unsigned short) (a->unk_25 + 0x84));
            }
        } else {
            if (a->unk_26 == 0) {
                func_020044c0(a->unk_18, a->unk_25 + 0x84, 0x7f, 0);
            } else {
                func_0200456c((unsigned short) (a->unk_25 + 0x84));
            }
        }
    }
}

void func_0201a5d8(void *param0)
{
    unsigned char *ptr;
    unsigned char val;
    void *base;

    ptr = (unsigned char *) param0;
    if (ptr[0x24] == 1) {
        if (ptr[0x26] == 0) {
            base = *(void **) (ptr + 0x18);
            val = ptr[0x25];
            func_020044b0((int) base, val + 0x84, 0x7f, 0);
        }
    }
}

void func_0201a5b0(unsigned char *arg0)
{
    unsigned char val;
    unsigned char val2;

    val = *(unsigned char *) (arg0 + 0x24);
    if (val == 1) {
        val2 = *(unsigned char *) (arg0 + 0x26);
        if (val2 != 0) {
            func_0200454c();
        }
    }
    *(unsigned char *) (arg0 + 0x24) = 2;
    return;
}

void func_0201a518(UnkStruct_0201a518_2 *self, int param2, int param3, int param4, u16 param5, int param6)
{
    Elem *e = &self->elems[param6];
    s16 value = e->value;

    if (value < 0 || value >= 0x66) {
        return;
    }
    if (self->unk_1C != param4 || self->unk_1C == 0x137) {
        return;
    }

    if (e->unk_02 == param5) {
        int slot = func_0201a6f8((int *) self);
        if (slot != -1) {
            self->slots[slot] = func_020912ac((u16) e->value, self->unk_27, param2, &param3);
            if (e->unk_03 == 0) {
                func_0201a720((int) self, (int *) e, 1);
            }
        }
    }

    {
        UnkStruct_0201a518 *rec = (UnkStruct_0201a518 *) func_02018fdc(self->unk_25);
        char *p = (char *) rec + 12 * self->unk_20;
        s16 v2 = *(s16 *) (p + 10);
        if (v2 == param5) {
            func_0201a608((struct UnkStruct_0201a608 *) self, (unsigned char *) e);
        }
    }
}

void func_0201a4e4(int *array)
{
    int i;
    int local;
    local = 0;
    for (i = 0; i < 4; i++) {
        if (array[i] == ~local) {
            continue;
        }
        func_0209129c(array[i]);
        array[i] = ~local;
    }
    func_0201a5b0((unsigned char *) array);
}
