/* town_growth: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02048bc0 @ 0x02048bc0, 0xf8 bytes, Thumb
 * func_02048b54 @ 0x02048b54, 0x6c bytes, Thumb
 * func_02048b0c @ 0x02048b0c, 0x48 bytes, Thumb
 * func_02048ab0 @ 0x02048ab0, 0x5c bytes, Thumb
 * func_02048a80 @ 0x02048a80, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

struct UnkStruct_02048b54 {
    char pad_00[0x20];
    unsigned int : 3;
    signed int flag : 1;
};

struct UnkStruct_02048b54_2 {
    struct UnkStruct_02048b54 arr[4];
};

typedef struct {
    unsigned char pad_00[0x20];
    int f20 : 5;
    int bit5 : 1;
    int pad2 : 26;
} UnkStruct_02048ab0;

extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_0204a25c(int a, int b, int c, int d, int e);
extern int func_020644cc(int);
extern struct UnkStruct_02048b54_2 data_021c7a08[];
extern unsigned char data_021c79e4[];

int func_02048bc0(int p0, int p1, int p2, int p3, int p4)
{
    int result;
    int x;
    int y;
    Pt list[256];
    u16 kinds[256];
    Pt *e;
    int inner;
    int count;
    int outer;
    int k;
    u16 v;
    u16 *p;

    e = list;
    do {
        e->x = 0;
        e->y = 0;
        e++;
    } while (e != list + 256);
    count = 0;
    result = 0;
    for (outer = 0; outer < 0x10; outer++) {
        for (inner = 0; inner < 0x10; inner++) {
            p = func_0204f5e0(p1, p2, p3, inner, outer, 0);
            if (p == 0) {
                continue;
            }
            func_0204f800(&x, &y, p2, p3, inner, outer);
            v = *p;
            switch (v) {
                case 0x2a:
                    list[count].x = x;
                    list[count].y = y;
                    kinds[count] = 0x66;
                    count++;
                    break;
                case 0x61:
                    list[count].x = x;
                    list[count].y = y;
                    kinds[count] = 0x6a;
                    count++;
                    break;
            }
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        func_0204a25c(p1, list[k].x, list[k].y, (u16) (p4 + kinds[k]), 0);
        result = 1;
    }
    return result;
}

void func_02048b54(int p0, int p1, int p2, int p3)
{
    int i;
    int start = 0;
    int flag = 0;
    for (i = 0; i < p2; i++) {
        int found = 1;
        int j = start;
        while (j < p3) {
            if (data_021c7a08[i].arr[j].flag) {
                found = flag;
                break;
            }
            j++;
        }

        if (found) {
            int sum = func_020644cc(p3) + 1;
            func_02048bc0(p0, p1, i + 1, sum, 1);
        }
    }
}

void func_02048b0c(int a, int b, int c, int d)
{
    int i;
    int t1;
    int t2;

    i = 2 - data_021c79e4[0xc];
    while (i != 0) {
        t1 = func_020644cc(c);
        t2 = func_020644cc(d);
        func_02048bc0(a, b, t1 + 1, t2 + 1, 0);
        i--;
    }
}

void func_02048ab0(void *a, void *b, int c, int d)
{
    int j;
    int i;
    int j0 = 0;
    for (i = 0; i < d; i++) {
        for (j = j0; j < c; j++) {
            UnkStruct_02048ab0 *e = (UnkStruct_02048ab0 *) (((unsigned char *) data_021c7a08) + j * 0x90 + i * 0x24);
            if (e->bit5 == 0) {
                func_02048bc0((int) a, (int) b, j + 1, i + 1, 2);
            }
        }
    }
}

void func_02048a80(int a, int b, int c, int d)
{
    func_02048b54(a, b, c, d);
    func_02048b0c(a, b, c, d);
    func_02048ab0((void *) a, (void *) b, c, d);
}
