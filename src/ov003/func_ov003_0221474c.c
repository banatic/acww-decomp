/* func_ov003_0221474c @ 0x0221474c, 0x454 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    int a[9];
    Vec pos;
} Blk;
typedef struct {
    u16 a, b, c, d;
} Msg;

typedef struct {
    u8 pad_00[0x7e];
    char unk_7E;
    u8 pad_7F[0x1ff - 0x7f];
    u8 unk_1FF;
} Actor;

typedef struct {
    u8 pad_00[0xec];
    u8 unk_EC[0x2d0 - 0xec];
    u8 unk_2D0[0x2d8 - 0x2d0];
    int unk_2D8;
    u8 pad_2DC[0x5a0 - 0x2dc];
    u8 unk_5A0[0x5c8 - 0x5a0];
    u8 unk_5C8[0x698 - 0x5c8];
    Blk unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[2];
    u8 pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x810 - 0x804];
    int unk_810;
    u8 pad_814[0x81c - 0x814];
    int unk_81C;
    u8 pad_820[0x8f0 - 0x820];
    u8 unk_8F0[4];
} UnkStruct_0221474c;

extern u8 data_ov003_0223c026[];
extern void *data_020ccf94;
extern const int data_ov003_02238104;
extern const int data_ov003_02238108;

extern Actor *func_020604f8(void *);
extern void func_ov003_02219668(Blk *, int);
extern void func_0203f7d0(Vec *, Vec *);
extern void func_ov003_0222aa50(Actor *, Vec *, Vec *);
extern void func_ov003_0222a8a8(int);
extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_0221474c *, int);
extern void func_0200d4e8(UnkStruct_0221474c *, int, int, int);
extern int func_02073908(void *, int);
extern void func_0209a110(u16 *);
extern void func_02060460(void *);
extern void func_020109fc(UnkStruct_0221474c *, int, int, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_0206f6f8(int, Actor *);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void func_020604fc(void *, int);
extern int func_0200f290(UnkStruct_0221474c *, int);
extern void func_0200f268(UnkStruct_0221474c *, int);
extern void func_0203ee08(UnkStruct_0221474c *, void *);
extern void func_0203e19c(void);
extern u16 func_0206f6a4(void);
extern void func_ov003_0220d498(UnkStruct_0221474c *, const void *, int, int, int);
extern int func_02043554(int, u16);
extern void func_ov003_0222aaa0(Vec *, int);
extern void func_ov003_02214c00(void *, int);
extern void func_02060448(void *);
extern int func_ov003_02214bfc(void *);

void func_ov003_0221474c(UnkStruct_0221474c *self)
{
    Msg m;
    Vec c;
    Blk blk;
    Vec v48;
    Vec v54;
    Vec v60;
    Vec v6c;
    Vec v78;
    Vec v84;
    Vec v90;
    Actor *act;
    int v;
    int a2;
    u8 *st;
    void *sub;
    unsigned int ok;
    u16 hi, lo;
    void *bp;

    act = func_020604f8(self->unk_5C8);
    if (self->unk_704 == 0x5a) {
        v = self->unk_2D8 >> 12;
        if ((u16) v < 6) {
            if (act != 0) {
                a2 = (data_ov003_0223c026[act->unk_1FF * 0x14] << 12) / 0x64;
                v = (s16) (a2 - a2 * (u16) v / 6);
            } else {
                v = (s16) (0x1000 - 0x2ab * (u16) v);
            }
        } else {
            v = 0;
        }
    } else {
        v = 0;
    }
    c.x = v;
    c.y = v;
    c.z = v;
    blk = self->unk_698;
    func_ov003_02219668(&blk, 0);
    v48.x = blk.pos.x;
    v48.y = blk.pos.y;
    v48.z = blk.pos.z;
    m.a = 0xfff1;
    if (act != 0) {
        func_0203f7d0(&v48, &v48);
        v54.x = v48.x;
        v54.y = v48.y;
        v54.z = v48.z;
        v60.x = c.x;
        v60.y = c.y;
        v60.z = c.z;
        func_ov003_0222aa50(act, &v54, &v60);
        m.a = (u16) (act->unk_7E + 0x12e8);
        if (v == 0) {
            func_ov003_0222a8a8(self->unk_800);
        }
    }
    st = self->unk_7D4;
    sub = self->unk_8F0;
    switch (st[0]) {
        case 0:
            if (func_02056f94(self->unk_2D0) == 0) {
                break;
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 6, 1, -1);
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                m.d = m.a;
                func_0209a110(&m.d);
            }
            func_02060460(self->unk_5C8);
            break;
        case 1:
            if (self->unk_704 == 0x5a) {
                if (func_02056f94(self->unk_2D0) == 0) {
                    break;
                }
                func_020109fc(self, 0x6c, 6, 6);
                func_0205eae0(self->unk_5A0, 0x13, 6, 0);
            }
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                if (self->unk_81C == 5) {
                    if (func_0206f6f8(m.a, act) == 0) {
                        break;
                    }
                    self->unk_81C = 6;
                    break;
                }
                if (self->unk_81C == 6) {
                    if (func_0206fbc0() == 0) {
                        break;
                    }
                    self->unk_81C = 0xf;
                    if (func_0206fc6c() != 0) {
                        func_020604fc(self->unk_5C8, 0);
                        if (func_0200f290(self, 0x11) != 0) {
                            func_0200f268(self, 0x11);
                            bp = (char *) self;
                            if (self != 0) {
                                bp = (char *) bp + 0xec;
                            }
                            func_0203ee08(self, bp);
                        }
                        func_0203e19c();
                        m.b = func_0206f6a4();
                        self->unk_7FC = func_02008258(self, self->unk_7F0);
                        ok = 0;
                        hi = *(volatile u16 *) &m.b;
                        lo = *(volatile u16 *) &m.b;
                        if (lo >= 0x12e8 && hi <= 0x131f) {
                            ok = 1;
                        }
                        if (ok != 0) {
                            func_ov003_0220d498(self, &data_ov003_02238104, 0, 6, -1);
                            break;
                        }
                        func_0200d4e8(self, 6, 1, -1);
                        st[0] = 2;
                        break;
                    }
                } else if (self->unk_81C < 0xf) {
                    break;
                }
                ok = 0;
                hi = *(volatile u16 *) &m.a;
                lo = *(volatile u16 *) &m.a;
                if (lo >= 0x1320 && hi <= 0x1322) {
                    ok = 1;
                }
                if (ok != 0) {
                    st[0] = 3;
                    if (self->unk_810 == -1) {
                        self->unk_810 = func_02043554(self->unk_800, m.a);
                        if (self->unk_810 != -1) {
                            st[0] = 2;
                        }
                    }
                } else {
                    if (act != 0) {
                        func_ov003_0222aaa0(&c, act->unk_7E);
                        v6c.x = v48.x;
                        v6c.y = v48.y;
                        v6c.z = v48.z;
                        v78.x = c.x;
                        v78.y = c.y;
                        v78.z = c.z;
                        func_ov003_0222aa50(act, &v6c, &v78);
                    }
                    func_ov003_0220d498(self, &data_ov003_02238108, 0, 6, -1);
                    func_ov003_02214c00(sub, 2);
                }
                func_02060448(self->unk_5C8);
                if (func_0200f290(self, 0x11) != 0) {
                    func_0200f268(self, 0x11);
                    bp = (char *) self;
                    if (self != 0) {
                        bp = (char *) bp + 0xec;
                    }
                    func_0203ee08(self, bp);
                }
                func_0203e19c();
                break;
            }
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            if (func_ov003_02214bfc(sub) == 2) {
                if (act != 0) {
                    func_ov003_0222aaa0(&c, act->unk_7E);
                    v84.x = v48.x;
                    v84.y = v48.y;
                    v84.z = v48.z;
                    v90.x = c.x;
                    v90.y = c.y;
                    v90.z = c.z;
                    func_ov003_0222aa50(act, &v84, &v90);
                }
                func_02060448(self->unk_5C8);
                st[0] = 2;
                func_020109fc(self, 0, 6, 6);
            }
            break;
        case 2:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 6, 1, -1);
            break;
        case 3:
            if (self->unk_810 == -1) {
                self->unk_810 = func_02043554(self->unk_800, m.a);
                if (self->unk_810 != -1) {
                    st[0] = 2;
                }
            }
            break;
    }
}
