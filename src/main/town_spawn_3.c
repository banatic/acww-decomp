/* town_spawn_3: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02048698 @ 0x02048698, 0x40 bytes, Thumb
 * func_0204864c @ 0x0204864c, 0x4c bytes, Thumb
 * func_020485d4 @ 0x020485d4, 0x78 bytes, Thumb
 * func_02048594 @ 0x02048594, 0x40 bytes, Thumb
 * func_0204855c @ 0x0204855c, 0x38 bytes, Thumb
 * func_0204851c @ 0x0204851c, 0x40 bytes, Thumb
 * func_020484c8 @ 0x020484c8, 0x54 bytes, Thumb
 */

typedef struct {
    int x;
    int y;
} Result;

typedef struct {
    char pad_00[0x20];
    int unk_20;
} Cell;

typedef struct {
    int pad_00[13];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
} UnkStruct_020484c8;

extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048f54(void *, int, int);
extern int func_020644cc(int);
extern int func_02048f6c(void *, int, int);
extern unsigned char data_021c79e4[8];
extern Cell data_021c7a08[][4];
extern int func_02048ee4(void *, int, int);
extern unsigned char data_021c79c4[];
extern int func_0204f5e0(int, int, int, int, int, int);
extern void func_0204a200(int, int, int, int, int, int, int, int);

void func_02048698(int a0, int a1, int a2, int a3)
{
    int r = (int __arm) func_020644cc(a2);
    int s = (int __arm) func_020644cc(a3);
    func_02048cb8(a0, a1, r + 1, s + 1, 29, (((int (*)(int, int, int)) func_02048f54)), 0);
}

void func_0204864c(int p1, int p2, int p3, int p4)
{
    int a = func_020644cc(p3);
    int b = func_020644cc(p4);
    int c = func_020644cc(100);
    func_02048cb8(p1, p2, a + 1, b + 1, (c < 2) ? 0x20 : 0x1f, (((int (*)(int, int, int)) func_02048f6c)), 0);
}

void func_020485d4(Result *out, int unused, int w, int h)
{
    int k, i, j;
    int total = w * h - data_021c79e4[4];
    if (total > 0) {
        k = func_020644cc(total);
        for (j = 0; j < h; j++) {
            for (i = 0; i < w; i++) {
                Cell *c = (Cell *) ((char *) data_021c7a08 + i * 0x90 + j * 0x24);
                if (((c->unk_20 << 30) >> 31) == 0) {
                    if (k == 0) {
                        out->x = i;
                        out->y = j;
                        return;
                    }
                    k--;
                }
            }
        }
    }
    out->x = -1;
    out->y = -1;
}

void func_02048594(int p0, int p1, int argument2, int argument3)
{
    struct {
        int x;
        int y;
    } s;
    int a, b;

    func_020485d4((Result *) (&s), p0, (int) argument2, (int) argument3);
    a = s.x;
    b = s.y;
    if (a == -1) {
        return;
    }
    func_02048cb8(p0, p1, a + 1, b + 1, 26, (((int (*)(int, int, int)) func_02048ee4)), 0);
}

void func_0204855c(int r0, int r1, int r2, int r3)
{
    int *ptr;
    int a, b, c, d;

    ptr = (int *) data_021c79c4;
    if (*ptr == 4) {
        if (func_020644cc(100) < 50) {
            a = r0;
            b = r1;
            c = r2;
            d = r3;
            func_02048594(a, b, c, d);
        }
    }
}

int func_0204851c(int a, int b, int c, int d)
{
    int t1 = func_020644cc(c);
    int t2 = func_020644cc(d);
    return func_02048cb8(a, b, t1 + 1, t2 + 1, 0x1b, (((int (*)(int, int, int)) func_02048ee4)), 0);
}

void func_020484c8(int a0, int a1)
{
    int v3c = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_3C;
    int v40 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_40;
    int v34 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_34;
    int v38 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_38;
    if (func_0204f5e0(a1, v34 + 1, v38 + 1, v3c, v40, 0) != 0) {
        v3c = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_3C;
        v40 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_40;
        v34 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_34;
        v38 = *(volatile int *) &(*(UnkStruct_020484c8 *) data_021c79c4).unk_38;
        func_0204a200(a0, a1, v34 + 1, v38 + 1, v3c, v40, 0x89, 0);
    }
}
