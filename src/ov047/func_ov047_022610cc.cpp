/* func_ov047_022610cc @ 0x022610cc, 0x54c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O1,s
 */

// Local static table with pointer to member initialisers; the PMFs are copied on first use.
// Built at -O1,s. The gN names are placeholders.

struct UnkStruct_022610cc;
typedef void (UnkStruct_022610cc::*PMF)(void);
struct Entry {
    int key;
    PMF fn;
};

struct UnkStruct_022610cc {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    int unk_40;
    unsigned char pad_44[0xc8 - 0x44];
    int unk_C8;
    unsigned char unk_CC;
    unsigned char pad_CD[1];
    unsigned short unk_CE;
    int unk_D0;
};

struct UnkStruct_022610cc_2 {
    unsigned char c[4];
    unsigned short s[6];
};

extern PMF data_ov047_02262b18;
extern PMF data_ov047_02262b10;
extern PMF data_ov047_02262b08;
extern PMF data_ov047_02262b00;
extern PMF data_ov047_02262af8;
extern PMF data_ov047_02262af0;
extern PMF data_ov047_02262ae8;
extern PMF data_ov047_02262ae0;
extern PMF data_ov047_02262ad8;
extern PMF data_ov047_02262ad0;
extern PMF data_ov047_022629f8;
extern PMF data_ov047_02262ac0;
extern PMF data_ov047_02262ab8;
extern PMF data_ov047_02262ab0;
extern PMF data_ov047_022629e8;
extern PMF data_ov047_02262aa0;
extern PMF data_ov047_02262b28;
extern PMF data_ov047_02262a90;
extern PMF data_ov047_02262960;
extern PMF data_ov047_02262a80;
extern PMF data_ov047_02262a78;
extern PMF data_ov047_02262a70;
extern PMF data_ov047_02262a68;
extern PMF data_ov047_02262a60;
extern PMF data_ov047_02262a58;
extern PMF data_ov047_02262a50;
extern PMF data_ov047_02262a48;
extern PMF data_ov047_02262b60;
extern PMF data_ov047_02262a30;
extern PMF data_ov047_02262a40;
extern PMF data_ov047_02262aa8;
extern PMF data_ov047_02262b20;
extern PMF data_ov047_02262a18;
extern PMF data_ov047_02262a10;
extern PMF data_ov047_02262a08;
extern char data_ov047_02262fc0[];
extern char data_021dc7a8[];
extern char data_021f38f8[];

extern "C" {

extern int func_020a12e8(void);
extern int strlen(void *p);
extern int strncmp(void *a, void *b, int c);
extern int func_0209f150(void *p, int k);
extern void func_0206844c(int h, unsigned char *p, void *q);
extern void func_ov047_02261618(UnkStruct_022610cc *self);
extern int func_02070f5c(void *p);
extern int func_02015094(UnkStruct_022610cc *self);
extern int func_02070e98(void *p);
extern int func_020984e8(void);
extern int func_02070f1c(void *p);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);
extern void func_02071110(void *p, unsigned short *q);
extern void func_0209f128(void *p, int k);
extern void func_02098ff8(int h, int k);
extern void func_0209a050(int k);
extern int func_020535f0(unsigned short *p);
extern int func_020535b4(int k);
extern int func_02070d74(void *p, int k);

