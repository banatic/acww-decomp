/* friend_code_entry_2: 19 functions, module ov133
 * mwccarm 1.2/base -O4,s
 * func_ov133_0229b73c @ 0x0229b73c, 0x54 bytes, Thumb
 * func_ov133_0229b714 @ 0x0229b714, 0x28 bytes, Thumb
 * func_ov133_0229b6b8 @ 0x0229b6b8, 0x5c bytes, Thumb
 * func_ov133_0229b660 @ 0x0229b660, 0x56 bytes, Thumb
 * func_ov133_0229b500 @ 0x0229b500, 0x160 bytes, Thumb
 * func_ov133_0229b4b0 @ 0x0229b4b0, 0x50 bytes, Thumb
 * func_ov133_0229b44c @ 0x0229b44c, 0x64 bytes, Thumb
 * func_ov133_0229b3f8 @ 0x0229b3f8, 0x54 bytes, Thumb
 * func_ov133_0229b36c @ 0x0229b36c, 0x8c bytes, Thumb
 * func_ov133_0229b344 @ 0x0229b344, 0x28 bytes, Thumb
 * func_ov133_0229b320 @ 0x0229b320, 0x24 bytes, Thumb
 * func_ov133_0229b2e4 @ 0x0229b2e4, 0x3a bytes, Thumb
 * func_ov133_0229b2ac @ 0x0229b2ac, 0x36 bytes, Thumb
 * func_ov133_0229b280 @ 0x0229b280, 0x2a bytes, Thumb
 * func_ov133_0229b1e8 @ 0x0229b1e8, 0x96 bytes, Thumb
 * func_ov133_0229b190 @ 0x0229b190, 0x58 bytes, Thumb
 * func_ov133_0229b0f0 @ 0x0229b0f0, 0xa0 bytes, Thumb
 * func_ov133_0229b0d4 @ 0x0229b0d4, 0x1c bytes, Thumb
 * func_ov133_0229afec @ 0x0229afec, 0xe8 bytes, Thumb
 */

#include "types.h"

#define CUR(s) (*(vu8 *) ((s) + 0x9f))

struct UnkStruct_0229b500 {
    char pad_00[0x64];
    int unk_64;
};

extern const u8 data_ov133_0229c7a8[];
extern int func_02099658(int);
extern int func_0206fc8c(void);
extern void *func_02077d00(void *entries);
extern void *func_020984e8(void);
extern void *func_02077c3c(void *e);
extern int func_02077e50(void *t);
extern int func_02077e74(void *key, void *u);
extern void *func_02099664(void *a);
extern long long func_02077be0(void *b);
extern void func_02077ec0(void *buf);
extern void func_02077e68(void *buf);
extern void *func_02077bcc(void *record);
extern int func_02077dd4(void *p, char *q, void *r);
extern void func_ov133_0229bb78(char *self, int a, int b);
extern void func_0200467c(int cmd);
extern void func_02077ebc(void *buf);
extern void func_0206fc4c(int v);
extern void *func_ov002_0220a720(char *p, int v);
extern void func_ov002_02208090(char *self, int v);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
extern int func_0206fca4(void);
extern int func_ov133_0229c3d4(char *self, int v);
extern int func_020ee45c(char *self);
extern void func_ov090_02298fa4(int);
extern void func_0206f51c(void);
extern int func_02073dd4(struct UnkStruct_0229b500 *p, int v);
extern int func_020ec1e8(void);
extern void *func_02077d68(void *t);
extern int func_020eaf48(u8 a, void *b);
extern struct UnkStruct_0229b500 *data_020ccf94;
extern void func_02077c40(void *p);
extern int func_ov133_0229ae94(char *self);
extern int func_ov002_0220a620(char *p, int i);
extern void func_ov130_02299dbc(void);
extern int func_0200457c(int x);
extern const u8 data_ov133_0229c790[];
extern int func_ov002_022088ac(void *pad);
extern int func_ov002_0220889c(void *pad);
extern int func_ov133_0229ba84(u8 *self);
extern int func_ov133_0229ba34(u8 *self);
extern void func_ov002_0220a0b4(u8 *p, int a, int b);
extern u8 data_021f6c58;
extern int func_02077d84(void *p, char *q);
extern void func_ov133_0229ad78(u8 *self, int v);
extern void func_ov002_0220a63c(void *, int);
extern void func_ov002_0220a658(void *, int);

