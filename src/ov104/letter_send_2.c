/* letter_send_2: 9 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229ca44 @ 0x0229ca44, 0x5c bytes, Thumb
 * func_ov104_0229c9fc @ 0x0229c9fc, 0x48 bytes, Thumb
 * func_ov104_0229c9c4 @ 0x0229c9c4, 0x38 bytes, Thumb
 * func_ov104_0229c944 @ 0x0229c944, 0x80 bytes, Thumb
 * func_ov104_0229c870 @ 0x0229c870, 0xd4 bytes, Thumb
 * func_ov104_0229c7e8 @ 0x0229c7e8, 0x88 bytes, Thumb
 * func_ov104_0229c7dc @ 0x0229c7dc, 0xc bytes, Thumb
 * func_ov104_0229c6a0 @ 0x0229c6a0, 0x13c bytes, Thumb
 * func_ov104_0229c648 @ 0x0229c648, 0x58 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xb2];
    unsigned short flags;
} UnkStruct_0229c870;

typedef struct {
    char data[0x100];
} Entry;

struct UnkStruct_0229c6a0 {
    unsigned char pad_00[0x100];
};

struct UnkStruct_0229c6a0_2 {
    unsigned char pad_00[0x20];
};

extern void func_0200467c(unsigned int cmd);
extern void func_ov104_0229c344(void *self, unsigned int value);
extern void *func_ov002_0220a720(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_02073d90(void *ptr);
extern void func_ov104_0229c558(void *self);
extern void *data_020ccf94;
extern void func_ov104_0229c354(int, int);
extern int func_02065ec0(const void *);
extern int func_02065e9c(const void *);
extern void func_0206f980(u8 *p);
extern void func_02066650(u8 *p);
extern int func_02097890(const char *, int);
extern int func_020979ac(const char *);
extern int func_020978bc(Entry *p, int n);
extern int func_020979f0(int a, int b);
extern int func_02097958(struct UnkStruct_0229c6a0 *);
extern int func_02097a74(struct UnkStruct_0229c6a0 *, int, int);
extern int func_02097900(struct UnkStruct_0229c6a0 *);
extern void func_02097a44(struct UnkStruct_0229c6a0 *);
extern int func_020682e0(int);
extern void *func_02094fd4(struct UnkStruct_0229c6a0_2 *);
extern int func_02098844(void *, int);
extern int func_02099870(int);
extern void *func_02095074(int, struct UnkStruct_0229c6a0_2 *);
extern void func_02068404(int, int, struct UnkStruct_0229c6a0_2 *);
extern void *func_02094fbc(struct UnkStruct_0229c6a0_2 *);
extern void *data_021dc7bc;

int func_ov104_0229c7dc(int a, int b);

void func_ov104_0229ca44(unsigned char *self)
{
    func_0200467c(0x27);
    func_ov104_0229c344(self, 0x400);
    func_ov002_0220a720(self + 0x41b4, 9);
    func_ov002_02208098((void *) (self), 0x1b);
    self[0x8c] = 4;
    func_ov104_0229c344(self, 0x100);
    if (func_02073d90(data_020ccf94) != 0) {
        func_ov104_0229c558(self);
    }
}

void func_ov104_0229c9fc(int param)
{
    func_0200467c(0x28);
    func_ov104_0229c354(param, 0x400);
    func_ov002_0220a720((void *) (param + 0x41b4), 7);
    func_ov002_02208098((void *) (param), 0x1b);
    *(char *) (param + 0x8c) = 4;
    func_ov104_0229c344((void *) param, 0x100);
}

int func_ov104_0229c9c4(int unused, const char *ptr)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(ptr) == 1 && func_02065e9c(ptr) != 0) {
            return 1;
        }
        ptr += 0x100;
    }
    return 0;
}

unsigned short func_ov104_0229c944(void *unused, u8 *p)
{
    unsigned short flags;
    int found;
    int i;
    u8 *q;
    u8 *hit;

    flags = 0;
    found = -1;
    q = p;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0((const void *) q) == 1 && func_02065e9c((const void *) q) != 0) {
            if (found == -1) {
                found = i;
            } else {
                found = -2;
            }
        }
        q += 0x100;
    }
    if (found != -1) {
        if (found == -2) {
            flags |= 2;
        } else {
            flags |= 1;
            hit = p + (found << 8);
            func_0206f980(hit);
            func_02066650(hit);
        }
    }
    return flags;
}

unsigned short func_ov104_0229c870(UnkStruct_0229c870 *self, const char *ptr, int flag)
{
    unsigned short result;
    int i;

    if (func_02097890(ptr, 10) == 0) {
        return 0;
    }

    result = 0;
    i = 0;

loop_body:
    if (func_02065ec0((const void *) ptr) == 0) {
        goto next_iter;
    }
    if (func_02065ec0((const void *) ptr) == 1) {
        goto case_one;
    }

    if (flag != 0) {
        self->flags |= (1 << i);
    } else {
        func_02066650((u8 *) ptr);
    }
    goto next_iter;

case_one:
    if (func_02065e9c((const void *) ptr) != 0) {
        goto next_iter;
    }
    if (func_020979ac(ptr) == 0) {
        goto result_108;
    }
    if (func_ov104_0229c7dc((int) self, (int) ptr) == 0) {
        goto result_110;
    }

    if (flag != 0) {
        self->flags |= (1 << i);
    } else {
        func_02066650((u8 *) ptr);
    }
    result |= 0x300;
    goto next_iter;

result_110:
    result |= 0x110;
    goto next_iter;

result_108:
    result |= 0x108;
    goto next_iter;

next_iter:
    ptr += 0x100;
    i++;
    if (i < 10) {
        goto loop_body;
    }

    return result;
}

unsigned short func_ov104_0229c7e8(int a, Entry *p)
{
    int count, i;
    unsigned short flags = 0;

    count = func_020978bc(p, 0xa);
    if (count == 0) {
        return flags;
    }

    for (i = 0; i < count; i++) {
        if (func_02065ec0((const void *) p) != 1) {
            func_02066650((u8 *) p);
        } else {
            if (func_02065e9c((const void *) p) == 0) {
                if (func_020979ac((const char *) p) != 0) {
                    if (func_ov104_0229c7dc(a, (int) p) != 0) {
                        func_02066650((u8 *) p);
                        flags |= 0x200;
                    } else {
                        flags |= 0x20;
                    }
                }
            }
        }
        p++;
    }

    return flags;
}

int func_ov104_0229c7dc(int a, int b)
{
    return func_020979f0(b, 1);
}

u16 func_ov104_0229c6a0(int unused, struct UnkStruct_0229c6a0 *p)
{
    struct UnkStruct_0229c6a0_2 buf;
    u16 ret;
    int n;
    int mask;
    int obj;
    int idx;
    volatile int zero;
    int count;
    int i;
    int j;
    int k;
    ret = 0;
    n = func_020978bc((Entry *) p, 10);
    if (n == 0) {
        return ret;
    }
    mask = 0;
    count = 0;
    i = 0;
    for (i = 0; i < n; i++) {
        if (func_02065e9c((const void *) p) == 0) {
            idx = func_02097958(p);
            if ((idx != (~1)) & 0xFFFFFFFFFFFFFFFFu) {
                if (idx != (~0)) {
                    if (func_02097a74(p, idx, 1)) {
                        func_02066650((u8 *) p);
                        ret = (u16) (ret | 0x200);
                    } else if ((mask & (1 << idx)) == 0) {
                        mask = mask | (1 << idx);
                        count++;
                    }
                } else if (func_02097900(p) >= 0) {
                    func_02097a44(p);
                    func_02066650((u8 *) p);
                    ret = (u16) (ret | 0x200);
                }
            }
        }
        p = (struct UnkStruct_0229c6a0 *) (((char *) p) + 0x100);
    }

    if (count != 0) {
        j = 0;
        obj = func_020682e0(j);
        func_02094fd4(&buf);
        for (k = j; k < 4; k++) {
            if (mask & (1 << k)) {
                func_02095074(func_02099870(func_02098844(&data_021dc7bc, k)), &buf);
                switch (j) {
                    case 0:
                        func_02068404(obj, 7, &buf);
                        break;

                    case 1:
                        func_02068404(obj, 8, &buf);
                        break;

                    case 2:
                        func_02068404(obj, 9, &buf);
                        break;
                }

                j++;
            }
        }

        ret = (u16) (ret | (count << 6));
        func_02094fbc(&buf);
    }
    return ret;
}

int func_ov104_0229c648(int unused, unsigned char *p)
{
    unsigned short flags = 0;
    int count;
    int i;

    count = func_020978bc((Entry *) p, 0xa);
    if (count == 0) {
        return flags;
    }

    i = 0;
    while (i < count) {
        if (func_02097900((struct UnkStruct_0229c6a0 *) p) >= 0) {
            func_02097a44((struct UnkStruct_0229c6a0 *) p);
            func_02066650((u8 *) p);
            flags = (unsigned short) (flags | 0x200);
        }
        p += 0x100;
        i++;
    }
    return flags;
}
