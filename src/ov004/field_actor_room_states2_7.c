/* field_actor_room_states2_7: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222ac24 @ 0x0222ac24, 0x4e bytes, Thumb
 * func_ov004_0222aa90 @ 0x0222aa90, 0x194 bytes, Thumb
 * func_ov004_0222aa8c @ 0x0222aa8c, 0x2 bytes, Thumb
 * func_ov004_0222a9f4 @ 0x0222a9f4, 0x98 bytes, Thumb
 * func_ov004_0222a94c @ 0x0222a94c, 0xa8 bytes, Thumb
 * func_ov004_0222a504 @ 0x0222a504, 0x448 bytes, Thumb
 * func_ov004_0222a4e4 @ 0x0222a4e4, 0x20 bytes, Thumb
 * func_ov004_0222a4dc @ 0x0222a4dc, 0x8 bytes, Thumb
 */

#include "types.h"

#define PTR(o, k) (*(char **) ((o) + (k)))
#define BYTE(o, k) (*(u8 *) ((o) + (k)))
#define HALF(o, k) (*(u16 *) ((o) + (k)))
#define WORD(o, k) (*(int *) ((o) + (k)))
#define CALL_BASE(fn)                                                                                                         \
    {                                                                                                                         \
        char *base = self;                                                                                                    \
        if (self)                                                                                                             \
            base += 0xec;                                                                                                     \
        fn(self, base);                                                                                                       \
    }
#define START_DIALOG(n, res, k)                                                                                               \
    {                                                                                                                         \
        *state = (n);                                                                                                         \
        CALL_BASE(func_0203ee14);                                                                                             \
        func_0200f27c(self, 0x11);                                                                                            \
        func_020a8164(self + 0xec, (res));                                                                                    \
        BYTE(self, 0x10a) = (k);                                                                                              \
        WORD(PTR(self, 0x12c), 8) = 1;                                                                                        \
    }
#define CLOSE_DIALOG()                                                                                                        \
    {                                                                                                                         \
        CALL_BASE(func_0203ee08);                                                                                             \
        func_0200f268(self, 0x11);                                                                                            \
        func_0203e19c();                                                                                                      \
    }
#define START_ITEM()                                                                                                          \
    {                                                                                                                         \
        if (WORD(self, 0x810) == -1) {                                                                                        \
            *state = 4;                                                                                                       \
            func_020109fc(self, 0, 6, 6);                                                                                     \
            WORD(self, 0x810) = func_02043540(PTR(self, 0x800), HALF(self, 0x820));                                           \
        }                                                                                                                     \
    }
#define FINISH_ITEM()                                                                                                         \
    {                                                                                                                         \
        WORD(self, 0x7fc) = func_02008258(self, WORD(self, 0x7f0));                                                           \
        func_0200d4e8(self, 3, 1, -1);                                                                                        \
    }

struct UnkStruct_0222aa90 {
    int unk_00;
    u8 unk_04;
    u8 unk_05;
};