void func_ov133_0229b280(char *self);
int func_ov133_0229b1e8(u8 *self, int flag);
void func_ov133_0229b190(u8 *self);
int func_ov133_0229b0f0(u8 *self, u8 v);
int func_ov133_0229b0d4(u8 *p);

int func_ov133_0229b73c(char *self, int x, int y)
{
    int cx, cy;

    cx = x - 0x50;
    cy = y - 0x60;
    if (cx >= 0 && cx < 0x60 && cy >= 0 && cy < 0x40) {
        *(u8 *) (self + 0x9c) = data_ov133_0229c7a8[(cx >> 5) + 3 * (cy >> 4)];
        return *(u8 *) (self + 0x9c);
    }
    if (y >= 0x40 && y <= 0x50) {
        *(u8 *) (self + 0x9c) = 0xc;
        return *(u8 *) (self + 0x9c);
    }
    return 0xf;
}

int func_ov133_0229b714(void *receiver)
{
    int base;
    int index;
    int result;

    base = func_02099658((int) (int) func_020984e8());
    index = func_0206fc8c();
    result = (int) func_02077d00((void *) base);
    result += index * 0x24;
    return result;
}

int func_ov133_0229b6b8(void *self, void *key)
{
    void *a;
    int skip;
    char *e;
    int i;

    a = func_020984e8();
    skip = func_0206fc8c();
    e = func_02077d00((void *) func_02099658((int) a));
    for (i = 0; i < 0x20; e += 0x24, i++) {
        if (func_02077e50(func_02077c3c(e)) && i != skip && func_02077e74(key, func_02077c3c(e))) {
            return 1;
        }
    }
    return 0;
}

int func_ov133_0229b660(u8 *self)
{
    void *a;
    long long acc;
    int i;

    a = func_020984e8();
    acc = 0;
    for (i = 0; i < 0xc; i++) {
        u8 *p = self + i;

        acc *= 10;
        acc += (long long) p[0xa4];
    }
    if (acc == func_02077be0(func_02099664(a))) {
        return 1;
    }
    return 0;
}

void func_ov133_0229b500(char *self)
{
    char buf[0xc];
    void *a;
    void *e;
    void *t;
    struct UnkStruct_0229b500 *p;
    int m;
    int b;

    a = func_020984e8();
    func_02077ec0(buf);
    func_02077e68(buf);
    if (func_02077dd4(buf, self + 0xa4, func_02077bcc(func_02099664(a))) == 0) {
        func_ov133_0229bb78(self, 0x19, 0);
        func_0200467c(0x73);
        func_02077ebc(buf);
        return;
    }
    if (func_ov133_0229b660((u8 *) self)) {
        func_ov133_0229bb78(self, 0x1d, 0);
        func_0200467c(0x73);
        func_02077ebc(buf);
        return;
    }
    if (func_ov133_0229b6b8((void *) self, buf)) {
        func_ov133_0229bb78(self, 0x14, 0);
        func_0200467c(0x73);
        func_02077ebc(buf);
        return;
    }
    e = (void *) func_ov133_0229b714(self);
    t = func_02077c3c(e);
    func_02077dd4(t, self + 0xa4, func_02077bcc(func_02099664(a)));
    func_0206fc4c(1);
    func_ov002_0220a720(self + 0x180, 6);
    func_ov002_02208090(self, 3);
    func_ov002_02208098(self, 0xa);
    func_0200467c(0x29);
    if (func_0206fca4() == 0xe) {
        func_ov133_0229c3d4(self, 0xc);
    } else {
        func_ov090_02298fa4((int) func_020ee45c(self));
        func_ov133_0229c3d4(self, 6);
        func_0206f51c();
        p = data_020ccf94;
        if (func_02073dd4(p, p->unk_64)) {
            m = func_020ec1e8();
            switch (m) {
                case 3:
                case 4:
                    b = func_0206fc8c();
                    if (func_020eaf48(b, func_02077d68(func_02077c3c(e))) == 0) {
                        func_ov002_02208098(self, 0xc);
                        func_02077ebc(buf);
                        return;
                    }
                    break;
            }
        }
    }
    func_02077ebc(buf);
}

