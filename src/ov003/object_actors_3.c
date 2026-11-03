/* object_actors_3: 15 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022208b4 @ 0x022208b4, 0x18 bytes, Thumb
 * func_ov003_02220890 @ 0x02220890, 0x24 bytes, Thumb
 * func_ov003_02220870 @ 0x02220870, 0x20 bytes, Thumb
 * func_ov003_02220848 @ 0x02220848, 0x28 bytes, Thumb
 * func_ov003_022207e0 @ 0x022207e0, 0x68 bytes, Thumb
 * func_ov003_022207dc @ 0x022207dc, 0x4 bytes, Thumb
 * func_ov003_022207d8 @ 0x022207d8, 0x4 bytes, Thumb
 * func_ov003_0222079c @ 0x0222079c, 0x3c bytes, Thumb
 * func_ov003_02220798 @ 0x02220798, 0x2 bytes, Thumb
 * func_ov003_02220794 @ 0x02220794, 0x2 bytes, Thumb
 * func_ov003_02220520 @ 0x02220520, 0x274 bytes, Thumb
 * func_ov003_02220460 @ 0x02220460, 0xc0 bytes, Thumb
 * func_ov003_0222040c @ 0x0222040c, 0x52 bytes, Thumb
 * func_ov003_022203fc @ 0x022203fc, 0x10 bytes, Thumb
 * func_ov003_022203f4 @ 0x022203f4, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02220520 {
    char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02220520;

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern void func_ov003_02220138(void);
extern unsigned char data_020da13c[];
extern unsigned char data_ov003_02239b2c[];
extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *p);
extern void func_020b1e54(void);
extern void func_020b2980(void);
extern int func_020b3b38(int);
extern int func_ov003_0221fe34(int);
extern int func_ov003_0221ffec(int);
extern int func_ov003_0221fec0(int);
extern int func_0202f134(int, int, int, int);
extern int data_021f42f4;
extern void func_ov003_02220120(void);
extern int func_020b3b20(void *param);
extern void func_ov003_0221ffcc(void *ptr);
extern void func_ov003_0221feb8(void *ptr);
extern void func_ov003_0221fe30(void *ptr);
extern char data_ov003_0223cea0[];
extern char data_ov003_0223ce80[];
extern char data_ov003_0223ce58[];
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
extern int func_020b6660(void);
extern int func_02073dd4(void *p, int k);
extern void *func_0204e414(void);
extern int func_0204dfe0(void *a, void *b, int *qx, int *qy);
extern void func_0204f794(int *dst, void *x, void *y);
extern int func_020b2a60(void *obj);
extern int func_02003348(int a, unsigned short b, int *c, int d, int e);
extern int func_0204eb1c(void *a, unsigned short *b, void *c, void *d, int e);
extern void *func_020b3b50(int);
extern unsigned int func_020b3ed4(void *);
extern int func_020b3db8(void *, int *, int *, int *, unsigned int);
extern int func_02030920(int, int, unsigned char);
extern void func_0205ca64(unsigned int, int);
extern void func_0205ca48(void);

void *func_ov003_02220890(void *arg0);
void func_ov003_02220798(int a);
void func_ov003_02220794(int a);
int func_ov003_02220520(void *arg);
int func_ov003_02220460(void *a, unsigned short *b, void *c, void *d, unsigned char e);
int func_ov003_0222040c(int unused, int key, int baseX, int baseY);
void func_ov003_022203fc(int a);
void func_ov003_022203f4(void *param);

void func_ov003_022208b4(void)
{
    void *p;

    p = func_020edf70(0x50);
    if (p != 0) {
        func_ov003_02220890(p);
    }
}

void *func_ov003_02220890(void *arg0)
{
    func_020ee660(arg0);
    *(void **) arg0 = (void *) data_020da13c;
    *(void **) arg0 = (void *) data_ov003_02239b2c;
    func_ov003_02220138();
    return arg0;
}

void *func_ov003_02220870(void *ptr)
{
    *(void *volatile *) ptr = ((char *) data_ov003_02239b2c);
    *(void *volatile *) ptr = ((char *) data_020da13c);
    func_020ee62c(ptr);
    return ptr;
}

void *func_ov003_02220848(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) ((int *) data_ov003_02239b2c);
    *(volatile unsigned int *) p = (unsigned int) ((int *) data_020da13c);
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

int func_ov003_022207e0(int r0)
{
    int r4 = r0;
    func_020b1e54();
    func_ov003_02220138();
    func_020b2980();
    func_020b3b38(r4);
    func_ov003_022203fc(r4);
    func_ov003_0221fe34((int) ((int *) data_ov003_0223ce58));
    func_ov003_0221ffec((int) ((int *) data_ov003_0223cea0));
    func_ov003_0221fec0((int) ((int *) data_ov003_0223ce80));
    func_ov003_02220798(r4);
    func_ov003_02220794(r4);
    func_ov003_02220520((void *) r4);
    func_0202f134(0xf, data_021f42f4, 0, 0);
    return 1;
}

int func_ov003_022207dc(void)
{
    return 1;
}

int func_ov003_022207d8(void)
{
    return 1;
}

int func_ov003_0222079c(void *param)
{
    func_ov003_02220120();
    func_020b3b20(param);
    func_ov003_0221ffcc(data_ov003_0223cea0);
    func_ov003_0221feb8(data_ov003_0223ce80);
    func_ov003_0221fe30(data_ov003_0223ce58);
    func_ov003_022203f4(param);
    return 1;
}

void func_ov003_02220798(int a) {}

void func_ov003_02220794(int a) {}

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
                        if (func_ov003_02220460(arg, (unsigned short *) o, (void *) px, (void *) py, 1) != 0) {
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
                func_ov003_02220460(arg, (unsigned short *) (&ids[0]), (void *) qx, (void *) (qy + 1), 0);
            }
        }
    }
    return count;
}

int func_ov003_02220460(void *a, unsigned short *b, void *c, void *d, unsigned char e)
{
    int local[3];
    struct {
        unsigned int pad[3];
    } obj;
    unsigned short val;
    unsigned int flag;
    unsigned int index;
    void *table;

    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    func_0204f794(local, c, d);

    flag = 0;
    val = *b;
    if (val >= 0x5000 && val <= 0x5021) {
        flag = 1;
    }

    if (flag) {
        index = val & 0xfff;
    } else {
        index = -1;
    }

    if (index < 0x22) {
        table = ((unsigned char *) data_020d1f24) + index * 10;
    } else {
        table = ((unsigned char *) data_020d1f24);
    }

    func_020b2a68(&obj, (char *) table);

    if (func_02003348(func_020b2a60(&obj), *b, local, 0, 0) != 0) {
        if (e != 0) {
            func_0204eb1c((*(void * *) &data_021c80bc), b, c, d, 0);
            func_ov003_0222040c((int) a, (int) b, (int) c, (int) d);
        }
        func_020b2a64(&obj);
        return 1;
    } else {
        func_020b2a64(&obj);
        return 0;
    }
}

int func_ov003_0222040c(int unused, int key, int baseX, int baseY)
{
    void *A;
    unsigned int n, i;

    A = func_020b3b50(key);
    if (A != 0) {
        int v1, v2, v3;
        n = func_020b3ed4(A);
        for (i = 0; i < n; i++) {
            if (func_020b3db8(A, &v3, &v1, &v2, i)) {
                func_02030920(baseX + v1, baseY + v2, (unsigned char) v3);
            }
        }
    }
    return 1;
}

void func_ov003_022203fc(int a)
{
    func_0205ca64(0x1f000, 0);
}

void func_ov003_022203f4(void *param)
{
    func_0205ca48();
}
