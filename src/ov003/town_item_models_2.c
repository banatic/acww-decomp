/* town_item_models_2: 17 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02225714 @ 0x02225714, 0x54 bytes, Thumb
 * func_ov003_02225694 @ 0x02225694, 0x80 bytes, Thumb
 * func_ov003_02225608 @ 0x02225608, 0x8c bytes, Thumb
 * func_ov003_02225598 @ 0x02225598, 0x70 bytes, Thumb
 * func_ov003_02225538 @ 0x02225538, 0x60 bytes, Thumb
 * func_ov003_02225474 @ 0x02225474, 0xc4 bytes, Thumb
 * func_ov003_02225404 @ 0x02225404, 0x70 bytes, Thumb
 * func_ov003_022253a8 @ 0x022253a8, 0x5c bytes, Thumb
 * func_ov003_0222535c @ 0x0222535c, 0x4a bytes, Thumb
 * func_ov003_022252fc @ 0x022252fc, 0x60 bytes, Thumb
 * func_ov003_022252a0 @ 0x022252a0, 0x5c bytes, Thumb
 * func_ov003_02225240 @ 0x02225240, 0x60 bytes, Thumb
 * func_ov003_022251e8 @ 0x022251e8, 0x58 bytes, Thumb
 * func_ov003_022251a4 @ 0x022251a4, 0x44 bytes, Thumb
 * func_ov003_022249cc @ 0x022249cc, 0x7d8 bytes, Thumb
 * func_ov003_02224970 @ 0x02224970, 0x5c bytes, Thumb
 * func_ov003_022248e4 @ 0x022248e4, 0x8c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} UnkStruct_02225714;

typedef struct {
    int w[12];
} UnkStruct_02225694;

typedef struct {
    int w[12];
} UnkStruct_02225608;

typedef struct {
    int w[12];
} UnkStruct_02225598;

typedef struct {
    int w[12];
} Big;

typedef struct {
    int w[12];
} UnkStruct_02225404;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    Big unk_64;
} UnkStruct_022251a4;

typedef struct {
    int m[12];
} Mtx;

typedef struct {
    int px;
    int pz;
    Vec3 unk_08;
    Vec3 unk_14;
    Vec3 unk_20;
    Vec3 unk_2C;
    Vec3 unk_38;
    Mtx m;
    Vec3 unk_74;
    Vec3 unk_80;
} St;

extern char *func_ov003_02225768(void *a, void *b, void *c, int d, Vec3 *v, UnkStruct_02225714 m);
extern int func_0204b7a0(void *b);
extern void func_020ad238(Vec3 *v, u8 k);
extern int func_02049ec4(void *b);
extern int func_02049d78(void *b);
void func_020ad228(void *c);
void func_02055e90(UnkStruct_022251a4 *o, int k);
int func_02065604(void);
void func_02107524(int a, u16 b);
extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern Mtx data_021fbe48;
extern void func_0204f7e0(Vec3 *a, Vec3 *b);
extern void func_0204f818(int *px, int *pz, Vec3 *v);
extern int func_0203f8d0(Vec3 *a, Vec3 *b);
extern void func_020e96c8(Mtx *m, int x, int y, int z);
extern void func_020e9774(Mtx *m, int a);
extern u16 *func_0204f5a8(void *p1, Vec3 *v, int layer);
extern int func_0204ba94(u16 *t);
extern int func_0203adc4(Vec3 *v, int a, int b);
extern int func_01ffcbd8(void *p1, int x, int z);
extern int func_0204c63c(u16 *t);
extern void *data_021c80bc;
void func_ov003_022214b4(void *p);
void func_ov003_0222399c(void *p);
extern int data_ov003_0223cfe4[];
extern void *data_ov003_0223cf74;
extern void *data_ov003_0223cf78;
extern int data_ov003_0223cf70;
extern int func_020552b0(void *p);
extern void func_ov003_02223928(void *p);
extern void func_ov003_02221488(int *p);
extern void func_02045d44(void);
extern void func_020e9fd4(void *h);

void func_ov003_022251a4(void *self, UnkStruct_022251a4 *o, Big s);

void func_ov003_02225714(void *a, void *b, void *c, int d, Vec3 *v, UnkStruct_02225714 m)
{
    Vec3 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    func_ov003_02225768(a, b, c, d, &t, m);
    func_020ad238(v, (u8) func_0204b7a0(b));
}

char *func_ov003_02225694(char *self, u16 *b, int c, int d, UnkStruct_02225694 m)
{
    char *p;
    u16 v = *b;
    if (v == 0x25) {
        p = self + 0x480 + ((c ^ d) & 1) * 0x3a8;
    } else if (v == 0xc7) {
        p = self + 0x14f4;
    } else {
        p = self + 0xf78;
    }
    func_ov003_022251a4((void *) self, (UnkStruct_022251a4 *) p, *(Big *) &m);
    return p;
}

char *func_ov003_02225608(char *self, u16 *b, UnkStruct_02225608 m)
{
    char *p;
    int c;
    u16 v;
    int k;
    c = 0;
    v = *b;
    if (v >= 0x2b && v <= 0x2e) {
        c = 1;
    }
    if (c) {
        k = v - 0x2b;
    } else if (v >= 0xff && v <= 0x102) {
        k = v - 0xff;
    } else if (v >= 0x62 && v <= 0x65) {
        k = v - 0x5e;
    } else {
        k = v - 0xc8;
    }
    p = *(char **) (self + k * 4 + 0x4978);
    func_ov003_022251a4((void *) self, (UnkStruct_022251a4 *) p, *(Big *) &m);
    return p;
}

char *func_ov003_02225598(char *a, void *b, UnkStruct_02225598 m)
{
    int i;
    int j;
    char *p;
    i = func_02049ec4(b);
    j = func_02049d78(b);
    p = a + 0x1590 + i * 0x618 + j * 0x9c;
    func_ov003_022251a4((void *) a, (UnkStruct_022251a4 *) p, *(Big *) &m);
    return p;
}

void *func_ov003_02225538(char *self, void *a, Big s)
{
    void *o = self + 0x1590 + 0x618 * func_02049ec4(a);
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) o, s);
    return o;
}

void *func_ov003_02225474(char *self, u16 *key, Big b)
{
    void *p;

    switch (*key) {
        case 0x1a:
            p = self + 0x2df0;
            break;
        case 0x1b:
            p = self + 0x2f28;
            break;
        case 0x1c:
            break;
        case 0x1d:
            p = *(void **) (self + 0x3060);
            break;
        case 0x1e:
            p = *(void **) (self + 0x3064);
            break;
        case 0x88:
        case 0xa4:
            p = self + 0x2e8c;
            break;
        case 0x89:
            p = self + 0x2fc4;
            break;
    }
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) p, b);
    return p;
}

char *func_ov003_02225404(char *a, u16 *b, UnkStruct_02225404 m)
{
    char *p;
    int k;
    int c;
    u16 v;
    c = 0;
    v = *b;
    if (v >= 0x1f && v <= 0x20) {
        c = 1;
    }
    if (c) {
        k = 4;
    } else {
        k = v - 0x21;
    }
    p = a + 0x43e8 + k * 0x9c;
    func_ov003_022251a4((void *) a, (UnkStruct_022251a4 *) p, *(Big *) &m);
    return p;
}

void *func_ov003_022253a8(char *self, u16 *k, Big s)
{
    void *o = *(void **) (self + ((*k - 0xe3) % 5) * 4 + 0x46f4);
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) o, s);
    return o;
}

void func_ov003_0222535c(void *a, void *b, void *c, Big s)
{
    func_ov003_022253a8((char *) a, (u16 *) b, s);
    func_020ad228(c);
}

void *func_ov003_022252fc(char *self, u16 *k, Big s)
{
    int i = 0;
    void *o;
    if (*k == 0xfd) {
        i = 1;
    }
    o = self + 0x4708 + 0x9c * i;
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) o, s);
    return o;
}

void func_ov003_022252a0(char *self, u16 *k, Big s)
{
    int i = 0;
    if (*k == 0xfe) {
        i = 1;
    }
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) (self + 0x4840 + 0x9c * i), s);
}

void *func_ov003_02225240(char *self, u16 *k, Big s)
{
    int i = 0;
    void *o;
    if (*k == 0xe2) {
        i = 1;
    }
    o = self + 0x49a8 + 0x9c * i;
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) o, s);
    return o;
}

void *func_ov003_022251e8(char *self, u16 *k, Big s)
{
    void *o = self + 0x3068 + 0x9c * (*k - 0xa7);
    func_ov003_022251a4(self, (UnkStruct_022251a4 *) o, s);
    return o;
}

void func_ov003_022251a4(void *self, UnkStruct_022251a4 *o, Big s)
{
    volatile u16 a, b;
    if (o == 0) {
        return;
    }
    o->unk_64 = s;
    func_02055e90(o, 0);
    a = (u16) func_02065604();
    b = a;
    func_02107524(o->unk_5C, b);
}

void func_ov003_022249cc(char *p0, void *p1)
{
    int n;
    u16 *tile;
    int fj;
    int d;
    int fh;
    int ii;
    int jj;
    int cnt;
    int sel;
    u16 id;
    int fg;
    int ff;
    int r;
    int fe;
    St s;
    int fd;
    int fc;
    int fb;
    int fa;
    int q1;
    int q2;
    int q3;
    int q4;
    unsigned int kk;

    if (data_021c67a4 == 0) {
        return;
    }
    s.unk_20.x = data_021c67d0.x;
    s.unk_20.y = data_021c67d0.y;
    s.unk_20.z = data_021c67d0.z;
    func_0204f7e0(&s.unk_38, &s.unk_20);
    func_0204f818(&s.px, &s.pz, &s.unk_38);
    s.unk_2C.x = s.unk_38.x + 0x12000;
    cnt = 0;
    s.unk_2C.y = 0;
    s.unk_2C.z = s.unk_38.z + 0x8000;
    for (jj = 4; jj >= -14; s.unk_2C.z = s.unk_2C.z - 0x2000, jj--) {
        func_0204f7e0(&s.unk_08, &s.unk_2C);
        r = func_0203f8d0(&s.unk_14, &s.unk_08);
        func_020e96c8(&data_021fbe48, s.unk_14.x, s.unk_14.y, s.unk_14.z);
        func_020e9774(&data_021fbe48, r);
        s.m = data_021fbe48;
        d = s.unk_08.z - s.unk_38.z;
        for (ii = 9; ii >= -9; s.m.m[9] = s.m.m[9] - 0x2000, s.unk_08.x = s.unk_08.x - 0x2000, ii--) {
            tile = func_0204f5a8(p1, &s.unk_08, 0);
            if (tile == 0) {
                continue;
            }
            fj = 1;
            fh = 1;
            fg = 1;
            ff = 1;
            fe = 1;
            fd = 1;
            fc = 1;
            fb = 1;
            fa = 0;
            id = *tile;
            if (id >= 0x26 && id <= 0x2a) {
                fa = 1;
            }
            if (fa == 0) {
                if (!(id >= 0x5d && id <= 0x61)) {
                    fb = 0;
                }
            }
            if (fb == 0) {
                if (!(id >= 0x2f && id <= 0x56)) {
                    fc = 0;
                }
            }
            if (fc == 0) {
                if (!(id >= 0x57 && id <= 0x5b)) {
                    fd = 0;
                }
            }
            if (fd == 0) {
                if (!(id >= 0x66 && id <= 0x68)) {
                    fe = 0;
                }
            }
            if (fe == 0) {
                if (id != 0x69) {
                    ff = 0;
                }
            }
            if (ff == 0) {
                if (!(id >= 0x6a && id <= 0x6c)) {
                    fg = 0;
                }
            }
            if (fg == 0) {
                if (id != 0x6d) {
                    fh = 0;
                }
            }
            if (fh == 0) {
                if (!(id >= 0xc8 && id <= 0xcf)) {
                    fj = 0;
                }
            }
            if (fj != 0) {
                if (func_0204ba94(tile) == 0) {
                    if (func_0203adc4(&s.unk_08, 0x2000, 0x2000) != 0) {
                        continue;
                    }
                }
            }
            id = *tile;
            sel = (id & 0xf000) >> 12;
            switch (sel) {
                case 0:
                    do {
                        if ((id >= 0x26 && id <= 0x2a) || (id >= 0x5d && id <= 0x61) || (id >= 0x2f && id <= 0x56) ||
                            (id >= 0x57 && id <= 0x5b) || (id >= 0x66 && id <= 0x68) || id == 0x69 ||
                            (id >= 0x6a && id <= 0x6c) || id == 0x6d || (id >= 0xc8 && id <= 0xcf) ||
                            (id >= 0xe3 && id <= 0xe7) || (id >= 0xe8 && id <= 0xfb)) {
                            if (d > -0x1c200 && d < 0x8200) {
                                goto L_ok;
                            }
                        }
                        if (d > -0x14a00 && d < 0x6400) {
                            goto L_ok;
                        }
                        goto L_chk;
                    L_ok:
                        if ((id >= 0x26 && id <= 0x2a) || (id >= 0x5d && id <= 0x61) || (id >= 0x2f && id <= 0x56) ||
                            (id >= 0x57 && id <= 0x5b) || (id >= 0x66 && id <= 0x68) || id == 0x69 ||
                            (id >= 0x6a && id <= 0x6c) || id == 0x6d || (id >= 0xc8 && id <= 0xcf)) {
                            s.unk_74.x = s.unk_08.x;
                            s.unk_74.y = s.unk_08.y;
                            s.unk_74.z = s.unk_08.z;
                            func_ov003_02225714(p0, (void *) tile, (void *) (s.px + ii), s.pz + jj, &s.unk_74,
                                                *(UnkStruct_02225714 *) &s.m);
                            break;
                        }
                        if ((id >= 0x21 && id <= 0x24) || (id >= 0x1f && id <= 0x20)) {
                            func_ov003_02225404((char *) p0, tile, *(UnkStruct_02225404 *) &s.m);
                            break;
                        }
                        q1 = 0;
                        if (id <= 0x19) {
                            q1 = 1;
                        }
                        if (q1 == 0) {
                            if (id != 0x1c) {
                                goto L_a;
                            }
                        }
                        func_ov003_02225598((char *) p0, (void *) tile, *(UnkStruct_02225598 *) &s.m);
                        break;
                    L_a:
                        if ((id >= 0x6e && id <= 0x73) || (id >= 0x74 && id <= 0x79) || (id >= 0x7a && id <= 0x7f) ||
                            (id >= 0x80 && id <= 0x87) || (id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) ||
                            (id >= 0x96 && id <= 0x9b) || (id >= 0x9c && id <= 0xa3) || id == 0xa5) {
                            func_ov003_02225538((char *) p0, (void *) tile, *(Big *) &s.m);
                            break;
                        }
                        if ((id >= 0xe3 && id <= 0xe7) || (id >= 0xe8 && id <= 0xfb)) {
                            s.unk_80.x = s.unk_08.x;
                            s.unk_80.y = s.unk_08.y;
                            s.unk_80.z = s.unk_08.z;
                            func_ov003_0222535c(p0, (void *) tile, (void *) (&s.unk_80), *(Big *) &s.m);
                            break;
                        }
                        if (id == 0xa6 || id == 0xfe) {
                            func_ov003_022252a0((char *) p0, tile, *(Big *) &s.m);
                            break;
                        }
                        if (id >= 0xfc && id <= 0xfd) {
                            func_ov003_022252fc((char *) p0, tile, *(Big *) &s.m);
                            break;
                        }
                        if (id == 0x25 || id == 0x5c || id == 0xc7) {
                            func_ov003_02225694((char *) p0, tile, s.px + ii, s.pz + jj, *(UnkStruct_02225694 *) &s.m);
                            break;
                        }
                        if ((id >= 0x2b && id <= 0x2e) || (id >= 0xff && id <= 0x102) || (id >= 0x62 && id <= 0x65) ||
                            (id >= 0xd0 && id <= 0xd3)) {
                            func_ov003_02225608((char *) p0, tile, *(UnkStruct_02225608 *) &s.m);
                            break;
                        }
                        q2 = 0;
                        kk = (u16) (id + 0xffe6);
                        if (kk <= 4) {
                            if ((1 << kk) & 0x1b) {
                                q2 = 1;
                            }
                        }
                        if (q2 == 0) {
                            if (id != 0x88) {
                                if (id != 0x89) {
                                    if (id != 0xa4) {
                                        goto L_b;
                                    }
                                }
                            }
                        }
                        func_ov003_02225474((char *) p0, tile, *(Big *) &s.m);
                        break;
                    L_b:
                        if (func_01ffcbd8(p1, s.px + ii, s.pz + jj) != 0) {
                            func_ov003_022252a0((char *) p0, tile, *(Big *) &s.m);
                            break;
                        }
                        q3 = 0;
                        id = *tile;
                        if (id >= 0xa7 && id <= 0xc6) {
                            q3 = 1;
                        }
                        if (q3 != 0) {
                            func_ov003_022251e8((char *) p0, tile, *(Big *) &s.m);
                            break;
                        }
                        if ((id >= 0xd4 && id <= 0xda) || (id >= 0xdb && id <= 0xe1) || id == 0xe2) {
                            func_ov003_02225240((char *) p0, tile, *(Big *) &s.m);
                            break;
                        }
                    } while (0);
                    cnt++;
                    goto L_chk;
                case 1:
                case 3:
                case 4:
                    if (func_01ffcbd8(p1, s.px + ii, s.pz + jj) != 0) {
                        func_ov003_022252a0((char *) p0, tile, *(Big *) &s.m);
                        break;
                    }
                    n = func_0204c63c(tile);
                    func_ov003_022251a4(p0, (UnkStruct_022251a4 *) (*(void **) (p0 + n * 4 + 0x50)), *(Big *) &s.m);
                    break;
                default:
                    goto L_chk;
            }
            cnt++;
        L_chk:
            if (cnt >= 0xfc) {
                return;
            }
        }
    }
}

int func_ov003_02224970(char *self)
{
    void *a = data_021c80bc;
    void *b = data_021c67a4;
    if (a != 0 && b != 0) {
        *(int *) (self + 0x6a6c) = (*(int *) (self + 0x6a6c) + 1) % 0x3c;
        func_ov003_022249cc((char *) self, a);
        func_ov003_022214b4(((int *) data_ov003_0223cfe4));
        func_ov003_0222399c(self + 0x4b20);
    }
    return 1;
}

int func_ov003_022248e4(char *self)
{
    func_020552b0(self + 0x4ae0);
    func_020552b0(self + 0x4af0);
    func_020552b0(self + 0x4b00);
    func_020552b0(self + 0x4b10);
    func_ov003_02223928(self + 0x4b20);
    func_ov003_02221488(data_ov003_0223cfe4);
    func_02045d44();
    if (data_ov003_0223cf74) {
        func_020e9fd4(data_ov003_0223cf74);
        data_ov003_0223cf74 = 0;
    }
    if (data_ov003_0223cf78) {
        func_020e9fd4(data_ov003_0223cf78);
        data_ov003_0223cf78 = 0;
    }
    data_ov003_0223cf70 = 0;
    return 1;
}
