/* func_ov003_022249cc @ 0x022249cc, 0x7d8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
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
extern void func_ov003_02225714(void *g, u16 *t, int a, int b, Vec3 *v, Mtx m);
extern char *func_ov003_02225404(void *g, u16 *t, Mtx m);
extern char *func_ov003_02225598(void *g, u16 *t, Mtx m);
extern void *func_ov003_02225538(void *g, u16 *t, Mtx m);
extern void func_ov003_0222535c(void *g, u16 *t, Vec3 *v, Mtx m);
extern void func_ov003_022252a0(void *g, u16 *t, Mtx m);
extern void *func_ov003_022252fc(void *g, u16 *t, Mtx m);
extern char *func_ov003_02225694(void *g, u16 *t, int a, int b, Mtx m);
extern char *func_ov003_02225608(void *g, u16 *t, Mtx m);
extern void *func_ov003_02225474(void *g, u16 *t, Mtx m);
extern void *func_ov003_022251e8(void *g, u16 *t, Mtx m);
extern void *func_ov003_02225240(void *g, u16 *t, Mtx m);
extern void func_ov003_022251a4(void *g, void *p, Mtx m);

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
                            func_ov003_02225714(p0, tile, s.px + ii, s.pz + jj, &s.unk_74, s.m);
                            break;
                        }
                        if ((id >= 0x21 && id <= 0x24) || (id >= 0x1f && id <= 0x20)) {
                            func_ov003_02225404(p0, tile, s.m);
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
                        func_ov003_02225598(p0, tile, s.m);
                        break;
                    L_a:
                        if ((id >= 0x6e && id <= 0x73) || (id >= 0x74 && id <= 0x79) || (id >= 0x7a && id <= 0x7f) ||
                            (id >= 0x80 && id <= 0x87) || (id >= 0x8a && id <= 0x8f) || (id >= 0x90 && id <= 0x95) ||
                            (id >= 0x96 && id <= 0x9b) || (id >= 0x9c && id <= 0xa3) || id == 0xa5) {
                            func_ov003_02225538(p0, tile, s.m);
                            break;
                        }
                        if ((id >= 0xe3 && id <= 0xe7) || (id >= 0xe8 && id <= 0xfb)) {
                            s.unk_80.x = s.unk_08.x;
                            s.unk_80.y = s.unk_08.y;
                            s.unk_80.z = s.unk_08.z;
                            func_ov003_0222535c(p0, tile, &s.unk_80, s.m);
                            break;
                        }
                        if (id == 0xa6 || id == 0xfe) {
                            func_ov003_022252a0(p0, tile, s.m);
                            break;
                        }
                        if (id >= 0xfc && id <= 0xfd) {
                            func_ov003_022252fc(p0, tile, s.m);
                            break;
                        }
                        if (id == 0x25 || id == 0x5c || id == 0xc7) {
                            func_ov003_02225694(p0, tile, s.px + ii, s.pz + jj, s.m);
                            break;
                        }
                        if ((id >= 0x2b && id <= 0x2e) || (id >= 0xff && id <= 0x102) || (id >= 0x62 && id <= 0x65) ||
                            (id >= 0xd0 && id <= 0xd3)) {
                            func_ov003_02225608(p0, tile, s.m);
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
                        func_ov003_02225474(p0, tile, s.m);
                        break;
                    L_b:
                        if (func_01ffcbd8(p1, s.px + ii, s.pz + jj) != 0) {
                            func_ov003_022252a0(p0, tile, s.m);
                            break;
                        }
                        q3 = 0;
                        id = *tile;
                        if (id >= 0xa7 && id <= 0xc6) {
                            q3 = 1;
                        }
                        if (q3 != 0) {
                            func_ov003_022251e8(p0, tile, s.m);
                            break;
                        }
                        if ((id >= 0xd4 && id <= 0xda) || (id >= 0xdb && id <= 0xe1) || id == 0xe2) {
                            func_ov003_02225240(p0, tile, s.m);
                            break;
                        }
                    } while (0);
                    cnt++;
                    goto L_chk;
                case 1:
                case 3:
                case 4:
                    if (func_01ffcbd8(p1, s.px + ii, s.pz + jj) != 0) {
                        func_ov003_022252a0(p0, tile, s.m);
                        break;
                    }
                    n = func_0204c63c(tile);
                    func_ov003_022251a4(p0, *(void **) (p0 + n * 4 + 0x50), s.m);
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
