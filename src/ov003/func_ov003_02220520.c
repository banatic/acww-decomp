/* func_ov003_02220520 @ 0x02220520, 0x274 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02220520 {
    char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02220520;

extern u16 data_ov003_0223ce54;
extern UnkStruct_02220520 *data_021c80bc;
extern char data_020d1f24[];
extern void *data_020ccf94;

extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern int func_02037e84(char *e);
extern int func_02037e44(char *e, u16 *p, int a, int b, int c);
extern u16 *func_02037e0c(char *e, int i, int j, int k);
extern void func_0204f800(int *px, int *py, int x, int y, int i, int j);
extern void func_020b2a68(void *o, char *p);
extern int func_020b2a58(void *o);
extern void func_020b2a64(void *o);
extern int func_0204bcdc(u16 *o);
extern int func_0204bc64(u16 *o);
extern int func_020b6598(void);
extern int func_ov003_02220460(void *arg, u16 *o, int px, int py, int f);
extern int func_020b6660(void);
extern int func_02073dd4(void *p, int k);
extern void *func_0204e414(void);
extern int func_0204dfe0(void *a, void *b, int *qx, int *qy);

int func_ov003_02220520(void *arg)
{
    int want;
    unsigned int w, h;
    unsigned int i, j;
    int count;
    int mode;
    char *e;
    int flagA;
    unsigned int x, y;
    u16 ids[3];
    int px, py;
    int qx, qy;
    char obj[12];
    char misc[0x10];
    UnkStruct_02220520 *g;
    u16 *o;
    int ok;
    unsigned int n;
    char *p;
    int t1;
    int r;
    void *a2;

    data_ov003_0223ce54 = 0;
    g = data_021c80bc;
    w = g->unk_04;
    h = g->unk_08;
    flagA = 1;
    if (func_020b22b8() == 0 && func_020b22dc() == 0) {
        flagA = 0;
    }
    count = 0;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (x < g->unk_04 && y < g->unk_08 && g->unk_00 != 0) {
                e = g->unk_00 + 0x28 * (x + y * g->unk_04);
            } else {
                e = 0;
            }
            t1 = func_02037e84(e);
            switch (t1) {
                case 0x1a:
                case 0x1b:
                case 0x1c:
                    ids[1] = 0x500b;
                    func_02037e44(e, &ids[1], 7, 0, 0);
                    break;
            }
            for (j = 0; j < 0x10; j++) {
                for (i = 0; i < 0x10; i++) {
                    o = func_02037e0c(e, i, j, 0);
                    if (o == 0) {
                        continue;
                    }
                    ok = 0;
                    if (*o >= 0x5000 && *o <= 0x5021) {
                        ok = 1;
                    }
                    if (ok == 0) {
                        continue;
                    }
                    func_0204f800(&px, &py, x, y, i, j);
                    ok = 0;
                    if (*o >= 0x5000 && *o <= 0x5021) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        n = *o & 0xfff;
                    } else {
                        n = -1;
                    }
                    if (n < 0x22) {
                        p = data_020d1f24 + 0xa * n;
                    } else {
                        p = data_020d1f24;
                    }
                    func_020b2a68(obj, p);
                    mode = func_020b2a58(obj);
                    if (flagA == 0 || mode != 2) {
                        want = 1;
                    } else {
                        want = 0;
                    }
                    if (func_0204bcdc(o) != 0) {
                        ids[2] = 0x501e;
                        t1 = func_0204bc64(o);
                        r = (t1 == func_0204bc64(&ids[2])) ? 1 : 0;
                    } else {
                        if (*o == 0x501e) {
                            r = 1;
                        } else {
                            r = 0;
                        }
                    }
                    if (r != 0 && func_020b6598() == 0) {
                        want = 0;
                    }
                    if (want != 0) {
                        if (func_ov003_02220460(arg, o, px, py, 1) != 0) {
                            if (mode == 1) {
                                data_ov003_0223ce54 = data_ov003_0223ce54 + 1;
                            }
                            count++;
                        }
                    }
                    func_020b2a64(obj);
                }
            }
        }
    }
    if (func_020b6660() != 0 && func_02073dd4(data_020ccf94, *(int *) ((char *) data_020ccf94 + 0x64)) == 0) {
        a2 = func_0204e414();
        if (func_020b22b8() != 0 || func_020b22dc() != 0) {
            if (func_0204dfe0(a2, misc, &qx, &qy) != 0) {
                ids[0] = 0x501b;
                func_ov003_02220460(arg, &ids[0], qx, qy + 1, 0);
            }
        }
    }
    return count;
}
