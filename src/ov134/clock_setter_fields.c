/* clock_setter_fields: 15 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_0229abd4 @ 0x0229abd4, 0x64 bytes, Thumb
 * func_ov134_0229ab80 @ 0x0229ab80, 0x54 bytes, Thumb
 * func_ov134_0229ab2c @ 0x0229ab2c, 0x54 bytes, Thumb
 * func_ov134_0229aad8 @ 0x0229aad8, 0x54 bytes, Thumb
 * func_ov134_0229aaa8 @ 0x0229aaa8, 0x30 bytes, Thumb
 * func_ov134_0229aa78 @ 0x0229aa78, 0x30 bytes, Thumb
 * func_ov134_0229aa6c @ 0x0229aa6c, 0xc bytes, Thumb
 * func_ov134_0229aa4c @ 0x0229aa4c, 0x1e bytes, Thumb
 * func_ov134_0229aa3c @ 0x0229aa3c, 0x10 bytes, Thumb
 * func_ov134_0229a96c @ 0x0229a96c, 0xd0 bytes, Thumb
 * func_ov134_0229a918 @ 0x0229a918, 0x54 bytes, Thumb
 * func_ov134_0229a8e8 @ 0x0229a8e8, 0x2e bytes, Thumb
 * func_ov134_0229a8a8 @ 0x0229a8a8, 0x40 bytes, Thumb
 * func_ov134_0229a8a0 @ 0x0229a8a0, 0x6 bytes, Thumb
 * func_ov134_0229a868 @ 0x0229a868, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xa0];
    unsigned char sel;
} FileInfo;

struct UnkStruct_0229aa78 {
    char pad_00[0xA0];
    unsigned char type;
};

typedef struct {
    u8 pad_00[0xa0];
    u8 unk_A0;
    u8 pad_A1[0x10];
    u8 unk_B1;
    u8 pad_B2[0x9];
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
    u8 pad_BE[0x870 - 0xbe];
} UnkStruct_0229a96c;

typedef struct {
    unsigned char pad_00[177];
    unsigned char unk_B1;
} UnkStruct_0229a8a0;

typedef struct {
    char pad_00[0xb1];
    unsigned char b;
} UnkStruct_0229a868;

extern void *data_ov134_0229bfd4[];
extern void *data_ov134_0229bfec[];
extern void *data_ov134_0229bf74[];
extern int data_ov134_0229bf8c[];
extern int data_ov134_0229bfbc[];
extern int data_ov134_0229c004[];
extern int data_ov134_0229bfa4[];
extern int func_0209de88(int year, int month, int day);
extern void func_ov134_022995a0(UnkStruct_0229a96c *self, int n);
extern void func_ov134_022995b0(UnkStruct_0229a96c *self, int n);
extern void func_0206fdd4(void *dst, int a, int b, int c, int d, int e);

void *func_ov134_0229aaa8(FileInfo *self, int idx);
int func_ov134_0229aa78(struct UnkStruct_0229aa78 *self, int index);
int func_ov134_0229aa4c(int a, int b);
int func_ov134_0229aa3c(void *argument0, int argument1);

int func_ov134_0229abd4(void *self, int a, int b)
{
    int i;
    int x = a >> 3;
    int y = b >> 3;
    for (i = 0; i <= 4; i++) {
        int extra;
        if (i == 3) {
            extra = 2;
        } else {
            extra = 3;
        }
        if ((int) func_ov134_0229aaa8((FileInfo *) self, i) > x) {
            continue;
        }
        if (func_ov134_0229aa4c((int) self, i) + extra < x) {
            continue;
        }
        if (func_ov134_0229aa78((struct UnkStruct_0229aa78 *) self, i) > y) {
            continue;
        }
        if (func_ov134_0229aa3c(self, i) < y) {
            continue;
        }
        return i;
    }
    return 6;
}

int func_ov134_0229ab80(void *p, int a, int b)
{
    int i;
    int r4 = a >> 3;
    int r6 = b >> 3;

    for (i = 0; i <= 2; i++) {
        if ((int) func_ov134_0229aaa8((FileInfo *) p, i) > r4) {
            continue;
        }
        if (func_ov134_0229aa4c((int) p, i) + 3 < r4) {
            continue;
        }
        if (func_ov134_0229aa78((struct UnkStruct_0229aa78 *) p, i) > r6) {
            continue;
        }
        if (func_ov134_0229aa3c(p, i) < r6) {
            continue;
        }
        return i;
    }
    return 6;
}

int func_ov134_0229ab2c(int a, int b, int c)
{
    int i;
    int r4 = b >> 3;
    int r6 = c >> 3;

    for (i = 1; i <= 2; i++) {
        if ((int) func_ov134_0229aaa8((FileInfo *) a, i) > r4) {
            continue;
        }
        if (func_ov134_0229aa4c(a, i) + 3 < r4) {
            continue;
        }
        if (func_ov134_0229aa78((struct UnkStruct_0229aa78 *) a, i) > r6) {
            continue;
        }
        if (func_ov134_0229aa3c((void *) a, i) < r6) {
            continue;
        }
        return i;
    }
    return 6;
}

int func_ov134_0229aad8(int a, int b, int c)
{
    int i;
    int r4 = b >> 3;
    int r6 = c >> 3;

    for (i = 3; i <= 4; i++) {
        if ((int) func_ov134_0229aaa8((FileInfo *) a, i) > r4) {
            continue;
        }
        if (func_ov134_0229aa4c(a, i) + 3 < r4) {
            continue;
        }
        if (func_ov134_0229aa78((struct UnkStruct_0229aa78 *) a, i) > r6) {
            continue;
        }
        if (func_ov134_0229aa3c((void *) a, i) < r6) {
            continue;
        }
        return i;
    }
    return 6;
}

void *func_ov134_0229aaa8(FileInfo *self, int idx)
{
    unsigned char sel = self->sel;
    if (sel == 2) {
        return data_ov134_0229bfd4[idx];
    }
    if (sel == 1) {
        return data_ov134_0229bfec[idx];
    }
    return data_ov134_0229bf74[idx];
}

int func_ov134_0229aa78(struct UnkStruct_0229aa78 *self, int index)
{
    unsigned char t = self->type;
    if (t == 2) {
        return data_ov134_0229bf8c[index];
    } else if (t == 1) {
        return data_ov134_0229bfbc[index];
    } else {
        return data_ov134_0229c004[index];
    }
}

int func_ov134_0229aa6c(int unused, int index)
{
    return data_ov134_0229bfa4[index];
}

int func_ov134_0229aa4c(int a, int b)
{
    int x = (int) func_ov134_0229aaa8((FileInfo *) ((void *) a), b);
    int y = func_ov134_0229aa6c(a, b);
    return x + y - 1;
}

int func_ov134_0229aa3c(void *argument0, int argument1)
{
    return func_ov134_0229aa78((struct UnkStruct_0229aa78 *) argument0, argument1) + 1;
}

void func_ov134_0229a96c(UnkStruct_0229a96c *self, int a, int b)
{
    u8 com = self->unk_A0;

    if (com == 1) {
        if (a == 0) {
            return;
        }

        if (a == 1 || a == 2 || a == 5) {
            if (b == 3) {
                b = 4;
            }
            if (b == 5) {
                b = 7;
            }
        }
    } else if (com == 2) {
        if (a != 1 && a != 2) {
            return;
        }
    }

    if (a == 5 && b == 3) {
        if (func_0209de88(self->unk_BD, self->unk_BC, self->unk_BB) == 0) {
            b = 8;
            func_ov134_022995b0(self, b);
        } else {
            func_ov134_022995a0(self, 8);
        }
    }

    if (self->unk_B1 == a && b == 3) {
        b = 5;
    }

    func_0206fdd4((u8 *) self + 0x870, (int) func_ov134_0229aaa8((FileInfo *) self, a), func_ov134_0229aa78((struct UnkStruct_0229aa78 *) self, a),
                  func_ov134_0229aa4c((int) self, a), func_ov134_0229aa3c((void *) self, a), b);

    func_ov134_022995b0(self, 2);
}

void func_ov134_0229a918(unsigned char *p, int a1, int a2)
{
    int v1 = func_ov134_0229aa4c((int) p, a1) + 1;
    int v2 = func_ov134_0229aa78((struct UnkStruct_0229aa78 *) p, a1);
    int v3;
    if (p[0xa0] == 0 && a1 == 3) {
        v3 = v1 + 1;
    } else {
        v3 = v1 + 2;
    }
    func_0206fdd4((void *) (p + 0x870), v1, v2, v3, v2 + 1, a2);
    func_ov134_022995b0((UnkStruct_0229a96c *) p, 2);
}

void func_ov134_0229a8e8(void *p)
{
    int i;
    for (i = 0; i <= 5; i++) {
        func_ov134_0229a96c((UnkStruct_0229a96c *) p, i, 3);
    }
    for (i = 0; i <= 5; i++) {
        ((char *) p + i)[0x98] = 0;
    }
}

void func_ov134_0229a8a8(unsigned char *p)
{
    int i;

    for (i = 0; i <= 5; i++) {
        if ((p + i)[0x98] != 0) {
            (p + i)[0x98]--;
            if ((p + i)[0x98] == 0) {
                func_ov134_0229a96c((UnkStruct_0229a96c *) p, i, 3);
            }
        }
    }
}

unsigned char func_ov134_0229a8a0(UnkStruct_0229a8a0 *p)
{
    return p->unk_B1;
}

void func_ov134_0229a868(UnkStruct_0229a868 *self, int arg1)
{
    unsigned char old = self->b;
    if (old == arg1) {
        return;
    }
    self->b = arg1;
    if (old != 6) {
        func_ov134_0229a96c((UnkStruct_0229a96c *) self, old, 3);
    }
    if (arg1 != 6) {
        func_ov134_0229a96c((UnkStruct_0229a96c *) self, arg1, 3);
    }
}