void func_ov133_0229b4b0(char *self)
{
    func_0206fc4c(0);
    func_ov002_0220a720((char *) (self + 0x180), 7);
    func_ov002_02208090((char *) self, 3);
    func_ov002_02208098((char *) self, 0xa);
    func_ov133_0229c3d4((char *) self, 6);
    if (func_0206fca4() == 0xe) {
        func_02077c40((void *) func_ov133_0229b714(self));
    }
    func_0200467c(0x28);
}

int func_ov133_0229b44c(char *self)
{
    u8 k = *(u8 *) (self + 0x9c);

    if (k <= 0xb) {
        if (func_ov133_0229ae94(self)) {
            func_ov002_02208098(self, 7);
            return 1;
        }
        return 2;
    }
    switch (k) {
        case 0xc:
            break;
        case 0xd:
            if (func_ov002_0220a620(self + 0x180, 6) == 0) {
                func_ov133_0229b500(self);
                return 1;
            }
            return 0;
        case 0xe:
            func_ov133_0229b4b0(self);
            return 1;
    }
    return 0;
}

int func_ov133_0229b3f8(char *self, int flag)
{
    u8 s = *(u8 *) (self + 0x9c);

    switch (s) {
        case 0xb:
            if (flag) {
                func_ov133_0229b280(self);
                func_ov130_02299dbc();
            }
            *(u8 *) (self + 0x9d) = 0;
            return 0;
        case 0xa:
            func_ov133_0229b1e8((u8 *) self, 1);
            return 1;
        default:
            if (s <= 9) {
                if (func_ov133_0229b0f0((u8 *) self, data_ov133_0229c790[s])) {
                    func_0200457c(0);
                }
            }
            return 1;
    }
}

int func_ov133_0229b36c(u8 *self, void *pad)
{
    u8 prev = CUR(self);
    int a;
    int b;

    if (func_ov002_022088ac(pad)) {
        if (CUR(self) != 0) {
            CUR(self) = CUR(self) - 1;
        }
    } else if (func_ov002_0220889c(pad)) {
        if (func_ov133_0229b0d4(self) > CUR(self)) {
            CUR(self) = CUR(self) + 1;
        }
    }
    if (prev != CUR(self)) {
        a = func_ov133_0229ba84(self);
        b = func_ov133_0229ba34(self);
        func_ov002_0220a0b4(self + 0x11c, a, b);
        return 1;
    }
    return 0;
}

int func_ov133_0229b344(void *p)
{
    int t;
    int v;
    int w;

    t = data_021f6c58 - 0x18;
    if (t < 0) {
        t = 0;
    }
    v = t >> 4;
    w = func_ov133_0229b0d4((u8 *) p);
    if (v > w) {
        v = w;
    }
    return v;
}

void func_ov133_0229b320(char *self, u8 v)
{
    *(u8 *) (self + 0x9f) = v;
    *(u8 *) (self + 0xa1) = 0x10;
    *(u8 *) (self + 0xa2) = v;
    *(u8 *) (self + 0xa3) = v;
    func_ov133_0229ad78((u8 *) self, 0x10);
}

void func_ov133_0229b2e4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x9f) = a1;
    *(u8 *) (self + 0xa1) = 0x10;
    if (*(u8 *) (self + 0xa2) != a1) {
        func_0200467c(0x15);
    }
    *(u8 *) (self + 0xa2) = a1;
    func_ov133_0229ad78((u8 *) self, 0x10);
}

void func_ov133_0229b2ac(char *self)
{
    if (func_02077d84(func_02077c3c((void *) func_ov133_0229b714(self)), self + 0xa4)) {
        func_ov133_0229b320(self, 0);
        func_ov133_0229ad78((u8 *) self, 8);
    } else {
        func_ov133_0229b280(self);
    }
}

void func_ov133_0229b280(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0xc; i++) {
        *(u8 *) (self + i + 0xa4) = 0xa;
    }
    func_ov133_0229b320((char *) self, 0x0);
    func_ov133_0229ad78((u8 *) self, 0x8);
}