void func_ov047_022610cc(UnkStruct_022610cc *self)
{
    int h;
    UnkStruct_022610cc_2 b;
    unsigned int i;
    int st;
    int cond;
    int t;
    int k;
    int m;
    int w;
    void *q;
    int key;

    if (func_020a12e8() != 0) {
        return;
    }
    if (strncmp((char *) self + 4, data_ov047_02262fc0, strlen(data_ov047_02262fc0)) != 0) {
        return;
    }
    st = self->unk_1E;
    if (st < 0xc) {
        if (func_0209f150(data_021dc7a8, 0xc) != 0) {
            self->unk_D0 = 0x44;
        } else {
            self->unk_D0 = 0xc;
        }
        b.c[0] = (unsigned char) self->unk_D0;
        func_0206844c(self->unk_40, &b.c[0], data_ov047_02262fc0);
        return;
    }
    if (st == 0x33 || (st >= 0x6e && st <= 0xa5)) {
        func_ov047_02261618(self);
        if (func_02070f5c(data_021f38f8) != 0) {
            self->unk_D0 = 0x34;
        } else {
            self->unk_D0 = 0x27;
        }
        func_02015094(self);
        b.c[1] = (unsigned char) self->unk_D0;
        func_0206844c(self->unk_40, &b.c[1], data_ov047_02262fc0);
        return;
    }
    if (st >= 0xaa && st <= 0xe1) {
        func_ov047_02261618(self);
        if (func_02070e98(data_021f38f8) != 0) {
            self->unk_D0 = 0x36;
        } else {
            self->unk_D0 = 0x27;
        }
        func_02015094(self);
        b.c[2] = (unsigned char) self->unk_D0;
        func_0206844c(self->unk_40, &b.c[2], data_ov047_02262fc0);
        return;
    }
    h = func_020984e8();
    self->unk_D0 = 0xff;
    {
        static Entry tbl[35] = {
            {0x14, data_ov047_02262b18}, {0x15, data_ov047_02262b10}, {0x16, data_ov047_02262b08}, {0x17, data_ov047_02262b00},
            {0x18, data_ov047_02262af8}, {0x19, data_ov047_02262af0}, {0x1a, data_ov047_02262ae8}, {0x1b, data_ov047_02262ae0},
            {0x1c, data_ov047_02262ad8}, {0x1d, data_ov047_02262ad0}, {0x1f, data_ov047_022629f8}, {0x26, data_ov047_02262ac0},
            {0x29, data_ov047_02262ab8}, {0x2e, data_ov047_02262ab0}, {0x2f, data_ov047_022629e8}, {0x30, data_ov047_02262aa0},
            {0x31, data_ov047_02262b28}, {0x32, data_ov047_02262a90}, {0x33, data_ov047_02262960}, {0x34, data_ov047_02262a80},
            {0x35, data_ov047_02262a78}, {0x36, data_ov047_02262a70}, {0x37, data_ov047_02262a68}, {0x38, data_ov047_02262a60},
            {0x39, data_ov047_02262a58}, {0x3a, data_ov047_02262a50}, {0x3b, data_ov047_02262a48}, {0x3c, data_ov047_02262b60},
            {0x3d, data_ov047_02262a30}, {0x3f, data_ov047_02262a40}, {0x40, data_ov047_02262aa8}, {0x41, data_ov047_02262b20},
            {0x42, data_ov047_02262a18}, {0x43, data_ov047_02262a10}, {0x6a, data_ov047_02262a08}};
        unsigned char *p1e;
        i = 0;
        p1e = &self->unk_1E;
        for (; i < 0x23; i++) {
            key = tbl[i].key;
            if (key == *p1e) {
                (self->*tbl[i].fn)();
            }
        }
    }
    st = self->unk_1E;
    if (st >= 0x50 && st <= 0x67) {
        if (func_02070f1c(data_021f38f8) != 0) {
            self->unk_D0 = 0x29;
        } else {
            if (self->unk_CC == 0) {
                self->unk_D0 = 0x27;
            } else {
                self->unk_D0 = 0x20;
            }
        }
        self->unk_CE = 0xfff1;
        func_02015094(self);
    }
    st = self->unk_1E;
    if (st == 0x25 || st == 0x2c || st == 0x2d || st == 0x69) {
        if (func_0204bcdc(&self->unk_CE) != 0) {
            b.s[0] = 0xfff1;
            t = func_0204bc64(&self->unk_CE);
            cond = (t == func_0204bc64(&b.s[0])) ? 1 : 0;
        } else {
            cond = (self->unk_CE == 0xfff1) ? 1 : 0;
        }
        if (cond != 0) {
            goto final;
        }
        q = data_021f38f8;
        func_02071110(q, &self->unk_CE);
        func_0209f128(data_021dc7a8, 0xc);
        func_02098ff8(h, 8);
        if (self->unk_C8 >= 0) {
            func_0209a050(self->unk_C8);
            self->unk_C8 = -1;
        }
        k = func_020535f0(&self->unk_CE);
        m = func_020535b4(k);
        w = func_02070d74(q, k);
        if (m == 1) {
            if (self->unk_1E == 0x2d) {
                if (func_0204bcdc(&self->unk_CE) != 0) {
                    b.s[1] = 0xfff1;
                    t = func_0204bc64(&self->unk_CE);
                    cond = (t == func_0204bc64(&b.s[1])) ? 1 : 0;
                } else {
                    cond = (self->unk_CE == 0xfff1) ? 1 : 0;
                }
                if (cond != 0) {
                    goto final;
                }
                k = k + 0x50;
                self->unk_D0 = (unsigned char) k;
            } else {
                self->unk_D0 = 0x2d;
            }
        } else if (m == w) {
            if (func_0204bcdc(&self->unk_CE) != 0) {
                b.s[2] = 0xfff1;
                t = func_0204bc64(&self->unk_CE);
                cond = (t == func_0204bc64(&b.s[2])) ? 1 : 0;
            } else {
                cond = (self->unk_CE == 0xfff1) ? 1 : 0;
            }
            if (cond != 0) {
                goto final;
            }
            k = k + 0x50;
            self->unk_D0 = (unsigned char) k;
        } else {
            self->unk_D0 = 0x26;
        }
    }
final:
    if (self->unk_D0 != 0xff) {
        b.c[3] = (unsigned char) self->unk_D0;
        func_0206844c(self->unk_40, &b.c[3], data_ov047_02262fc0);
    }
}
}
