/* gatekeeper2: 9 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022251a4 @ 0x022251a4, 0x6 bytes, Thumb
 * func_ov004_0222511c @ 0x0222511c, 0x88 bytes, Thumb
 * func_ov004_02224ff4 @ 0x02224ff4, 0x128 bytes, Thumb
 * func_ov004_02224f98 @ 0x02224f98, 0x5c bytes, Thumb
 * func_ov004_02224f6c @ 0x02224f6c, 0x2c bytes, Thumb
 * func_ov004_02224f30 @ 0x02224f30, 0x3c bytes, Thumb
 * func_ov004_02224dd4 @ 0x02224dd4, 0x15c bytes, Thumb
 * func_ov004_02224da8 @ 0x02224da8, 0x2c bytes, Thumb
 * func_ov004_02224d80 @ 0x02224d80, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_022251a4;

struct UnkStruct_02224f98 {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
};

struct UnkStruct_02224f30 {
    unsigned char pad_00[0x563];
    unsigned char unk_563;
    unsigned char pad_564[0xb4];
    unsigned char unk_618;
};

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_02224d80;

extern int func_0206fc6c(void);
extern void *func_020984e8(void);
extern void *func_0206fc8c(void);
extern void *func_020996b8(void *);
extern int func_02072ba4(int object);
extern int func_02072b64(int, void *);
extern int func_02071d8c(int, int, int, int, int);
extern int func_0200442c(void *, int, int, int);
extern void func_0206844c(int, void *, void *);
extern void *data_ov004_02254794;
extern int func_02071aa8(int a, int b, int c, int d, int e);
extern u16 *func_02099710(void *h);
extern u16 *func_020996f8(void *h);
extern int func_02095b58(u16 *p);
extern int func_02095b40(u16 *p);
extern unsigned short *func_0206faf0(void);
extern void func_02015de4(void *self, unsigned short *p, int a, int b);
extern int func_02014868(void *);
extern int func_0201c014(void *);
extern char *data_020ccf94;
extern void func_0201c054(void *, int, int, int);
extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(void);
extern void func_ov004_022256ec(void *, int);
extern void *func_ov004_022254ac(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov004_02254918[];

void func_ov004_022251a4(UnkStruct_022251a4 *p, unsigned long v)
{
    p->unk_B4 = v;
}

void func_ov004_0222511c(char *self)
{
    unsigned char buf[4];
    if (func_0206fc6c() != 0) {
        void *a = func_020984e8();
        void *b = func_0206fc8c();
        a = func_020996b8(a);
        func_02071d8c(9, func_02072b64(func_02072ba4((int) a), b), 5, 0, 1);
        func_0200442c(*(char **) (self + 0xb0) + 0x514, 0x50, 0x7f, 0);
        buf[0] = 0x18;
        func_0206844c(*(int *) (self + 0x40), &buf[0], data_ov004_02254794);
    } else {
        buf[1] = 1;
        func_0206844c(*(int *) (self + 0x40), &buf[1], data_ov004_02254794);
    }
}

static inline u16 first(unsigned c)
{
    if (c < 8) {
        return (u16) (c + 0x12a8);
    }
    return 0x12a8;
}

static inline u16 second(unsigned c)
{
    if (c < 8) {
        return (u16) (c + 0x1429);
    }
    return 0x1429;
}

static inline unsigned isfirst(u16 *p)
{
    unsigned flag = 0;
    u16 c = *p;
    if (c >= 0x12a8 && c <= 0x12af) {
        flag = 1;
    }
    return flag;
}

static inline unsigned issecond(u16 *p)
{
    unsigned flag = 0;
    u16 c = *p;
    if (c >= 0x1429 && c <= 0x1430) {
        flag = 1;
    }
    return flag;
}

void func_ov004_02224ff4(char *self)
{
    struct {
        u8 b0, b1;
        u16 h2, h4;
    } m;
    void *a;
    int b;
    unsigned c;
    u16 va, vb;
    u16 cur1, cur2;
    int flag;

    if (func_0206fc6c() != 0) {
        a = func_020984e8();
        b = (int) func_0206fc8c();
        c = func_02072b64((int) ((void *) func_02072ba4((int) (func_020996b8(a)))), (void *) b);
        func_02071aa8(9, c, 5, 0, 1);
        func_0200442c((char *) *(void **) (self + 0xb0) + 0x514, 0x50, 0x7f, 0);

        va = first(c);
        vb = second(c);

        cur1 = *func_02099710(a);
        cur2 = *func_020996f8(a);

        if (va == cur1) {
            if (isfirst(func_02099710(a)) > 0) {
                m.h2 = va;
                func_02095b58(&m.h2);
            }
        }
        if (vb == cur2) {
            if (issecond(func_020996f8(a)) > 0) {
                m.h4 = vb;
                func_02095b40(&m.h4);
            }
        }

        m.b0 = 0x19;
        func_0206844c((int) (*(void **) (self + 0x40)), (void *) (&m.b0), data_ov004_02254794);
    } else {
        m.b1 = 1;
        func_0206844c((int) (*(void **) (self + 0x40)), (void *) (&m.b1), data_ov004_02254794);
    }
}

void func_ov004_02224f98(char *self)
{
    struct UnkStruct_02224f98 t;
    void *ctx = *(void **) (self + 0x40);

    t.b = 0x20;
    if (func_0206fc6c() != 0) {
        if ((unsigned int) func_0206fc8c() > 1) {
            t.b = 0x1c;
        } else {
            t.h = *func_0206faf0();
            func_02015de4(self, &t.h, 0, 7);
            t.b = 0x1e;
        }
    }
    func_0206844c((int) ctx, (void *) (&t), (void *) ((*(int *) &data_ov004_02254794)));
}

int func_ov004_02224f6c(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov004_02224f30(struct UnkStruct_02224f30 *self)
{
    if (self->unk_563) {
        return 1;
    }
    if (func_02014868(&self->unk_618) != 0) {
        goto ret0;
    }
    if (func_0201c014(self) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov004_02224dd4(unsigned char *self, unsigned int kind, int value)
{
    int a, b;
    switch (kind) {
        case 3:
            self[0x560] = value;
            if (value != 4) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), value);
                func_ov004_022256ec(self, 6);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
                func_ov004_022256ec(self, 6);
            }
            break;
        case 1:
            func_ov004_022256ec(self, 1);
            break;
        case 0:
            self[0x560] = value;
            if (value != 4 && value != *(int *) (data_020ccf94 + 0x64)) {
                func_0201c054(self, 1, value, value);
                func_ov004_022256ec(self, 5);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
                func_ov004_022256ec(self, 1);
            }
            break;
        case 8:
            if (value == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
                    func_ov004_022256ec(self, 3);
                } else {
                    func_0201c054(self, 1, 4, *(int *) (data_020ccf94 + 0x64));
                    func_ov004_022256ec(self, 4);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                a = 4;
                b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if ((value != 4 && value == b) || value == 4) {
                        func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
                        func_ov004_022256ec(self, 0);
                    }
                }
            }
            break;
    }
}

void *func_ov004_02224da8(void *s)
{
    *(void **) s = &data_ov004_02254918;
    func_ov004_022254ac((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_02224d80(UnkStruct_02224d80 *param)
{
    param->unk_00 = ((char *) data_ov004_02254918);
    func_ov004_022254ac(&param->sub);
    func_0202ee5c(param);
    return param;
}