int func_ov133_0229b1e8(u8 *self, int flag)
{
    int i;

    if (self[0xa2] != self[0xa3]) {
        func_ov133_0229b190(self);
        func_0200467c(0x35);
        return 1;
    }
    if (self[0x9f] == 0) {
        if (self[0xa4] != 0xa) {
            self[0x9f] = 1;
        } else {
            if (flag) {
                func_0200467c(0x34);
            }
            return 0;
        }
    }
    for (i = self[0x9f]; i < 0xc; i++) {
        u8 *p = self + i;
        u8 t = p[0xa4];

        p = self + (i - 1);
        p[0xa4] = t;
    }
    self[0xaf] = 0xa;
    func_ov133_0229ad78(self, 8);
    func_ov133_0229b320((char *) self, self[0x9f] - 1);
    func_0200467c(0x35);
    return 1;
}

void func_ov133_0229b190(u8 *self)
{
    unsigned int a = self[0xa3];
    unsigned int b = self[0xa2];
    int lo, hi;

    if (b < a) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }
    func_ov133_0229b320((char *) self, lo);
    for (; hi < 0xc; lo++, hi++) {
        u8 *s = self + hi;
        u8 *d = self + lo;
        d[0xa4] = s[0xa4];
    }
    for (; lo < 0xc; lo++) {
        u8 *d = self + lo;
        d[0xa4] = 0xa;
    }
    func_ov133_0229ad78(self, 8);
}

int func_ov133_0229b0f0(u8 *self, u8 v)
{
    int i;

    if (self[0x9f] == 0xc && self[0xa2] == self[0xa3]) {
        func_0200467c(0x34);
        return 0;
    }
    if (self[0xa2] == self[0xa3] && self[0xaf] != 0xa) {
        func_0200467c(0x34);
        return 0;
    }
    if (self[0xa2] != self[0xa3]) {
        func_ov133_0229b190(self);
    }
    i = 0xb;
    while (i > self[0x9f]) {
        u8 *s = self + (i - 1);
        u8 *d = self + i;

        d[0xa4] = s[0xa4];
        i--;
    }
    {
        u8 *d = self + self[0x9f];
        d[0xa4] = v;
    }
    func_ov133_0229b320((char *) self, self[0x9f] + 1);
    func_ov133_0229ad78(self, 8);
    return 1;
}

int func_ov133_0229b0d4(u8 *p)
{
    int i;

    for (i = 0; i < 0xc; i++) {
        u8 *q = p + i;
        if (q[0xa4] == 0xa) {
            return i;
        }
    }
    return 0xc;
}

void func_ov133_0229afec(u8 *self)
{
    int i;
    u8 *p;
    p = self + 0xb94;
    p += 0x1c8;
    for (i = 0; i < 12; i++) {
        if ((*((self + 0xa4) + i)) == 0xa) {
            u16 v;
            v = *((u16 *) p);
            *((u16 *) p) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 2));
            *((u16 *) (p + 2)) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 0x40));
            *((u16 *) (p + 0x40)) = (v & 0xfc00) | 0x176;
            v = *((u16 *) (p + 0x42));
            *((u16 *) (p + 0x42)) = (v & 0xfc00) | 0x176;
        } else {
            int x;
            u16 v;
            x = ((*((self + 0xa4) + i)) << 2) + 0x84;
            v = *((u16 *) p);
            *((u16 *) p) = (v & 0xfc00) | x;
            v = *((u16 *) (p + 2));
            *((u16 *) (p + 2)) = (v & 0xfc00) | (x + 1);
            v = *((u16 *) (p + 0x40));
            *((u16 *) (p + 0x40)) = (v & 0xfc00) | (x + 2);
            v = *((u16 *) (p + 0x42));
            *((u16 *) (p + 0x42)) = (v & 0xfc00) | (x + 3);
        }
        p += 4;
    }

    if (func_ov002_0220a620((char *) (self + 0x180), 6)) {
        if (self[0xaf] != 0xa) {
            func_ov002_0220a63c(self + 0x180, 6);
        }
    } else if (self[0xaf] == 0xa) {
        func_ov002_0220a658(self + 0x180, 6);
    }
}