struct UnkStruct_0222aa90_2 {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    int unk_04;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov004_0222ac74(void *, void *, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_0204f794(void *p, int a, int b);
extern int func_ov004_0223c5a4(void *p);
extern u16 *func_0204f5a8(void *g, void *p, int k);
extern int func_02008258(void *self, int a);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_02099fe8(void);
extern int func_020b67d4(void);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern unsigned int func_020b2300(void);
extern unsigned int *func_0200f27c(void *self, int a);
extern void func_02045f08(int *p, int a);
extern int func_ov004_0223bb20(int v, u16 *a, u16 *b);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_0200f328(void *self, int a);
extern void *data_021c80bc;
extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int a);
extern int func_0200f290(void *self, int a);
extern int func_ov004_0223badc(int a);
extern int _s32_div_f(int a, int b);
extern void func_0200f268(void *self, int a);
extern void func_0200f650(void *self, int a);
extern char data_ov004_02254b10[];
extern char data_ov004_02254b00[];
extern int func_02056f94(char *);
extern int func_0203e1c4(void);
extern int func_0200fbe0(char *);
extern void func_0205eae0(char *, int, int, int);
extern void func_0203ee14(char *, char *);
extern void func_0203ee08(char *, char *);
extern void func_020a8164(char *, char *);
extern int func_0209a110(void *);
extern int func_02043540(char *, u16);
extern int func_0206f6d4(u16);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0203e19c(void);
extern void func_02010d64(int);

int func_ov004_0222ac24(void *a, int *b, void *c, int d, short e)
{
    int local0[2];
    char local1[12];
    char local2[16];
    func_0200e92c(&local1);
    func_0200e90c(&local1, 0x1c, d, e);
    local0[0] = b[0];
    local0[1] = b[1];
    func_ov004_0222ac74(&local2, local0, c);
    {
        int result = func_0200e894(a, &local1);
        func_0200e91c(&local1);
        return result;
    }
}

static __inline int chk(u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

void func_ov004_0222aa90(void *self, void *msg, int previous)
{
    // DECLS
    struct UnkStruct_0222aa90_2 *m;
    int v;
    struct UnkStruct_0222aa90 *o;
    int b;
    int c;
    u16 *r;
    // ENDDECLS
    int arr[2];

    m = (struct UnkStruct_0222aa90_2 *) ((char *) msg + 0xc);
    v = m->unk_04;
    o = (struct UnkStruct_0222aa90 *) ((char *) self + 0x7d4);
    o->unk_04 = 0;
    o->unk_05 = 0;
    o->unk_00 = v;
    b = *(u8 *) ((char *) msg + 0xc);
    c = m->unk_01;
    func_0204f794((char *) self + 0x824, b, c);
    *(int *) ((char *) self + 0x828) = func_ov004_0223c5a4((char *) self + 0x824);
    *(int *) ((char *) self + 0x830) = 0x1000;
    *(int *) ((char *) self + 0x834) = 0x1000;
    *(int *) ((char *) self + 0x838) = 0x1000;
    if (v < 0) {
        r = func_0204f5a8(data_021c80bc, (char *) self + 0x824, 1);
        if (r == 0) {
            *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
        }
        *(u16 *) ((char *) self + 0x822) = *r;
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
    }
    if (func_02099fe8() == -1 && func_020b67d4() != 0 && chk((u16 *) ((char *) self + 0x820), 0xfff1) == 0) {
        func_020109fc(self, 0, 3, 0);
        o->unk_05 = 6;
        *(u16 *) ((char *) self + 0x822) = 0xfff1;
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
        return;
    }
    if (func_020b2300() <= 1) {
        if (v < 0) {
            func_0200f27c(self, 0xd);
            arr[0] = b;
            arr[1] = c;
            func_02045f08(arr, 1);
        } else {
            func_ov004_0223bb20(v, (u16 *) ((char *) self + 0x820), (u16 *) ((char *) self + 0x822));
        }
        func_020109a0(self, 0x19, 3, 0);
        func_0200f328(self, 0x52);
    } else {
        o->unk_05 = 0xa;
        func_020109fc(self, 0, 3, 0);
    }
}

void func_ov004_0222aa8c(void *callbackObject, int event) {}

void func_ov004_0222a9f4(char *self)
{
    unsigned char *q;
    unsigned int k;
    int m;

    q = (unsigned char *) (self + 0x7d4);
    if (q[5] >= 6) {
        func_02010f5c(self);
        return;
    }
    k = q[4];
    if (k == 2) {
        if (func_02056f28(self + 0x2d0, 7) != 0) {
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_0200d4e8(self, 3, 1, -1);
            return;
        }
    } else if (k == 0) {
        if (((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16) < 7) {
            m = *(int *) (self + 0x818);
            if (m == 2) {
                q[4] = 2;
            } else if (m == 1) {
                q[4] = 1;
                func_0200f27c(self, 0xd);
            }
        }
    }
    func_02010f5c(self);
}

void func_ov004_0222a94c(char *self)
{
    int *q;
    int t;
    unsigned int v;

    if (func_0200f290(self, 0xd) == 0) {
        q = (int *) (self + 0x7d4);
        if (*q < 0) {
            return;
        }
        if (func_ov004_0223badc(*q) == 0) {
            return;
        }
        func_0200f27c(self, 0xd);
        *q = -1;
    }
    if (*(int *) (self + 0x704) != 0x19) {
        *(int *) (self + 0x830) = 0;
        *(int *) (self + 0x834) = 0;
        *(int *) (self + 0x838) = 0;
        return;
    }
    v = (unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16;
    if (v < 8) {
        return;
    }
    t = 0x1000 - _s32_div_f((v - 8) << 12, 7);
    if (t < 0) {
        t = 0;
        func_0200f268(self, 0xd);
    }
    *(int *) (self + 0x830) = t;
    *(int *) (self + 0x834) = t;
    *(int *) (self + 0x838) = t;
    func_0200f650(self, t);
}

void func_ov004_0222a504(char *self)
{
    u8 *state = (u8 *) (self + 0x7d9);
    // The ROM stores the two address-taken items at sp+4 and sp+6;
    // the leading word is never accessed.
    struct {
        unsigned int reserved;
        u16 copied, sentinel;
    } scratch;
    unsigned equal;
    int mode;
    switch (*state) {
        case 0:
            if (!func_02056f94(self + 0x2d0)) {
                break;
            }
            if (func_02099fe8() == -1) {
                if (func_0204bcdc((void *) (self + 0x820))) {
                    scratch.sentinel = 0xfff1;
                    equal = func_0204bc64(self + 0x820) == func_0204bc64(&scratch.sentinel) ? 1 : 0;
                } else {
                    equal = HALF(self, 0x820) == 0xfff1 ? 1 : 0;
                }
                if (!equal) {
                    if (!func_0203e1c4()) {
                        break;
                    }
                    func_020109fc((void *) self, 0x6c, 3, 0);
                    mode = func_0200fbe0(self);
                    if (mode == 4) {
                        func_0205eae0(self + 0x5a0, 0, 9, 0);
                    } else if (mode == 3) {
                        func_0205eae0(self + 0x5a0, 0x13, 3, 0);
                    }
                    START_DIALOG(1, data_ov004_02254b10, 2);
                    break;
                }
            }
            scratch.copied = HALF(self, 0x820);
            func_0209a110(&scratch.copied);
            *state = 5;
            break;
        case 1:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 2;
                WORD(self, 0x81c) = 3;
            }
            break;
        case 2:
            if (WORD(self, 0x81c) >= 15) {
                *state = 3;
                START_ITEM();
            } else if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                if (WORD(self, 0x81c) == 5) {
                    if (func_0206f6d4(HALF(self, 0x820))) {
                        WORD(self, 0x81c) = 6;
                    }
                } else if (WORD(self, 0x81c) == 6) {
                    if (func_0206fbc0()) {
                        WORD(self, 0x81c) = 15;
                        WORD(self, 0x2e0) = 0x1000;
                        if (func_0206fc6c()) {
                            *state = 5;
                            CLOSE_DIALOG();
                        } else {
                            *state = 3;
                            START_ITEM();
                        }
                    }
                }
            }
            break;
        case 3:
            START_ITEM();
            break;
        case 4:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                *state = 5;
                func_020109fc((void *) self, 0, 6, 6);
            }
            break;
        case 5:
            FINISH_ITEM();
            func_0200f268((void *) self, 13);
            WORD(self, 0x81c) = 15;
            break;
        case 6:
            if (func_0203e1c4()) {
                START_DIALOG(7, data_ov004_02254b10, 0);
            }
            break;
        case 7:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 8;
            }
            break;
        case 8:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                *state = 9;
            }
            break;
        case 9:
            FINISH_ITEM();
            func_0200f268((void *) self, 13);
            break;
        case 10:
            if (func_0203e1c4()) {
                START_DIALOG(11, data_ov004_02254b00, 1);
            }
            break;
        case 11:
            if (PTR(self, 0x12c) && WORD(PTR(self, 0x12c), 4)) {
                *state = 12;
            }
            break;
        case 12:
            if (PTR(self, 0x12c) && !WORD(PTR(self, 0x12c), 4)) {
                CLOSE_DIALOG();
                FINISH_ITEM();
            }
            break;
    }
}

void func_ov004_0222a4e4(int arg)
{
    func_ov004_0222a9f4((char *) arg);
    func_02010d64(arg);
    func_ov004_0222a94c((char *) arg);
    func_ov004_0222a504((char *) arg);
}

void func_ov004_0222a4dc(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
