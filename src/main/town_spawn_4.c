/* town_spawn_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02048a54 @ 0x02048a54, 0x2c bytes, Thumb
 * func_020489c4 @ 0x020489c4, 0x90 bytes, Thumb
 * func_020488e4 @ 0x020488e4, 0xe0 bytes, Thumb
 * func_0204886c @ 0x0204886c, 0x78 bytes, Thumb
 * func_02048824 @ 0x02048824, 0x46 bytes, Thumb
 * func_020487d8 @ 0x020487d8, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
} Pt;

extern int func_020644cc(int);
extern int func_02048cb8(void *, void *, int, int, unsigned short, int (*predicate)(int, int, int), int);
extern int func_02048ee4(void *, int, int);
extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern int func_02048ec8(int a, int b, int c);
extern int func_02048d2c(int a, int b, int c, Pt *d, int e, int f);
extern u8 data_020cab28[];
extern u16 data_020cabc4[];
extern unsigned char data_021e5a2c[];
extern void *func_0207b3dc(void *);
extern void *func_0207cec0(void *, int);
extern int func_020405a8(void *, void *);
extern void *func_0207f1c8(void *);
extern void *func_0209b5ec(void *);
extern int func_0209c330(void *);
extern void *func_020800d0(void *);
extern int func_02081f80(void *);
extern void MI_CpuCopy8(int p1, char *p2, int p3);
extern int func_0203fc78(int p1, char *p2, int p3);

int func_02048a54(void *unused, Pair *a, Pair *arr, int count)
{
    int result = 0;
    while (count != 0) {
        if (a->unk_00 == arr->unk_00 && a->unk_04 == arr->unk_04) {
            result = 1;
            break;
        }
        arr++;
        count--;
    }
    return result;
}

void func_020489c4(void *obj, void *p1)
{
    Point pt;
    Point arr[3];
    int n, i, v;

    pt.x = 0;
    pt.y = 0;
    arr[0].x = 0;
    arr[0].y = 0;
    arr[1].x = 0;
    arr[1].y = 0;
    arr[2].x = 0;
    arr[2].y = 0;
    n = 0;
    for (i = 0; i < 3; i++) {
        do {
            v = func_020644cc(0x10);
            pt.x = v % 4;
            pt.y = v / 4;
        } while (func_02048a54(obj, (Pair *) (&pt), (Pair *) arr, n) != 0);
        func_02048cb8(obj, p1, pt.x + 1, pt.y + 1, (unsigned short) (func_020644cc(4) + 0x21),
                      (((int (*)(int, int, int)) func_02048ee4)), 0);
        arr[n].x = pt.x;
        arr[n].y = pt.y;
        n++;
    }
}

void func_020488e4(int p0, int p1, Pt *base, int cnt)
{
    Pt list[17];
    int n;
    int idx;
    int x;
    int y;
    int x4;
    int y4;
    int count;
    int i;
    u8 d;
    u16 *r;
    Pt *e;

    e = list;
    do {
        e->x = 0;
        e->y = 0;
        e++;
    } while (e != list + 17);
    n = 0;
    for (idx = 0; idx < 0x11; idx++) {
        d = data_020cab28[idx];
        x = base->x + ((d >> 4) - 8);
        y = base->y + ((d & 0xf) - 8);
        x4 = x >> 4;
        y4 = y >> 4;
        r = func_0204f5e0(p1, x4, y4, x - (x4 << 4), y - (y4 << 4), 0);
        if (r != 0 && *r == 0xfff1) {
            if (func_02048ec8(p1, x, y) != 0) {
                list[n].x = x;
                list[n].y = y;
                n++;
            }
        }
    }
    count = cnt << 1;
    while (n > 0) {
        i = func_02048d2c(p0, p1, n, list, data_020cabc4[func_020644cc(0xc)], 0);
        count = count - 1;
        if (count <= 0) {
            break;
        }
        while (i < 0x10) {
            list[i].x = list[i + 1].x;
            list[i].y = list[i + 1].y;
            i++;
        }
        n = n - 1;
    }
}

void func_0204886c(void *a0, int a1, int a2, int a3)
{
    void *saved;
    void *p;
    int i;
    int tmp[2];
    int b0;
    int b1;

    saved = func_0207b3dc(data_021e5a2c);

    for (i = 0; i < 8; i++) {
        p = func_0207cec0(data_021e5a2c, i);

        if (func_020405a8(p, saved) == 0) {
            continue;
        }

        if (a2 == 0) {
            if (func_0209c330((func_0209b5ec((void *) func_0207f1c8(p)))) != 5) {
                continue;
            }
        }

        p = func_020800d0(p);

        if (func_02081f80(p) == 0) {
            continue;
        }

        b1 = ((unsigned char *) p)[1];
        b0 = ((unsigned char *) p)[0];
        tmp[0] = b0;
        tmp[1] = b1;

        func_020488e4((int) a0, a1, (Pt *) tmp, a3);
    }
}

void func_02048824(int a, int b, int c, int d)
{
    char buf[8];
    int cond;

    MI_CpuCopy8(c, buf, 8);
    cond = (func_0203fc78(14, buf, 0) == 2) ? 0 : 1;
    if (cond != 0) {
        if (d > 7) {
            d = 7;
        }
        func_0204886c((void *) a, b, 0, d);
    }
}

void func_020487d8(int p0, int p1, int p2, int p3)
{
    int v1 = func_020644cc(p2);
    int v2 = func_020644cc(p3);
    int idx = func_020644cc(0xc);

    func_02048cb8((void *) p0, (void *) p1, v1 + 1, v2 + 1, ((unsigned short *) data_020cabc4)[idx],
                  (((int (*)(int, int, int))(int (*)(void *, int, int)) func_02048ec8)), 0);
}
